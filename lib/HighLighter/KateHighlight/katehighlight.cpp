/* This file is part of the KDE libraries
   Copyright (C) 2007 Mirko Stocker <me@misto.ch>
   Copyright (C) 2007 Matthew Woehlke <mw_triad@users.sourceforge.net>
   Copyright (C) 2003, 2004 Anders Lund <anders@alweb.dk>
   Copyright (C) 2003 Hamish Rodda <rodda@kde.org>
   Copyright (C) 2001,2002 Joseph Wenninger <jowenn@kde.org>
   Copyright (C) 2001 Christoph Cullmann <cullmann@kde.org>
   Copyright (C) 1999 Jochen Wilhelmy <digisnap@cs.tu-berlin.de>

   This library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Library General Public
   License version 2 as published by the Free Software Foundation.

   This library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Library General Public License for more details.

   You should have received a copy of the GNU Library General Public License
   along with this library; see the file COPYING.LIB.  If not, write to
   the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.
*/

//BEGIN INCLUDES
#include "katehighlight.h"

#include "katehighlighthelpers.h"
#include "katetextline.h"
#include "katesyntaxdocument.h"
#include "kateextendedattribute.h"
#include <utils/Configuration.h>
#include <utils/StringUtil.h>

#include <QSet>
#include <QStringList>
#include <QTextStream>
#include <QVarLengthArray>
#include <QAction>
#include <QApplication>
#include <QDebug>

//END

//BEGIN defines
// x is a QString. if x is "true" or "1" this expression returns "true"
#define IS_TRUE(x) x.toLower() == QLatin1String("true") || x.toInt() == 1
//END defines

//BEGIN STATICS
namespace {
inline const QString stdDeliminator()
{
    return QStringLiteral(" \t.():!+,-<=>%&*/;?[]^{|}~\\");
}
}
//END

//BEGIN KateHighlighting
KateHighlighting::KateHighlighting(const KateSyntaxModeListItem *def) : refCount(0)
{
    errorsAndWarnings = QString();
    building = false;
    noHl = false;
    m_foldingIndentationSensitive = false;
    folding = false;

    if (def == 0) {
        noHl = true;
        iName = QString::fromLatin1("None"); // not translated internal name (for config and more)
        iNameTranslated = "None"; // user visible name
        iSection = QString();
    } else {
        iName = def->name;
        iNameTranslated = def->nameTranslated;
        iSection = def->section;
        iHidden = def->hidden;
        identifier = def->identifier;
        iVersion = def->version;
        iStyle = def->style;
        iAuthor = def->author;
        iLicense = def->license;
        m_extension = def->extension;
    }

    deliminator = stdDeliminator();
}

KateHighlighting::~KateHighlighting()
{
    // cleanup ;)
    cleanup();

    qDeleteAll(m_additionalData);
}

void KateHighlighting::cleanup()
{
    qDeleteAll(m_contexts);
    m_contexts.clear();

    qDeleteAll(m_hlItemCleanupList);
    m_hlItemCleanupList.clear();

    m_attributeArrays.clear();

    internalIDList.clear();
}

KateHlContext *KateHighlighting::generateContextStack(Kate::TextLineData::ContextStack &contextStack,
        KateHlContextModification modification,
        int &indexLastContextPreviousLine)
{
    while (true) {
        switch (modification.type) {
        /**
         * stay, do nothing, just return the last context
         * in the stack or 0
         */
        case KateHlContextModification::doNothing:
            return contextNum(contextStack.isEmpty() ? 0 : contextStack.last());

        /**
         * just add a new context to the stack
         * and return this one
         */
        case KateHlContextModification::doPush:
            contextStack.append(modification.newContext);
            return contextNum(modification.newContext);

        /**
         * pop some contexts + add a new one afterwards, immediate....
         */
        case KateHlContextModification::doPopsAndPush:
            // resize stack
            contextStack.resize((modification.pops >= contextStack.size()) ? 0 : (contextStack.size() - modification.pops));

            // push imediate the new context....
            // don't handle the previous line stuff at all....
            // ### TODO ### think about this
            contextStack.append(modification.newContext);
            return contextNum(modification.newContext);

        /**
         * do only pops...
         */
        default: {
            // resize stack
            contextStack.resize((modification.pops >= contextStack.size()) ? 0 : (contextStack.size() - modification.pops));

            // handling of context of previous line....
            if (indexLastContextPreviousLine >= (contextStack.size() - 1)) {
                // set new index, if stack is empty, this is -1, done for eternity...
                indexLastContextPreviousLine = contextStack.size() - 1;

                // stack already empty, nothing to do...
                if (contextStack.isEmpty()) {
                    return contextNum(0);
                }

                KateHlContext *c = contextNum(contextStack.last());

                // this must be a valid context, or our context stack is borked....
                Q_ASSERT(c);

                // handle line end context as new modificationContext
                modification = c->lineEndContext;
                continue;
            }

            return contextNum(contextStack.isEmpty() ? 0 : contextStack.last());
        }
        }
    }

    // should never be reached
    Q_ASSERT(false);

    return contextNum(0);
}

/**
 * Creates a new dynamic context or reuse an old one if it has already been created.
 */
int KateHighlighting::makeDynamicContext(KateHlContext *model, const QStringList *args)
{
    QPair<KateHlContext *, QString> key(model, args->front());
    short value;

    if (dynamicCtxs.contains(key)) {
        value = dynamicCtxs[key];
    } else {
#ifdef HIGHLIGHTING_DEBUG
        qCDebug(LOG_KTE) << "new stuff: " << startctx;
#endif

        KateHlContext *newctx = model->clone(args);

        m_contexts.push_back(newctx);

        value = startctx++;
        dynamicCtxs[key] = value;
        KateHlManager::self()->incDynamicCtxs();
    }

    // qCDebug(LOG_KTE) << "Dynamic context: using context #" << value << " (for model " << model << " with args " << *args << ")";

    return value;
}

/**
 * Drop all dynamic contexts. Shall be called with extreme care, and shall be immediately
 * followed by a full HL invalidation.
 */
void KateHighlighting::dropDynamicContexts()
{
    if (refCount == 0) { // unused highlighting - nothing to drop
        return;
    }

    if (noHl) { // "normal texts" highlighting - no context list
        return;
    }

    qDeleteAll(m_contexts.begin() + base_startctx, m_contexts.end()); // delete dynamic contexts (after base_startctx)
    m_contexts.resize(base_startctx);

    dynamicCtxs.clear();
    startctx = base_startctx;
}

