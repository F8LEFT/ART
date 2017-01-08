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

#include "EditorTab/TextEditor.h"


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
    void reload(int delay);
    void closeFile();

    QString getFilePath() {return mFileEdit->documentTitle();}
    QString getFileName() {return QFileInfo(getFilePath()).fileName(); }

    void loadFromConfig();
    void saveToConfig();

    int currentLine();

public slots:

    void textChanged();

    void onFindAction();
    void onFindClose();

    // find && replace text in document
    void onFind(const QString &subString, QTextDocument::FindFlags options);
    void onReplace(const QString &subString, const QString &replaceWith);
    void onReplaceAll(const QString &subString, const QString &replaceWith);

private:
    void highlightWord(const QString &subString, QTextDocument::FindFlags  options);
protected:

    QTimer* mFileChangedTimer;
    QTimer* mFileReloadTimer;
    TextEditor* mFileEdit;
    QSyntaxHighlighter* mHighlighter;

    FindWidget* mFindWidget;

    int mLine;

    bool notReload = false;

};

#endif //ANDROIDREVERSETOOLKIT_TEXTEDITORWIDGET_H
