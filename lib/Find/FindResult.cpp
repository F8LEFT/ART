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

#include <utils/StringUtil.h>
#include <utils/ProjectInfo.h>

#include <QMessageBox>
#include <QDir>
#include <QTextCursor>
#include <QTextLayout>
#include <QTextBlock>
#include <QDebug>
#include <utils/CmdMsgUtil.h>


FindResult::FindResult(QWidget *parent) :
        QWidget(parent),
        ui(new Ui::FindResult)
{
    ui->setupUi(this);
    ui->mReplaceWidget->hide ();

    ui->mResultTree->setUniformRowHeights (true);

    connect(ui->mReplaceEdit, SIGNAL(returnPressed()), this, SLOT(onReplaceClick()));
    connect(ui->mReplaceBtn, SIGNAL(clicked(bool)), this, SLOT(onReplaceClick()));

    connect(ui->mResultTree, SIGNAL(itemDoubleClicked(QTreeWidgetItem*,int)),
            this, SLOT(onTreeFileOpen(QTreeWidgetItem*,int)));
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
    mThread = new FindThread();
    mThread->setFind (subString, directory, options, useRegexp);
    connect(mThread, SIGNAL(newResult(QString,QStringList,QList<int>)),
            this, SLOT(onNewResult(QString,QStringList,QList<int>)));
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
    QString replace = ui->mReplaceEdit->text ();

    QStringList allfiles;
    for(QTreeWidgetItemIterator it(ui->mResultTree); *it; it++) {
        if((*it)->type () != treeFileItemType)
            continue;
        QString filePath = (*it)->data (0, Qt::UserRole).toString ();
        allfiles << filePath;
    }
    auto thread = new ReplaceThread();
    thread->setReplace (mSubString, replace, mOptions, mUseRegexp);
    thread->setFiles(allfiles);
    thread->start ();
}

void FindResult::onNewResult (QString filePath,QStringList text,QList<int> line)
{
    QString projectRoot = GetProjectsProjectPath (projinfo ("ProjectName"));
    QFileInfo rootInfo(projectRoot);
    QFileInfo fileInfo(filePath);

    QString canPath = fileInfo.absoluteFilePath ().remove (
            rootInfo.absoluteFilePath () + "/");

    auto fileroot = new QTreeWidgetItem(
            QStringList() << canPath + "(" + QString::number (text.size ()) + ")",
            treeFileItemType);
    fileroot->setData (0, Qt::UserRole, filePath);

    ui->mResultTree->addTopLevelItem (fileroot);

    QList<QTreeWidgetItem*> items;
    auto itLine = line.begin (), itLineEnd = line.end ();
    auto itText = text.begin (), itTextEnd = text.end ();
    for(;itLine != itLineEnd && itText != itTextEnd;
         itLine++, itText++) {
        QStringList itemData;
        itemData << *itText + "  --- line " + QString::number (*itLine);
        auto item = new QTreeWidgetItem(itemData, treeLineItemType);
        item->setData (0, Qt::UserRole, *itLine);
        items.append (item);
    }

    fileroot->addChildren (items);
}

void FindResult::onTreeFileOpen (QTreeWidgetItem *item,int column)
{
    if(item == nullptr || item->type () != treeLineItemType) {
        return;
    }
    QString filePath = item->parent ()->data (0, Qt::UserRole).toString ();
    int line = item->data (0, Qt::UserRole).toInt ();

    QStringList args;
    args<< filePath
        << QString::number (line);
    cmdexec("OpenFile", args);
}


// FindThread
FindThread::FindThread(QObject *parent)
        :QThread(parent)
{
    connect(this, SIGNAL(finished()), this, SLOT(deleteLater()));
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
    if(QFileInfo(mSearchPath).isFile ()) {
        searchFile (mSearchPath);
    } else {
        QDir dir(mSearchPath);
        searchDirectory (dir);
    }
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

            QStringList text;
            QList<int> lines;
            while(!cursor.isNull ()) {
                text.push_back (cursor.block ().text ());
                lines.push_back (currentline (cursor));
                cursor = document.find(regExp, cursor, mOptions);
            }
            if(!text.isEmpty ()) {
                 newResult (filePath, text, lines);
            }
        } else {
            auto cursor = document.find(mSubString, 0, mOptions);

            QStringList text;
            QList<int> lines;
            while(!cursor.isNull ()) {
                text.push_back (cursor.block ().text ());
                lines.push_back (currentline (cursor));
                cursor = document.find(mSubString, cursor, mOptions);
            }
            if(!text.isEmpty ()) {
                 newResult (filePath, text, lines);
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

ReplaceThread::ReplaceThread (QObject *parent)
        : QThread (parent)
{
    connect(this, SIGNAL(finished()), this, SLOT(deleteLater()));
}

void ReplaceThread::setReplace (const QString &subString,const QString &replaceWith,
                                QTextDocument::FindFlags options, bool useRegexp)
{
    mSubString = subString;
    mReplaceWith = replaceWith;
    mOptions = options;
    mUseRegexp = useRegexp;
}

void ReplaceThread::run ()
{
            foreach(QString file, mFiles) {
            replaceFile (file);
        }
    qDebug() << "global Replace thread quit";
}

bool ReplaceThread::replaceFile (const QString &filePath)
{
    QFile file(filePath);
    if(!file.open (QFile::ReadOnly | QFile::Text)) {
        return false;
    }

    QTextDocument document(file.readAll ());

    if(mUseRegexp) {
        QRegExp regExp(mSubString);
        auto cursor = document.find(regExp, 0, mOptions);
        while(!cursor.isNull ()) {
            cursor.insertText (mReplaceWith);
            cursor = document.find(regExp, cursor, mOptions);
        }
    } else {
        auto cursor = document.find(mSubString, 0, mOptions);
        while(!cursor.isNull ()) {
            cursor.insertText (mReplaceWith);
            cursor = document.find(mSubString, cursor, mOptions);
        }
    }
    file.close ();

    if(!file.open (QFile::WriteOnly | QFile::Truncate | QFile::Text)) {
        return false;
    }

    QTextStream out(&file);
    out<<document.toPlainText ();
    out.flush();
    file.close();

    return true;
}