void KateHighlighting::doHighlight(const Kate::TextLineData *_prevLine,
                                   Kate::TextLineData *textLine,
                                   const Kate::TextLineData *nextLine,
                                   bool &ctxChanged,
                                   int tabWidth,
                                   QVector<ContextChange>* contextChanges)
{
    if (!textLine) {
        return;
    }

    // in all cases, remove old hl, or we will grow to infinite ;)
    textLine->clearAttributes();

    // reset folding start
    textLine->clearMarkedAsFoldingStart();

    // no hl set, nothing to do more than the above cleaning ;)
    if (noHl) {
        return;
    }

    const bool firstLine = (_prevLine == 0);
    const Kate::TextLine dummy = Kate::TextLine(new Kate::TextLineData());
    const Kate::TextLineData *prevLine = firstLine ?
                                (const Kate::TextLineData *)dummy.data() : _prevLine;

    int previousLine = -1;
    KateHlContext *context;

    // duplicate the ctx stack, only once !
    Kate::TextLineData::ContextStack ctx(prevLine->contextStack());

    if (ctx.isEmpty()) {
        // If the stack is empty, we assume to be in Context 0 (Normal)
        if (firstLine) {
            context = contextNum(0);
        } else {
            context = generateContextStack(ctx, contextNum(0)->lineEndContext, previousLine); //get stack ID to use
        }
    } else {
        //qCDebug(LOG_KTE) << "\t\tctxNum = " << ctxNum << " contextList[ctxNum] = " << contextList[ctxNum]; // ellis

        //if (lineContinue)   qCDebug(LOG_KTE)<<QString("The old context should be %1").arg((int)ctxNum);
        context = contextNum(ctx.last());

        //qCDebug(LOG_KTE)<<"test1-2-1-text2";

        previousLine = ctx.size() - 1; //position of the last context ID of th previous line within the stack

        // hl continue set or not ???
        if (prevLine->hlLineContinue()) {
            previousLine--;
        } else {
            context = generateContextStack(ctx, context->lineEndContext, previousLine);    //get stack ID to use
        }

        //qCDebug(LOG_KTE)<<"test1-2-1-text4";

        //if (lineContinue)   qCDebug(LOG_KTE)<<QString("The new context is %1").arg((int)ctxNum);
    }

    // text, for programming convenience :)
    QChar lastChar = QLatin1Char(' ');
    const QString &text = textLine->string();
    const int len = textLine->length();

    // calc at which char the first char occurs, set it to length of line if never
    const int firstChar = textLine->firstChar();
    const int startNonSpace = (firstChar == -1) ? len : firstChar;

    // last found item
    KateHlItem *item = 0;

    // loop over the line, offset gives current offset
    int offset = 0;

    KateHighlighting::HighlightPropertyBag *additionalData = m_additionalData[context->hlId];
    KateHlContext *oldContext = context;

    // optimization: list of highlighting items that need their cache reset
    static QVarLengthArray<KateHlItem *> cachingItems;

    // catch empty lines
    if (len == 0) {
        // regenerate context stack if needed
        if (context->emptyLineContext) {
            context = generateContextStack(ctx, context->emptyLineContextModification, previousLine);
        }
    } else {
        /**
         * check if the folding begin/ends are balanced!
         * constructed on demand!
         */
        QHash<short, int> *foldingStartToCount = 0;

        /**
         * loop over line content!
         */
        QChar lastDelimChar = 0;
        int lastOffset = offset;
        int infiniteLoopDetectionCounter = 0;
        KateHlContext* previous = context;
        while (offset < len) {
            // If requested (happens from completion), return where context changes occur.
            if (contextChanges && ( offset == 0 || context != previous )) {
                previous = context;
                const ContextChange change = {context, offset};
                contextChanges->append(change);
            }

            /**
             * infinite loop check
             */
            if (lastOffset < offset) {
                /**
                 * we did advance a bit, reset counter
                 */
                lastOffset = offset;
                infiniteLoopDetectionCounter = 0;
            } else {
                /**
                 * we did not advance, inc counter
                 */
                ++infiniteLoopDetectionCounter;

                /**
                 * not more than four times as many rounds as contexts known
                 * break out of this loop and issue message
                 */
                if (infiniteLoopDetectionCounter > (4 * m_contexts.size())) {
                    qDebug() << "potential infinite loop found during highlighting, hl: " << iName;
                    break;
                }
            }

            bool anItemMatched = false;
            bool customStartEnableDetermined = false;

            foreach (item, context->items) {
                // does we only match if we are firstNonSpace?
                if (item->firstNonSpace && (offset > startNonSpace)) {
                    continue;
                }

                // have we a column specified? if yes, only match at this column
                if ((item->column != -1) && (item->column != offset)) {
                    continue;
                }

                if (!item->alwaysStartEnable) {
                    if (item->customStartEnable) {
                        if (oldContext != context) {
                            oldContext = context;
                            additionalData = m_additionalData[oldContext->hlId];
                        }
                        if (customStartEnableDetermined || additionalData->deliminator.contains(lastChar)) {
                            customStartEnableDetermined = true;
                        } else {
                            continue;
                        }
                    } else {
                        if (lastDelimChar == lastChar) {
                        } else if (stdDeliminator().contains(lastChar)) {
                            lastDelimChar = lastChar;
                        } else {
                            continue;
                        }
                    }
                }

                int offset2 = item->checkHgl(text, offset, len - offset);
                if (item->haveCache && !item->cachingHandled) {
                    cachingItems.append(item);
                    item->cachingHandled = true;
                }

                if (offset2 <= offset) {
                    continue;
                }

                // dominik: on lookAhead, do not preocess any data by fixing offset2
                if (item->lookAhead) {
                    offset2 = offset;
                } else {
                    // make sure the rule does not violate the text line length
                    if (offset2 > len) {
                        offset2 = len;
                    }
                }

                // BUG 144599: Ignore a context change that would push the same context
                // without eating anything... this would be an infinite loop!
                if (item->lookAhead && (item->ctx.pops < 2 && item->ctx.newContext == (ctx.isEmpty() ? 0 : ctx.last()))) {
                    continue;
                }

                // regenerate context stack if needed
                context = generateContextStack(ctx, item->ctx, previousLine);

                // dynamic context: substitute the model with an 'instance'
                if (context->dynamic) {
                    // try to retrieve captures from regexp
                    QStringList captures;
                    item->capturedTexts(captures);
                    if (!captures.empty()) {
                        // Replace the top of the stack and the current context
                        int newctx = makeDynamicContext(context, &captures);
                        if (ctx.size() > 0) {
                            ctx[ctx.size() - 1] = newctx;
                        }

                        context = contextNum(newctx);
                    }
                }

                // handle folding end or begin
                if (item->region || item->region2) {
                    /**
                     * for each end region, decrement counter for that type, erase if count reaches 0!
                     */
                    if (item->region2 && foldingStartToCount) {
                        QHash<short, int>::iterator end = foldingStartToCount->find(-item->region2);
                        if (end != foldingStartToCount->end()) {
                            if (end.value() > 1) {
                                --(end.value());
                            } else {
                                foldingStartToCount->erase(end);
                            }
                        }
                    }

                    /**
                     * increment counter for each begin region!
                     */
                    if (item->region) {
                        // construct on demand!
                        if (!foldingStartToCount) {
                            foldingStartToCount = new QHash<short, int> ();
                        }

                        ++(*foldingStartToCount)[item->region];
                    }
                }

                // even set attributes or end of region! ;)
                int attribute = item->onlyConsume ? context->attr : item->attr;
                if ((attribute > 0 && !item->lookAhead) || item->region2) {
                    textLine->addAttribute(Kate::TextLineData::Attribute(offset, offset2 - offset, attribute, item->region2));
                }

                // create 0 length attribute for begin of region, if any!
                if (item->region) {
                    textLine->addAttribute(Kate::TextLineData::Attribute(offset2, 0, attribute, item->region));
                }

                // only process, if lookAhead is false
                if (!item->lookAhead) {
                    offset = offset2;
                    lastChar = text[offset - 1];
                }

                anItemMatched = true;
                break;
            }

            // something matched, continue loop
            if (anItemMatched) {
                continue;
            }

            item = 0;

            // nothing found: set attribute of one char
            // anders: unless this context does not want that!
            if (context->fallthrough) {
                // set context to context->ftctx.
                context = generateContextStack(ctx, context->ftctx, previousLine); //regenerate context stack

                //qCDebug(LOG_KTE)<<"context num after fallthrough at col "<<z<<": "<<ctxNum;
                // the next is necessary, as otherwise keyword (or anything using the std delimitor check)
                // immediately after fallthrough fails. Is it bad?
                // jowenn, can you come up with a nicer way to do this?
                /*  if (offset)
                    lastChar = text[offset - 1];
                  else
                    lastChar = '\\';*/
                continue;
            } else {
                // set attribute if any
                if (context->attr > 0) {
                    textLine->addAttribute(Kate::TextLineData::Attribute(offset, 1, context->attr, 0));
                }

                lastChar = text[offset];
                offset++;
            }
        }

        /**
         * check if folding is not balanced and we have more starts then ends
         * then this line is a possible folding start!
         */
        if (foldingStartToCount) {
            /**
             * possible folding start, if imbalanced, aka hash not empty!
             */
            if (!foldingStartToCount->isEmpty()) {
                textLine->markAsFoldingStartAttribute();
            }

            /**
             * kill hash
             */
            delete foldingStartToCount;
            foldingStartToCount = 0;
        }
    }

    /**
     * has the context stack changed?
     */
    if ((ctxChanged = (ctx != textLine->contextStack()))) {
        /**
         * try to share the simple stack that contains only 0
         */
        static const Kate::TextLineData::ContextStack onlyDefaulContext(1, 0);
        if (ctx == onlyDefaulContext) {
            textLine->setContextStack(onlyDefaulContext);
        }

        /**
         * next try: try to share data with last line
         */
        else if (ctx == prevLine->contextStack()) {
            textLine->setContextStack(prevLine->contextStack());
        }

        /**
         * ok, really use newly constructed stack!
         */
        else {
            textLine->setContextStack(ctx);
        }
    }

    // write hl continue flag
    textLine->setHlLineContinue(item && item->lineContinue());

    // check for indentation based folding
    if (m_foldingIndentationSensitive && (tabWidth > 0) && !textLine->markedAsFoldingStartAttribute()) {
        bool skipIndentationBasedFolding = false;
        for (int i = ctx.size() - 1; i >= 0; --i) {
            if (contextNum(ctx[i])->noIndentationBasedFolding) {
                skipIndentationBasedFolding = true;
                break;
            }
        }

        /**
         * compute if we increase indentation in next line
         */
        if (!skipIndentationBasedFolding && !isEmptyLine(textLine) && !isEmptyLine(nextLine)
                && (textLine->indentDepth(tabWidth) < nextLine->indentDepth(tabWidth))) {
            textLine->markAsFoldingStartIndentation();
        }
    }

    // invalidate caches
    for (int i = 0; i < cachingItems.size(); ++i) {
        cachingItems[i]->cachingHandled = false;
        cachingItems[i]->haveCache = false;
    }
    cachingItems.clear();
}

void KateHighlighting::getKateExtendedAttributeList(const QString &schema, QList<KTextEditor::Attribute::Ptr> &list)
{

    list.clear();
    createKateExtendedAttribute(list);

    foreach (KTextEditor::Attribute::Ptr p, list) {
        Q_ASSERT(p);

//        QStringList s = config.readEntry(p->name(), QStringList());
            QStringList s;
//    qCDebug(LOG_KTE)<<p->name<<s.count();
        if (s.count() > 0) {

            while (s.count() < 10) {
                s << QString();
            }
            QString name = p->name();
            bool spellCheck = !p->skipSpellChecking();
            p->clear();
            p->setName(name);
            p->setSkipSpellChecking(!spellCheck);

            QString tmp = s[0]; if (!tmp.isEmpty()) {
                p->setDefaultStyle(static_cast<KTextEditor::DefaultStyle> (tmp.toInt()));
            }

            QRgb col;

            tmp = s[1]; if (!tmp.isEmpty()) {
                col = tmp.toUInt(0, 16); p->setForeground(QColor(col));
            }

            tmp = s[2]; if (!tmp.isEmpty()) {
                col = tmp.toUInt(0, 16); p->setSelectedForeground(QColor(col));
            }

            tmp = s[3]; if (!tmp.isEmpty()) {
                p->setFontBold(tmp != QLatin1String("0"));
            }

            tmp = s[4]; if (!tmp.isEmpty()) {
                p->setFontItalic(tmp != QLatin1String("0"));
            }

            tmp = s[5]; if (!tmp.isEmpty()) {
                p->setFontStrikeOut(tmp != QLatin1String("0"));
            }

            tmp = s[6]; if (!tmp.isEmpty()) {
                p->setFontUnderline(tmp != QLatin1String("0"));
            }

            tmp = s[7]; if (!tmp.isEmpty()) {
                col = tmp.toUInt(0, 16); p->setBackground(QColor(col));
            }

            tmp = s[8]; if (!tmp.isEmpty()) {
                col = tmp.toUInt(0, 16); p->setSelectedBackground(QColor(col));
            }

            tmp = s[9]; if (!tmp.isEmpty() && tmp != QLatin1String("---")) {
                p->setFontFamily(tmp);
            }

        }
    }
}

void KateHighlighting::getKateExtendedAttributeListCopy(const QString &schema, QList< KTextEditor::Attribute::Ptr > &list)
{
    QList<KTextEditor::Attribute::Ptr> attributes;
    getKateExtendedAttributeList(schema, attributes);

    list.clear();

    foreach (const KTextEditor::Attribute::Ptr &attribute, attributes) {
        list.append(KTextEditor::Attribute::Ptr(new KTextEditor::Attribute(*attribute.data())));
    }
}

