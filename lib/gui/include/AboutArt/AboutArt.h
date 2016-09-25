//===- AboutArt.h - ART-GUI MainWindow --------------------------*- C++ -*-===//
//
//                     ANDROID REVERSE TOOLKIT
//
// This file is distributed under the GNU GENERAL PUBLIC LICENSE
// V3 License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file defines ART-GUI AboutArt dialog's behaviour.
//
//===----------------------------------------------------------------------===//
#ifndef ABOUTART_H
#define ABOUTART_H

#include <QDialog>

namespace Ui {
class AboutArt;
}

class AboutArt : public QDialog
{
    Q_OBJECT

public:
    explicit AboutArt(QWidget *parent = 0);
    ~AboutArt();

private:
    Ui::AboutArt *ui;
};

#endif // ABOUTART_H
