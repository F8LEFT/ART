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

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // connect Menu signal/slots
    // File Menu
    connect(ui->actionExit, SIGNAL(triggered(bool)), this, SLOT(actionExit()));

    // About Menu
    connect(ui->actionAbout_ART, SIGNAL(triggered(bool))
            , this, SLOT(actionAboutArt()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::actionExit()
{
    exit(0);
}

void MainWindow::actionAboutArt()
{
    AboutArt about(this);
    about.exec ();
}
