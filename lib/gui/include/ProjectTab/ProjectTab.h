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
#include <QtWidgets/QListWidget>

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
    // script
    void onProjectOpenClick(const QModelIndex &index);
    void openProject(QStringList args);
    void openProject(QString projectName);
    void closeProject();

    void onProjectOpened(QStringList projName);
    void onProjectClosed();

    // button
    void onSaveBtnClick();
    void onResetBtnClick();

    // ActivityInfo
    void onActivityClick(QListWidgetItem* item);
    void openActivityInEditor(QString activityName);

private:
    void readProjectInfo();
    void readProjectYmlInfo();          // for apktool.yml
    void readProjectManifestInfo();     // for AndroidManifest.xml
private:
    Ui::ProjectTab *ui;

    QFileSystemModel* mFileSystemModel;
    bool mHasProject;

    // project info
    QString mProjectName;
    QList<QString> mSmaliDirectory;
    QString mVersion;
    QString mVersionCode;
    QString mVersionName;
    QString mPackageName;
    QString mApplicationName;
    QString mActivityEntryName;
};

#endif // PROJECTTAB_H
