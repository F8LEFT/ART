//===- SmaliHighlight.h - ART-GUI HighLighter--------------------*- C++ -*-===//
//
//                     ANDROID REVERSE TOOLKIT
//
// This file is distributed under the GNU GENERAL PUBLIC LICENSE
// V3 License. See LICENSE.TXT for details.
//
//===---------------------------------------------------------------------===//
//
// SmaliHighlight is used to highlight smali file
//
//===----------------------------------------------------------------------===//



#ifndef PROJECT_SMALIHIGHLIGHT_H
#define PROJECT_SMALIHIGHLIGHT_H
#include <QSyntaxHighlighter>
#include <HighLighter/HighLightConfig.h>


class SmaliHighlight: public QSyntaxHighlighter
{
    Q_OBJECT

public:
    SmaliHighlight(QTextDocument *parent, QString fileName,
                   HighLightConfig* config);

protected:
    void highlightBlock(const QString &text) Q_DECL_OVERRIDE;

private:
    QMap<HighLightConfig::FORMAT , QTextCharFormat> &mFormatMap;

};


#endif //PROJECT_SMALIHIGHLIGHT_H
