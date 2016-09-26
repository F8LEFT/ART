//===- ProjectTab.cpp - ART-GUI Project Tab --------------------*- C++ -*-===//
//
//                     ANDROID REVERSE TOOLKIT
//
// This file is distributed under the GNU GENERAL PUBLIC LICENSE
// V3 License. See LICENSE.TXT for details.
//
//===---------------------------------------------------------------------===//
#include "ProjectTab/ProjectTab.h"
#include "ui_ProjectTab.h"

ProjectTab::ProjectTab(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ProjectTab)
{
    ui->setupUi(this);
}

ProjectTab::~ProjectTab()
{
    delete ui;
}
