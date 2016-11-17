/* This file is part of the KDE libraries
   Copyright (C) 2003, 2004 Anders Lund <anders@alweb.dk>
   Copyright (C) 2003 Hamish Rodda <rodda@kde.org>
   Copyright (C) 2001,2002 Joseph Wenninger <jowenn@kde.org>
   Copyright (C) 2001 Christoph Cullmann <cullmann@kde.org>
   Copyright (C) 1999 Jochen Wilhelmy <digisnap@cs.tu-berlin.de>
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Library General Public
 *  License as published by the Free Software Foundation; either
 *  version 2 of the License, or (at your option) any later version.
 *
 *  This library is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  Library General Public License for more details.
 *
 *  You should have received a copy of the GNU Library General Public License
 *  along with this library; see the file COPYING.LIB.  If not, write to
 *  the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 *  Boston, MA 02110-1301, USA.
 */

//BEGIN INCLUDES
#include "katehighlighthelpers.h"

#include "katesyntaxdocument.h"
#include "kateextendedattribute.h"
#include <QDebug>
#include <QSet>
//END

//BEGIN KateHlItem
KateHlItem::KateHlItem(int attribute, KateHlContextModification context, signed char regionId, signed char regionId2)
    : attr(attribute),
      ctx(context),
      region(regionId),
      region2(regionId2),
      lookAhead(false),
      dynamic(false),
      dynamicChild(false),
      firstNonSpace(false),
      onlyConsume(false),
      column(-1),
      alwaysStartEnable(true),
      customStartEnable(false),
      haveCache(false),
      cachingHandled(false)
{
}

KateHlItem::~KateHlItem()
{
}

void KateHlItem::dynamicSubstitute(QString &str, const QStringList *args)
{
    for (int i = 0; i < str.length() - 1; ++i) {
        if (str[i] == QLatin1Char('%')) {
            char c = str[i + 1].toLatin1();
            if (c == '%') {
                str.remove(i, 1);
            } else if (c >= '0' && c <= '9') {
                if ((int)(c - '0') < args->size()) {
                    str.replace(i, 2, (*args)[c - '0']);
                    i += ((*args)[c - '0']).length() - 1;
                } else {
                    str.remove(i, 2);
                    --i;
                }
            }
        }
    }
}
//END

//BEGIN KateHlCharDetect
KateHlCharDetect::KateHlCharDetect(int attribute, KateHlContextModification context, signed char regionId, signed char regionId2, QChar c)
    : KateHlItem(attribute, context, regionId, regionId2)
    , sChar(c)
{
}

int KateHlCharDetect::checkHgl(const QString &text, int offset, int /*len*/)
{
    if (text[offset] == sChar) {
        return offset + 1;
    }

    return 0;
}

KateHlItem *KateHlCharDetect::clone(const QStringList *args)
{
    char c = sChar.toLatin1();

    if (c < '0' || c > '9' || (c - '0') >= args->size()) {
        return this;
    }

    KateHlCharDetect *ret = new KateHlCharDetect(attr, ctx, region, region2, (*args)[c - '0'][0]);
    ret->dynamicChild = true;
    return ret;
}
//END

//BEGIN KateHl2CharDetect
KateHl2CharDetect::KateHl2CharDetect(int attribute, KateHlContextModification context, signed char regionId, signed char regionId2, QChar ch1, QChar ch2)
    : KateHlItem(attribute, context, regionId, regionId2)
    , sChar1(ch1)
    , sChar2(ch2)
{
}

int KateHl2CharDetect::checkHgl(const QString &text, int offset, int len)
{
    if ((len >= 2) && text[offset++] == sChar1 && text[offset++] == sChar2) {
        return offset;
    }

    return 0;
}

KateHlItem *KateHl2CharDetect::clone(const QStringList *args)
{
    char c1 = sChar1.toLatin1();
    char c2 = sChar2.toLatin1();

    if (c1 < '0' || c1 > '9' || (c1 - '0') >= args->size()) {
        return this;
    }

    if (c2 < '0' || c2 > '9' || (c2 - '0') >= args->size()) {
        return this;
    }

    KateHl2CharDetect *ret = new KateHl2CharDetect(attr, ctx, region, region2, (*args)[c1 - '0'][0], (*args)[c2 - '0'][0]);
    ret->dynamicChild = true;
    return ret;
}
//END

