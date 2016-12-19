//===- Environment.cpp - ART-GUI Config --------------------------*- C++ -*-===//
//
//                     ANDROID REVERSE TOOLKIT
//
// This file is distributed under the GNU GENERAL PUBLIC LICENSE
// V3 License. See LICENSE.TXT for details.
//
//===---------------------------------------------------------------------===//
#include "Environment.h"
#include "ui_Environment.h"

Environment::Environment(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Environment)
{
    ui->setupUi(this);
}

Environment::~Environment()
{
    delete ui;
}

void Environment::save()
{

}
