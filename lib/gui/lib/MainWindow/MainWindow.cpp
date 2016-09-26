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

#include "AboutArt/AboutArt.h"
#include "OpenApk/OpenApk.h"

#include <QMimeData>
#include <QMessageBox>
#include <QDragEnterEvent>
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    mCenterWidget = new WorkSpace(this);
    setCentralWidget(mCenterWidget);
    // connect Menu signal/slots
    // File Menu
    connect(ui->actionExit, SIGNAL(triggered(bool)), this, SLOT(actionExit()));
    connect(ui->actionOpen, SIGNAL(triggered(bool)), this, SLOT(actionOpen()));
    // About Menu
    connect(ui->actionAbout_ART, SIGNAL(triggered(bool))
            , this, SLOT(actionAboutArt()));
}

MainWindow::~MainWindow()
{
    delete ui;
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
