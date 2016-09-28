//===- BookMark.cpp - ART-GUI BookMark -------------------------*- C++ -*-===//
//
//                     ANDROID REVERSE TOOLKIT
//
// This file is distributed under the GNU GENERAL PUBLIC LICENSE
// V3 License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
#include <utils/CmdMsgUtil.h>
#include "BookMark/BookMark.h"
#include "ui_BookMark.h"


BookMark::BookMark(QString file, QWidget *parent) :
        QWidget(parent),
        ui(new Ui::BookMark)
{
    ui->setupUi(this);
    mFilePath = file;
}

BookMark::~BookMark()
{
    delete ui;
}

void BookMark::setFileName(QString fp)
{
    mFileName = fp;
    ui->mFileLabel->setText(mFileName);
}

void BookMark::setHint(QString hint)
{
    mHint = hint.trimmed();
    ui->mHintLabel->setText(hint);
}

void BookMark::setLine(int line)
{
    mLine = line;
    ui->mLineLabel->setText(QString().number(mLine));
}

QString BookMark::fileName()
{
    return mFileName;
}

QString BookMark::filePath()
{
    return mFilePath;
}

QString BookMark::hint()
{
    return mHint;
}

int BookMark::line()
{
    return mLine;
}

void BookMark::onClicked(BookMark *pBook)
{
    QStringList args;
    args<< mFilePath
        << ui->mLineLabel->text();
    cmdexec("OpenFile", args);
}