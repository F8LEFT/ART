//===- MainWindow.cpp - ART-GUI MainWindow ---------------------*- C++ -*-===//
//
//                     ANDROID REVERSE TOOLKIT
//
// This file is distributed under the GNU GENERAL PUBLIC LICENSE
// V3 License. See LICENSE.TXT for details.
//
//===---------------------------------------------------------------------===//
#include "MainWindow/MainWindow.h"
#include "ui_MainWindow.h"


#include "StatusLabel.h"
#include "CommandLineEdit.h"
#include "AboutArt/AboutArt.h"
#include "OpenApk/OpenApk.h"
#include "RunDevice/RunDevice.h"
#include "Config/Config.h"
#include "TabWidget.h"


#include "utils/CmdMsgUtil.h"
#include "utils/Configuration.h"
#include "utils/StringUtil.h"
#include "utils/ProjectInfo.h"
#include "utils/ScriptEngine.h"


#include <QMimeData>
#include <QMessageBox>
#include <QDragEnterEvent>
#include <QFileDialog>
#include <QDebug>
#include <QDockWidget>
#include <QDesktopServices>
#include <QStringList>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("Android Reverse Toolkit");

    // setup dialogs
    setupCenterWindows();
    setupDockWindows();
    setupCommandBar();
    setupStatusBar();
    mRunDevice = RunDevice::instance (this);

    // connect Menu signal/slots
    // File Menu
    connect(ui->actionExit, SIGNAL(triggered(bool)), this, SLOT(actionExit()));
    connect(ui->actionOpen, SIGNAL(triggered(bool)), this, SLOT(actionOpen()));
    connect(ui->actionClose_Project, SIGNAL(triggered(bool)),
            this, SLOT(actionCloseProject()));
    connect(ui->actionSave_All, SIGNAL(triggered(bool)), this, SLOT(actionSaveAll()));
    connect(ui->actionOption, SIGNAL(triggered(bool)), this, SLOT(actionOption()));

    // Edit
    connect(ui->actionUndo, SIGNAL(triggered(bool)), this, SLOT(actionUndo()));
    connect(ui->actionRedo, SIGNAL(triggered(bool)), this, SLOT(actionRedo()));
    connect(ui->actionCut, SIGNAL(triggered(bool)), this, SLOT(actionCut()));
    connect(ui->actionCopy, SIGNAL(triggered(bool)), this, SLOT(actionCopy()));
    connect(ui->actionPaste, SIGNAL(triggered(bool)), this, SLOT(actionPaste()));
    connect(ui->actionDelete, SIGNAL(triggered(bool)), this, SLOT(actionDelete()));
    connect(ui->actionSelect_All, SIGNAL(triggered(bool)), this, SLOT(actionSelectAll()));
    connect(ui->actionFind_Replace, SIGNAL(triggered(bool)), this, SLOT(actionFind()));
    connect(ui->actionGoto_Line, SIGNAL(triggered(bool)), this, SLOT(actionGotoLine()));
    connect(ui->actionSearch_Global, SIGNAL(triggered(bool)), this, SLOT(actionFindAdvance()));

    // run
    connect(ui->actionBuild, SIGNAL(triggered(bool)), this, SLOT(actionBuild()));
    connect(ui->actionInstall, SIGNAL(triggered(bool)), this, SLOT(actionInstall()));
    connect(ui->actionRun, SIGNAL(triggered(bool)), this, SLOT(actionRun()));
    connect(ui->actionDebug, SIGNAL(triggered(bool)), this, SLOT(actionDebug()));
    connect(ui->actionStop, SIGNAL(triggered(bool)), this, SLOT(actionStop()));
    connect(ui->actionDevices, SIGNAL(triggered(bool)), this, SLOT(actionDevices()));

    // About Menu
    connect(ui->actionAbout_ART, SIGNAL(triggered(bool)),
            this, SLOT(actionAboutArt()));

    // file tree view signal
    connect(mFileTreeView, SIGNAL(doubleClicked(QModelIndex)),
            this, SLOT(treeFileOpen(QModelIndex)));
    connect(mFileTreeView, SIGNAL(customContextMenuRequested(QPoint)),
            this, SLOT(treeFileMenuRequested(QPoint)));

    // command line signal
    auto *cmdMsgUtil = CmdMsg::instance ();
    connect(cmdMsgUtil, SIGNAL(addCmdMsg(QString)), this, SLOT(onCmdMessage(QString)));

    // tab signal
    connect(mTabWidget, SIGNAL(tabMovedTabWidget(int, int)),
            this, SLOT(tabMovedSlot(int, int)));

    // script
    auto* script = ScriptEngine::instance();
    connect(script, SIGNAL(projectOpened(QStringList)),
            this, SLOT(onProjectOpened(QStringList)));
    connect(script, SIGNAL(projectClosed(QStringList)),
            this, SLOT(onProjectClosed()));
    connect(script, SIGNAL(findAdvance(QStringList)), this, SLOT(onFindAdvance (QStringList)));
    connect(script, SIGNAL(openWindow(QStringList)), this, SLOT(onOpenWindow (QStringList)));

    cmdmsg()->addCmdMsg("Android Reverse Toolkit v"
                            + GetCompileVersion () + " by f8left");
    cmdmsg()->setStatusMsg("ready");
    cmdmsg()->setLastLogMsg("init complete");

    showQWidgetTab(mProjectTab);
    loadFromConfig();

    mFileTreeView->raise();
    mDockCommand->raise();
}

