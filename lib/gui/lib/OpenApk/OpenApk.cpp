//===- OpenApk.cpp - ART-GUI OpenApk Dialog --------------------*- C++ -*-===//
//
//                     ANDROID REVERSE TOOLKIT
//
// This file is distributed under the GNU GENERAL PUBLIC LICENSE
// V3 License. See LICENSE.TXT for details.
//
//===---------------------------------------------------------------------===//
#include "OpenApk/OpenApk.h"
#include "ui_OpenApk.h"

OpenApk::OpenApk(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::OpenApk)
{
    ui->setupUi(this);
}

OpenApk::~OpenApk()
{
    delete ui;
}