//BEGIN KateHlStringDetect
KateHlStringDetect::KateHlStringDetect(int attribute, KateHlContextModification context, signed char regionId, signed char regionId2, const QString &s, bool inSensitive)
    : KateHlItem(attribute, context, regionId, regionId2)
    , str(inSensitive ? s.toUpper() : s)
    , strLen(str.length())
    , _inSensitive(inSensitive)
{
}

int KateHlStringDetect::checkHgl(const QString &text, int offset, int len)
{
    if (len < strLen) {
        return 0;
    }

    if (_inSensitive) {
        for (int i = 0; i < strLen; i++)
            if (text[offset++].toUpper() != str[i]) {
                return 0;
            }

        return offset;
    } else {
        for (int i = 0; i < strLen; i++)
            if (text[offset++] != str[i]) {
                return 0;
            }

        return offset;
    }

    return 0;
}

KateHlItem *KateHlStringDetect::clone(const QStringList *args)
{
    QString newstr = str;

    dynamicSubstitute(newstr, args);

    if (newstr == str) {
        return this;
    }

    KateHlStringDetect *ret = new KateHlStringDetect(attr, ctx, region, region2, newstr, _inSensitive);
    ret->dynamicChild = true;
    return ret;
}
//END

//BEGIN KateHlWordDetect

KateHlWordDetect::KateHlWordDetect(int attribute, KateHlContextModification context, signed char regionId, signed char regionId2, const QString &s, bool inSensitive)
    : KateHlStringDetect(attribute, context, regionId, regionId2, s, inSensitive)
{
}

inline bool isWordCharacter(const QChar &c)
{
    // http://pcre.org/pcre.txt say for word characters:
    //     \w  any character that matches \p{L} or \p{N}, plus underscore
    return c.isLetterOrNumber() || c.isMark() || c.unicode() == '_';
}

int KateHlWordDetect::checkHgl(const QString &text, int offset, int len)
{
    //NOTE: word boundary means: any non-word character.

    // make sure there is no letter or number before the word starts
    if (offset > 0 && isWordCharacter(text.at(offset - 1))) {
        return 0;
    }
    offset = KateHlStringDetect::checkHgl(text, offset, len);
    // make sure there is no letter or number after the word ends
    if (offset && offset < text.length() && isWordCharacter(text.at(offset))) {
        return 0;
    }
    return offset;
}

KateHlItem *KateHlWordDetect::clone(const QStringList *args)
{
    QString newstr = str;

    dynamicSubstitute(newstr, args);

    if (newstr == str) {
        return this;
    }

    KateHlWordDetect *ret = new KateHlWordDetect(attr, ctx, region, region2, newstr, _inSensitive);
    ret->dynamicChild = true;
    return ret;
}

//END KateHlWordDetect

//BEGIN KateHlRangeDetect
KateHlRangeDetect::KateHlRangeDetect(int attribute, KateHlContextModification context, signed char regionId, signed char regionId2, QChar ch1, QChar ch2)
    : KateHlItem(attribute, context, regionId, regionId2)
    , sChar1(ch1)
    , sChar2(ch2)
{
}

int KateHlRangeDetect::checkHgl(const QString &text, int offset, int len)
{
    if (text[offset] == sChar1) {
        do {
            offset++;
            len--;
            if (len < 1) {
                return 0;
            }
        } while (text[offset] != sChar2);

        return offset + 1;
    }
    return 0;
}
//END

//BEGIN KateHlKeyword
KateHlKeyword::KateHlKeyword(int attribute, KateHlContextModification context, signed char regionId, signed char regionId2, bool insensitive, const QString &delims)
    : KateHlItem(attribute, context, regionId, regionId2)
    , _insensitive(insensitive)
    , minLen(0xFFFFFF)
    , maxLen(0)
{
    alwaysStartEnable = false;
    customStartEnable = true;
    foreach (const QChar &c, delims) {
        deliminators << c;
    }
}

