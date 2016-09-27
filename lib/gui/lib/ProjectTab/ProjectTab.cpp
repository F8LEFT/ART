//===- ProjectTab.cpp - ART-GUI Project Tab --------------------*- C++ -*-===//
//
//                     ANDROID REVERSE TOOLKIT
//
// This file is distributed under the GNU GENERAL PUBLIC LICENSE
// V3 License. See LICENSE.TXT for details.
//
//===---------------------------------------------------------------------===//
#include <QtCore/QDir>
#include <utils/StringUtil.h>
#include <utils/CmdMsgUtil.h>
#include <utils/ProjectInfo.h>
#include <utils/ScriptEngine.h>
#include "ProjectTab/ProjectTab.h"
#include "ui_ProjectTab.h"

ProjectTab::ProjectTab(QWidget *parent) :
    QStackedWidget(parent),
    ui(new Ui::ProjectTab)
{
    ui->setupUi(this);

    setCurrentIndex(0);

    mFileSystemModel = new QFileSystemModel(this);
    QDir dir(GetProjectsPath ());
    if (dir.exists()) {
        QString projectRootPath = dir.absolutePath();
        mFileSystemModel->setRootPath(projectRootPath);

        ui->mProjectList->setModel(mFileSystemModel);
        ui->mProjectList->setRootIndex(mFileSystemModel->index(projectRootPath));
        ui->mProjectList->setEditTriggers(QAbstractItemView::NoEditTriggers);
        ui->mProjectList->setSelectionBehavior(QAbstractItemView::SelectRows);
        ui->mProjectList->hideColumn(1); ui->mProjectList->hideColumn(2);

        QHeaderView * hHeader = ui->mProjectList->horizontalHeader();
        hHeader->setSectionResizeMode(QHeaderView::Stretch);
        hHeader->setStretchLastSection(false);
        hHeader->setSortIndicator(1, Qt::AscendingOrder);    // sort by date
        hHeader->hide();
        ui->mProjectList->verticalHeader()->hide();
    }

    auto* script = ScriptEngine::instance();
    connect(ui->mProjectList, SIGNAL(doubleClicked(QModelIndex)), SLOT(onProjectOpenClick(QModelIndex)));

}

ProjectTab::~ProjectTab()
{
    delete ui;
}

void ProjectTab::onProjectOpenClick(const QModelIndex &index)
{
    openProject (ui->mProjectList->model()->
            index(index.row(), 0, ui->mProjectList->rootIndex()).data().toString());
}

void ProjectTab::openProject (QString projectName)
{
    auto projPath = GetProjectsPath (projectName);

    QDir dir(QApplication::applicationDirPath() + "/Projects/" + projectName + "/Project");
    if (!dir.exists()) {
        cmdmsg ()->addCmdMsg("project " + projectName + " not exist");
        return;
    }
    auto projMsg = ProjectInfo::instance ();
    projMsg->setInfo ("projectName", projectName);
    cmdexec("ProjectOpened");
}

void ProjectTab::onProjectOpened (QStringList projName)
{

}
