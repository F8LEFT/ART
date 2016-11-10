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
    ui->mCloseButton->setShortcut (Qt::Key_Escape);

    connect(ui->mFindEdit, SIGNAL(returnPressed()),
            this, SLOT(onFindNextBtnClick ()));
    connect(ui->mReplaceEdit, SIGNAL(returnPressed()),
            this, SLOT(onFindNextBtnClick ()));
    connect(ui->mFindEdit, SIGNAL(textChanged(QString)),
            this, SLOT(onFindNextBtnClick()));


    connect(ui->mFindNextButton, SIGNAL(clicked(bool)),
            this, SLOT(onFindNextBtnClick()));
    connect(ui->mFindPreviousButton, SIGNAL(clicked(bool)),
            this, SLOT(onFindPrevBtnClick()));
    connect(ui->mReplaceButton, SIGNAL(clicked(bool)),
            this, SLOT(onReplaceBtnClick()));
    connect(ui->mReplaceNextButton, SIGNAL(clicked(bool)),
            this, SLOT(onReplaceNextBtnClick()));
    connect(ui->mReplaceAllButton, SIGNAL(clicked(bool)),
            this, SLOT(onReplaceAllBtnClick()));

    connect(ui->mCloseButton, SIGNAL(clicked(bool)),
            this, SLOT(onCloseBtnClicked()));
}

FindWidget::~FindWidget()
{
    delete ui;
}

void FindWidget::setFindEditFocus ()
{
    ui->mFindEdit->setFocus ();
    ui->mFindEdit->selectAll ();
}

void FindWidget::setFindText (const QString s)
{
    ui->mFindEdit->setText (s);
    ui->mReplaceEdit->setText ("");
}

void FindWidget::onFindPrevBtnClick()
{
    auto findtext = ui->mFindEdit->text();
    emit find(findtext, QTextDocument::FindBackward);
}


void FindWidget::onFindNextBtnClick ()
{
    auto findtext = ui->mFindEdit->text ();
    emit find (findtext);
}

void FindWidget::onReplaceBtnClick()
{
    auto findtext = ui->mFindEdit->text();
    auto replacetext = ui->mReplaceEdit->text();
    emit replace(findtext, replacetext);
}

void FindWidget::onReplaceNextBtnClick()
{
    auto findtext = ui->mFindEdit->text();
    auto replacetext = ui->mReplaceEdit->text();
    emit replace(findtext, replacetext);
    emit find (findtext);
}

void FindWidget::onReplaceAllBtnClick()
{
    auto findtext = ui->mFindEdit->text();
    auto replacetext = ui->mReplaceEdit->text();
    emit replaceAll(findtext, replacetext);
}

void FindWidget::onCloseBtnClicked ()
{
    emit closeWidget ();
}




