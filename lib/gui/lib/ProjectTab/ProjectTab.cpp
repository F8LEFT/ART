//===- ProjectTab.cpp - ART-GUI Project Tab --------------------*- C++ -*-===//
//
//                     ANDROID REVERSE TOOLKIT
//
// This file is distributed under the GNU GENERAL PUBLIC LICENSE
// V3 License. See LICENSE.TXT for details.
//
//===---------------------------------------------------------------------===//
#include "ProjectTab/ProjectTab.h"
#include "ui_ProjectTab.h"

#include <utils/StringUtil.h>
#include <utils/CmdMsgUtil.h>
#include <utils/ProjectInfo.h>
#include <utils/ScriptEngine.h>

#include <QtCore/QDir>

ProjectTab::ProjectTab(QWidget *parent) :
    QStackedWidget(parent),
    ui(new Ui::ProjectTab),
    mHasProject(false)
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
    connect(ui->mProjectList, SIGNAL(doubleClicked(QModelIndex)),
            this, SLOT(onProjectOpenClick(QModelIndex)));

    connect(script, SIGNAL(openProject (QStringList)),
            this, SLOT(openProject (QStringList)));
    connect(script, SIGNAL(closeProject (QStringList)),
            this, SLOT(closeProject ()));
    connect(script, SIGNAL(projectOpened(QStringList)),
            this, SLOT(onProjectOpened(QStringList)));
    connect(script, SIGNAL(projectClosed(QStringList)),
            this, SLOT(onProjectClosed()));
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

void ProjectTab::openProject (QStringList args)
{
    if(args.empty ())
        return;
    openProject (args.front ());
}

void ProjectTab::openProject (QString projectName)
{
    if(mHasProject)
        return;
    mHasProject = true;
    cmdmsg ()->addCmdMsg ("opening project " + projectName);

    auto projPath = GetProjectsProjectPath (projectName);

    QDir dir(projPath);
    if (!dir.exists()) {
        cmdmsg ()->addCmdMsg("project " + projectName + " not exist");
        return;
    }
    projinfoset ("ProjectName", projectName);
    projinfoset ("ProjectCur", projectName);

    mProjectName = projectName;

    cmdexec("ProjectOpened", projectName);
}

void ProjectTab::closeProject()
{
    if(!mHasProject)
        return;
    mHasProject = false;
    cmdmsg ()->addCmdMsg ("closing project " + mProjectName);

    projinfoset ("ProjectName", QString());
    projinfoset ("ProjectLast", mProjectName);

    QFile cfgFile(ProjectInfo::instance ()->getProjectCfgLastPath ());
    if(cfgFile.exists ()) {
        cfgFile.remove ();
    }

    cmdexec("ProjectClosed");
}

void ProjectTab::onProjectOpened (QStringList projName)
{
    cmdmsg ()->addCmdMsg ("project " + mProjectName + " opened.");
    setCurrentIndex(1);
}

void ProjectTab::onProjectClosed()
{
    cmdmsg ()->addCmdMsg ("project " + mProjectName + " closed");
    setCurrentIndex(0);
}