KateHlKeyword::~KateHlKeyword()
{
    qDeleteAll(dict);
}

QSet<QString> KateHlKeyword::allKeywords() const
{
    QSet<QString> result;
    foreach (const QSet<QString>* v, dict) {
        if (!v) {
            continue;
        }
        result.unite(*v);
    }
    return result;
}

void KateHlKeyword::addList(const QStringList &list)
{
    for (int i = 0; i < list.count(); ++i) {
        int len = list[i].length();

        if (minLen > len) {
            minLen = len;
        }

        if (maxLen < len) {
            maxLen = len;
        }

        if (len >= dict.size()) {
            uint oldSize = dict.size();
            dict.resize(len + 1);

            for (int m = oldSize; m < dict.size(); ++m) {
                dict[m] = 0;
            }
        }

        if (!dict[len]) {
            dict[len] = new QSet<QString> ();
        }

        if (!_insensitive) {
            dict[len]->insert(list[i]);
        } else {
            dict[len]->insert(list[i].toLower());
        }
    }
}

int KateHlKeyword::checkHgl(const QString &text, int offset, int len)
{
    int offset2 = offset;
    int wordLen = 0;

    while ((len > wordLen) && !deliminators.contains(text[offset2])) {
        offset2++;
        wordLen++;

        if (wordLen > maxLen) {
            return 0;
        }
    }

    if (wordLen < minLen || !dict[wordLen]) {
        return 0;
    }

    if (!_insensitive) {
        if (dict[wordLen]->contains(QString::fromRawData(text.unicode() + offset, wordLen))) {
            return offset2;
        }
    } else {
        if (dict[wordLen]->contains(QString::fromRawData(text.unicode() + offset, wordLen).toLower())) {
            return offset2;
        }
    }

    return 0;
}
//END

//BEGIN KateHlInt
KateHlInt::KateHlInt(int attribute, KateHlContextModification context, signed char regionId, signed char regionId2)
    : KateHlItem(attribute, context, regionId, regionId2)
{
    alwaysStartEnable = false;
}

int KateHlInt::checkHgl(const QString &text, int offset, int len)
{
    int offset2 = offset;

    while ((len > 0) && text[offset2].isDigit()) {
        offset2++;
        len--;
    }

    if (offset2 > offset) {
        if (len > 0) {
            for (int i = 0; i < subItems.size(); i++) {
                if ((offset = subItems[i]->checkHgl(text, offset2, len))) {
                    return offset;
                }
            }
        }

        return offset2;
    }

    return 0;
}
//END

//BEGIN KateHlFloat
KateHlFloat::KateHlFloat(int attribute, KateHlContextModification context, signed char regionId, signed char regionId2)
    : KateHlItem(attribute, context, regionId, regionId2)
{
    alwaysStartEnable = false;
}

int KateHlFloat::checkHgl(const QString &text, int offset, int len)
{
    bool b = false;
    bool p = false;

    while ((len > 0) && text[offset].isDigit()) {
        offset++;
        len--;
        b = true;
    }

    if ((len > 0) && (p = (text[offset] == QLatin1Char('.')))) {
        offset++;
        len--;

        while ((len > 0) && text[offset].isDigit()) {
            offset++;
            len--;
            b = true;
        }
    }

    if (!b) {
        return 0;
    }

    if ((len > 0) && ((text[offset].toLatin1() & 0xdf) == 'E')) {
        offset++;
        len--;
    } else {
        if (!p) {
            return 0;
        } else {
            if (len > 0) {
                for (int i = 0; i < subItems.size(); ++i) {
                    int offset2 = subItems[i]->checkHgl(text, offset, len);

                    if (offset2) {
                        return offset2;
                    }
                }
            }

            return offset;
        }
    }

    if ((len > 0) && (text[offset] == QLatin1Char('-') || text[offset] == QLatin1Char('+'))) {
        offset++;
        len--;
    }

    b = false;

    while ((len > 0) && text[offset].isDigit()) {
        offset++;
        len--;
        b = true;
    }

    if (b) {
        if (len > 0) {
            for (int i = 0; i < subItems.size(); ++i) {
                int offset2 = subItems[i]->checkHgl(text, offset, len);

                if (offset2) {
                    return offset2;
                }
            }
        }

        return offset;
    }

    return 0;
}
//END

