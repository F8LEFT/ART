//===- ProjectTab.h - ART-GUI Project Tab ----------------------*- C++ -*-===//
//
//                     ANDROID REVERSE TOOLKIT
//
// This file is distributed under the GNU GENERAL PUBLIC LICENSE
// V3 License. See LICENSE.TXT for details.
//
//===---------------------------------------------------------------------===//
//
// This file defines project tab in workspace tab bar. It helps user to
// choose project to open or change project setting.
//
//===----------------------------------------------------------------------===//
#ifndef PROJECTTAB_H
#define PROJECTTAB_H

#include <QWidget>

namespace Ui {
class ProjectTab;
}

class ProjectTab : public QWidget
{
    Q_OBJECT

public:
    explicit ProjectTab(QWidget *parent = 0);
    ~ProjectTab();

private:
    Ui::ProjectTab *ui;
};

#endif // PROJECTTAB_H
