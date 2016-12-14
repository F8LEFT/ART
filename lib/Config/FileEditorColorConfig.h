//===- FileEditorColorConfig.h - ART-GUI Config ----------------*- C++ -*-===//
//
//                     ANDROID REVERSE TOOLKIT
//
// This file is distributed under the GNU GENERAL PUBLIC LICENSE
// V3 License. See LICENSE.TXT for details.
//
//===---------------------------------------------------------------------===//
//
// Theme EditorColorRole config.
//
//===----------------------------------------------------------------------===//


#ifndef ANDROIDREVERSETOOLKIT_FILEEDITORCOLORCONFIG_H
#define ANDROIDREVERSETOOLKIT_FILEEDITORCOLORCONFIG_H

#include "ColorItem.h"


#include <Theme>

#include <QWidget>
#include <QList>
#include <QTableWidget>


class FileEditorColorConfig: public QWidget
{
    Q_OBJECT
public:
    FileEditorColorConfig(QWidget* parent = Q_NULLPTR);

    void save();

    void setTheme(KSyntaxHighlighting::Theme theme);

signals:
    void formatUpdate();

private:
    KSyntaxHighlighting::Theme m_theme;
    QTableWidget* m_colorTable;
};


#endif //ANDROIDREVERSETOOLKIT_FILEEDITORCOLORCONFIG_H
