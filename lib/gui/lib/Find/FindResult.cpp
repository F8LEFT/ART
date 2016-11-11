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

#include <QMessageBox>
#include <QDir>
#include <QTextCursor>
#include <QTextLayout>
#include <QTextBlock>
#include <QDebug>


FindResult::FindResult(QWidget *parent) :
        QWidget(parent),
        ui(new Ui::FindResult)
{
    ui->setupUi(this);
    ui->mReplaceWidget->hide ();

    connect(ui->mReplaceEdit, SIGNAL(returnPressed()), this, SLOT(onReplaceClick()));
    connect(ui->mReplaceBtn, SIGNAL(clicked(bool)), this, SLOT(onReplaceClick()));
}

FindResult::~FindResult()
{
    delete ui;
}

void FindResult::startNewFind (const QString &subString,const QString &directory,
                               QTextDocument::FindFlags options,
                               bool useRegexp,bool needReplace)
{
    mSubString = subString;
    mSearchPath = directory;
    mOptions = options;
    mUseRegexp = useRegexp;
    mNeedReplace = needReplace;

    if(needReplace)
        ui->mReplaceWidget->show ();
    mThread = new FindThread(this);
    mThread->setFind (subString, directory, options, useRegexp);
    connect(mThread, SIGNAL(newResult(QString,QString,int)),
            this, SLOT(onNewResult(QString,QString,int)), Qt::QueuedConnection);
    mThread->start ();
}

void FindResult::onReplaceClick ()
{
    QMessageBox msg(QMessageBox::Warning,
                    tr("Replace search result"),
                    tr("Do you want to replace all files? This can not undo."),
                    QMessageBox::Ok | QMessageBox::Cancel);
    if(msg.exec() == QMessageBox::Cancel)
        return;


}

void FindResult::onNewResult (QString filePath,QString text,int line)
{
    qDebug() << "SearchResult:" << filePath << " line " << line << " :" << text;
}

// FindThread
FindThread::FindThread(QObject *parent)
        :QThread(parent)
{

}

void FindThread::setFind (const QString &subString,const QString &directory,
                          QTextDocument::FindFlags options,bool useRegexp)
{
    mSubString = subString;
    mSearchPath = directory;
    mOptions = options;
    mUseRegexp = useRegexp;
}

void FindThread::run()
{
    QDir dir(mSearchPath);
    searchDirectory (dir);
    qDebug() << "global Search thread quit";
}

void FindThread::searchDirectory (QDir dir)
{
    if(!dir.exists ())
        return ;
    dir.setFilter (QDir::Dirs | QDir::NoSymLinks);
            foreach(QFileInfo mfi ,dir.entryInfoList())
        {
            if(mfi.fileName()=="." || mfi.fileName() == "..")continue;
            searchDirectory (mfi.absoluteFilePath ());
        }
    dir.setFilter (QDir::Files| QDir::NoSymLinks);
            foreach(QFileInfo mfi ,dir.entryInfoList())
        {
            searchFile (mfi.absoluteFilePath ());
        }
}

void FindThread::searchFile (QString filePath)
{
    QFile file(filePath);
    if (file.open(QFile::ReadOnly | QFile::Text)) {
        QTextDocument document(file.readAll ());
        if(mUseRegexp) {
            QRegExp regExp(mSubString);
            auto cursor = document.find(regExp, 0, mOptions);
            while(!cursor.isNull ()) {
                auto line = currentline (cursor);
                emit newResult (filePath, cursor.block ().text (), line);
                cursor = document.find(regExp, cursor, mOptions);
            }
        } else {
            auto cursor = document.find(mSubString, 0, mOptions);
            while(!cursor.isNull ()) {
                auto line = currentline (cursor);
                emit newResult (filePath, cursor.block ().text (), line);
                cursor = document.find(mSubString, cursor, mOptions);
            }
        }
    }
}

int FindThread::currentline (const QTextCursor &cursor)
{
    QTextLayout *pLayout = cursor.block().layout();
    int nCurpos = cursor.position() - cursor.block().position();
    return pLayout->lineForTextPosition(nCurpos).lineNumber()
           + cursor.block().firstLineNumber() + 1;
}
