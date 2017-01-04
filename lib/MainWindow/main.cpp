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
#include <utils/StringUtil.h>

#include <QTranslator>
#include <QLibraryInfo>
#include <QLocale>
#include <QDebug>
#include <QStandardPaths>
#include <utils/ProjectInfo.h>

bool loadTranslation(QApplication * app);

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QDir::setCurrent (GetSoftPath());

//    "/home/f8left/.local/share" first directory
//    qDebug() << QStandardPaths::standardLocations(QStandardPaths::ApplicationsLocation);
//    dirs = QStandardPaths::locateAll(QStandardPaths::GenericDataLocation, QStringLiteral("org.kde.syntax-highlighting/themes"), QStandardPaths::LocateDirectory);

    auto conf = Configuration::instance ();
    loadTranslation (&a);

//    qRegisterMetaType<>("CmdMsg::ProcInfo");

    // init global class
    ScriptEngine::instance();

    ProcessUtil *process = new ProcessUtil();
    process->start ();

    MainWindow* w = new MainWindow;
    w->show();
    int ret = a.exec();
    ProjectInfo::saveAllConfig();
    delete w;

    // auto save config
    delete conf;

    return ret;
}


bool loadTranslation(QApplication * app)
{
    QTranslator *translator = new QTranslator(app);

    auto loadlan = ConfigString("System", "language");
    if(loadlan == "system") {
        QLocale locale;
        auto uiLanguages = locale.system ().uiLanguages ();
        foreach(QString language, uiLanguages ) {
                qDebug() << "loading translate file " << language;
                if(translator->load (QString("qt_%1").arg(language),
                       QLibraryInfo::location(QLibraryInfo::TranslationsPath))) {
                    app->installTranslator(translator);
                    break;
                }
            }
    } else {
        if(translator->load (QString("qt_%1").arg(loadlan),
                             QLibraryInfo::location(QLibraryInfo::TranslationsPath))) {
            app->installTranslator(translator);
        }
    }
    return true;
}