void KateHighlighting::setKateExtendedAttributeList(const QString &schema, QList<KTextEditor::Attribute::Ptr> &list,
                                                    HighLightConfig* config, bool writeDefaultsToo)
{

    QStringList settings;

    KateAttributeList defList;
    KateHlManager::self()->getDefaults(schema, defList, config);

    foreach (const KTextEditor::Attribute::Ptr &p, list) {
        Q_ASSERT(p);

        settings.clear();
        KTextEditor::DefaultStyle defStyle = p->defaultStyle();
        KTextEditor::Attribute::Ptr a(defList[defStyle]);
        settings << QString::number(p->defaultStyle(), 10);
        settings << (p->hasProperty(QTextFormat::ForegroundBrush) ? QString::number(p->foreground().color().rgb(), 16) : (writeDefaultsToo ? QString::number(a->foreground().color().rgb(), 16) : QString()));
        settings << (p->hasProperty(SelectedForeground) ? QString::number(p->selectedForeground().color().rgb(), 16) : (writeDefaultsToo ? QString::number(a->selectedForeground().color().rgb(), 16) : QString()));
        settings << (p->hasProperty(QTextFormat::FontWeight) ? (p->fontBold() ? QLatin1String("1") : QLatin1String("0")) : (writeDefaultsToo ? (a->fontBold() ? QLatin1String("1") : QLatin1String("0")) : QString()));
        settings << (p->hasProperty(QTextFormat::FontItalic) ? (p->fontItalic() ? QLatin1String("1") : QLatin1String("0")) : (writeDefaultsToo ? (a->fontItalic() ? QLatin1String("1") : QLatin1String("0")) : QString()));
        settings << (p->hasProperty(QTextFormat::FontStrikeOut) ? (p->fontStrikeOut() ? QLatin1String("1") : QLatin1String("0")) : (writeDefaultsToo ? (a->fontStrikeOut() ? QLatin1String("1") : QLatin1String("0")) : QString()));
        settings << (p->hasProperty(QTextFormat::FontUnderline) ? (p->fontUnderline() ? QLatin1String("1") : QLatin1String("0")) : (writeDefaultsToo ? (a->fontUnderline() ? QLatin1String("1") : QLatin1String("0")) : QString()));
        settings << (p->hasProperty(QTextFormat::BackgroundBrush) ? QString::number(p->background().color().rgb(), 16) : ((writeDefaultsToo && a->hasProperty(QTextFormat::BackgroundBrush)) ? QString::number(a->background().color().rgb(), 16) : QString()));
        settings << (p->hasProperty(SelectedBackground) ? QString::number(p->selectedBackground().color().rgb(), 16) : ((writeDefaultsToo && a->hasProperty(SelectedBackground)) ? QString::number(a->selectedBackground().color().rgb(), 16) : QString()));
        settings << (p->hasProperty(QTextFormat::FontFamily) ? (p->fontFamily()) : (writeDefaultsToo ? a->fontFamily() : QString()));
        settings << QLatin1String("---");
//        config.writeEntry(p->name(), settings);
    }
}

const QHash<QString, QChar> &KateHighlighting::getCharacterEncodings(int attrib) const
{
    return m_additionalData[ hlKeyForAttrib(attrib) ]->characterEncodings;
}

const KatePrefixStore &KateHighlighting::getCharacterEncodingsPrefixStore(int attrib) const
{
    return m_additionalData[ hlKeyForAttrib(attrib) ]->characterEncodingsPrefixStore;
}

const QHash<QChar, QString> &KateHighlighting::getReverseCharacterEncodings(int attrib) const
{
    return m_additionalData[ hlKeyForAttrib(attrib) ]->reverseCharacterEncodings;
}

int KateHighlighting::getEncodedCharactersInsertionPolicy(int attrib) const
{
    return m_additionalData[ hlKeyForAttrib(attrib) ]->encodedCharactersInsertionPolicy;
}

void KateHighlighting::addCharacterEncoding(const QString &key, const QString &encoding, const QChar &c)
{
    m_additionalData[ key ]->characterEncodingsPrefixStore.addPrefix(encoding);
    m_additionalData[ key ]->characterEncodings[ encoding ] = c;
    m_additionalData[ key ]->reverseCharacterEncodings[ c ] = encoding;
}

/**
 * Increase the usage count, and trigger initialization if needed.
 */
void KateHighlighting::use()
{
    if (refCount == 0) {
        init();
    }

    refCount = 1;
}

/**
 * Reload the highlighting.
 */

void KateHighlighting::reload()
{
    // nop if not referenced
    if (refCount == 0) {
        return;
    }

    cleanup();
    init();
}

/**
 * Initialize a context for the first time.
 */

void KateHighlighting::init()
{
    // shall be only called if clean!
    Q_ASSERT(m_contexts.empty());

    // try to create contexts
    makeContextList();

    // fixup internal id list, if empty
    if (internalIDList.isEmpty()) {
        internalIDList.append(KTextEditor::Attribute::Ptr(new KTextEditor::Attribute(QString("Normal Text"), KTextEditor::dsNormal)));
    }

    // something went wrong or no hl, fill something in
    if (noHl) {
        iHidden = false;
        m_additionalData.insert(QString::fromLatin1("none"), new HighlightPropertyBag);
        m_additionalData[QLatin1String("none")]->deliminator = stdDeliminator();
        m_additionalData[QLatin1String("none")]->wordWrapDeliminator = stdDeliminator();
        m_hlIndex[0] = QLatin1String("none");
        m_ctxIndex[0] = QLatin1String("none");

        // create one dummy context!
        m_contexts.push_back(new KateHlContext(identifier, 0,
            KateHlContextModification(), false, KateHlContextModification(),
            false, false, false, KateHlContextModification()));
    }

    // clear domdocument cache
    KateHlManager::self()->syntax.clearCache();
}

/**
 * KateHighlighting - createKateExtendedAttribute
 * This function reads the itemData entries from the config file, which specifies the
 * default attribute styles for matched items/contexts.
 *
 * @param list A reference to the internal list containing the parsed default config
 */
void KateHighlighting::createKateExtendedAttribute(QList<KTextEditor::Attribute::Ptr> &list)
{
    // trigger hl load, if needed
    use();

    // return internal list, never empty!
    Q_ASSERT(!internalIDList.empty());
    list = internalIDList;
}

/**
 * Adds the styles of the currently parsed highlight to the itemdata list
 */
void KateHighlighting::addToKateExtendedAttributeList()
{
    //Tell the syntax document class which file we want to parse and which data group
    KateHlManager::self()->syntax.setIdentifier(buildIdentifier);
    KateSyntaxContextData *data = KateHlManager::self()->syntax.getGroupInfo(QLatin1String("highlighting"), QLatin1String("itemData"));

    // use global color instance, creation is expensive!
//    const KateDefaultColors &colors(KTextEditor::EditorPrivate::self()->defaultColors());
    QColor colors(Qt::red);
    //begin with the real parsing
    while (KateHlManager::self()->syntax.nextGroup(data)) {
        // read all attributes
        const QString color = KateHlManager::self()->syntax.groupData(data, QLatin1String("color"));
        const QString selColor = KateHlManager::self()->syntax.groupData(data, QLatin1String("selColor"));
        const QString bold = KateHlManager::self()->syntax.groupData(data, QLatin1String("bold"));
        const QString italic = KateHlManager::self()->syntax.groupData(data, QLatin1String("italic"));
        const QString underline = KateHlManager::self()->syntax.groupData(data, QLatin1String("underline"));
        const QString strikeOut = KateHlManager::self()->syntax.groupData(data, QLatin1String("strikeOut"));
        const QString bgColor = KateHlManager::self()->syntax.groupData(data, QLatin1String("backgroundColor"));
        const QString selBgColor = KateHlManager::self()->syntax.groupData(data, QLatin1String("selBackgroundColor"));
        const QString spellChecking = KateHlManager::self()->syntax.groupData(data, QLatin1String("spellChecking"));
        const QString fontFamily = KateHlManager::self()->syntax.groupData(data, QLatin1String("fontFamily"));

        const QString itemDataName = KateHlManager::self()->syntax.groupData(data, QLatin1String("name")).simplified();
        const QString defStyleName = KateHlManager::self()->syntax.groupData(data, QLatin1String("defStyleNum"));

        KTextEditor::Attribute::Ptr newData(new KTextEditor::Attribute(
                                               buildPrefix + itemDataName,
                                               static_cast<KTextEditor::DefaultStyle> (KateHlManager::defaultStyleNameToIndex(defStyleName))));

        /* here the custom style overrides are specified, if needed */
        if (!color.isEmpty()) {
            newData->setForeground(colors);
        }
        if (!selColor.isEmpty()) {
            newData->setSelectedForeground(colors);
        }
        if (!bold.isEmpty()) {
            newData->setFontBold(IS_TRUE(bold));
        }
        if (!italic.isEmpty()) {
            newData->setFontItalic(IS_TRUE(italic));
        }
        // new attributes for the new rendering view
        if (!underline.isEmpty()) {
            newData->setFontUnderline(IS_TRUE(underline));
        }
        if (!strikeOut.isEmpty()) {
            newData->setFontStrikeOut(IS_TRUE(strikeOut));
        }
        if (!bgColor.isEmpty()) {
            newData->setBackground(colors);
        }
        if (!selBgColor.isEmpty()) {
            newData->setSelectedBackground(colors);
        }
        // is spellchecking desired?
        if (!spellChecking.isEmpty()) {
            newData->setSkipSpellChecking(!(IS_TRUE(spellChecking)));
        }
        if (!fontFamily.isEmpty()) {
            newData->setFontFamily(fontFamily);
        }

        internalIDList.append(newData);
    }

    //clean up
    if (data) {
        KateHlManager::self()->syntax.freeGroupInfo(data);
    }
}

/**
 * KateHighlighting - lookupAttrName
 * This function is  a helper for makeContextList and createKateHlItem. It looks the given
 * attribute name in the itemData list up and returns its index
 *
 * @param name the attribute name to lookup
 * @param iDl the list containing all available attributes
 *
 * @return The index of the attribute, or 0 if the attribute isn't found
 */
int  KateHighlighting::lookupAttrName(const QString &name, QList<KTextEditor::Attribute::Ptr> &iDl)
{
    const QString needle = buildPrefix + name;
    for (int i = 0; i < iDl.count(); i++)
        if (iDl.at(i)->name() == needle) {
            return i;
        }

#ifdef HIGHLIGHTING_DEBUG
    qCDebug(LOG_KTE) << "Couldn't resolve itemDataName:" << name;
#endif

    return 0;
}

/**
 * KateHighlighting - createKateHlItem
 * This function is  a helper for makeContextList. It parses the xml file for
 * information.
 *
 * @param data Data about the item read from the xml file
 * @param iDl List of all available itemData entries.
 *            Needed for attribute name->index translation
 * @param RegionList list of code folding region names
 * @param ContextNameList list of context names
 *
 * @return A pointer to the newly created item object
 */