//BEGIN KateHlCOct
KateHlCOct::KateHlCOct(int attribute, KateHlContextModification context, signed char regionId, signed char regionId2)
    : KateHlItem(attribute, context, regionId, regionId2)
{
    alwaysStartEnable = false;
}

int KateHlCOct::checkHgl(const QString &text, int offset, int len)
{
    if (text[offset].toLatin1() == '0') {
        offset++;
        len--;

        int offset2 = offset;

        while ((len > 0) && (text[offset2].toLatin1() >= '0' && text[offset2].toLatin1() <= '7')) {
            offset2++;
            len--;
        }

        if (offset2 > offset) {
            if ((len > 0) && ((text[offset2].toLatin1() & 0xdf) == 'L' || (text[offset].toLatin1() & 0xdf) == 'U')) {
                offset2++;
            }

            return offset2;
        }
    }

    return 0;
}
//END

//BEGIN KateHlCHex
KateHlCHex::KateHlCHex(int attribute, KateHlContextModification context, signed char regionId, signed char regionId2)
    : KateHlItem(attribute, context, regionId, regionId2)
{
    alwaysStartEnable = false;
}

int KateHlCHex::checkHgl(const QString &text, int offset, int len)
{
    if ((len > 1) && (text[offset++].toLatin1() == '0') && ((text[offset++].toLatin1() & 0xdf) == 'X')) {
        len -= 2;

        int offset2 = offset;

        while ((len > 0) && (text[offset2].isDigit() || ((text[offset2].toLatin1() & 0xdf) >= 'A' && (text[offset2].toLatin1() & 0xdf) <= 'F'))) {
            offset2++;
            len--;
        }

        if (offset2 > offset) {
            if ((len > 0) && ((text[offset2].toLatin1() & 0xdf) == 'L' || (text[offset2].toLatin1() & 0xdf) == 'U')) {
                offset2++;
            }

            return offset2;
        }
    }

    return 0;
}
//END

//BEGIN KateHlCFloat
KateHlCFloat::KateHlCFloat(int attribute, KateHlContextModification context, signed char regionId, signed char regionId2)
    : KateHlFloat(attribute, context, regionId, regionId2)
{
    alwaysStartEnable = false;
}

int KateHlCFloat::checkIntHgl(const QString &text, int offset, int len)
{
    int offset2 = offset;

    while ((len > 0) && text[offset].isDigit()) {
        offset2++;
        len--;
    }

    if (offset2 > offset) {
        return offset2;
    }

    return 0;
}

int KateHlCFloat::checkHgl(const QString &text, int offset, int len)
{
    int offset2 = KateHlFloat::checkHgl(text, offset, len);

    if (offset2) {
        if ((text[offset2].toLatin1() & 0xdf) == 'F') {
            offset2++;
        }

        return offset2;
    } else {
        offset2 = checkIntHgl(text, offset, len);

        if (offset2 && ((text[offset2].toLatin1() & 0xdf) == 'F')) {
            return ++offset2;
        } else {
            return 0;
        }
    }
}
//END

//BEGIN KateHlAnyChar
KateHlAnyChar::KateHlAnyChar(int attribute, KateHlContextModification context, signed char regionId, signed char regionId2, const QString &charList)
    : KateHlItem(attribute, context, regionId, regionId2)
    , _charList(charList)
{
}

int KateHlAnyChar::checkHgl(const QString &text, int offset, int)
{
    if (_charList.contains(text[offset])) {
        return ++offset;
    }

    return 0;
}
//END

