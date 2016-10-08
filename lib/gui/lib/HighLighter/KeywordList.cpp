//===- KeywordList.cpp - ART-GUI HighLighter--------------------*- C++ -*-===//
//
//                     ANDROID REVERSE TOOLKIT
//
// This file is distributed under the GNU GENERAL PUBLIC LICENSE
// V3 License. See LICENSE.TXT for details.
//
//===---------------------------------------------------------------------===//


#include "KeywordList.h"


void KeywordList::addKeyword(const QString &keyword) {
    if (keyword.isEmpty())
        return;

    m_keywords.insert(keyword);
}

bool KeywordList::isKeyword(const QString &keyword, Qt::CaseSensitivity sensitivity) const {
    if (keyword.isEmpty())
        return false;

    if (sensitivity == Qt::CaseSensitive) {
        return m_keywords.contains(keyword);
    } else {
                foreach (const QString &s, m_keywords)
                if (keyword.compare(s, Qt::CaseInsensitive) == 0)
                    return true;
        return false;
    }
}

const QSet<QString> &KeywordList::keyword() {
    return m_keywords;
}