KateHlItem *KateHighlighting::createKateHlItem(KateSyntaxContextData *data,
        QList<KTextEditor::Attribute::Ptr> &iDl,
        QStringList *RegionList,
        QStringList *ContextNameList)
{
    // No highlighting -> exit
    if (noHl) {
        return 0;
    }

    // get the (tagname) itemd type
    const QString dataname = KateHlManager::self()->syntax.groupItemData(data, QString());

    // code folding region handling:
    const QString beginRegionStr = KateHlManager::self()->syntax.groupItemData(data, QLatin1String("beginRegion"));
    const QString endRegionStr = KateHlManager::self()->syntax.groupItemData(data, QLatin1String("endRegion"));

    signed char regionId = 0;
    signed char regionId2 = 0;

    if (!beginRegionStr.isEmpty()) {
        regionId = RegionList->indexOf(beginRegionStr);

        if (regionId == -1) { // if the region name doesn't already exist, add it to the list
            (*RegionList) << beginRegionStr;
            regionId = RegionList->indexOf(beginRegionStr);
        }

        regionId++;

#ifdef HIGHLIGHTING_DEBUG
        qCDebug(LOG_KTE) << "########### BEG REG: "  << beginRegionStr << " NUM: " << regionId;
#endif
    }

    if (!endRegionStr.isEmpty()) {
        regionId2 = RegionList->indexOf(endRegionStr);

        if (regionId2 == -1) { // if the region name doesn't already exist, add it to the list
            (*RegionList) << endRegionStr;
            regionId2 = RegionList->indexOf(endRegionStr);
        }

        regionId2 = -regionId2 - 1;

#ifdef HIGHLIGHTING_DEBUG
        qCDebug(LOG_KTE) << "########### END REG: "  << endRegionStr << " NUM: " << regionId2;
#endif
    }

    int attr = 0;
    const QString tmpAttr = KateHlManager::self()->syntax.groupItemData(data, QLatin1String("attribute")).simplified();
    bool onlyConsume = tmpAttr.isEmpty();

    // only relevant for non consumer
    if (!onlyConsume) {
        if (QString::fromLatin1("%1").arg(tmpAttr.toInt()) == tmpAttr) {
            errorsAndWarnings += QString(
                                     "<b>%1</b>: Deprecated syntax. Attribute (%2) not addressed by symbolic name<br />").arg (
                                     buildIdentifier, tmpAttr);
            attr = tmpAttr.toInt();
        } else {
            attr = lookupAttrName(tmpAttr, iDl);
        }
    }

    // Info about context switch
    KateHlContextModification context = -1;
    QString unresolvedContext;
    const QString tmpcontext = KateHlManager::self()->syntax.groupItemData(data, QLatin1String("context"));
    if (!tmpcontext.isEmpty()) {
        context = getContextModificationFromString(ContextNameList, tmpcontext, unresolvedContext);
    }

    // Get the char parameter (eg DetectChar)
    QChar chr;
    if (! KateHlManager::self()->syntax.groupItemData(data, QLatin1String("char")).isEmpty()) {
        chr = (KateHlManager::self()->syntax.groupItemData(data, QLatin1String("char")))[0];
    }

    // Get the String parameter (eg. StringDetect)
    const QString stringdata = KateHlManager::self()->syntax.groupItemData(data, QLatin1String("String"));

    // Get a second char parameter (char1) (eg Detect2Chars)
    QChar chr1;
    if (! KateHlManager::self()->syntax.groupItemData(data, QLatin1String("char1")).isEmpty()) {
        chr1 = (KateHlManager::self()->syntax.groupItemData(data, QLatin1String("char1")))[0];
    }

    // Will be removed eventually. Atm used for StringDetect, WordDetect, keyword and RegExp
    const QString &insensitive_str = KateHlManager::self()->syntax.groupItemData(data, QLatin1String("insensitive"));
    bool insensitive = IS_TRUE(insensitive_str);

    // for regexp only
    bool minimal = IS_TRUE(KateHlManager::self()->syntax.groupItemData(data, QLatin1String("minimal")));

    // dominik: look ahead and do not change offset. so we can change contexts w/o changing offset1.
    bool lookAhead = IS_TRUE(KateHlManager::self()->syntax.groupItemData(data, QLatin1String("lookAhead")));

    bool dynamic = IS_TRUE(KateHlManager::self()->syntax.groupItemData(data, QLatin1String("dynamic")));

    bool firstNonSpace = IS_TRUE(KateHlManager::self()->syntax.groupItemData(data, QLatin1String("firstNonSpace")));

    int column = -1;
    QString colStr = KateHlManager::self()->syntax.groupItemData(data, QLatin1String("column"));
    if (!colStr.isEmpty()) {
        column = colStr.toInt();
    }

    // Create the item corresponding to its type and set its parameters
    KateHlItem *tmpItem;

    if (dataname == QLatin1String("keyword")) {
        bool keywordInsensitive = insensitive_str.isEmpty() ? !casesensitive : insensitive;
        KateHlKeyword *keyword = new KateHlKeyword(attr, context, regionId, regionId2, keywordInsensitive,
                m_additionalData[ buildIdentifier ]->deliminator);

        //Get the entries for the keyword lookup list
        keyword->addList(KateHlManager::self()->syntax.finddata(QLatin1String("highlighting"), stringdata));
        tmpItem = keyword;
    } else if (dataname == QLatin1String("Float")) {
        tmpItem = (new KateHlFloat(attr, context, regionId, regionId2));
    } else if (dataname == QLatin1String("Int")) {
        tmpItem = (new KateHlInt(attr, context, regionId, regionId2));
    } else if (dataname == QLatin1String("DetectChar")) {
        tmpItem = (new KateHlCharDetect(attr, context, regionId, regionId2, chr));
    } else if (dataname == QLatin1String("Detect2Chars")) {
        tmpItem = (new KateHl2CharDetect(attr, context, regionId, regionId2, chr, chr1));
    } else if (dataname == QLatin1String("RangeDetect")) {
        tmpItem = (new KateHlRangeDetect(attr, context, regionId, regionId2, chr, chr1));
    } else if (dataname == QLatin1String("LineContinue")) {
        tmpItem = (new KateHlLineContinue(attr, context, regionId, regionId2, chr));
    } else if (dataname == QLatin1String("StringDetect")) {
        tmpItem = (new KateHlStringDetect(attr, context, regionId, regionId2, stringdata, insensitive));
    } else if (dataname == QLatin1String("WordDetect")) {
        tmpItem = (new KateHlWordDetect(attr, context, regionId, regionId2, stringdata, insensitive));
    } else if (dataname == QLatin1String("AnyChar")) {
        tmpItem = (new KateHlAnyChar(attr, context, regionId, regionId2, stringdata));
    } else if (dataname == QLatin1String("RegExpr")) {
        tmpItem = (new KateHlRegExpr(attr, context, regionId, regionId2, stringdata, insensitive, minimal));
    } else if (dataname == QLatin1String("HlCChar")) {
        tmpItem = (new KateHlCChar(attr, context, regionId, regionId2));
    } else if (dataname == QLatin1String("HlCHex")) {
        tmpItem = (new KateHlCHex(attr, context, regionId, regionId2));
    } else if (dataname == QLatin1String("HlCOct")) {
        tmpItem = (new KateHlCOct(attr, context, regionId, regionId2));
    } else if (dataname == QLatin1String("HlCFloat")) {
        tmpItem = (new KateHlCFloat(attr, context, regionId, regionId2));
    } else if (dataname == QLatin1String("HlCStringChar")) {
        tmpItem = (new KateHlCStringChar(attr, context, regionId, regionId2));
    } else if (dataname == QLatin1String("DetectSpaces")) {
        tmpItem = (new KateHlDetectSpaces(attr, context, regionId, regionId2));
    } else if (dataname == QLatin1String("DetectIdentifier")) {
        tmpItem = (new KateHlDetectIdentifier(attr, context, regionId, regionId2));
    } else {
        // oops, unknown type. Perhaps a spelling error in the xml file
        return 0;
    }

    // set lookAhead & dynamic properties
    tmpItem->lookAhead = lookAhead;
    tmpItem->dynamic = dynamic;
    tmpItem->firstNonSpace = firstNonSpace;
    tmpItem->column = column;
    tmpItem->onlyConsume = onlyConsume;

    if (!unresolvedContext.isEmpty()) {
        unresolvedContextReferences.insert(&(tmpItem->ctx), unresolvedContext);
    }

    // remember all to delete them
    m_hlItemCleanupList.append(tmpItem);

    return tmpItem;
}

int KateHighlighting::attribute(int ctx) const
{
    return m_contexts[ctx]->attr;
}

bool KateHighlighting::attributeRequiresSpellchecking(int attr)
{
    if (attr >= 0 && attr < internalIDList.size() && internalIDList[attr]->hasProperty(Spellchecking)) {
        return !internalIDList[attr]->boolProperty(Spellchecking);
    }
    return true;
}

KTextEditor::DefaultStyle KateHighlighting::defaultStyleForAttribute(int attr) const
{
    if (attr >= 0 && attr < internalIDList.size()) {
        return internalIDList[attr]->defaultStyle();
    }
    return KTextEditor::dsNormal;
}

QString KateHighlighting::hlKeyForContext(int i) const
{
    int k = 0;
    QMap<int, QString>::const_iterator it = m_ctxIndex.constEnd();
    while (it != m_ctxIndex.constBegin()) {
        --it;
        k = it.key();
        if (i >= k) {
            break;
        }
    }
    return it.value();
}

QString KateHighlighting::hlKeyForAttrib(int i) const
{
    // find entry. This is faster than QMap::find. m_hlIndex always has an entry
    // for key '0' (it is "none"), so the result is always valid.
    int k = 0;
    QMap<int, QString>::const_iterator it = m_hlIndex.constEnd();
    while (it != m_hlIndex.constBegin()) {
        --it;
        k = it.key();
        if (i >= k) {
            break;
        }
    }
    return it.value();
}

bool KateHighlighting::isInWord(QChar c, int attrib) const
{
    return m_additionalData[ hlKeyForAttrib(attrib) ]->deliminator.indexOf(c) < 0
           && !c.isSpace()
           && c != QLatin1Char('"') && c != QLatin1Char('\'') && c != QLatin1Char('`');
}

