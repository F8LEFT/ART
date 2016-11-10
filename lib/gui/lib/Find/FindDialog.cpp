//===- FindDialog.cpp - ART-GUI Find ---------------------------*- C++ -*-===//
//
//                     ANDROID REVERSE TOOLKIT
//
// This file is distributed under the GNU GENERAL PUBLIC LICENSE
// V3 License. See LICENSE.TXT for details.
//
//===---------------------------------------------------------------------===//
#include "Find/FindDialog.h"
#include "ui_FindDialog.h"

FindDialog::FindDialog(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FindDialog)
{
    ui->setupUi(this);

    ui->mFilterList->addItem ("Project");
    ui->mFilterList->setCurrentIndex (0);

    // signal slots
    connect(ui->mSearchTerm, SIGNAL(returnPressed()), this, SLOT(onSearchStart()));
    connect(ui->mSearchButton, SIGNAL(clicked(bool)), this, SLOT(onSearchStart()));
//    connect(ui->mReplaceButton, SIGNAL(clicked(bool)), this, SLOT(onSearchStart()));

}

FindDialog::~FindDialog()
{
    delete ui;
}

void FindDialog::onSearchStart ()
{

}

