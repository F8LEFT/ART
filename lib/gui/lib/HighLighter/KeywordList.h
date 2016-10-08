//===- KeywordList.h - ART-GUI HighLighter-----------------------*- C++ -*-===//
//
//                     ANDROID REVERSE TOOLKIT
//
// This file is distributed under the GNU GENERAL PUBLIC LICENSE
// V3 License. See LICENSE.TXT for details.
//
//===---------------------------------------------------------------------===//
//
//
//
//===----------------------------------------------------------------------===//


#ifndef PROJECT_KEYWORDLIST_H
#define PROJECT_KEYWORDLIST_H

#include <QSet>
#include <QString>
class KeywordList {
public:
    void addKeyword(const QString &keyword);
    bool isKeyword(const QString &keyword, Qt::CaseSensitivity sensitivity = Qt::CaseSensitive) const;
    const QSet<QString>& keyword();
private:
    QSet<QString> m_keywords;
};

#endif //PROJECT_KEYWORDLIST_H
