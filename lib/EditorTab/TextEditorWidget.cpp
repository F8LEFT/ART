//===- TextEditorWidget.cpp - ART-GUI TextEditorWidget Tab ---------------*- C++ -*-===//
//
//                     ANDROID REVERSE TOOLKIT
//
// This file is distributed under the GNU GENERAL PUBLIC LICENSE
// V3 License. See LICENSE.TXT for details.
//
//===---------------------------------------------------------------------===//
#include "TextEditorWidget.h"

#include "SmaliEditor.h"
#include "CodeEditor.h"

#include <utils/Configuration.h>

#include <QTextStream>
#include <QtConcurrent/QtConcurrent>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QVBoxLayout>
#include <QFileInfo>
#include <QWidget>


TextEditorWidget::TextEditorWidget(QWidget *parent) :
        QWidget(parent),
        mFileEdit(Q_NULLPTR)
{
    mFileChangedTimer = new QTimer(this);
    mFileReloadTimer = new QTimer(this);
    mFileReloadTimer->setSingleShot (true);
    mFindWidget = new FindWidget(this);

    mFileChangedTimer->start(60*1000);

    connect(this, SIGNAL(readText(QString)), this, SLOT(setText(QString)));
    connect(this, SIGNAL(readLine(QString)), this, SLOT(appendLine(QString)));
    connect(this, SIGNAL(readEnd()), this, SLOT(readFileEnd()));

    connect(mFileChangedTimer, SIGNAL(timeout()), this, SLOT(textChangedTimeOut()));
    connect(mFileReloadTimer, SIGNAL(timeout()), this, SLOT(fileReloadTimeOut ()));

    connect(mFileEdit, SIGNAL(onCTRL_F_Click()), this, SLOT(onFindAction ()));
    connect(mFileEdit, SIGNAL(textChanged()), this, SLOT(textChanged ()));

    // FindWidget signal
    connect(mFindWidget, SIGNAL(find(QString,QTextDocument::FindFlags)),
            this, SLOT(onFind(QString,QTextDocument::FindFlags)));
    connect(mFindWidget, SIGNAL(replace(QString,QString)),
            this, SLOT(onReplace(QString,QString)));
    connect(mFindWidget, SIGNAL(replaceAll(QString,QString)),
            this, SLOT(onReplaceAll(QString,QString)));
    connect(mFindWidget, SIGNAL(closeWidget()),
            this, SLOT(onFindClose ()));

    mFileWatcher = new QFileSystemWatcher(this);
    connect(mFileWatcher, SIGNAL(fileChanged(QString)),
            this, SLOT(onFileChange (QString)));


    mFindWidget->hide ();
    loadFromConfig();

}

TextEditorWidget::~TextEditorWidget()
{
    closeFile();
    saveToConfig();
}


bool TextEditorWidget::openFile(QString filePath, int iLine)
{
    if(!QFileInfo::exists(filePath)) {
        return false;
    }
    Q_ASSERT(mFileEdit == Q_NULLPTR && "invoke again?");
    if(filePath.endsWith(".smali")) {
        mFileEdit = new SmaliEditor(this);
    } else {
        mFileEdit = new CodeEditor(this);
    }
    if(!mFileEdit->openFile(filePath, iLine)) {
        mFileEdit->deleteLater();
        return false;
    }

    mFileWatcher->addPath(filePath);
    mFindWidget->setFilePath(filePath);

    // setup editor layout
    QVBoxLayout* vLayout = new QVBoxLayout(this);
    vLayout->setContentsMargins(0, 0, 0, 0);
    vLayout->addWidget(mFileEdit);
    vLayout->addWidget(mFindWidget);
    setLayout(vLayout);
    return true;
}

bool TextEditorWidget::saveFile()
{
    if(!mFileEdit->saveFile()) {
        return false;
    }
    notReload = true;
    return true;
}

bool TextEditorWidget::reload()
{
    return mFileEdit->reload();
}

void TextEditorWidget::closeFile()
{
    saveFile();
    mFileEdit->deleteLater();
    mFileEdit = Q_NULLPTR;
}