bool KateHighlighting::canBreakAt(QChar c, int attrib) const
{
    static const QString &sq = QStringLiteral("\"'");
    return (m_additionalData[ hlKeyForAttrib(attrib) ]->wordWrapDeliminator.indexOf(c) != -1) && (sq.indexOf(c) == -1);
}

QLinkedList<QRegularExpression> KateHighlighting::emptyLines(int attrib) const
{
#ifdef HIGHLIGHTING_DEBUG
    qCDebug(LOG_KTE) << "hlKeyForAttrib: " << hlKeyForAttrib(attrib);
#endif

    return m_additionalData[hlKeyForAttrib(attrib)]->emptyLines;
}

signed char KateHighlighting::commentRegion(int attr) const
{
    QString commentRegion = m_additionalData[ hlKeyForAttrib(attr) ]->multiLineRegion;
    return (commentRegion.isEmpty() ? 0 : (commentRegion.toShort()));
}

bool KateHighlighting::canComment(int startAttrib, int endAttrib) const
{
    QString k = hlKeyForAttrib(startAttrib);
    return (k == hlKeyForAttrib(endAttrib) &&
            ((!m_additionalData[k]->multiLineCommentStart.isEmpty() && !m_additionalData[k]->multiLineCommentEnd.isEmpty()) ||
             ! m_additionalData[k]->singleLineCommentMarker.isEmpty()));
}

QString KateHighlighting::getCommentStart(int attrib) const
{
    return m_additionalData[ hlKeyForAttrib(attrib) ]->multiLineCommentStart;
}

QString KateHighlighting::getCommentEnd(int attrib) const
{
    return m_additionalData[ hlKeyForAttrib(attrib) ]->multiLineCommentEnd;
}

QString KateHighlighting::getCommentSingleLineStart(int attrib) const
{
    return m_additionalData[ hlKeyForAttrib(attrib) ]->singleLineCommentMarker;
}

KateHighlighting::CSLPos KateHighlighting::getCommentSingleLinePosition(int attrib) const
{
    return m_additionalData[ hlKeyForAttrib(attrib) ]->singleLineCommentPosition;
}

const QHash<QString, QChar> &KateHighlighting::characterEncodings(int attrib) const
{
    return m_additionalData[ hlKeyForAttrib(attrib) ]->characterEncodings;
}

/**
 * Helper for makeContextList. It parses the xml file for
 * information, how single or multi line comments are marked
 */
void KateHighlighting::readCommentConfig()
{
    KateHlManager::self()->syntax.setIdentifier(buildIdentifier);
    KateSyntaxContextData *data = KateHlManager::self()->syntax.getGroupInfo(QLatin1String("general"), QLatin1String("comment"));

    QString cmlStart, cmlEnd, cmlRegion, cslStart;
    CSLPos cslPosition = CSLPosColumn0;

    if (data) {
        while (KateHlManager::self()->syntax.nextGroup(data)) {
            if (KateHlManager::self()->syntax.groupData(data, QLatin1String("name")) == QLatin1String("singleLine")) {
                cslStart = KateHlManager::self()->syntax.groupData(data, QLatin1String("start"));
                QString cslpos = KateHlManager::self()->syntax.groupData(data, QLatin1String("position"));
                if (cslpos == QLatin1String("afterwhitespace")) {
                    cslPosition = CSLPosAfterWhitespace;
                } else {
                    cslPosition = CSLPosColumn0;
                }
            } else if (KateHlManager::self()->syntax.groupData(data, QLatin1String("name")) == QLatin1String("multiLine")) {
                cmlStart = KateHlManager::self()->syntax.groupData(data, QLatin1String("start"));
                cmlEnd = KateHlManager::self()->syntax.groupData(data, QLatin1String("end"));
                cmlRegion = KateHlManager::self()->syntax.groupData(data, QLatin1String("region"));
            }
        }

        KateHlManager::self()->syntax.freeGroupInfo(data);
    }

    m_additionalData[buildIdentifier]->singleLineCommentMarker = cslStart;
    m_additionalData[buildIdentifier]->singleLineCommentPosition = cslPosition;
    m_additionalData[buildIdentifier]->multiLineCommentStart = cmlStart;
    m_additionalData[buildIdentifier]->multiLineCommentEnd = cmlEnd;
    m_additionalData[buildIdentifier]->multiLineRegion = cmlRegion;
}

void KateHighlighting::readEmptyLineConfig()
{
    KateHlManager::self()->syntax.setIdentifier(buildIdentifier);
    KateSyntaxContextData *data = KateHlManager::self()->syntax.getGroupInfo(QLatin1String("general"), QLatin1String("emptyLine"));

    QLinkedList<QRegularExpression> exprList;

    if (data) {
        while (KateHlManager::self()->syntax.nextGroup(data)) {
#ifdef HIGHLIGHTING_DEBUG
            qCDebug(LOG_KTE) << "creating an empty line regular expression";
#endif

            QString regexprline = KateHlManager::self()->syntax.groupData(data, QLatin1String("regexpr"));
            bool regexprcase = (KateHlManager::self()->syntax.groupData(data, QLatin1String("casesensitive")).toUpper().compare(QLatin1String("TRUE")) == 0);
            exprList.append(QRegularExpression(regexprline, !regexprcase ? QRegularExpression::CaseInsensitiveOption : QRegularExpression::NoPatternOption));
        }
        KateHlManager::self()->syntax.freeGroupInfo(data);
    }

    m_additionalData[buildIdentifier]->emptyLines = exprList;
}

/**
 * Helper for makeContextList. It parses the xml file for information,
 * if keywords should be treated case(in)sensitive and creates the keyword
 * delimiter list. Which is the default list, without any given weak deliminiators
 */
void KateHighlighting::readGlobalKeywordConfig()
{
    deliminator = stdDeliminator();

#ifdef HIGHLIGHTING_DEBUG
    qCDebug(LOG_KTE) << "readGlobalKeywordConfig:BEGIN";
#endif

    // Tell the syntax document class which file we want to parse
    KateHlManager::self()->syntax.setIdentifier(buildIdentifier);
    KateSyntaxContextData *data = KateHlManager::self()->syntax.getConfig(QLatin1String("general"), QLatin1String("keywords"));

    if (data) {
#ifdef HIGHLIGHTING_DEBUG
        qCDebug(LOG_KTE) << "Found global keyword config";
#endif

        casesensitive = IS_TRUE(KateHlManager::self()->syntax.groupItemData(data, QLatin1String("casesensitive")));

        //get the weak deliminators
        weakDeliminator = (KateHlManager::self()->syntax.groupItemData(data, QLatin1String("weakDeliminator")));

#ifdef HIGHLIGHTING_DEBUG
        qCDebug(LOG_KTE) << "weak delimiters are: " << weakDeliminator;
#endif

        // remove any weakDelimitars (if any) from the default list and store this list.
        for (int s = 0; s < weakDeliminator.length(); s++) {
            int f = deliminator.indexOf(weakDeliminator[s]);

            if (f > -1) {
                deliminator.remove(f, 1);
            }
        }

        QString addDelim = (KateHlManager::self()->syntax.groupItemData(data, QLatin1String("additionalDeliminator")));

        if (!addDelim.isEmpty()) {
            deliminator = deliminator + addDelim;
        }

        KateHlManager::self()->syntax.freeGroupInfo(data);
    } else {
        //Default values
        casesensitive = true;
        weakDeliminator = QString();
    }

#ifdef HIGHLIGHTING_DEBUG
    qCDebug(LOG_KTE) << "readGlobalKeywordConfig:END";
    qCDebug(LOG_KTE) << "delimiterCharacters are: " << deliminator;
#endif

    m_additionalData[buildIdentifier]->deliminator = deliminator;
}

/**
 * Helper for makeContextList. It parses the xml file for any wordwrap
 * deliminators, characters * at which line can be broken. In case no keyword
 * tag is found in the xml file, the wordwrap deliminators list defaults to the
 * standard denominators. In case a keyword tag is defined, but no
 * wordWrapDeliminator attribute is specified, the deliminator list as computed
 * in readGlobalKeywordConfig is used.
 *
 * @return the computed delimiter string.
 */
void KateHighlighting::readWordWrapConfig()
{
#ifdef HIGHLIGHTING_DEBUG
    qCDebug(LOG_KTE) << "readWordWrapConfig:BEGIN";
#endif

    // Tell the syntax document class which file we want to parse
    KateHlManager::self()->syntax.setIdentifier(buildIdentifier);
    KateSyntaxContextData *data = KateHlManager::self()->syntax.getConfig(QLatin1String("general"), QLatin1String("keywords"));

    QString wordWrapDeliminator = stdDeliminator();
    if (data) {
#ifdef HIGHLIGHTING_DEBUG
        qCDebug(LOG_KTE) << "Found global keyword config";
#endif

        wordWrapDeliminator = (KateHlManager::self()->syntax.groupItemData(data, QLatin1String("wordWrapDeliminator")));
        //when no wordWrapDeliminator is defined use the deliminator list
        if (wordWrapDeliminator.length() == 0) {
            wordWrapDeliminator = deliminator;
        }

#ifdef HIGHLIGHTING_DEBUG
        qCDebug(LOG_KTE) << "word wrap deliminators are " << wordWrapDeliminator;
#endif

        KateHlManager::self()->syntax.freeGroupInfo(data);
    }

#ifdef HIGHLIGHTING_DEBUG
    qCDebug(LOG_KTE) << "readWordWrapConfig:END";
#endif

    m_additionalData[buildIdentifier]->wordWrapDeliminator = wordWrapDeliminator;
}

void KateHighlighting::readIndentationConfig()
{
    m_indentation = QString();

    KateHlManager::self()->syntax.setIdentifier(buildIdentifier);
    KateSyntaxContextData *data = KateHlManager::self()->syntax.getConfig(QLatin1String("general"), QLatin1String("indentation"));

    if (data) {
        m_indentation = (KateHlManager::self()->syntax.groupItemData(data, QLatin1String("mode")));

        KateHlManager::self()->syntax.freeGroupInfo(data);
    }
}

