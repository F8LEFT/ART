//===- WorkSpace.cpp - ART-GUI WorkSpace ------------------------*- C++ -*-===//
//
//                     ANDROID REVERSE TOOLKIT
//
// This file is distributed under the GNU GENERAL PUBLIC LICENSE
// V3 License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
#include "WorkSpace/WorkSpace.h"
#include "ui_WorkSpace.h"

WorkSpace::WorkSpace(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WorkSpace)
{
    ui->setupUi(this);
}

WorkSpace::~WorkSpace()
{
    delete ui;
}