void TextEditorWidget::loadFromConfig()
{
//    Configuration *config = Config();
}

void TextEditorWidget::saveToConfig()
{
//    Configuration *config = Config();
}


int TextEditorWidget::currentLine ()
{
    return mFileEdit->currentLine ();
}

void TextEditorWidget::setText (const QString &text)
{
    mFileEdit->setPlainText (text);
}

void TextEditorWidget::appendLine(const QString& line)
{
    mFileEdit->appendPlainText(line);
}

void TextEditorWidget::readFileEnd()
{
    mFileEdit->setReadOnly(false);
    mFileEdit->setFocus();
    mFileEdit->gotoLine(mLine);
    mFileEdit->document ()->setModified (false);
}

void TextEditorWidget::textChanged()
{
}

void TextEditorWidget::textChangedTimeOut()
{
    saveFile();
}

void TextEditorWidget::fileReloadTimeOut ()
{
    if(notReload) {
        notReload = false;
        return;
    }
    reload ();
}

void TextEditorWidget::onFindAction ()
{
    mFindWidget->show ();
    auto text = mFileEdit->textCursor ().selectedText ();
    if(!text.isEmpty ()) {
        mFindWidget->setFindText (text);
    }
    mFindWidget->setFindEditFocus ();
}

void TextEditorWidget::onFindClose ()
{
    mFindWidget->hide ();
    mFileEdit->setFocus ();
    QList<QTextEdit::ExtraSelection> extraSelections;
    extraSelections.push_front (mFileEdit->extraSelections ().front ());
    mFileEdit->setExtraSelections(extraSelections);
}

void TextEditorWidget::onFind(const QString &subString, QTextDocument::FindFlags options)
{
    highlightWord (subString, options);

    auto select = mFileEdit->textCursor ().selectedText ();
    if(select != subString) {
        auto cursor = mFileEdit->textCursor ();
        cursor.setPosition (cursor.selectionStart ());
        mFileEdit->setTextCursor (cursor);
    }
    // find current
    if(!mFileEdit->find (subString, options)) {
        // research from top or buttom
        auto cursor = mFileEdit->textCursor ();
        if(options == QTextDocument::FindBackward) {
            mFileEdit->moveCursor (QTextCursor::End);
        } else {
            mFileEdit->moveCursor (QTextCursor::Start);
        }
        if(!mFileEdit->find (subString, options)) {
            // restore backup cursor
            mFileEdit->setTextCursor (cursor);
        }
    }
}

void TextEditorWidget::onReplace(const QString &subString, const QString &replaceWith)
{
    auto select = mFileEdit->textCursor ().selectedText ();
    if(select == subString) {
        mFileEdit->insertPlainText (replaceWith);
    }
}

void TextEditorWidget::onReplaceAll(const QString &subString, const QString &replaceWith)
{
    auto document = mFileEdit->document ();
    auto cursor = document->find (subString);
    while(!cursor.isNull ()) {
        cursor.insertText (replaceWith);
        cursor = document->find (subString, cursor);
    }
}


void TextEditorWidget::onFileChange (const QString &filePath)
{
    qDebug() << "File watcher file changed " << filePath;
    mFileReloadTimer->start (1500);
}

void TextEditorWidget::highlightWord (const QString &subString,QTextDocument::FindFlags options)
{
    QList<QTextEdit::ExtraSelection> extraSelections;
    extraSelections.push_front (mFileEdit->extraSelections ().front ());
    auto document = mFileEdit->document ();
    auto cursor = document->find (subString, 0,
                                  options & (~QTextDocument::FindBackward));
    while(!cursor.isNull ()) {
        QTextEdit::ExtraSelection selection;
        QColor lineColor = QColor(Qt::yellow).lighter(100);
        selection.format.setBackground(lineColor);
        selection.cursor = cursor;
        extraSelections.append(selection);
        cursor = document->find (subString, cursor,
                                 options & (~QTextDocument::FindBackward));
    }
    mFileEdit->setExtraSelections(extraSelections);
}