void KateHighlighting::readFoldingConfig()
{
#ifdef HIGHLIGHTING_DEBUG
    qCDebug(LOG_KTE) << "readfoldignConfig:BEGIN";
#endif

    // Tell the syntax document class which file we want to parse
    KateHlManager::self()->syntax.setIdentifier(buildIdentifier);
    KateSyntaxContextData *data = KateHlManager::self()->syntax.getConfig(QLatin1String("general"), QLatin1String("folding"));

    if (data) {
#ifdef HIGHLIGHTING_DEBUG
        qCDebug(LOG_KTE) << "Found global keyword config";
#endif

        m_foldingIndentationSensitive = IS_TRUE(KateHlManager::self()->syntax.groupItemData(data, QLatin1String("indentationsensitive")));

        KateHlManager::self()->syntax.freeGroupInfo(data);
    } else {
        //Default values
        m_foldingIndentationSensitive = false;
    }

#ifdef HIGHLIGHTING_DEBUG
    qCDebug(LOG_KTE) << "readfoldingConfig:END";
    qCDebug(LOG_KTE) << "############################ use indent for fold are: " << m_foldingIndentationSensitive;
#endif
}

void KateHighlighting::readSpellCheckingConfig()
{
    KateHlManager::self()->syntax.setIdentifier(buildIdentifier);
    KateSyntaxContextData *data = KateHlManager::self()->syntax.getGroupInfo(QLatin1String("spellchecking"), QLatin1String("encoding"));

    if (data) {
        while (KateHlManager::self()->syntax.nextGroup(data)) {
            QString encoding = KateHlManager::self()->syntax.groupData(data, QLatin1String("string"));
            QString character = KateHlManager::self()->syntax.groupData(data, QLatin1String("char"));
            QString ignored = KateHlManager::self()->syntax.groupData(data, QLatin1String("ignored"));

            const bool ignoredIsTrue = IS_TRUE(ignored);
            if (encoding.isEmpty() || (character.isEmpty() && !ignoredIsTrue)) {
                continue;
            }
            QRegularExpression newLineRegExp(QLatin1String("\\r|\\n"));
            if (encoding.indexOf(newLineRegExp) >= 0) {
                encoding.replace(newLineRegExp, QLatin1String("<\\n|\\r>"));

#ifdef HIGHLIGHTING_DEBUG
                qCDebug(LOG_KTE) << "Encoding" << encoding
                                  << "contains new-line characters. Ignored.";
#endif
            }
            QChar c = (character.isEmpty() || ignoredIsTrue) ? QChar() : character[0];
            addCharacterEncoding(buildIdentifier, encoding, c);
        }

        KateHlManager::self()->syntax.freeGroupInfo(data);
    }

    data = KateHlManager::self()->syntax.getConfig(QLatin1String("spellchecking"), QLatin1String("configuration"));
    if (data) {
        QString policy = KateHlManager::self()->syntax.groupItemData(data, QLatin1String("encodingReplacementPolicy"));
        QString policyLowerCase = policy.toLower();
        int p;

        if (policyLowerCase == QLatin1String("encodewhenpresent")) {
            p = KTextEditor::DocumentPrivate::EncodeWhenPresent;
        } else if (policyLowerCase == QLatin1String("encodealways")) {
            p = KTextEditor::DocumentPrivate::EncodeAlways;
        } else {
            p = KTextEditor::DocumentPrivate::EncodeNever;
        }

        m_additionalData[buildIdentifier]->encodedCharactersInsertionPolicy = p;

        KateHlManager::self()->syntax.freeGroupInfo(data);
    }
}

void  KateHighlighting::createContextNameList(QStringList *ContextNameList, int ctx0)
{
#ifdef HIGHLIGHTING_DEBUG
    qCDebug(LOG_KTE) << "creatingContextNameList:BEGIN";
#endif

    if (ctx0 == 0) {
        ContextNameList->clear();
    }

    KateHlManager::self()->syntax.setIdentifier(buildIdentifier);

    KateSyntaxContextData *data = KateHlManager::self()->syntax.getGroupInfo(QLatin1String("highlighting"), QLatin1String("context"));

    int id = ctx0;

    if (data) {
        while (KateHlManager::self()->syntax.nextGroup(data)) {
            QString tmpAttr = KateHlManager::self()->syntax.groupData(data, QLatin1String("name")).simplified();
            if (tmpAttr.isEmpty()) {
                tmpAttr = QString::fromLatin1("!KATE_INTERNAL_DUMMY! %1").arg(id);
                errorsAndWarnings += QString("<b>%1</b>: Deprecated syntax. Context %2 has no symbolic name<br />").arg(buildIdentifier, id - ctx0);
            } else {
                tmpAttr = buildPrefix + tmpAttr;
            }
            (*ContextNameList) << tmpAttr;
            id++;
        }
        KateHlManager::self()->syntax.freeGroupInfo(data);
    }

#ifdef HIGHLIGHTING_DEBUG
    qCDebug(LOG_KTE) << "creatingContextNameList:END";
#endif
}

KateHlContextModification KateHighlighting::getContextModificationFromString(QStringList *ContextNameList, QString tmpLineEndContext, /*NO CONST*/ QString &unres)
{
    // nothing unresolved
    unres = QString();

    // context to push on stack
    int context = -1;

    // number of contexts to pop
    int pops = 0;

    // we allow arbitrary #stay and #pop at the start
    bool anyFound = false;
    while (tmpLineEndContext.startsWith(QLatin1String("#stay")) ||
            tmpLineEndContext.startsWith(QLatin1String("#pop"))) {
        // ignore stay
        if (tmpLineEndContext.startsWith(QLatin1String("#stay"))) {
            tmpLineEndContext.remove(0, 5);
        } else { // count the pops
            ++pops;
            tmpLineEndContext.remove(0, 4);
        }

        anyFound = true;
    }

    /**
     * we want a ! if we have found any pop or push and still have stuff in the string...
     */
    if (anyFound && !tmpLineEndContext.isEmpty()) {
        if (tmpLineEndContext.startsWith(QLatin1Char('!'))) {
            tmpLineEndContext.remove(0, 1);
        }
    }

    /**
     * empty string, done
     */
    if (tmpLineEndContext.isEmpty()) {
        return KateHlContextModification(context, pops);
    }

    /**
     * handle the remaining string, this might be a ##contextname
     * or a normal contextname....
     */
    if (tmpLineEndContext.contains(QLatin1String("##"))) {
        int o = tmpLineEndContext.indexOf(QLatin1String("##"));
        // FIXME at least with 'foo##bar'-style contexts the rules are picked up
        // but the default attribute is not
        QString tmp = tmpLineEndContext.mid(o + 2);
        if (!embeddedHls.contains(tmp)) {
            embeddedHls.insert(tmp, KateEmbeddedHlInfo());
        }
        unres = tmp + QLatin1Char(':') + tmpLineEndContext.left(o);

#ifdef HIGHLIGHTING_DEBUG
        qCDebug(LOG_KTE) << "unres = " << unres;
#endif

        context = 0;
    }

    else {
        context = ContextNameList->indexOf(buildPrefix + tmpLineEndContext);
        if (context == -1) {
            context = tmpLineEndContext.toInt();
            errorsAndWarnings += QString(
                                     "<B>%1</B>:Deprecated syntax. Context %2 not addressed by a symbolic name").arg(
                                     buildIdentifier, tmpLineEndContext);
        }
//#warning restructure this the name list storage.
//    context=context+buildContext0Offset;
    }

    return KateHlContextModification(context, pops);
}

/**
 * The most important initialization function for each highlighting. It's called
 * each time a document gets a highlighting style assigned. parses the xml file
 * and creates a corresponding internal structure
 */
void KateHighlighting::makeContextList()
{
    if (noHl) { // if this a highlighting for "normal texts" only, tere is no need for a context list creation
        return;
    }

    embeddedHls.clear();
    embeddedHighlightingModes.clear();
    unresolvedContextReferences.clear();
    RegionList.clear();
    ContextNameList.clear();

    // prepare list creation. To reuse as much code as possible handle this
    // highlighting the same way as embedded onces
    embeddedHls.insert(iName, KateEmbeddedHlInfo());

    bool something_changed;
    // the context "0" id is 0 for this hl, all embedded context "0"s have offsets
    startctx = base_startctx = 0;
    // inform everybody that we are building the highlighting contexts and itemlists
    building = true;

    do {
#ifdef HIGHLIGHTING_DEBUG
        qCDebug(LOG_KTE) << "**************** Outer loop in make ContextList";
        qCDebug(LOG_KTE) << "**************** Hl List count:" << embeddedHls.count();
#endif

        something_changed = false; //assume all "embedded" hls have already been loaded
        for (KateEmbeddedHlInfos::iterator it = embeddedHls.begin(); it != embeddedHls.end(); ++it) {
            if (!it.value().loaded) { // we found one, we still have to load
#ifdef HIGHLIGHTING_DEBUG
                qCDebug(LOG_KTE) << "**************** Inner loop in make ContextList";
#endif

                QString identifierToUse;

#ifdef HIGHLIGHTING_DEBUG
                qCDebug(LOG_KTE) << "Trying to open highlighting definition file: " << it.key();
#endif

                if (iName == it.key()) { // the own identifier is known
                    identifierToUse = identifier;
                } else {             // all others have to be looked up
                    identifierToUse = KateHlManager::self()->identifierForName(it.key());
                }

#ifdef HIGHLIGHTING_DEBUG
                qCDebug(LOG_KTE) << "Location is:" << identifierToUse;
#endif

                if (identifierToUse.isEmpty()) {
                    qWarning() << "Unknown highlighting description referenced:" << it.key() << "in" << identifier;
                }

                buildPrefix = it.key() + QLatin1Char(':'); // attribute names get prefixed by the names
                // of the highlighting definitions they belong to

#ifdef HIGHLIGHTING_DEBUG
                qCDebug(LOG_KTE) << "setting (" << it.key() << ") to loaded";
#endif

                //mark hl as loaded
                it = embeddedHls.insert(it.key(), KateEmbeddedHlInfo(true, startctx));
                //set class member for context 0 offset, so we don't need to pass it around
                buildContext0Offset = startctx;
                //parse one hl definition file
                startctx = addToContextList(identifierToUse, startctx);

                if (noHl) {
                    return;    // an error occurred
                }

                base_startctx = startctx;
                something_changed = true; // something has been loaded
            }
        }
    } while (something_changed);  // as long as there has been another file parsed
    // repeat everything, there could be newly added embedded hls.

#ifdef HIGHLIGHTING_DEBUG
    // at this point all needed highlighing (sub)definitions are loaded. It's time
    // to resolve cross file  references (if there are any)#
    qCDebug(LOG_KTE) << "Unresolved contexts, which need attention: " << unresolvedContextReferences.count();
#endif

    //optimize this a littlebit
    for (KateHlUnresolvedCtxRefs::iterator unresIt = unresolvedContextReferences.begin();
            unresIt != unresolvedContextReferences.end();
            ++unresIt) {
        QString incCtx = unresIt.value();

#ifdef HIGHLIGHTING_DEBUG
        qCDebug(LOG_KTE) << "Context " << incCtx << " is unresolved";
#endif

        // only resolve '##Name' contexts here; handleKateHlIncludeRules() can figure
        // out 'Name##Name'-style inclusions, but we screw it up
        if (incCtx.endsWith(QLatin1Char(':'))) {
#ifdef HIGHLIGHTING_DEBUG
            qCDebug(LOG_KTE) << "Looking up context0 for ruleset " << incCtx;
#endif

            incCtx = incCtx.left(incCtx.length() - 1);
            //try to find the context0 id for a given unresolvedReference
            KateEmbeddedHlInfos::const_iterator hlIt = embeddedHls.constFind(incCtx);
            if (hlIt != embeddedHls.constEnd()) {
                *(unresIt.key()) = hlIt.value().context0;
            }
        }
    }

    // eventually handle KateHlIncludeRules items, if they exist.
    // This has to be done after the cross file references, because it is allowed
    // to include the context0 from a different definition, than the one the rule
    // belongs to
    handleKateHlIncludeRules();

    embeddedHighlightingModes = embeddedHls.keys();
    embeddedHighlightingModes.removeOne(iName);

    embeddedHls.clear(); //save some memory.
    unresolvedContextReferences.clear(); //save some memory
    RegionList.clear();  // I think you get the idea ;)
    ContextNameList.clear();

    // if there have been errors show them
    if (!errorsAndWarnings.isEmpty())
    // we have finished
    building = false;

    Q_ASSERT(m_contexts.size() > 0);
}

