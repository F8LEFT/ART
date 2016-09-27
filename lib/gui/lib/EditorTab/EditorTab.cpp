//===- EditorTab.cpp - ART-GUI Editor Tab --------------------*- C++ -*-===//
//
//                     ANDROID REVERSE TOOLKIT
//
// This file is distributed under the GNU GENERAL PUBLIC LICENSE
// V3 License. See LICENSE.TXT for details.
//
//===---------------------------------------------------------------------===//
#include "EditorTab/EditorTab.h"
#include "ui_EditorTab.h"

EditorTab::EditorTab(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::EditorTab)
{
    ui->setupUi(this);
}

EditorTab::~EditorTab()
{
    delete ui;
}
