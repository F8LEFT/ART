//===- HighlightDefinition.cpp - ART-GUI HighLighter------------*- C++ -*-===//
//
//                     ANDROID REVERSE TOOLKIT
//
// This file is distributed under the GNU GENERAL PUBLIC LICENSE
// V3 License. See LICENSE.TXT for details.
//
//===---------------------------------------------------------------------===//

#include "HighlightDefinition.h"
#include "HighLighterUtil.h"
#include <QDebug>


template<class Element, class Container>
QSharedPointer<Element> createHelper(const QString &name, Container &container) {
    if (name.isEmpty()) {
        // TODO Error
        qDebug() << "GenericHighlighter Element name is empty.";
//        throw HighlighterException(
//                QCoreApplication::translate("GenericHighlighter", "Element name is empty."));
    }

    if (container.contains(name)) {
        // TODO Error
        qDebug() << "GenericHighlighter Duplicate element name" << name;
//        throw HighlighterException(
//                QCoreApplication::translate("GenericHighlighter",
//                                            "Duplicate element name \"%1\".").arg(name));
    }

    return container.insert(name, QSharedPointer<Element>(new Element)).value();
}

template<class Element, class Container>
QSharedPointer<Element>
findHelper(const QString &name, const Container &container) {
    typename Container::const_iterator it = container.find(name);
    if (it == container.end()) {
        // TODO Error
        qDebug() << "GenericHighlighter Name " << name << " not found.";
//        throw HighlighterException(
//                QCoreApplication::translate("GenericHighlighter",
//                                            "Name \"%1\" not found.").arg(name));
    }

    return it.value();
}


HighlightDefinition::HighlightDefinition() :
        m_keywordCaseSensitivity(Qt::CaseSensitive),
        m_singleLineCommentAfterWhiteSpaces(false),
        m_indentationBasedFolding(false) {
    QString s(QLatin1String(".():!+,-<=>%&/;?[]^{|}~\\*, \t"));
            foreach (const QChar &c, s)
            m_delimiters.insert(c);
}

HighlightDefinition::~HighlightDefinition() {}

bool HighlightDefinition::isValid() const {
    return !m_initialContext.isEmpty();
}

QSharedPointer<KeywordList> HighlightDefinition::createKeywordList(const QString &list) {
    return createHelper<KeywordList>(list, m_lists);
}

QSharedPointer<KeywordList> HighlightDefinition::keywordList(const QString &list) {
    return findHelper<KeywordList>(list, m_lists);
}

QSharedPointer<ItemData> HighlightDefinition::createItemData(const QString &itemData) {
    return createHelper<ItemData>(itemData, m_itemsData);
}

QSharedPointer<ItemData> HighlightDefinition::itemData(const QString &itemData) const {
    return findHelper<ItemData>(itemData, m_itemsData);
}

QSharedPointer<Context> HighlightDefinition::createContext(const QString &context) {
    return createHelper<Context>(context, m_contexts);
}

QSharedPointer<Context> HighlightDefinition::context(const QString &context) const {
    return findHelper<Context>(context, m_contexts);
}

void HighlightDefinition::setSingleLineComment(const QString &start) { m_singleLineComment = start; }

const QString &HighlightDefinition::singleLineComment() const { return m_singleLineComment; }

void HighlightDefinition::setCommentAfterWhitespaces(const QString &after) {
    if (after == QLatin1String("afterwhitespace"))
        m_singleLineCommentAfterWhiteSpaces = true;
}

bool HighlightDefinition::isCommentAfterWhiteSpaces() const { return m_singleLineCommentAfterWhiteSpaces; }

void HighlightDefinition::setMultiLineCommentStart(const QString &start) { m_multiLineCommentStart = start; }

const QString &HighlightDefinition::multiLineCommentStart() const { return m_multiLineCommentStart; }

void HighlightDefinition::setMultiLineCommentEnd(const QString &end) { m_multiLineCommentEnd = end; }

const QString &HighlightDefinition::multiLineCommentEnd() const { return m_multiLineCommentEnd; }

void HighlightDefinition::setMultiLineCommentRegion(const QString &region) { m_multiLineCommentRegion = region; }

const QString &HighlightDefinition::multiLineCommentRegion() const { return m_multiLineCommentRegion; }

void HighlightDefinition::removeDelimiters(const QString &characters) {
    for (int i = 0; i < characters.length(); ++i)
        m_delimiters.remove(characters.at(i));
}

void HighlightDefinition::addDelimiters(const QString &characters) {
    for (int i = 0; i < characters.length(); ++i) {
        if (!m_delimiters.contains(characters.at(i)))
            m_delimiters.insert(characters.at(i));
    }
}

bool HighlightDefinition::isDelimiter(const QChar &character) const {
    if (m_delimiters.contains(character))
        return true;
    return false;
}

void HighlightDefinition::setKeywordsSensitive(const QString &sensitivity) {
    if (!sensitivity.isEmpty())
        m_keywordCaseSensitivity = toCaseSensitivity(toBool(sensitivity));
}

Qt::CaseSensitivity HighlightDefinition::keywordsSensitive() const { return m_keywordCaseSensitivity; }

void HighlightDefinition::setIndentationBasedFolding(
        const QString &indentationBasedFolding) { m_indentationBasedFolding = toBool(indentationBasedFolding); }

bool HighlightDefinition::isIndentationBasedFolding() const { return m_indentationBasedFolding; }

const QHash<QString, QSharedPointer<Context>> & HighlightDefinition::context() {
    return m_contexts;
}

