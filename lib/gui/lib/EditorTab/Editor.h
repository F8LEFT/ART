//===- Editor.h - ART-GUI Editor Tab ---------------------------*- C++ -*-===//
//
//                     ANDROID REVERSE TOOLKIT
//
// This file is distributed under the GNU GENERAL PUBLIC LICENSE
// V3 License. See LICENSE.TXT for details.
//
//===---------------------------------------------------------------------===//
//
// Editor is a widget to open/modify/save file.
//
//===----------------------------------------------------------------------===//

#ifndef PROJECT_EDITOR_H
#define PROJECT_EDITOR_H

#include "TextEditorWidget.h"

#include <BookMark/BookMark.h>
#include <Find/FindWidget.h>


#include <QWidget>
#include <QThread>
#include <QTimer>
#include <QSyntaxHighlighter>
#include <QAction>

class Editor : public QWidget
{
    Q_OBJECT

public:
    Editor(QWidget *parent = 0);
    ~Editor();
    virtual void setTextLayout();
    bool openFile(QString filePath, int iLine = 1);
    bool saveFile();
    bool reload();
    void closeFile();

    QString getFilePath() {return fp;}
    QString getFileName() {return fn;}

    void loadFromConfig();
    void saveToConfig();

    void gotoLine(int line, int column = 0, bool centerLine = true);
    int currentLine();

signals:
    void readLine(QString line);
    void readEnd();

public slots:
    void appendLine(QString line);
    void readFileEnd();

    void textChanged();
    void textChangedTimeOut();

    void onFindAction();
    void onFindClose();

    // find && replace text in document
    void onFind(const QString &subString, QTextDocument::FindFlags options);
    void onReplace(const QString &subString, const QString &replaceWith);
    void onReplaceAll(const QString &subString, const QString &replaceWith);

private:
    void highlightWord(const QString &subString, QTextDocument::FindFlags  options);
protected:
    QString fp;
    QString fn;

    bool isUpdated = false;
    QTimer* mFileChangedTimer;
    TextEditorWidget* mFileEdit;
    QSyntaxHighlighter* mHighlighter;

    FindWidget* mFindWidget;

    int mLine;
};


#endif //PROJECT_EDITOR_H
