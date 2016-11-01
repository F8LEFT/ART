//===- FindDialog.h - ART-GUI Find -----------------------------*- C++ -*-===//
//
//                     ANDROID REVERSE TOOLKIT
//
// This file is distributed under the GNU GENERAL PUBLIC LICENSE
// V3 License. See LICENSE.TXT for details.
//
//===---------------------------------------------------------------------===//
//
// Show find dialog and search all project file.
//
//===----------------------------------------------------------------------===//

#ifndef FINDDIALOG_H
#define FINDDIALOG_H

#include <QWidget>

namespace Ui {
class FindDialog;
}

class FindDialog : public QWidget
{
    Q_OBJECT

public:
    explicit FindDialog(QWidget *parent = 0);
    ~FindDialog();


private:
    Ui::FindDialog *ui;
};

#endif // FINDDIALOG_H
