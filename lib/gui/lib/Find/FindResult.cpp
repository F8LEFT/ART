//===- FindResult.cpp - ART-GUI Find ---------------------------*- C++ -*-===//
//
//                     ANDROID REVERSE TOOLKIT
//
// This file is distributed under the GNU GENERAL PUBLIC LICENSE
// V3 License. See LICENSE.TXT for details.
//
//===---------------------------------------------------------------------===//

#include "FindResult.h"
#include "ui_FindResult.h"

FindResult::FindResult(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FindResult)
{
    ui->setupUi(this);
}

FindResult::~FindResult()
{
    delete ui;
}