void KateHighlighting::handleKateHlIncludeRules()
{
    // if there are noe include rules to take care of, just return
#ifdef HIGHLIGHTING_DEBUG
    qCDebug(LOG_KTE) << "KateHlIncludeRules, which need attention: " << includeRules.size();
#endif

    if (includeRules.isEmpty()) {
        return;
    }

    buildPrefix = QString();
    QString dummy;

    // By now the context0 references are resolved, now more or less only inner
    // file references are resolved. If we decide that arbitrary inclusion is
    // needed, this doesn't need to be changed, only the addToContextList
    // method.

    //resolove context names
    for (KateHlIncludeRules::iterator it = includeRules.begin(); it != includeRules.end();) {
        if ((*it)->incCtx.newContext == -1) { // context unresolved ?

            if ((*it)->incCtxN.isEmpty()) {
                // no context name given, and no valid context id set, so this item is
                // going to be removed
                KateHlIncludeRules::iterator it1 = it;
                ++it1;
                delete(*it);
                includeRules.erase(it);
                it = it1;
            } else {
                // resolve name to id
                (*it)->incCtx = getContextModificationFromString(&ContextNameList, (*it)->incCtxN, dummy).newContext;

#ifdef HIGHLIGHTING_DEBUG
                qCDebug(LOG_KTE) << "Resolved " << (*it)->incCtxN << " to " << (*it)->incCtx.newContext << " for include rule";
#endif

                // It would be good to look here somehow, if the result is valid
            }
        } else {
            ++it;    //nothing to do, already resolved (by the cross definition reference resolver)
        }
    }

    // now that all KateHlIncludeRule items should be valid and completely resolved,
    // do the real inclusion of the rules.
    // recursiveness is needed, because context 0 could include context 1, which
    // itself includes context 2 and so on.
    //  In that case we have to handle context 2 first, then 1, 0
    //TODO: catch circular references: eg 0->1->2->3->1
    for (int i = 0; i < includeRules.count(); i++) {
        handleKateHlIncludeRulesRecursive(i, &includeRules);
    }
    qDeleteAll(includeRules);
    includeRules.clear();
}

void KateHighlighting::handleKateHlIncludeRulesRecursive(int index, KateHlIncludeRules *list)
{
    if (index < 0 || index >= list->count()) {
        return;    //invalid iterator, shouldn't happen, but better have a rule prepared ;)
    }

    int index1 = index;
    int ctx = list->at(index1)->ctx;

    if (ctx == -1) {
        return;    // skip already processed entries
    }

    // find the last entry for the given context in the KateHlIncludeRules list
    // this is need if one context includes more than one. This saves us from
    // updating all insert positions:
    // eg: context 0:
    // pos 3 - include context 2
    // pos 5 - include context 3
    // During the building of the includeRules list the items are inserted in
    // ascending order, now we need it descending to make our life easier.
    while (index < list->count() && list->at(index)->ctx == ctx) {
        index1 = index;
        ++index;
    }

    // iterate over each include rule for the context the function has been called for.
    while (index1 >= 0 && index1 < list->count() && list->at(index1)->ctx == ctx) {
        KateHlContextModification ctx1 = list->at(index1)->incCtx;

        //let's see, if the included context includes other contexts
        for (int index2 = 0; index2 < list->count(); ++index2) {
            if (list->at(index2)->ctx == ctx1.newContext) {
                if (index2 == index1) {
                    // prevent accidental infinite recursion
                    qWarning() << "infinite recursion in IncludeRules in language file for " << iName << "in context" << list->at(index1)->incCtxN;
                    continue;
                }
                //yes it does, so first handle that include rules, since we want to
                // include those subincludes too
                handleKateHlIncludeRulesRecursive(index2, list);
                break;
            }
        }

        // if the context we want to include had sub includes, they are already inserted there.
        KateHlContext *dest = m_contexts[ctx];
        KateHlContext *src = m_contexts[ctx1.newContext];
//     qCDebug(LOG_KTE)<<"linking included rules from "<<ctx<<" to "<<ctx1;

        // If so desired, change the dest attribute to the one of the src.
        // Required to make commenting work, if text matched by the included context
        // is a different highlight than the host context.
        if (list->at(index1)->includeAttrib) {
            dest->attr = src->attr;
        }

        // insert the included context's rules starting at position p
        int p = list->at(index1)->pos;

        // remember some stuff
        int oldLen = dest->items.size();
        uint itemsToInsert = src->items.size();

        // resize target
        dest->items.resize(oldLen + itemsToInsert);

        // move old elements
        for (int i = oldLen - 1; i >= p; --i) {
            dest->items[i + itemsToInsert] = dest->items[i];
        }

        // insert new stuff
        for (uint i = 0; i < itemsToInsert; ++i) {
            dest->items[p + i] = src->items[i];
        }

        index = index1; //backup the iterator
        --index1;  //move to the next entry, which has to be take care of
        list->at(index)->ctx = -1;  // set ctx to -1 to mark already processed entries
    }
}

/**
 * Add one highlight to the contextlist.
 *
 * @return the number of contexts after this is added.
 */
