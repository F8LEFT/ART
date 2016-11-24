//===- TabBar.h - ART-GUI WorkSpace -----------------------------*- C++ -*-===//
//===----------------------------------------------------------------------===//
//
// This file is copyed from X64Dbg project.
//
//===----------------------------------------------------------------------===//
#ifndef __MHTABBAR_H__
#define __MHTABBAR_H__

#include <QTabBar>
#include <QMenu>
#include <QAction>

//////////////////////////////////////////////////////////////////////////////
// Summary:
//    MHTabBar implements the a Tab Bar with detach functionality.
//////////////////////////////////////////////////////////////////////////////
class MHTabBar: public QTabBar
{
    Q_OBJECT

public:
    MHTabBar(QWidget* parent, bool allowDetach, bool allowDelete);
    ~MHTabBar(void);

protected:
    void contextMenuEvent(QContextMenuEvent* event);
    void mouseDoubleClickEvent(QMouseEvent* event);

signals:
    // Detach Tab
    void OnDetachTab(int index, QPoint & dropPoint);
    // Move Tab
    void OnMoveTab(int fromIndex, int toIndex);
    // Delete Tab
    void OnDeleteTab(int index);
    // Double Click on Tab, Get Index
    void OnDoubleClickTabIndex(int index);

private:
    bool mAllowDetach;
    bool mAllowDelete;
};

#endif // __MHTABBAR_H__
