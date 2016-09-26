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

#include "utils/CmdMsgUtil.h"

#include <QMimeData>
#include <QMessageBox>
#include <QDragEnterEvent>
#include <QFileDialog>
#include <utils/Configuration.h>
#include <utils/StringUtil.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    loadFromConfig();

    mCenterWidget = new WorkSpace(this);
    setCentralWidget(mCenterWidget);

    setupCommandBar();
    setupStatusBar();
    // connect Menu signal/slots
    // File Menu
    connect(ui->actionExit, SIGNAL(triggered(bool)), this, SLOT(actionExit()));
    connect(ui->actionOpen, SIGNAL(triggered(bool)), this, SLOT(actionOpen()));
    // About Menu
    connect(ui->actionAbout_ART, SIGNAL(triggered(bool))
            , this, SLOT(actionAboutArt()));

    cmdmsg()->addCmdMsg("Android Reverse Toolkit v"
                        + GetCompileVersion () + " by f8left");
    cmdmsg()->setStatusMsg("ready");
    cmdmsg()->setLastLogMsg("init complete");
}

MainWindow::~MainWindow()
{
    saveToConfig ();
    delete ui;
}

void MainWindow::loadFromConfig()
{
    Configuration *config = Config();
    QPoint p;
    p.setX (config->getUint ("MainWindow","x"));
    p.setY (config->getUint ("MainWindow","y"));
    move(p);
    QSize s;
    s.setWidth (config->getUint ("MainWindow","width"));
    s.setHeight (config->getUint ("MainWindow","height"));
    resize (s);
}

void MainWindow::saveToConfig()
{
    Configuration *config = Config();

    QPoint p = pos();
    config->setUint ("MainWindow","x",p.x ());
    config->setUint ("MainWindow","y",p.y ());
    QSize s = size ();
    config->setUint ("MainWindow","width",s.width ());
    config->setUint ("MainWindow","height",s.height ());
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

    connect(cmdMsgUtil, SIGNAL(setStatusMsg(QString)), mStatusLabel, SLOT(logUpdate(QString)));
    connect(cmdMsgUtil, SIGNAL(setLastLogMsg(QString)), mLastLogLabel, SLOT(logUpdate(QString)));
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

void MainWindow::actionExit()
{
    exit(0);
}

void MainWindow::actionOpen()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), "", "apk File (*.apk *.dex)");
    openFile(fileName);
}

void MainWindow::actionAboutArt()
{
    AboutArt about(this);
    about.exec ();
}

void MainWindow::openFile(QString fileName)
{
    //if (mWorkSpace->isProjectOpened()) {
    //    QMessageBox msg(QMessageBox::Warning, "已存在打开的项目", "是否关闭现有项目", QMessageBox::Ok | QMessageBox::Cancel);
//        msg.setWindowIcon(QIcon(":/icons/images/compile-warning.png"));
        //msg.setWindowFlags(msg.windowFlags() & (~Qt::WindowContextHelpButtonHint));
        //if(msg.exec() == QMessageBox::Cancel)
        //    return;
        //else
        //    cmdMsg::executeCommand("CloseProject", cmdMsg::script);
    //}

    if (fileName.isEmpty()) {
        return;
    }
    if (!fileName.endsWith(".apk") && !fileName.endsWith(".dex")) {
        return;
    }

    OpenApk* openWidget = new OpenApk(fileName, this);
    if (openWidget->exec() == QDialog::Accepted) {
        // decompile
        // QString cmd = openWidget->getDecompileCmd();
        // cmdMsg::executeCommand(cmd, cmdMsg::cmd);
        // openProject
        // QStringList args;
        // args << openWidget->getProjectName();
        // cmdMsg::executeCommand("OpenProject", args, cmdMsg::script);
        // setConfig
        // args.clear();
        //args  << "compileCmd" << openWidget->getCompileCmd();
        // cmdMsg::executeCommand("SetConfig", args, cmdMsg::script);
        // UpdateProject
//        args.clear();
//        cmdMsg::executeCommand("UpdateProject", args, cmdMsg::script);
    }
    delete openWidget;
}
