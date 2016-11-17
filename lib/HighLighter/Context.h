//===- Context.h - ART-GUI HighLighter--------------------------*- C++ -*-===//
//
//                     ANDROID REVERSE TOOLKIT
//
// This file is distributed under the GNU GENERAL PUBLIC LICENSE
// V3 License. See LICENSE.TXT for details.
//
//===---------------------------------------------------------------------===//
//
// Context defines xml key.
//
//===----------------------------------------------------------------------===//


#ifndef PROJECT_CONTEXT_H
#define PROJECT_CONTEXT_H

#include <QRegExp>
#include <QString>
class HighlightDefinition;

class Context {
public:
    enum CtxType {
        Keyword,
        RegExpr,
    };
public:
    void setName(const QString& name);
    const QString &name();

    void setRegion(const QString &begin);
    const QString& region();

    void setType(CtxType ctx);
    CtxType type();

    void setAttribute(const QString& attr);
    const QString& attribute();

    const QRegExp & getRegExpr(HighlightDefinition *define);
private:
    QString m_name;

    QString m_Region;
    QString m_attribute;
    CtxType m_type;

    bool m_firstNonSpace;
    bool m_consumesNonSpace;

    QRegExp pattern;
};

#endif //PROJECT_CONTEXT_H
