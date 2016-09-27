//===- main.cpp - ART-GUI main ----------------------------------*- C++ -*-===//
//
//                     ANDROID REVERSE TOOLKIT
//
// This file is distributed under the GNU GENERAL PUBLIC LICENSE
// V3 License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file defines the main function for ART-GUI.
//
//===----------------------------------------------------------------------===//
#include "MainWindow/MainWindow.h"
#include <QApplication>
#include <utils/Configuration.h>
#include <utils/ProcessUtil.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    // init global class
    auto conf = Configuration::instance ();
    ProcessUtil process;

    MainWindow* w = new MainWindow;
    w->show();
    int ret = a.exec();
    delete w;

    // auto save config
    delete conf;

    return ret;
}
