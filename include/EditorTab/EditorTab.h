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
#include "TextMark.h"

#include <QWidget>

namespace Ui {
class EditorTab;
}

class EditorTab : public QWidget
{
    Q_OBJECT

public:
    EditorTab(QWidget *parent = 0);
    ~EditorTab();

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

    // for edit
    void undo();
    void redo();
    void cut();
    void copy();
    void paste();
    void deleteR();
    void selectAll();
    void find(QStringList args);
    void gotoLine(QStringList args);
    void toggleBreakPoint();
    void toggleBookMark();

    void onProjectOpened(QStringList args);
    void onProjectClosed ();

    void onTextMarkUpdate(TextMark* mark, bool isAdd);

private slots:
    void documentIndxChanged(int index);
    void methodIndexChanged(int index);
private:
    void updateEditorMsg(QString file);

    Ui::EditorTab *ui;

    QIcon m_fieldIcon;
    QIcon m_methodIcon;
};

#endif // EDITORTAB_H
