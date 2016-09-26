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
}

ProjectTab::~ProjectTab()
{
    delete ui;
}
