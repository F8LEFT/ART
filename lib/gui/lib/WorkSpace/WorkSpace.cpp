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
#include <QGridLayout>
#include <QtGui/QDesktopServices>

WorkSpace::WorkSpace(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WorkSpace)
{
    ui->setupUi(this);

    initProjectDocumentTreeView();
    mBookMarkManager = BookMarkManager::instance(this);

    // init Project TreeView
    ui->mFileTreeView->setContextMenuPolicy(Qt::CustomContextMenu);

    // init Tabs
    mProjectTab = new ProjectTab(this);
    mProjectTab->setWindowTitle(tr("Project"));
    mEditorTab = new EditorTab(this);
    mEditorTab->setWindowTitle (tr ("Editor"));

    // init Tab widget
    mTabWidget = new MHTabWidget(this);
    ui->mRightTopFrameLayout->addWidget(mTabWidget);

    mWidgetList.push_back(mProjectTab);
    mWidgetNativeNameList.push_back("ProjectTab");
    mWidgetList.push_back (mEditorTab);
    mWidgetNativeNameList.push_back ("EditorTab");

    // init Command Area
    mFindDialog = new FindDialog (this);
    mFindDialog->hide ();
    mCmdTextBrowser = new QTextBrowser(this);
    mCmdTextBrowser->hide ();

    ui->mRightBotFrameLayout->addWidget (mCmdTextBrowser);
    ui->mRightBotFrameLayout->addWidget (mFindDialog);

    // connect signal / slots
    // file tree view signal
    connect(ui->mFileTreeView, SIGNAL(doubleClicked(QModelIndex)),
            this, SLOT(treeFileOpen(QModelIndex)));
    connect(ui->mFileTreeView, SIGNAL(customContextMenuRequested(QPoint)),
            this, SLOT(treeFileMenuRequested(QPoint)));

    // tab signal
    connect(mTabWidget, SIGNAL(tabMovedTabWidget(int, int)),
            this, SLOT(tabMovedSlot(int, int)));

    // BookMark signal
    connect(mBookMarkManager, SIGNAL(addBookMark(BookMark*,QListWidgetItem*)),
            this, SLOT(addBookMark(BookMark*,QListWidgetItem*)));
    connect(mBookMarkManager, SIGNAL(delBookMark(QListWidgetItem*)),
            this, SLOT(delBookMark(QListWidgetItem*)));
    connect(ui->mBookMarkListWidget, SIGNAL(itemClicked(QListWidgetItem*)),
            this, SLOT(bookmarkClick(QListWidgetItem*)));

    // command line signal
    auto *cmdMsgUtil = CmdMsg::instance ();
    connect(cmdMsgUtil, SIGNAL(addCmdMsg(QString)), this, SLOT(onCmdMessage(QString)));

    // command line Button signal
    connect(ui->mCmdBtn, SIGNAL(clicked(bool)), this, SLOT(onCmdBtnClick ()));
    connect(ui->mSearchBtn, SIGNAL(clicked(bool)), this, SLOT(onSearchBtnClick ()));

    // script signal
    ScriptEngine* script = ScriptEngine::instance();
    connect(script, SIGNAL(projectOpened(QStringList)), this, SLOT(onProjectOpened(QStringList)));
    connect(script, SIGNAL(projectClosed(QStringList)), this, SLOT(onProjectClosed ()));

    loadFromConfig();
    showQWidgetTab(mProjectTab);
    ui->mCmdBtn->click ();
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
        mCmdTextBrowser->append(m);
    }
}

void WorkSpace::onCmdClear()
{
    mCmdTextBrowser->clear();
}

void WorkSpace::treeFileOpen(const QModelIndex &index)
{
    if (mFileModel->fileInfo(index).isFile()) {
        if(!mEditorTab->openFile(mFileModel->filePath(index), -1)) {
            // TODO Error happened in open file
        }
    }
}

void WorkSpace::treeFileMenuRequested (const QPoint &point)
{
    QModelIndex index=ui->mFileTreeView->currentIndex();
    if(!index.isValid ())
        return;

    QMenu* menu=new QMenu(this);
    menu->addAction(tr("Show in Files"), this, SLOT(treeFileShowInFile()));
    menu->exec(QCursor::pos());
    menu->deleteLater ();
}

void WorkSpace::treeFileShowInFile ()
{
    QModelIndex index=ui->mFileTreeView->currentIndex();
    auto fileinfo = mFileModel->fileInfo(index);

    QDesktopServices::openUrl(QUrl::fromLocalFile(fileinfo.absolutePath ()));
}

void WorkSpace::onProjectOpened(QStringList args)
{
    if(args.empty())
        return;

    QString projName = args.front();
    setProjectDocumentTree(GetProjectsProjectPath(projName));
}

void WorkSpace::onProjectClosed ()
{
    clearProjectDocumentTree();
}


void WorkSpace::addBookMark(BookMark *pBook, QListWidgetItem *pItem)
{
    pItem->setSizeHint(QSize(0, pBook->height()));

    ui->mBookMarkListWidget->addItem(pItem);
    ui->mBookMarkListWidget->setItemWidget(pItem, pBook);
}

void WorkSpace::delBookMark(QListWidgetItem *pItem)
{
    Q_ASSERT(pItem != nullptr);
    BookMark* pBook = (BookMark*)ui->mBookMarkListWidget->itemWidget(pItem);
    Q_ASSERT(pBook != nullptr);
    delete pBook;
    delete pItem;
}

void WorkSpace::bookmarkClick(QListWidgetItem *item)
{
    BookMark* pBook = (BookMark*)ui->mBookMarkListWidget->itemWidget(item);
    Q_ASSERT(pBook != nullptr);
    emit pBook->onClicked(pBook);
}

void WorkSpace::onCmdBtnClick ()
{
    changeCommandWidget (mCmdTextBrowser);
}

void WorkSpace::onSearchBtnClick ()
{
    changeCommandWidget (mFindDialog);
}

void WorkSpace::changeCommandWidget (QWidget *wiget)
{
    if(mCmdWidget != nullptr) {
        mCmdWidget->hide ();
    }
    if(mCmdWidget == wiget) {
        mCmdWidget = nullptr;
        return;
    }
    mCmdWidget = wiget;
    mCmdWidget->show ();
}

void WorkSpace::initProjectDocumentTreeView()
{
    ui->mFileTreeView->setModel(nullptr);
    auto *pHeader= ui->mFileTreeView->header();
    pHeader->setSectionResizeMode(QHeaderView::ResizeToContents);
    pHeader->setStretchLastSection(false);
    pHeader->setSortIndicator(0, Qt::AscendingOrder);

    mFileModel = new QFileSystemModel;
}

void WorkSpace::setProjectDocumentTree(QString path)
{
    mFileModel->setRootPath(path);
    ui->mFileTreeView->setModel(mFileModel);
    ui->mFileTreeView->setRootIndex(mFileModel->index(path));

    for (int i = 1; i < mFileModel->columnCount(); i++) {   // hide size date
        ui->mFileTreeView->hideColumn(i);
    }
}

void WorkSpace::clearProjectDocumentTree()
{
    ui->mFileTreeView->setModel(nullptr);
}




