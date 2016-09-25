//===- WorkSpace.h - ART-GUI WorkSpace --------------------------*- C++ -*-===//
//
//                     ANDROID REVERSE TOOLKIT
//
// This file is distributed under the GNU GENERAL PUBLIC LICENSE
// V3 License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file defines ART-GUI WorkSpace dialog's behaviour. WorkSpace widget
// is the central widget of MainWindow. It is the main work area of this
// sofe.
//
//===----------------------------------------------------------------------===//
#ifndef WORKSPACE_H
#define WORKSPACE_H

#include <QWidget>

namespace Ui {
class WorkSpace;
}

class WorkSpace : public QWidget
{
    Q_OBJECT

public:
    explicit WorkSpace(QWidget *parent = 0);
    ~WorkSpace();

private:
    Ui::WorkSpace *ui;
};

#endif // WORKSPACE_H