MainWindow::~MainWindow()
{
    saveToConfig ();
    delete ui;
}

void MainWindow::loadFromConfig()
{
    Configuration *config = Config();
    restoreGeometry(config->getByte("MainWindow", "Geometry"));
    restoreState(config->getByte("MainWindow", "State"));
}

void MainWindow::saveToConfig()
{
    Configuration *config = Config();
    config->setByte("MainWindow", "Geometry", saveGeometry());
    config->setByte("MainWindow", "State", saveState());
}

void MainWindow::setupCommandBar()
{
    mCmdLineEdit = new CommandLineEdit(ui->cmdBar);
    ui->cmdBar->addWidget(mCmdLineEdit->selectorWidget());
    ui->cmdBar->addWidget(mCmdLineEdit);
}

void MainWindow::setupStatusBar()
{
    CmdMsg* cmdMsgUtil = CmdMsg::instance ();

    // Status label (Ready, Paused, ...)
    mStatusLabel = new StatusLabel(ui->statusBar);
    ui->statusBar->addWidget(mStatusLabel);

    // Log line
    mLastLogLabel = new StatusLabel();
    ui->statusBar->addPermanentWidget(mLastLogLabel, 1);

    connect(cmdMsgUtil, SIGNAL(setStatusMsg(QString)),
            mStatusLabel, SLOT(logUpdate(QString)));
    connect(cmdMsgUtil, SIGNAL(setLastLogMsg(QString)),
            mLastLogLabel, SLOT(logUpdate(QString)));
}

void MainWindow::dragEnterEvent(QDragEnterEvent *event)
{
    if(event->mimeData()->hasUrls()) {
        event->acceptProposedAction();
    }
}

void MainWindow::dropEvent(QDropEvent *event)
{
    QList<QUrl> urls = event->mimeData()->urls();
    if (urls.isEmpty())
        return;
    QString fileName = urls.first().toLocalFile();
    openFile(fileName);
}

void MainWindow::closeEvent (QCloseEvent *event)
{
//    switch( QMessageBox::information( this, tr("Confirm Exit"),
//                                      tr("Are you sure you want to exit ART?"),
//                                      tr("No"), tr("Yes"),
//                                      0, 1 ))
//    {
//        case 1:
    cmdexec("CloseProject", CmdMsg::script, true, false);
    event->accept();
//            break;
//        default:
//            event->ignore();
//            break;
//    }
}


void MainWindow::actionExit()
{
    close ();
}

void MainWindow::actionOpen()
{
    QString fileName = QFileDialog::getOpenFileName(this,
                                                    tr("Open File"), "", "apk File (*.apk *.dex)");
    openFile(fileName);
}

void MainWindow::actionCloseProject()
{
    cmdexec("CloseProject");
}

void MainWindow::actionSaveAll()
{
    mEditorTab->saveAll();
}

void MainWindow::actionOption()
{
    Config config;
    config.exec();
}

void MainWindow::actionUndo()
{
    mEditorTab->undo();
}

void MainWindow::actionRedo()
{
    mEditorTab->redo();
}

void MainWindow::actionCut()
{
    mEditorTab->cut();
}

