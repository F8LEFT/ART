//===- EditorTab.h - ART-GUI Editor Tab ----------------------*- C++ -*-===//
//
//                     ANDROID REVERSE TOOLKIT
//
// This file is distributed under the GNU GENERAL PUBLIC LICENSE
// V3 License. See LICENSE.TXT for details.
//
//===---------------------------------------------------------------------===//
//
// This file defines project tab in workspace tab bar. It helps user to
// edit project file.
//
//===----------------------------------------------------------------------===//
#ifndef EDITORTAB_H
#define EDITORTAB_H

#include <QWidget>

namespace Ui {
class EditorTab;
}

class Editor;
class EditorTab : public QWidget
{
    Q_OBJECT

public:
    EditorTab(QWidget *parent = 0);
    ~EditorTab();

    void showEditor(Editor* e);
    bool openFile(QString filePath, int iLine = 1);
    bool closeFile(QString filePath);
    bool saveFile(QString filePath);

public slots:
    void documentCloseClick(bool );

    void fileChanged(QString path);

    bool saveAll();
    bool closeAll();
    void saveFile(QStringList files);
    void closeFile(QStringList files);
    void openFile(QStringList args);
private:
    Ui::EditorTab *ui;
};

#endif // EDITORTAB_H
