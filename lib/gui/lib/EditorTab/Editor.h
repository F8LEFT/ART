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

#include <QWidget>
#include <QThread>
#include <QTimer>

class Editor : public QWidget
{
    Q_OBJECT

public:
    Editor(QWidget *parent = 0);
    ~Editor();

    bool openFile(QString filePath, QString fileName);
    bool saveFile();
    bool reload();
    void closeFile();

    QString getFilePath() {return fp;}
    QString getFileName() {return fn;}

    void loadFromConfig();
    void saveToConfig();

    void gotoLine(int line, int column = 0, bool centerLine = true);

    virtual TextEditorWidget* allocTextEditorWidget();

signals:
    void readLine(QString line);
    void readEnd();

public slots:
    void appendLine(QString line);
    void readFileEnd();

    void textChanged();
    void textChangedTimeOut();

protected:
    QString fp;
    QString fn;

    bool isUpdated = false;
    QTimer* mFileChangedTimer;
    TextEditorWidget* mFileEdit;
};


#endif //PROJECT_EDITOR_H
