//===- Editor.cpp - ART-GUI Editor Tab -------------------------*- C++ -*-===//
//
//                     ANDROID REVERSE TOOLKIT
//
// This file is distributed under the GNU GENERAL PUBLIC LICENSE
// V3 License. See LICENSE.TXT for details.
//
//===---------------------------------------------------------------------===//
#include "Editor.h"

#include <utils/Configuration.h>
#include "HighLighter/HighLighter.h"

#include <QTextStream>
#include <QtConcurrent/QtConcurrent>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QVBoxLayout>
#include <QFileInfo>
#include <QWidget>

void readFileThread(Editor* e, QString filePath);
void saveFileThread(QString text, QString  filePath);

Editor::Editor(QWidget *parent) :
        QWidget(parent)
{
    mFileChangedTimer = new QTimer(this);
    mFileEdit = new TextEditorWidget(this);
    mFindWidget = new FindWidget(this);


    connect(this, SIGNAL(readLine(QString)), this, SLOT(appendLine(QString)));
    connect(this, SIGNAL(readEnd()), this, SLOT(readFileEnd()));

    connect(mFileChangedTimer, SIGNAL(timeout()), this, SLOT(textChangedTimeOut()));

    connect(mFileEdit, SIGNAL(onCTRL_F_Click()), this, SLOT(onFindAction ()));

    // FindWidget signal
    connect(mFindWidget, SIGNAL(find(QString,QTextDocument::FindFlags)),
            this, SLOT(onFind(QString,QTextDocument::FindFlags)));
    connect(mFindWidget, SIGNAL(replace(QString,QString)),
            this, SLOT(onReplace(QString,QString)));
    connect(mFindWidget, SIGNAL(replaceAll(QString,QString)),
            this, SLOT(onReplaceAll(QString,QString)));
    connect(mFindWidget, SIGNAL(closeWidget()),
            this, SLOT(onFindClose ()));


    QFont font;
    font.setFamily("Courier");
    font.setFixedPitch(true);
    font.setPointSize(10);

    mFileEdit->setFont(font);
    mFindWidget->hide ();
    loadFromConfig();

}

Editor::~Editor()
{
    closeFile();
    saveToConfig();
}

// INFO this method should be invoked after init.
void Editor::setTextLayout ()
{
    QLayout* layout = new QVBoxLayout(this);
    layout->setContentsMargins (0,0,0,0);
    layout->addWidget (mFileEdit);
    layout->addWidget (mFindWidget);
    setLayout (layout);
}

bool Editor::openFile(QString filePath, int iLine)
{
    fp = filePath;
    QFile file(fp);
    if (file.open(QFile::ReadOnly | QFile::Text)) {
        fn = QFileInfo(file).fileName ();

        mFileEdit->setReadOnly(true);
        mFileEdit->setDocumentTitle(fn);
        mFileEdit->setDocumentPath(filePath);
        file.close();

        mHighlighter = setHighLighter(mFileEdit->document (), fn);

        mLine = iLine;
        QtConcurrent::run(readFileThread, this, filePath);
        return true;
    }
    return false;
}

bool Editor::saveFile()
{
    mFileChangedTimer->stop();
    if (mFileEdit->document ()->isModified ()) {
        QtConcurrent::run(saveFileThread, mFileEdit->toPlainText(), fp);
        mFileEdit->document ()->setModified (false);
    }

    return true;
}

bool Editor::reload()
{
    mFileEdit->clear();
    QtConcurrent::run(readFileThread, this, fp);
    return true;
}

void Editor::closeFile()
{
    saveFile();
}

void Editor::loadFromConfig()
{
//    Configuration *config = Config();
}

void Editor::saveToConfig()
{
//    Configuration *config = Config();
}

void Editor::gotoLine(int line, int column, bool centerLine)
{
    mFileEdit->gotoLine(line, column, centerLine);
}
int Editor::currentLine ()
{
    return mFileEdit->currentLine ();
}

void Editor::appendLine(QString line)
{
    mFileEdit->appendPlainText(line);
}

void Editor::readFileEnd()
{
    mFileEdit->setReadOnly(false);
    mFileEdit->setFocus();
    connect(mFileEdit, SIGNAL(textChanged()), this, SLOT(textChanged()));
    mFileEdit->gotoLine(mLine);
}

void Editor::textChanged()
{
    mFileChangedTimer->start(60*1000);
}

void Editor::textChangedTimeOut()
{
    saveFile();
}

void Editor::onFindAction ()
{
    mFindWidget->show ();
    auto text = mFileEdit->textCursor ().selectedText ();
    if(!text.isEmpty ()) {
        mFindWidget->setFindText (text);
    }
    mFindWidget->setFindEditFocus ();
}

void Editor::onFindClose ()
{
    mFindWidget->hide ();
    mFileEdit->setFocus ();
    QList<QTextEdit::ExtraSelection> extraSelections;
    extraSelections.push_front (mFileEdit->extraSelections ().front ());
    mFileEdit->setExtraSelections(extraSelections);

}

void Editor::onFind(const QString &subString, QTextDocument::FindFlags options)
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

void Editor::onReplace(const QString &subString, const QString &replaceWith)
{
    auto select = mFileEdit->textCursor ().selectedText ();
    if(select == subString) {
        mFileEdit->insertPlainText (replaceWith);
    }
}

void Editor::onReplaceAll(const QString &subString, const QString &replaceWith)
{
    auto document = mFileEdit->document ();
    auto cursor = document->find (subString);
    while(!cursor.isNull ()) {
        cursor.insertText (replaceWith);
        cursor = document->find (subString, cursor);
    }
}

void Editor::highlightWord (const QString &subString,QTextDocument::FindFlags options)
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


void readFileThread(Editor* e, QString filePath) {
    QFile file(filePath);
    if (file.open(QFile::ReadOnly | QFile::Text)) {
        while(!file.atEnd()) {
            emit e->readLine(file.readAll());
        }
        file.close();
    }
    emit e->readEnd();
    return ;
}

void saveFileThread(QString text, QString  filePath) {
    QFile file(filePath);
    if (file.open(QFile::WriteOnly | QFile::Truncate | QFile::Text)) {
        QTextStream out(&file);
        out<<text;
        out.flush();
        file.close();
    }
}