void MainWindow::actionCopy()
{
    mEditorTab->copy();
}

void MainWindow::actionPaste()
{
    mEditorTab->paste();
}

void MainWindow::actionDelete()
{
    mEditorTab->deleteR();
}

void MainWindow::actionSelectAll()
{
    mEditorTab->selectAll();
}

void MainWindow::actionFind()
{
    mEditorTab->find(QStringList());
}

void MainWindow::actionGotoLine()
{
    mEditorTab->gotoLine(QStringList());
}

void MainWindow::actionFindAdvance()
{
    mDockFind->raise();
}

void MainWindow::actionAboutArt()
{
    AboutArt about(this);
    about.exec ();
}


void MainWindow::actionBuild()
{
    if(!ProjectInfo::isProjectOpened()) {
        return;
    }
    mRunDevice->onBuildAction();
}

void MainWindow::actionInstall()
{
    if(!ProjectInfo::isProjectOpened()) {
        return;
    }
    mRunDevice->onInstallAction();
}

void MainWindow::actionRun()
{
    if(!ProjectInfo::isProjectOpened()) {
        return;
    }
    if(needToRebuild ()) {
        qDebug() << "Current project need to rebuild.";
        mRunDevice->onBuildAction();
        mRunDevice->onInstallAction();
    }
    mRunDevice->onRunAction();

}

void MainWindow::actionDebug()
{
    if(!ProjectInfo::isProjectOpened()) {
        return;
    }
    mRunDevice->onStopAction();
    if(needToRebuild ()) {
        qDebug() << "Current project need to rebuild.";
        mRunDevice->onBuildAction();
        mRunDevice->onInstallAction();
    }
    mRunDevice->onDebugAction();
}

bool MainWindow::needToRebuild ()
{
    auto pinfo = ProjectInfo::current();
    QFileInfo buildFile(pinfo->getBuildPath() + "/signed.apk");
    if(!buildFile.exists()) {
        return true;
    }
    auto buildModified = buildFile.lastModified ();
    QDirIterator it(pinfo->getSourcePath(), QDirIterator::Subdirectories);
    while (it.hasNext()) {
        auto filePath = it.next();
        auto info = QFileInfo(filePath);
        if(info.lastModified () > buildModified) {
            return true;
        }
    }
    return false;
}

void MainWindow::actionStop()
{
    mRunDevice->onStopAction();
}

void MainWindow::actionDevices()
{
    mRunDevice->exec();
}

void MainWindow::onProjectOpened(QStringList projName)
{
    if(projName.empty())
        return;
    QString &name = projName.front();
    setWindowTitle("Android Reverse Toolkit - " + name);

    setProjectDocumentTree(GetProjectsProjectPath(name));
}

void MainWindow::onProjectClosed()
{
    setWindowTitle("Android Reverse Toolkit");
    mDebugger->stopCurrentTarget ();
    clearProjectDocumentTree();
    showQWidgetTab(mProjectTab);
}

void MainWindow::openFile(QString fileName)
{
    if (fileName.isEmpty()) {
        return;
    }
    if (!fileName.endsWith(".apk") && !fileName.endsWith(".dex")) {
        return;
    }
    if(ProjectInfo::isProjectOpened ()) {
        QMessageBox msg(QMessageBox::Warning,
                        tr("an opened project has been found"),
                        tr("do you want to close current project?"),
                        QMessageBox::Ok | QMessageBox::Cancel);
        msg.setWindowIcon(QIcon(":/icons/images/compile-warning.png"));
        msg.setWindowFlags(msg.windowFlags() & (~Qt::WindowContextHelpButtonHint));
        if(msg.exec() == QMessageBox::Cancel)
            return;
        else
            cmdexec("CloseProject");
    }

    OpenApk* openWidget = new OpenApk(fileName, this);
    if (openWidget->exec() == QDialog::Accepted) {
        // decompile
        QString cmd = openWidget->getDecompileCmd();
        qDebug() << "decompile: " << cmd;
        cmdexec(cmd, CmdMsg::cmd);
//         openProject
        QStringList args;
        args << openWidget->getFileName ();
        cmdexec("OpenProject", args);
    }
    delete openWidget;
}