//BEGIN KateHlRegExpr
KateHlRegExpr::KateHlRegExpr(int attribute, KateHlContextModification context, signed char regionId, signed char regionId2, const QString &regexp, bool insensitive, bool minimal)
    : KateHlItem(attribute, context, regionId, regionId2)
    , m_regularExpression (regexp, (insensitive ? QRegularExpression::CaseInsensitiveOption : QRegularExpression::NoPatternOption)
                 | (minimal ? QRegularExpression::InvertedGreedinessOption : QRegularExpression::NoPatternOption))
    , m_handlesLineStart (regexp.startsWith(QLatin1Char('^')))
{
}

int KateHlRegExpr::checkHgl(const QString &text, int offset, int /*len*/)
{
    /**
     * skip any match, if we have ^ and offset is already > 0
     */
    if (m_handlesLineStart && (offset > 0)) {
        return 0;
    }

    /**
     * perhaps clear cache?
     * that is needed, if we had a match and our current offset is already too large!
     */
    if (haveCache && m_lastMatch.hasMatch() && (offset > m_lastMatch.capturedStart())) {
        haveCache = false;
    }

    /**
     * try to match if not already cached
     * store result in member variable for later reuse
     */
    if (!haveCache) {
        m_lastMatch = m_regularExpression.match(text, offset);
        haveCache = true;
    }

    /**
     * no match or we match at wrong position?
     * => bad match
     */
    if (!m_lastMatch.hasMatch() || offset != m_lastMatch.capturedStart()) {
        return 0;
    }

    /**
     * else: return current capture end
     */
    return m_lastMatch.capturedEnd();
}

void KateHlRegExpr::capturedTexts(QStringList &list)
{
    /**
     * return stored list, if any
     */
    list = m_lastMatch.capturedTexts();
}

KateHlItem *KateHlRegExpr::clone(const QStringList *args)
{
    QString regexp = m_regularExpression.pattern();
    QStringList escArgs = *args;

    for (QStringList::Iterator it = escArgs.begin(); it != escArgs.end(); ++it) {
        (*it).replace(QRegularExpression(QLatin1String("(\\W)")), QLatin1String("\\\\1"));
    }

    dynamicSubstitute(regexp, &escArgs);

    if (regexp == m_regularExpression.pattern()) {
        return this;
    }

    // qCDebug(LOG_KTE) << "clone regexp: " << regexp;

    KateHlRegExpr *ret = new KateHlRegExpr(attr, ctx, region, region2, regexp
        , m_regularExpression.patternOptions() & QRegularExpression::CaseInsensitiveOption
        , m_regularExpression.patternOptions() & QRegularExpression::InvertedGreedinessOption);
    ret->dynamicChild = true;
    return ret;
}
// //END

//BEGIN KateHlLineContinue
KateHlLineContinue::KateHlLineContinue(int attribute, KateHlContextModification context, signed char regionId, signed char regionId2, QChar c)
    : KateHlItem(attribute, context, regionId, regionId2)
    , m_trailer(c.isNull() ? QLatin1Char('\\') : c)
{
}

int KateHlLineContinue::checkHgl(const QString &text, int offset, int len)
{
    if ((len == 1) && (text[offset] == m_trailer)) {
        return ++offset;
    }

    return 0;
}
//END

//BEGIN KateHlCStringChar
KateHlCStringChar::KateHlCStringChar(int attribute, KateHlContextModification context, signed char regionId, signed char regionId2)
    : KateHlItem(attribute, context, regionId, regionId2)
{
}

