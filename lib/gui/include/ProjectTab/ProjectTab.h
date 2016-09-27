//===- ProjectTab.h - ART-GUI Project Tab ----------------------*- C++ -*-===//
//
//                     ANDROID REVERSE TOOLKIT
//
// This file is distributed under the GNU GENERAL PUBLIC LICENSE
// V3 License. See LICENSE.TXT for details.
//
//===---------------------------------------------------------------------===//
//
// This file defines project tab in workspace tab bar. It helps user to
// choose project to open or change project setting.
//
//===----------------------------------------------------------------------===//
#ifndef PROJECTTAB_H
#define PROJECTTAB_H

#include <QStackedWidget>
#include <QtWidgets/QFileSystemModel>

namespace Ui {
class ProjectTab;
}

class ProjectTab : public QStackedWidget
{
    Q_OBJECT

public:
    explicit ProjectTab(QWidget *parent = 0);
    ~ProjectTab();

protected slots:
    void onProjectOpenClick(const QModelIndex &index);
    void openProject(QString projectName);

    void onProjectOpened(QStringList projName);
private:
    Ui::ProjectTab *ui;

    QFileSystemModel* mFileSystemModel;
};

#endif // PROJECTTAB_H