void MainWindow::setProjectDocumentTree(QString path)
{
    Q_ASSERT (mFileModel == nullptr && "has been initialize?");
    // TODO use QSortFilterProxyModel to hide build directory
    mFileModel = new QFileSystemModel;

    mFileModel->setRootPath(path);
    mFileTreeView->setModel(mFileModel);
    mFileTreeView->setRootIndex(mFileModel->index(path));

    for (int i = 1; i < mFileModel->columnCount(); i++) {   // hide size date
        mFileTreeView->hideColumn(i);
    }
}

void MainWindow::clearProjectDocumentTree()
{
    mFileTreeView->setModel(nullptr);
    Q_ASSERT (mFileModel != nullptr && "not initialize?");
    mFileModel->deleteLater ();
    mFileModel = nullptr;
}

void MainWindow::setupCenterWindows()
{
    // init Tabs
    mTabWidget = new MHTabWidget(this);
    setCentralWidget(mTabWidget);
    mProjectTab = new ProjectTab(this);
    mProjectTab->setWindowTitle(tr("Project"));
    mEditorTab = new EditorTab(this);
    mEditorTab->setWindowTitle (tr ("Editor"));

    // init Tab widget
    mWidgetList.push_back(mProjectTab);
    mWidgetNativeNameList.push_back("ProjectTab");
    mWidgetList.push_back (mEditorTab);
    mWidgetNativeNameList.push_back ("EditorTab");
    loadTabOrder();
}


void MainWindow::setupDockWindows()
{
    setDockNestingEnabled(true);
    setTabPosition(Qt::LeftDockWidgetArea, QTabWidget::West);
    setTabPosition(Qt::RightDockWidgetArea, QTabWidget::East);
    setTabPosition(Qt::TopDockWidgetArea, QTabWidget::North);
    setTabPosition(Qt::BottomDockWidgetArea, QTabWidget::South);

    mFileTreeView = new QTreeView(this);
    mFileTreeView->setModel(nullptr);
    auto *pHeader= mFileTreeView->header();
    pHeader->setSectionResizeMode(QHeaderView::ResizeToContents);
    pHeader->setStretchLastSection(false);
    pHeader->setSortIndicator(0, Qt::AscendingOrder);
    mFileTreeView->setContextMenuPolicy(Qt::CustomContextMenu);
    mFileTreeView->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);

    mBookMarkListView = new BookMarkView(this);
    mBookMarkListView->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);

    mBreakPointListView = new BreakPointView(this);
    mBreakPointListView->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);

    mFindDialog = new FindDialog (this);
    mFindDialog->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    mCmdTextBrowser = new QTextBrowser(this);
    mCmdTextBrowser->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    mDebugger = new Debugger(this);
    mDebugger->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);

    mDockFileTree = new QDockWidget(tr("FileTree"), this);
    mDockFileTree->setObjectName("FileTree");
    mDockFileTree->setAllowedAreas(Qt::AllDockWidgetAreas);
    mDockFileTree->setWidget(mFileTreeView);
    mDockFileTree->setFeatures(QDockWidget::DockWidgetMovable|QDockWidget::DockWidgetFloatable);
    addDockWidget(Qt::LeftDockWidgetArea, mDockFileTree);

    mDockBookMark = new QDockWidget(tr("BookMark"), this);
    mDockBookMark->setObjectName("BookMark");
    mDockBookMark->setAllowedAreas(Qt::AllDockWidgetAreas);
    mDockBookMark->setWidget(mBookMarkListView);
    mDockBookMark->setFeatures(QDockWidget::DockWidgetMovable|QDockWidget::DockWidgetFloatable);

    tabifyDockWidget(mDockFileTree, mDockBookMark);

    mDockBreakMark = new QDockWidget(tr("BreakPoint"), this);
    mDockBreakMark->setObjectName("BreakMark");
    mDockBreakMark->setAllowedAreas(Qt::AllDockWidgetAreas);
    mDockBreakMark->setWidget(mBreakPointListView);
    mDockBreakMark->setFeatures(QDockWidget::DockWidgetMovable|QDockWidget::DockWidgetFloatable);

    tabifyDockWidget(mDockBookMark, mDockBreakMark);

    mDockCommand = new QDockWidget(tr("Messages"), this);
    mDockCommand->setObjectName("Message");
    mDockCommand->setAllowedAreas(Qt::AllDockWidgetAreas);
    mDockCommand->setWidget(mCmdTextBrowser);
    mDockCommand->setFeatures(QDockWidget::DockWidgetMovable|QDockWidget::DockWidgetFloatable);
    addDockWidget(Qt::BottomDockWidgetArea, mDockCommand, Qt::Horizontal);

    mDockFind = new QDockWidget(tr("Search && Replace"), this);
    mDockFind->setObjectName("SeachAReplace");
    mDockFind->setAllowedAreas(Qt::AllDockWidgetAreas);
    mDockFind->setWidget(mFindDialog);
    mDockFind->setFeatures(QDockWidget::DockWidgetMovable|QDockWidget::DockWidgetFloatable);
    tabifyDockWidget(mDockCommand, mDockFind);

    mDockDebugger = new QDockWidget(tr("Debug"), this);
    mDockDebugger->setObjectName("Debug");
    mDockDebugger->setAllowedAreas(Qt::AllDockWidgetAreas);
    mDockDebugger->setWidget(mDebugger);
    mDockDebugger->setFeatures(QDockWidget::DockWidgetMovable|QDockWidget::DockWidgetFloatable);
    tabifyDockWidget(mDockFind, mDockDebugger);
}

