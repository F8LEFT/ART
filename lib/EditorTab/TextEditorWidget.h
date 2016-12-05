//===- TextEditorWidget.h - ART-GUI TextEditorWidget Tab -----------------*- C++ -*-===//
//
//                     ANDROID REVERSE TOOLKIT
//
// This file is distributed under the GNU GENERAL PUBLIC LICENSE
// V3 License. See LICENSE.TXT for details.
//
//===---------------------------------------------------------------------===//
//
// The main TextEditorWidget widget.
//
//===----------------------------------------------------------------------===//

#ifndef ANDROIDREVERSETOOLKIT_TEXTEDITORWIDGET_H
#define ANDROIDREVERSETOOLKIT_TEXTEDITORWIDGET_H

#include "TextEditor.h"


#include <BookMark/BookMark.h>
#include <Find/FindWidget.h>


#include <QWidget>
#include <QThread>
#include <QTimer>
#include <QSyntaxHighlighter>
#include <QAction>
#include <QFileSystemWatcher>
#include <QFileInfo>

class TextEditorWidget : public QWidget
{
    Q_OBJECT

public:
    TextEditorWidget(QWidget *parent = Q_NULLPTR);
    ~TextEditorWidget();

    TextEditor* editor() { return mFileEdit; }
    bool openFile(QString filePath, int iLine = 1);
    bool saveFile();
    bool reload();
    void closeFile();

    QString getFilePath() {return mFileEdit->documentTitle();}
    QString getFileName() {return QFileInfo(getFilePath()).fileName(); }

    void loadFromConfig();
    void saveToConfig();

    int currentLine();

signals:
    void readText(const QString &text);
    void readLine(const QString &line);
    void readEnd();

public slots:
    void setText(const QString &text);
    void appendLine(const QString &line);
    void readFileEnd();

    void textChanged();
    void textChangedTimeOut();
    void fileReloadTimeOut();

    void onFindAction();
    void onFindClose();

    // find && replace text in document
    void onFind(const QString &subString, QTextDocument::FindFlags options);
    void onReplace(const QString &subString, const QString &replaceWith);
    void onReplaceAll(const QString &subString, const QString &replaceWith);

    // filewatcher
    void onFileChange(const QString &filePath);
private:
    void highlightWord(const QString &subString, QTextDocument::FindFlags  options);
protected:

    QTimer* mFileChangedTimer;
    QTimer* mFileReloadTimer;
    TextEditor* mFileEdit;
    QSyntaxHighlighter* mHighlighter;

    FindWidget* mFindWidget;

    QFileSystemWatcher* mFileWatcher;

    int mLine;

    bool notReload = false;

};

#endif //ANDROIDREVERSETOOLKIT_TEXTEDITORWIDGET_H
