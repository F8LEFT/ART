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


#include <QWidget>

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
public slots:
    // WidgetTab
    void addQWidgetTab(QWidget* qWidget, QString nativeName);
    void addQWidgetTab(QWidget* qWidget);
    void showQWidgetTab(QWidget* qWidget);
    void closeQWidgetTab(QWidget* qWidget);

    void tabMovedSlot(int from, int to);

private:
    Ui::WorkSpace *ui;
    MHTabWidget* mTabWidget;
    QVector<QWidget*> mWidgetList;
    QVector<QString> mWidgetNativeNameList;
};

#endif // WORKSPACE_H
