//===- WorkSpace.cpp - ART-GUI WorkSpace ------------------------*- C++ -*-===//
//
//                     ANDROID REVERSE TOOLKIT
//
// This file is distributed under the GNU GENERAL PUBLIC LICENSE
// V3 License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
#include "WorkSpace/WorkSpace.h"
#include "ui_WorkSpace.h"

#include "TabWidget.h"

#include <utils/Configuration.h>
#include <utils/CmdMsgUtil.h>
#include <utils/ScriptEngine.h>
#include <utils/ProjectInfo.h>
#include <utils/StringUtil.h>

WorkSpace::WorkSpace(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WorkSpace)
{
    ui->setupUi(this);

    initProjectDocumentTreeView();

    // init Tabs
    mProjectTab = new ProjectTab;
    mProjectTab->setWindowTitle(tr("Project"));

    // init Tab widget
    mTabWidget = new MHTabWidget(this);
    ui->mRightTopFrameLayout->addWidget(mTabWidget);

    mWidgetList.push_back(mProjectTab);
    mWidgetNativeNameList.push_back("ProjectTab");



    // connect signal / slots
    connect(mTabWidget, SIGNAL(tabMovedTabWidget(int, int)), this, SLOT(tabMovedSlot(int, int)));

    auto *cmdMsgUtil = CmdMsg::instance ();
    connect(cmdMsgUtil, SIGNAL(addCmdMsg(QString)), this, SLOT(onCmdMessage(QString)));

    ScriptEngine* engine = ScriptEngine::instance();
    connect(engine, SIGNAL(projectOpened(QStringList)), this, SLOT(onProjectOpened(QStringList)));
    connect(engine, SIGNAL(projectClosed(QStringList)), this, SLOT(onProjectClose()));




    loadFromConfig();
    showQWidgetTab(mProjectTab);
}

WorkSpace::~WorkSpace()
{
    saveToConfig();
    delete ui;
}


void WorkSpace::setTab(QWidget *widget)
{
    for(int i = 0; i < mTabWidget->count(); i++)
    {
        if(mTabWidget->widget(i) == widget)
        {
            mTabWidget->setCurrentIndex(i);
            break;
        }
    }
}

void WorkSpace::loadTabOrder()
{
    QList<QPair<QWidget*, QString>> tabIndexToWidget;

    Configuration *config = Config();
    // Get tabIndex for each widget and add them to tabIndexToWidget
    for(int i = 0; i < mWidgetList.size(); i++)
    {
        QString tabName = mWidgetNativeNameList[i];
        unsigned tabIndex = config->getUint("TabOrder", tabName);
        tabIndexToWidget.insert(tabIndex, qMakePair(mWidgetList[i], tabName));
    }

    // Setup tabs
    for(auto & widget : tabIndexToWidget)
        addQWidgetTab(widget.first, widget.second);
}


void WorkSpace::loadFromConfig()
{
    Configuration *config = Config();

    QList<int> lSplitter;
    lSplitter << config->getUint("WorkSpace", "LeftSplitterWidth")
              << config->getUint("WorkSpace", "RightSplitterWidth");
    ui->mHSplitter->setSizes(lSplitter);

    QList<int> lLeftSplitter;
    lLeftSplitter << config->getUint("WorkSpace", "LeftTopSplitterHeight")
                  << config->getUint("WorkSpace", "LeftBotSplitterHeight");
    ui->mLeftVSplitter->setSizes(lLeftSplitter);


    QList<int> lRightSplitter;
    lRightSplitter << config->getUint("WorkSpace", "RightTopSplitterHeight")
                   << config->getUint("WorkSpace", "RightBotSplitterHeight");
    ui->mRightVSplitter->setSizes(lRightSplitter);

    loadTabOrder();
}

void WorkSpace::saveToConfig()
{
    Configuration *config = Config();

    QList<int> lSplitter = ui->mHSplitter->sizes();
    config->setUint("WorkSpace", "LeftSplitterWidth", lSplitter[0]);
    config->setUint("WorkSpace", "RightSplitterWidth", lSplitter[1]);

    QList<int> lLeftSplitter = ui->mLeftVSplitter->sizes();
    config->setUint("WorkSpace", "LeftTopSplitterHeight", lLeftSplitter[0]);
    config->setUint("WorkSpace", "LeftBotSplitterHeight", lLeftSplitter[1]);

    QList<int> lRightSplitter = ui->mRightVSplitter->sizes();
    config->setUint("WorkSpace", "RightTopSplitterHeight", lRightSplitter[0]);
    config->setUint("WorkSpace", "RightBotSplitterHeight", lRightSplitter[1]);

}

void WorkSpace::addQWidgetTab(QWidget *qWidget, QString nativeName)
{
    mTabWidget->addTabEx(qWidget, qWidget->windowIcon(),
                         qWidget->windowTitle(), nativeName);
}

void WorkSpace::addQWidgetTab(QWidget *qWidget)
{
    addQWidgetTab(qWidget, qWidget->windowTitle());
}

void WorkSpace::showQWidgetTab(QWidget *qWidget)
{
    qWidget->show();
    qWidget->setFocus();
    setTab(qWidget);
}

void WorkSpace::closeQWidgetTab(QWidget *qWidget)
{
    for(int i = 0; i < mTabWidget->count(); i++)
    {
        if(mTabWidget->widget(i) == qWidget)
        {
            mTabWidget->DeleteTab(i);
            break;
        }
    }
}

void WorkSpace::tabMovedSlot(int from, int to)
{
    for(int i = 0; i < mTabWidget->count(); i++)
    {
        QString tabName = mTabWidget->getNativeName(i);
        Config()->setUint("TabOrder", tabName, i);
    }
}

void WorkSpace::onCmdMessage(QString msg)
{
    QStringList lineList = msg.split(QRegExp("\\n+"), QString::SkipEmptyParts);
    foreach(QString m, lineList) {
        ui->mCmdTextBrowser->append(m);
    }
}

void WorkSpace::onCmdClear()
{
    ui->mCmdTextBrowser->clear();
}

void WorkSpace::onProjectOpened(QStringList args)
{
    if(args.empty())
        return;

    QString projName = args.front();
    setProjectDocumentTree(GetProjectsProjectPath(projName));
}

void WorkSpace::onProjectClose()
{
    clearProjectDocumentTree();
}

void WorkSpace::initProjectDocumentTreeView()
{
    ui->mFileTreeView->setModel(nullptr);
    auto *pHeader= ui->mFileTreeView->header();
    pHeader->setSectionResizeMode(QHeaderView::ResizeToContents);
    pHeader->setStretchLastSection(false);
    pHeader->setSortIndicator(0, Qt::AscendingOrder);

    mFileModel = new QFileSystemModel;
    //mFileModel->setRootPath(".");
    //ui->mFileTreeView->setRootIndex(mFileModel->index("."));
    for (int i = 1; i < mFileModel->columnCount(); i++) {   // hide size date
        ui->mFileTreeView->hideColumn(i);
    }
}

void WorkSpace::setProjectDocumentTree(QString path)
{
    mFileModel->setRootPath(path);
    ui->mFileTreeView->setModel(mFileModel);
    ui->mFileTreeView->setRootIndex(mFileModel->index(path));
}

void WorkSpace::clearProjectDocumentTree()
{
    ui->mFileTreeView->setModel(nullptr);
}
