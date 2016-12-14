//===- FileFontConfig.h - ART-GUI Config ----------------*- C++ -*-===//
//
//                     ANDROID REVERSE TOOLKIT
//
// This file is distributed under the GNU GENERAL PUBLIC LICENSE
// V3 License. See LICENSE.TXT for details.
//
//===---------------------------------------------------------------------===//
//
// Editor Font Config
//
//===----------------------------------------------------------------------===//

#ifndef FILEFONTCONFIG_H
#define FILEFONTCONFIG_H

#include <Repository>
#include <Theme>

#include <QFontComboBox>
#include <QWidget>
#include <QCheckBox>

class FileFontConfig : public QWidget
{
    Q_OBJECT

public:
    explicit FileFontConfig(QWidget *parent = 0);
    ~FileFontConfig();

    QFont getFont();
    void setFont(const QFont& font);

signals:
    void formatUpdate(const QFont& font);


protected slots:
    void fontUpdate();

private:
    KSyntaxHighlighting::Theme m_theme;

    QFontComboBox* m_fontComboBox;
    QComboBox* m_fontSizeComboBox;
    QCheckBox* m_antialis;

};

#endif // FILEFONTCONFIG_H
