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

ScriptEngine::ScriptEngine(MainWindow *parent) : QObject((QObject*)parent)
{
    connect(this, SIGNAL(adb(QStringList)), this, SLOT(adbShell(QStringList)));

    // command list
    scripts.insert ("adb", &ScriptEngine::adb);
    scripts.insert ("OpenProject", &ScriptEngine::openProject);
    scripts.insert ("CloseProject", &ScriptEngine::closeProject);
    scripts.insert ("ProjectOpened", &ScriptEngine::projectOpened);
    scripts.insert ("ProjectClosed", &ScriptEngine::projectClosed);

    scripts.insert("OpenFile", &ScriptEngine::openFile);
    scripts.insert("CloseFile", &ScriptEngine::closeFile);
    scripts.insert("SaveFile", &ScriptEngine::saveFile);
    scripts.insert("SaveAll", &ScriptEngine::saveAllFile);
    scripts.insert("CloseAll", &ScriptEngine::closeAllFile);

    scripts.insert("Build", &ScriptEngine::build);
    scripts.insert("Install", &ScriptEngine::install);
    scripts.insert("Run", &ScriptEngine::run);
    scripts.insert("Debug", &ScriptEngine::debug);
    scripts.insert("Stop", &ScriptEngine::stop);
    scripts.insert("Devices", &ScriptEngine::devices);
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
        emit finished();
    } else {
        cmdmsg ()->addCmdMsg("script proc not found: " + proc);
        emit errorOccurred(QProcess::FailedToStart);
    }
}

void ScriptEngine::adbShell(QStringList args)
{
    QString adbPath = GetThirdPartyPath ("adb") + "/" + GetSystemType() + "/adb";
    cmdexec(adbPath, args, CmdMsg::ProcType::cmd);
}