// checks for C escaped chars \n and escaped hex/octal chars
static int checkEscapedChar(const QString &text, int offset, int &len)
{
    int i;
    if (text[offset] == QLatin1Char('\\') && len > 1) {
        offset++;
        len--;

        switch (text[offset].toLatin1()) {
        case  'a': // checks for control chars
        case  'b': // we want to fall through
        case  'e':
        case  'f':

        case  'n':
        case  'r':
        case  't':
        case  'v':
        case '\'':
        case '\"':
        case '?' : // added ? ANSI C classifies this as an escaped char
        case '\\':
            offset++;
            len--;
            break;

        case 'x': // if it's like \xff
            offset++; // eat the x
            len--;
            // these for loops can probably be
            // replaced with something else but
            // for right now they work
            // check for hexdigits
            for (i = 0; (len > 0) && (i < 2); i++) {
                const char ch = text[offset].toLatin1();
                if (((ch >= '0') && (ch <= '9')) || (((ch & 0xdf) >= 'A') && ((ch & 0xdf) <= 'F'))) {
                    offset++;
                    len--;
                } else {
                    break;
                }
            }

            if (i == 0) {
                return 0;    // takes care of case '\x'
            }

            break;

        case '0': case '1': case '2': case '3' :
        case '4': case '5': case '6': case '7' :
            for (i = 0; (len > 0) && (i < 3) && (text[offset] >= QLatin1Char('0') && text[offset] <= QLatin1Char('7')); i++) {
                offset++;
                len--;
            }
            break;

        default:
            return 0;
        }

        return offset;
    }

    return 0;
}

int KateHlCStringChar::checkHgl(const QString &text, int offset, int len)
{
    return checkEscapedChar(text, offset, len);
}
//END

//BEGIN KateHlCChar
KateHlCChar::KateHlCChar(int attribute, KateHlContextModification context, signed char regionId, signed char regionId2)
    : KateHlItem(attribute, context, regionId, regionId2)
{
}

int KateHlCChar::checkHgl(const QString &text, int offset, int len)
{
    if ((len > 1) && (text[offset] == QLatin1Char('\'')) && (text[offset + 1] != QLatin1Char('\''))) {
        int oldl;
        oldl = len;

        len--;

        int offset2 = checkEscapedChar(text, offset + 1, len);

        if (!offset2) {
            if (oldl > 2) {
                offset2 = offset + 2;
                len = oldl - 2;
            } else {
                return 0;
            }
        }

        if ((len > 0) && (text[offset2] == QLatin1Char('\''))) {
            return ++offset2;
        }
    }

    return 0;
}
//END

//BEGIN KateHl2CharDetect
KateHl2CharDetect::KateHl2CharDetect(int attribute, KateHlContextModification context, signed char regionId, signed char regionId2, const QChar *s)
    : KateHlItem(attribute, context, regionId, regionId2)
{
    sChar1 = s[0];
    sChar2 = s[1];
}
//END KateHl2CharDetect

//BEGIN KateHlContext
KateHlContext::KateHlContext(const QString &_hlId, int attribute, KateHlContextModification _lineEndContext, bool _fallthrough,
                             KateHlContextModification _fallthroughContext, bool _dynamic, bool _noIndentationBasedFolding,
                             bool _emptyLineContext, KateHlContextModification _emptyLineContextModification)
{
    hlId = _hlId;
    attr = attribute;
    lineEndContext = _lineEndContext;
    fallthrough = _fallthrough;
    ftctx = _fallthroughContext;
    dynamic = _dynamic;
    dynamicChild = false;
    noIndentationBasedFolding = _noIndentationBasedFolding;
    emptyLineContext = _emptyLineContext;
    emptyLineContextModification = _emptyLineContextModification;
    if (_noIndentationBasedFolding) {
        qDebug() << "**********************_noIndentationBasedFolding is TRUE*****************";
    }

}

KateHlContext *KateHlContext::clone(const QStringList *args)
{
    KateHlContext *ret = new KateHlContext(hlId, attr, lineEndContext, fallthrough, ftctx, false, noIndentationBasedFolding
                                           , emptyLineContext, emptyLineContextModification
                                          );

    for (int n = 0; n < items.size(); ++n) {
        KateHlItem *item = items[n];
        KateHlItem *i = (item->dynamic ? item->clone(args) : item);
        ret->items.append(i);
    }

    ret->dynamicChild = true;

    return ret;
}

KateHlContext::~KateHlContext()
{
    if (dynamicChild) {
        for (int n = 0; n < items.size(); ++n) {
            if (items[n]->dynamicChild) {
                delete items[n];
            }
        }
    }
}
//END