int KateHighlighting::addToContextList(const QString &ident, int ctx0)
{
    //qCDebug(LOG_KTE)<<"=== Adding hl with ident '"<<ident<<"' ctx0="<<ctx0;

    buildIdentifier = ident;
    QString dummy;

    // Let the syntax document class know, which file we'd like to parse
    if (!KateHlManager::self()->syntax.setIdentifier(ident)) {
        noHl = true;
        return 0;
    }

    // only read for the own stuff
    if (identifier == ident) {
        readIndentationConfig();
    }

    RegionList << QLatin1String("!KateInternal_TopLevel!");

    m_hlIndex[internalIDList.count()] = ident;
    m_ctxIndex[ctx0] = ident;

    // clear and reuse or create new
    if (m_additionalData[ident]) {
        *m_additionalData[ident] = HighlightPropertyBag();
    } else {
        m_additionalData.insert(ident, new HighlightPropertyBag);
    }

    // fill out the propertybag
    readCommentConfig();
    readEmptyLineConfig();
    readGlobalKeywordConfig();
    readWordWrapConfig();

    // only read for ourself
    if (identifier == ident) {
        readFoldingConfig();
    }

    readSpellCheckingConfig();

    // This list is needed for the translation of the attribute parameter,
    // if the itemData name is given instead of the index
    addToKateExtendedAttributeList();
    QList<KTextEditor::Attribute::Ptr> iDl = internalIDList;

    createContextNameList(&ContextNameList, ctx0);

#ifdef HIGHLIGHTING_DEBUG
    qCDebug(LOG_KTE) << "Parsing Context structure";
#endif

    //start the real work
    uint i = buildContext0Offset;
    KateSyntaxContextData *data = KateHlManager::self()->syntax.getGroupInfo(QLatin1String("highlighting"), QLatin1String("context"));
    if (data) {
        while (KateHlManager::self()->syntax.nextGroup(data)) {
#ifdef HIGHLIGHTING_DEBUG
            qCDebug(LOG_KTE) << "Found a context in file, building structure now";
#endif

            //BEGIN - Translation of the attribute parameter
            QString tmpAttr = KateHlManager::self()->syntax.groupData(data, QLatin1String("attribute")).simplified();
            int attr;
            if (QString::fromLatin1("%1").arg(tmpAttr.toInt()) == tmpAttr) {
                attr = tmpAttr.toInt();
            } else {
                attr = lookupAttrName(tmpAttr, iDl);
            }
            //END - Translation of the attribute parameter

            QString tmpLineEndContext = KateHlManager::self()->syntax.groupData(data, QLatin1String("lineEndContext")).simplified();
            KateHlContextModification context;

            context = getContextModificationFromString(&ContextNameList, tmpLineEndContext, dummy);

            QString tmpNIBF = KateHlManager::self()->syntax.groupData(data, QLatin1String("noIndentationBasedFolding"));
            bool noIndentationBasedFolding = IS_TRUE(tmpNIBF);

            //BEGIN get fallthrough props
            KateHlContextModification ftc = 0; // fallthrough context
            QString tmpFt = KateHlManager::self()->syntax.groupData(data, QLatin1String("fallthrough"));
            const bool ft = IS_TRUE(tmpFt);
            if (ft) {
                QString tmpFtc = KateHlManager::self()->syntax.groupData(data, QLatin1String("fallthroughContext"));

                ftc = getContextModificationFromString(&ContextNameList, tmpFtc, dummy);

                // stay is not allowed, we need to #pop or push some context...
                if (ftc.type == KateHlContextModification::doNothing) {
                    ftc = 0;
                }

#ifdef HIGHLIGHTING_DEBUG
                qCDebug(LOG_KTE) << "Setting fall through context (context " << i << "): " << ftc.newContext;
#endif
            }
            //END fallthrough props

            // empty line context
            QString emptyLineContext = KateHlManager::self()->syntax.groupData(data, QLatin1String("lineEmptyContext"));
            KateHlContextModification emptyLineContextModification;
            if (!emptyLineContext.isEmpty()) {
                emptyLineContextModification = getContextModificationFromString(&ContextNameList, emptyLineContext, dummy);
            }

            bool dynamic = false;
            QString tmpDynamic = KateHlManager::self()->syntax.groupData(data, QLatin1String("dynamic"));
            if (tmpDynamic.toLower() == QLatin1String("true") ||  tmpDynamic.toInt() == 1) {
                dynamic = true;
            }

            KateHlContext *ctxNew = new KateHlContext(
                ident,
                attr,
                context,
                ft, ftc, dynamic, noIndentationBasedFolding,
                !emptyLineContext.isEmpty(), emptyLineContextModification);

            m_contexts.push_back(ctxNew);

#ifdef HIGHLIGHTING_DEBUG
            qCDebug(LOG_KTE) << "INDEX: " << i << " LENGTH " << m_contexts.size() - 1;
#endif

            //Let's create all items for the context
            while (KateHlManager::self()->syntax.nextItem(data)) {
//         qCDebug(LOG_KTE)<< "In make Contextlist: Item:";

                // KateHlIncludeRules : add a pointer to each item in that context
                // TODO add a attrib includeAttrib
                QString tag = KateHlManager::self()->syntax.groupItemData(data, QString());
                if (tag == QLatin1String("IncludeRules")) { //if the new item is an Include rule, we have to take special care
                    QString incCtx = KateHlManager::self()->syntax.groupItemData(data, QLatin1String("context"));
                    QString incAttrib = KateHlManager::self()->syntax.groupItemData(data, QLatin1String("includeAttrib"));
                    bool includeAttrib = IS_TRUE(incAttrib);

                    // only context refernces of type Name, ##Name, and Subname##Name are allowed
                    if (incCtx.startsWith(QLatin1String("##")) || (!incCtx.startsWith(QLatin1Char('#')))) {
                        int incCtxi = incCtx.indexOf(QLatin1String("##"));
                        //#stay, #pop is not interesting here
                        if (incCtxi >= 0) {
                            QString incSet = incCtx.mid(incCtxi + 2);
                            QString incCtxN = incSet + QLatin1Char(':') + incCtx.left(incCtxi);

                            //a cross highlighting reference
#ifdef HIGHLIGHTING_DEBUG
                            qCDebug(LOG_KTE) << "Cross highlight reference <IncludeRules>, context " << incCtxN;
#endif

                            KateHlIncludeRule *ir = new KateHlIncludeRule(i, m_contexts[i]->items.count(), incCtxN, includeAttrib);

                            //use the same way to determine cross hl file references as other items do
                            if (!embeddedHls.contains(incSet)) {
                                embeddedHls.insert(incSet, KateEmbeddedHlInfo());
                            }
#ifdef HIGHLIGHTING_DEBUG
                            else {
                                qCDebug(LOG_KTE) << "Skipping embeddedHls.insert for " << incCtxN;
                            }
#endif

                            unresolvedContextReferences.insert(&(ir->incCtx), incCtxN);

                            includeRules.append(ir);
                        } else {
                            // a local reference -> just initialize the include rule structure
                            incCtx = buildPrefix + incCtx.simplified();
                            includeRules.append(new KateHlIncludeRule(i, m_contexts[i]->items.count(), incCtx, includeAttrib));
                        }
                    }

                    continue;
                }
// TODO -- can we remove the block below??
#if 0
                QString tag = KateHlManager::self()->syntax.groupKateExtendedAttribute(data, QString());
                if (tag == "IncludeRules") {
                    // attrib context: the index (jowenn, i think using names here
                    // would be a cool feat, goes for mentioning the context in
                    // any item. a map or dict?)
                    int ctxId = getIdFromString(&ContextNameList,
                                                KateHlManager::self()->syntax.groupKateExtendedAttribute(data, QString("context")), dummy); // the index is *required*
                    if (ctxId > -1) {  // we can even reuse rules of 0 if we want to:)
                        qCDebug(LOG_KTE) << "makeContextList[" << i << "]: including all items of context " << ctxId;
                        if (ctxId < (int) i) {   // must be defined
                            for (c = m_contexts[ctxId]->items.first(); c; c = m_contexts[ctxId]->items.next()) {
                                m_contexts[i]->items.append(c);
                            }
                        } else {
                            qCDebug(LOG_KTE) << "Context " << ctxId << "not defined. You can not include the rules of an undefined context";
                        }
                    }
                    continue; // while nextItem
                }
#endif
                KateHlItem *c = createKateHlItem(data, iDl, &RegionList, &ContextNameList);
                if (c) {
                    m_contexts[i]->items.append(c);

                    // Not supported completely atm and only one level. Subitems.(all have
                    // to be matched to at once)
                    KateSyntaxContextData *datasub = KateHlManager::self()->syntax.getSubItems(data);
                    for (bool tmpbool = KateHlManager::self()->syntax.nextItem(datasub);
                            tmpbool;
                            tmpbool = KateHlManager::self()->syntax.nextItem(datasub)) {
                        c->subItems.resize(c->subItems.size() + 1);
                        c->subItems[c->subItems.size() - 1] = createKateHlItem(datasub, iDl, &RegionList, &ContextNameList);
                    }
                    KateHlManager::self()->syntax.freeGroupInfo(datasub);
                }
            }
            i++;
        }

        KateHlManager::self()->syntax.freeGroupInfo(data);
    } else {
        // error handling: no "context" element at all in the xml file
        noHl = true;
        qWarning() << "There is no \"context\" in the highlighting file:" << buildIdentifier;
    }

    if (RegionList.count() != 1) {
        folding = true;
    }

    folding = folding || m_foldingIndentationSensitive;

    //BEGIN Resolve multiline region if possible
    if (!m_additionalData[ ident ]->multiLineRegion.isEmpty()) {
        long commentregionid = RegionList.indexOf(m_additionalData[ ident ]->multiLineRegion);
        if (-1 == commentregionid) {
            errorsAndWarnings += QString(
                                     "<b>%1</b>: Specified multiline comment region (%2) could not be resolved<br />").arg(
                                     buildIdentifier,  m_additionalData[ ident ]->multiLineRegion);
            m_additionalData[ ident ]->multiLineRegion.clear();

#ifdef HIGHLIGHTING_DEBUG
            qCDebug(LOG_KTE) << "ERROR comment region attribute could not be resolved";
#endif
        } else {
            m_additionalData[ ident ]->multiLineRegion = QString::number(commentregionid + 1);

#ifdef HIGHLIGHTING_DEBUG
            qCDebug(LOG_KTE) << "comment region resolved to:" << m_additionalData[ ident ]->multiLineRegion;
#endif
        }
    }
    //END Resolve multiline region if possible
    return i;
}

void KateHighlighting::clearAttributeArrays()
{
    QMutableHashIterator< QString, QList<KTextEditor::Attribute::Ptr> > it = m_attributeArrays;
    while (it.hasNext()) {
        it.next();

        // k, schema correct, let create the data
        KateAttributeList defaultStyleList;

        auto config = HighLightConfig::instance (
                HighLightConfig::GENERAL,
                GetCfgsPath ("genHlTheme/" +
                             ConfigString("Highlight", "GenHighlight")));
        KateHlManager::self()->getDefaults(it.key(), defaultStyleList, config);

        QList<KTextEditor::Attribute::Ptr> itemDataList;
        getKateExtendedAttributeList(it.key(), itemDataList);

        uint nAttribs = itemDataList.count();
        QList<KTextEditor::Attribute::Ptr> &array = it.value();
        array.clear();

        for (uint z = 0; z < nAttribs; z++) {
            KTextEditor::Attribute::Ptr itemData = itemDataList.at(z);
            KTextEditor::Attribute::Ptr newAttribute(new KTextEditor::Attribute(*defaultStyleList.at(itemData->defaultStyle())));

            if (itemData && itemData->hasAnyProperty()) {
                *newAttribute += *itemData;
            }

            array.append(newAttribute);
        }
    }
}

QList<KTextEditor::Attribute::Ptr> KateHighlighting::attributes(const QString &schema, HighLightConfig* config)
{
    // found it, already floating around
    if (m_attributeArrays.contains(schema)) {
        return m_attributeArrays[schema];
    }

    // k, schema correct, let create the data
    QList<KTextEditor::Attribute::Ptr> array;
    KateAttributeList defaultStyleList;

    KateHlManager::self()->getDefaults(schema, defaultStyleList, config);

    QList<KTextEditor::Attribute::Ptr> itemDataList;
    getKateExtendedAttributeList(schema, itemDataList);

    uint nAttribs = itemDataList.count();
    for (uint z = 0; z < nAttribs; z++) {
        KTextEditor::Attribute::Ptr itemData = itemDataList.at(z);
        KTextEditor::Attribute::Ptr newAttribute(new KTextEditor::Attribute(*defaultStyleList.at(itemData->defaultStyle())));

        if (itemData && itemData->hasAnyProperty()) {
            *newAttribute += *itemData;
        }

        array.append(newAttribute);
    }

    m_attributeArrays.insert(schema, array);

    return array;
}

KateHlContext *KateHighlighting::contextNum(int n) const
{
    if (n >= 0 && n < m_contexts.size()) {
        return m_contexts[n];
    }

    Q_ASSERT(false);
    return 0;
}

QStringList KateHighlighting::getEmbeddedHighlightingModes() const
{
    return embeddedHighlightingModes;
}

bool KateHighlighting::isEmptyLine(const Kate::TextLineData *textline) const
{
    const QString &txt = textline->string();
    if (txt.isEmpty()) {
        return true;
    }

    const QLinkedList<QRegularExpression> l = emptyLines(textline->attribute(0));
    if (l.isEmpty()) {
        return false;
    }

    foreach (const QRegularExpression &re, l) {
        const QRegularExpressionMatch match = re.match (txt, 0, QRegularExpression::NormalMatch, QRegularExpression::AnchoredMatchOption);
        if (match.hasMatch() && match.capturedLength() == txt.length()) {
            return true;
        }
    }

    return false;
}

//END

