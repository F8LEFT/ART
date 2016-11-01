//===- FindWidget.cpp - ART-GUI Find ---------------------------*- C++ -*-===//
//
//                     ANDROID REVERSE TOOLKIT
//
// This file is distributed under the GNU GENERAL PUBLIC LICENSE
// V3 License. See LICENSE.TXT for details.
//
//===---------------------------------------------------------------------===//

#include "Find/FindWidget.h"
#include "ui_FindWidget.h"

FindWidget::FindWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FindWidget)
{
    ui->setupUi(this);
}

FindWidget::~FindWidget()
{
    delete ui;
}
