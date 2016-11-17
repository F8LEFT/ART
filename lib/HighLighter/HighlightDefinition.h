//===- HighlightDefinition.h - ART-GUI HighLighter--------------*- C++ -*-===//
//
//                     ANDROID REVERSE TOOLKIT
//
// This file is distributed under the GNU GENERAL PUBLIC LICENSE
// V3 License. See LICENSE.TXT for details.
//
//===---------------------------------------------------------------------===//
//
// HighlightDefination save highlight define
//
//===----------------------------------------------------------------------===//

#ifndef PROJECT_HIGHLIGHTDEFINITION_H
#define PROJECT_HIGHLIGHTDEFINITION_H

#include "KeywordList.h"
#include "ItemData.h"
#include "Context.h"
#include <QString>
#include <QSharedPointer>
#include <QtWidgets/QSystemTrayIcon>

class HighlightDefinition {
public:
    HighlightDefinition();

    ~HighlightDefinition();

    bool isValid() const;

    QSharedPointer<KeywordList> createKeywordList(const QString &list);

    QSharedPointer<KeywordList> keywordList(const QString &list);

    QSharedPointer<ItemData> createItemData(const QString &itemData);

    QSharedPointer<ItemData> itemData(const QString &itemData) const;

    QSharedPointer<Context> createContext(const QString &context);

    QSharedPointer<Context> context(const QString& context) const;

    const QHash<QString, QSharedPointer<Context>> & context();

    void setKeywordsSensitive(const QString &sensitivity);

    Qt::CaseSensitivity keywordsSensitive() const;

    void addDelimiters(const QString &characters);

    void removeDelimiters(const QString &characters);

    bool isDelimiter(const QChar &character) const;

    void setSingleLineComment(const QString &start);

    const QString &singleLineComment() const;

    void setCommentAfterWhitespaces(const QString &after);

    bool isCommentAfterWhiteSpaces() const;

    void setMultiLineCommentStart(const QString &start);

    const QString &multiLineCommentStart() const;

    void setMultiLineCommentEnd(const QString &end);

    const QString &multiLineCommentEnd() const;

    void setMultiLineCommentRegion(const QString &region);

    const QString &multiLineCommentRegion() const;

    void setIndentationBasedFolding(const QString &indentationBasedFolding);

    bool isIndentationBasedFolding() const;

private:
    Q_DISABLE_COPY(HighlightDefinition)

    QHash<QString, QSharedPointer<KeywordList> > m_lists;
    QHash<QString, QSharedPointer<ItemData> > m_itemsData;
    QHash<QString, QSharedPointer<Context>> m_contexts;


    QString m_initialContext;

    QString m_singleLineComment;

    QString m_multiLineCommentStart;
    QString m_multiLineCommentEnd;
    QString m_multiLineCommentRegion;

    Qt::CaseSensitivity m_keywordCaseSensitivity;

    bool m_singleLineCommentAfterWhiteSpaces;
    bool m_indentationBasedFolding;

    QSet<QChar> m_delimiters;
};

#endif //PROJECT_HIGHLIGHTDEFINITION_H
