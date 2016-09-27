//===- EditorTab.h - ART-GUI Project Tab ----------------------*- C++ -*-===//
//
//                     ANDROID REVERSE TOOLKIT
//
// This file is distributed under the GNU GENERAL PUBLIC LICENSE
// V3 License. See LICENSE.TXT for details.
//
//===---------------------------------------------------------------------===//
//
// This file defines project tab in workspace tab bar. It helps user to
// edit project file.
//
//===----------------------------------------------------------------------===//
#ifndef EDITORTAB_H
#define EDITORTAB_H

#include <QWidget>

namespace Ui {
class EditorTab;
}

class EditorTab : public QWidget
{
    Q_OBJECT

public:
    explicit EditorTab(QWidget *parent = 0);
    ~EditorTab();

private:
    Ui::EditorTab *ui;
};

#endif // EDITORTAB_H
