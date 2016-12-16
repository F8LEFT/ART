//===- ScriptEngine.cpp - ART-GUI utilpart ----------------------*- C++ -*-===//
//
//                     ANDROID REVERSE TOOLKIT
//
// This file is distributed under the GNU GENERAL PUBLIC LICENSE
// V3 License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
#include "utils/ScriptEngine.h"
#include <utils/CmdMsgUtil.h>
#include <utils/StringUtil.h>
#include <QtGlobal>
#include <utils/Configuration.h>

ScriptEngine::ScriptEngine(MainWindow *parent) : QObject((QObject*)parent)
{
    connect(this, SIGNAL(adb(QStringList)), this, SLOT(adbShell(QStringList)));

    // command list
    scripts.insert("adb", &ScriptEngine::adb);
    scripts.insert ("OpenWindow", &ScriptEngine::openWindow);

    scripts.insert("OpenProject", &ScriptEngine::openProject);
    scripts.insert("CloseProject", &ScriptEngine::closeProject);
    scripts.insert("ProjectOpened", &ScriptEngine::projectOpened);
    scripts.insert("ProjectClosed", &ScriptEngine::projectClosed);

    scripts.insert("OpenFile", &ScriptEngine::openFile);
    scripts.insert("CloseFile", &ScriptEngine::closeFile);
    scripts.insert("SaveFile", &ScriptEngine::saveFile);
    scripts.insert("SaveAll", &ScriptEngine::saveAllFile);
    scripts.insert("CloseAll", &ScriptEngine::closeAllFile);
    scripts.insert("Undo", &ScriptEngine::undo);
    scripts.insert("Redo", &ScriptEngine::redo);
    scripts.insert("Cut", &ScriptEngine::cut);
    scripts.insert("Copy", &ScriptEngine::copy);
    scripts.insert("Paste", &ScriptEngine::paste);
    scripts.insert("Delete", &ScriptEngine::deleteR);
    scripts.insert("SelectAll", &ScriptEngine::selectAll);
    scripts.insert("Find", &ScriptEngine::find);
    scripts.insert("GotoLine", &ScriptEngine::gotoLine);
    scripts.insert("FindAdvance", &ScriptEngine::findAdvance);


    scripts.insert("Build", &ScriptEngine::build);
    scripts.insert("Install", &ScriptEngine::install);
    scripts.insert("Run", &ScriptEngine::run);
    scripts.insert("Debug", &ScriptEngine::debug);
    scripts.insert("Stop", &ScriptEngine::stop);
    scripts.insert("Devices", &ScriptEngine::devices);

    scripts.insert("DebugStart", &ScriptEngine::debugStart);

    scripts.insert("ThemeUpdate", &ScriptEngine::themeUpdate);
}

ScriptEngine::~ScriptEngine()
{

}

ScriptEngine *ScriptEngine::instance()
{
    static ScriptEngine* mPtr = nullptr;
    if (mPtr == nullptr) {
        mPtr = new ScriptEngine;
    }
    return mPtr;
}

void ScriptEngine::exec(QString proc, QStringList args)
{
    auto s = scripts.find(proc);
    if (s != scripts.end()) {
        emit (this->*(s.value()))(args);
    } else {
        cmdmsg ()->addCmdMsg("script proc not found: " + proc);
    }
}

QStringList ScriptEngine::getAllCommand ()
{
    return scripts.keys ();
}

void ScriptEngine::adbShell(QStringList args)
{
    QString adbPath;
    if(ConfigBool("System", "UseDefaultAdb")) {
        adbPath = GetThirdPartyPath ("adb") + "/adb";
    } else {
        adbPath = "adb";
    }

    cmdexec(adbPath, args, CmdMsg::ProcType::cmd);
}

