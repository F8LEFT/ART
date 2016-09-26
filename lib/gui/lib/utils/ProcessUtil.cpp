//===- ProcessUtil.cpp - ART-GUI utilpart -----------------------*- C++ -*-===//
//
//                     ANDROID REVERSE TOOLKIT
//
// This file is distributed under the GNU GENERAL PUBLIC LICENSE
// V3 License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
#include "utils/ProcessUtil.h"
#include <utils/StringUtil.h>
#include <QApplication>

ProcessUtil::ProcessUtil(QObject *parent):
    QProcess(parent)
{
    script = ScriptEngine::instance();

    connect(this, SIGNAL(finished(int)), this, SLOT(onProcFinish()));
    connect(this, SIGNAL(errorOccurred(QProcess::ProcessError)),
            this, SLOT(onProcError(QProcess::ProcessError)));
    connect(script, SIGNAL(finished()), this, SLOT(onProcFinish()));
    connect(script, SIGNAL(errorOccurred(QProcess::ProcessError)),
            this, SLOT(onProcError(QProcess::ProcessError)));

    connect(this, SIGNAL (onExecNext ()), this, SLOT (execNext ()));

    setWorkingDirectory(GetSoftPath());
}

void ProcessUtil::addProc(CmdMsg::ProcInfo info)
{
    if (info.toqueue) {
        mProcList.push_back(info);
        if (!isBusy) {
            isBusy = true;
            onExecNext ();
        }
    } else {
        new ProcessOneTime(info);
    }

}

void ProcessUtil::onProcFinish()
{
    CmdMsg::ProcInfo info = mProcList.front();
    emit ProcFinish(info);
    emit onExecNext();
}

void ProcessUtil::onProcError(QProcess::ProcessError error)
{
    if (error == QProcess::FailedToStart) {
        cmdmsg()->addCmdMsg("Unable to start process");
        emit onExecNext();
    }
}

void ProcessUtil::execNext()
{
    CmdMsg::ProcInfo info = mProcList.front();
    mProcList.pop_front();

    if (!mProcList.isEmpty()) {
        CmdMsg::ProcInfo next = mProcList.front();
        exec(next);
    } else {
        isBusy = false;
    }
}

void ProcessUtil::exec(const CmdMsg::ProcInfo &info)
{
    if (!info.silence) {
        QString cmdHint = CmdMsg::procTypeDescription(info.t) + ": " + info.proc;
        foreach (QString s, info.args) {
            cmdHint += " " + s;
        }
        cmdmsg()->addCmdMsg(cmdHint);
    }

    switch(info.t) {
    case CmdMsg::cmd:
        start(info.proc, info.args);
        break;
    //case cmdMsg::python:
    //    break;
    case CmdMsg::script:
        script->exec(info.proc, info.args);
        break;
    default:
        onExecNext ();
        break;
    }

}

ProcessOneTime::ProcessOneTime (CmdMsg::ProcInfo info,QObject *parent)
    : QProcess(parent)
{
    auto script = ScriptEngine::instance();

    connect(this, SIGNAL(finished(int)), this, SLOT(onProcFinish()));
    connect(this, SIGNAL(errorOccurred(QProcess::ProcessError)),
            this, SLOT(onProcError(QProcess::ProcessError)));
    connect(script, SIGNAL(finished()), this, SLOT(onProcFinish()));
    connect(script, SIGNAL(errorOccurred(QProcess::ProcessError)),
            this, SLOT(onProcError(QProcess::ProcessError)));

    if (!info.silence) {
        QString cmdHint = CmdMsg::procTypeDescription(info.t) + ": " + info.proc;
                foreach (QString s, info.args) {
                cmdHint += " " + s;
            }
        cmdmsg()->addCmdMsg(cmdHint);
    }

    switch(info.t) {
        case CmdMsg::cmd:
            start(info.proc, info.args);
            break;
            //case cmdMsg::python:
            //    break;
        case CmdMsg::script:
            script->exec(info.proc, info.args);
            break;
        default:
            break;
    }
}

void ProcessOneTime::onProcFinish ()
{
    this->deleteLater ();
}

void ProcessOneTime::onProcError (QProcess::ProcessError error)
{
    if (error == QProcess::FailedToStart) {
        cmdmsg()->addCmdMsg("Unable to start process");
    }
    this->deleteLater ();
}

