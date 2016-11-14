//===- FindConfig.cpp - ART-GUI Find ---------------------------*- C++ -*-===//
//
//                     ANDROID REVERSE TOOLKIT
//
// This file is distributed under the GNU GENERAL PUBLIC LICENSE
// V3 License. See LICENSE.TXT for details.
//
//===---------------------------------------------------------------------===//

#include "FindConfig.h"
#include "ui_FindConfig.h"

#include <QtCore/QFileInfo>


FindConfig::FindConfig(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FindConfig)
{
    ui->setupUi(this);

    ui->mFilterList->addItem (tr("Project"));
    ui->mFilterList->addItem (tr("Selected Directory") + " \"null\"");
    ui->mFilterList->setCurrentIndex (0);

    // signal slots
    connect(ui->mSearchTerm, SIGNAL(returnPressed()), this, SLOT(onSearchStart()));
    connect(ui->mSearchButton, SIGNAL(clicked(bool)), this, SLOT(onSearchStart()));
    connect(ui->mReplaceButton, SIGNAL(clicked(bool)), this, SLOT(onReplaceStart()));
}

FindConfig::~FindConfig()
{
    delete ui;
}

void FindConfig::reset (const QString &root, const QString &selectdir)
{
    ui->mFilterList->setItemData (0, root);
    ui->mFilterList->setItemData (1, selectdir);
    if(root != selectdir) {
        ui->mFilterList->setCurrentIndex (1);
    } else {
        ui->mFilterList->setCurrentIndex (0);
    }
    QFileInfo selectFInfo(selectdir);
    if(selectFInfo.isFile ()) {
        ui->mFilterList->setItemText (1, tr("Selected File") +
                " \"" + selectFInfo.fileName () + "\"");
    } else {
        ui->mFilterList->setItemText (1, tr("Selected Directory") +
                                         " \"" + selectFInfo.fileName () + "\"");
    }

    ui->mSearchTerm->clear ();
    ui->mMatchCaseCheckBox->setChecked (false);
    ui->mWholeWordsCheckBox->setChecked (false);
    ui->mRegexpCheckBox->setChecked (false);
}

void FindConfig::onSearchStart ()
{
    onSearch(false);
}

void FindConfig::onReplaceStart ()
{
    onSearch(true);
}

void FindConfig::onSearch (bool needReplace)
{
    QString directory = ui->mFilterList->currentData ().toString ();
    if(directory.isEmpty ()) {
        return;
    }

    auto findtext = ui->mSearchTerm->text ();
    if(findtext.isEmpty ()) {
        return;
    }

    QTextDocument::FindFlags options = 0;

    if(ui->mWholeWordsCheckBox->isChecked ()) {
        options |= QTextDocument::FindWholeWords;
    }
    if(ui->mMatchCaseCheckBox->isChecked ()) {
        options |= QTextDocument::FindCaseSensitively;
    }
    bool useRegexp = ui->mRegexpCheckBox->isChecked ();

    reset (ui->mFilterList->itemData (0).toString (),
           ui->mFilterList->itemData (0).toString ());

    emit startNewFind (findtext, directory, options, useRegexp, needReplace);
}

