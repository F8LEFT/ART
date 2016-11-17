//===- AboutArt.cpp - ART-GUI About Dialog ----------------------*- C++ -*-===//
//
//                     ANDROID REVERSE TOOLKIT
//
// This file is distributed under the GNU GENERAL PUBLIC LICENSE
// V3 License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
#include "AboutArt/AboutArt.h"
#include "ui_AboutArt.h"

#include <utils/StringUtil.h>
#include <QDesktopServices>
#include <QUrl>

AboutArt::AboutArt(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AboutArt)
{
    ui->setupUi(this);
    setWindowTitle ("About Android Reverse ToolKit");
    setWindowFlags(windowFlags()& ~Qt::WindowMaximizeButtonHint);
    setFixedSize(this->width(), this->height());

    ui->lAboutTitle->setText("About ART v"
                             + QString::number (GetCompileMajor ()));
    ui->lAboutText->setText(
        "ART version: " + GetCompileVersion () + "<br>" +
        "<br>Author: " + "F8LEFT - CURRWIN<br>" +
        "<br>Compiled on:<br>" + ToDateString (GetCompileDate ()) + ", "
             __TIME__ + "<br>" +
        "<br>This program is free and opensource software. Source code can "
            "be found in <a href=\"https://github.com/F8LEFT/ART\">"
            "https://github.com/F8LEFT/ART</a>. You can redistribute "
            "it and/or modify it under the terms of the GNU General Public "
            "License as published by the Free Software Foundation, either "
            "version 3 of the License, or (at your option) any later version."
            "<br>");
    ui->lAboutText->setOpenExternalLinks (true);

}

AboutArt::~AboutArt()
{
    delete ui;
}

