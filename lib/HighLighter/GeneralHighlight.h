//===- GeneralHighlight.h - ART-GUI HighLighter-----------------*- C++ -*-===//
//
//                     ANDROID REVERSE TOOLKIT
//
// This file is distributed under the GNU GENERAL PUBLIC LICENSE
// V3 License. See LICENSE.TXT for details.
//
//===---------------------------------------------------------------------===//
//
// GeneralHighlight read highlight defination from xml
//
//===----------------------------------------------------------------------===//


#ifndef PROJECT_GENERALHIGHLIGHT_H
#define PROJECT_GENERALHIGHLIGHT_H

#include <QSyntaxHighlighter>
#include <QTextCharFormat>
#include <QHash>
#include "HighLighterXmlReader.h"

class GeneralHighlight : public QSyntaxHighlighter
{
    Q_OBJECT

public:
    GeneralHighlight(QTextDocument *parent, QString fileName);

protected:
    void highlightBlock(const QString &text) Q_DECL_OVERRIDE;

private:
    // Xml Reader
    QSharedPointer<HighlightDefinition> definition;
};

#endif //PROJECT_GENERALHIGHLIGHT_H
