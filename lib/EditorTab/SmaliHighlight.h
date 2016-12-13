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

#include <Theme>

#include <QSyntaxHighlighter>


class SmaliHighlight: public QSyntaxHighlighter {
Q_OBJECT

public:
    SmaliHighlight(QTextDocument *parent);

    ~SmaliHighlight();

    void setTheme(const KSyntaxHighlighting::Theme &theme);

protected:
    void highlightBlock(const QString &text) Q_DECL_OVERRIDE;

private:
    KSyntaxHighlighting::Theme m_theme;

    QMap<KSyntaxHighlighting::Theme::TextStyle, QTextCharFormat> mFormatMap;
};


#endif //PROJECT_SMALIHIGHLIGHT_H
