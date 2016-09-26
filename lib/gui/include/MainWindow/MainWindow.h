//===- MainWindow.h - ART-GUI MainWindow -----------------------*- C++ -*-===//
//
//                     ANDROID REVERSE TOOLKIT
//
// This file is distributed under the GNU GENERAL PUBLIC LICENSE
// V3 License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file defines ART-GUI MainWindow's behaviour.
//
//===----------------------------------------------------------------------===//
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "WorkSpace/WorkSpace.h"

namespace Ui {
class MainWindow;
}
class StatusLabel;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

// configuration
    void loadFromConfig();
    void saveToConfig();

    void setupStatusBar();
protected:
    void dragEnterEvent(QDragEnterEvent* event) Q_DECL_OVERRIDE;
    void dropEvent(QDropEvent* event) Q_DECL_OVERRIDE;

signals:
    void addCmdMessge(QString msg);
protected slots:
    // File Menu
    void actionExit();
    void actionOpen();
    // Help Menu
    void actionAboutArt();

private:
    void openFile(QString fileName);
private:
    Ui::MainWindow *ui;

    WorkSpace* mCenterWidget;

    StatusLabel* mStatusLabel;
    StatusLabel* mLastLogLabel;
};

#endif // MAINWINDOW_H
