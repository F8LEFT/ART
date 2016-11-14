//===- WorkSpace.h - ART-GUI WorkSpace --------------------------*- C++ -*-===//
//
//                     ANDROID REVERSE TOOLKIT
//
// This file is distributed under the GNU GENERAL PUBLIC LICENSE
// V3 License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file defines ART-GUI WorkSpace dialog's behaviour. WorkSpace widget
// is the central widget of MainWindow. It is the main work area of this
// sofe.
//
//===----------------------------------------------------------------------===//
#ifndef WORKSPACE_H
#define WORKSPACE_H

#include "ProjectTab/ProjectTab.h"
#include "EditorTab/EditorTab.h"
#include "BookMark/BookMarkManager.h"
#include "Find/FindDialog.h"
#include <QWidget>
#include <QTextBrowser>

namespace Ui {
class WorkSpace;
}
class MHTabWidget;

class WorkSpace : public QWidget
{
    Q_OBJECT

public:
    explicit WorkSpace(QWidget *parent = 0);
    ~WorkSpace();

    void setTab(QWidget* widget);
    void loadTabOrder();

    // configuration
    void loadFromConfig();
    void saveToConfig();
public slots:
    // WidgetTab
    void addQWidgetTab(QWidget* qWidget, QString nativeName);
    void addQWidgetTab(QWidget* qWidget);
    void showQWidgetTab(QWidget* qWidget);
    void closeQWidgetTab(QWidget* qWidget);
    void tabMovedSlot(int from, int to);

    // cmdLine Message
    void onCmdMessage(QString msg);
    void onCmdClear();

    // fileTree
    void treeFileOpen(const QModelIndex &index);
    void treeFileMenuRequested(const QPoint & point);
    // fileTreeMenuSlot
    void treeFileShowInFile();

    // script Message
    void onProjectOpened(QStringList args);
    void onProjectClosed ();
    void onFindAdvance(QStringList args);

    void onOpenWindow(QStringList args);

    // BookMark message
    void addBookMark(BookMark* pBook, QListWidgetItem *pItem);
    void delBookMark(QListWidgetItem *pItem);
    void bookmarkClick(QListWidgetItem* item);

    // Command Btn message
    void onCmdBtnClick();
    void onSearchBtnClick();

private:
    void initProjectDocumentTreeView();
    void setProjectDocumentTree(QString path);
    void clearProjectDocumentTree();

    void changeCommandWidget(QWidget* wiget);
    void showCommandWidget(QWidget* widget);
private:
    Ui::WorkSpace *ui;
    MHTabWidget* mTabWidget;
    QVector<QWidget*> mWidgetList;
    QVector<QString> mWidgetNativeNameList;

    // Tab Widget
    ProjectTab* mProjectTab;
    EditorTab* mEditorTab;

    // FileTreeView
    QFileSystemModel *mFileModel = nullptr;

    // BookMark
    BookMarkManager* mBookMarkManager;

    // Command Area
    QTextBrowser *mCmdTextBrowser;
    FindDialog* mFindDialog;
    QWidget* mCmdWidget = nullptr;
};

#endif // WORKSPACE_H