void MainWindow::onCmdMessage(QString msg)
{
    QStringList lineList = msg.split(QRegExp("[\\n\\r]"), QString::SkipEmptyParts);
        foreach(QString m, lineList) {
            mCmdTextBrowser->append(m);
        }
}

void MainWindow::onCmdClear()
{
    mCmdTextBrowser->clear();
}

void MainWindow::treeFileOpen(const QModelIndex &index)
{
    if (mFileModel->fileInfo(index).isFile()) {
        if(mEditorTab->openFile(mFileModel->filePath(index), -1)) {
            showQWidgetTab(mEditorTab);
        }
    }
}

void MainWindow::treeFileMenuRequested (const QPoint &point)
{
    QModelIndex index=mFileTreeView->currentIndex();
    if(!index.isValid ())
        return;

    QMenu* menu=new QMenu(this);
    menu->addAction(tr("Show in Files"), this, SLOT(treeFileShowInFile()));
    menu->exec(QCursor::pos());
    menu->deleteLater ();
}

void MainWindow::treeFileShowInFile ()
{
    QModelIndex index=mFileTreeView->currentIndex();
    auto fileinfo = mFileModel->fileInfo(index);

    QDesktopServices::openUrl(QUrl::fromLocalFile(fileinfo.absolutePath ()));
}

void MainWindow::onFindAdvance(QStringList args)
{
    if(!args.isEmpty ()) {
        mFindDialog->onFindAdvance (args.front ());
    } else
    if(mFileTreeView->hasFocus()) {
        auto index = mFileTreeView->currentIndex ();
        if(index.isValid ()) {
            auto fInfo = mFileModel->fileInfo (index);
            mFindDialog->onFindAdvance (fInfo.absoluteFilePath ());
        }
    } else {
        mFindDialog->onFindAdvance (QString());
    }
    mFindDialog->setFocus();
}

void MainWindow::onOpenWindow (QStringList args)
{
    if(args.isEmpty ())
        return;
    QString &tabName = args.front ();
    for(int i = 0; i < mWidgetList.size(); i++)
    {
        if(tabName == mWidgetNativeNameList[i]) {
            showQWidgetTab (mWidgetList[i]);
            break;
        }
    }
}

void MainWindow::setTab(QWidget *widget)
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

void MainWindow::loadTabOrder()
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

void MainWindow::addQWidgetTab(QWidget *qWidget, QString nativeName)
{
    mTabWidget->addTabEx(qWidget, qWidget->windowIcon(),
                         qWidget->windowTitle(), nativeName);
}

void MainWindow::addQWidgetTab(QWidget *qWidget)
{
    addQWidgetTab(qWidget, qWidget->windowTitle());
}

void MainWindow::showQWidgetTab(QWidget *qWidget)
{
    qWidget->show();
    qWidget->setFocus();
    setTab(qWidget);
}

void MainWindow::closeQWidgetTab(QWidget *qWidget)
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

void MainWindow::tabMovedSlot(int from, int to)
{
    for(int i = 0; i < mTabWidget->count(); i++)
    {
        QString tabName = mTabWidget->getNativeName(i);
        Config()->setUint("TabOrder", tabName, i);
    }
}



