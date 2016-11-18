//===- FileEditor.h - ART-GUI Config ---------------------------*- C++ -*-===//
//
//                     ANDROID REVERSE TOOLKIT
//
// This file is distributed under the GNU GENERAL PUBLIC LICENSE
// V3 License. See LICENSE.TXT for details.
//
//===---------------------------------------------------------------------===//
//
// Set Text Editor config.
//
//===----------------------------------------------------------------------===//
#ifndef FILEEDITOR_H
#define FILEEDITOR_H

#include "FileSchemeConfig.h"
#include "HighLighter/HighLightConfig.h"

#include <QWidget>
#include <QList>


namespace Ui {
class FileEditor;
}

class FileEditor : public QWidget
{
    Q_OBJECT

public:
    explicit FileEditor(QWidget *parent = 0);
    ~FileEditor();
    void save();

private:
    Ui::FileEditor *ui;
    QList<FileSchemeConfig*> mTabs;

};


#endif // FILEEDITOR_H
