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

ProcessUtil::ProcessUtil(QObject *parent)
        : QThread(parent)
{
    mInfoSemaphore = new QSemaphore(0);
    mProcessMutex = new QMutex();
    mProcess = new ProcessOneTime();

    connect(mProcess, SIGNAL(finished(int)), this, SLOT(onProcFinish()));
    connect(mProcess, SIGNAL(errorOccurred(QProcess::ProcessError)),
            this, SLOT(onProcFinish()));
    connect(this, SIGNAL(execProcess (CmdMsg::ProcInfo)),
            mProcess, SLOT (exec(CmdMsg::ProcInfo)), Qt::QueuedConnection);

    connect(this, SIGNAL(finished()), this, SLOT(deleteLater()));

    auto cmdutil = cmdmsg ();
    connect(cmdutil, SIGNAL(onExecuteCommand(CmdMsg::ProcInfo)),
            this, SLOT(addProc(CmdMsg::ProcInfo)));
}

void ProcessUtil::addProc(const CmdMsg::ProcInfo & info)
{
    if (info.toqueue) {
        mProcList.push_back(info);
        mInfoSemaphore->release ();
        return;
    }

    // invokd directly
    if(info.t == CmdMsg::cmd) {
        auto process = new ProcessOneTime(this);
        connect(process, SIGNAL(finished(int)), process, SLOT(deleteLater()));
        connect(process, SIGNAL(errorOccurred(QProcess::ProcessError)),
                process, SLOT(deleteLater()));
        process->exec (info);
        return;
    }
    if(info.t == CmdMsg::script) {
        ScriptEngine::instance()->exec(info.proc, info.args);
        return;
    }
}

void ProcessUtil::onProcFinish()
{
    emit ProcFinish(mCurInfo);
    mProcessMutex->unlock ();
}

void ProcessUtil::run ()
{
    while(true) {
        mInfoSemaphore->acquire ();
        mProcessMutex->lock ();

        mCurInfo = mProcList.front();
        mProcList.pop_front();

        emit execProcess(mCurInfo);
    }
}

ProcessOneTime::ProcessOneTime (QObject *parent)
    : QProcess(parent)
{
    mScript = ScriptEngine::instance();

    connect(this, SIGNAL(errorOccurred(QProcess::ProcessError)),
            this, SLOT(onProcError(QProcess::ProcessError)));

    connect(this, SIGNAL(readyReadStandardOutput()), this, SLOT(onProcessStdRead()));
    connect(this, SIGNAL(readyReadStandardError()), this, SLOT(onProcessErrRead()));

    setWorkingDirectory(GetSoftPath());
}

void ProcessOneTime::exec(const CmdMsg::ProcInfo &info)
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
            start(info.proc, info.args);    //  wait for finish signal
            break;
        case CmdMsg::python:
            emit finished (0);
            break;
        case CmdMsg::script:
            mScript->exec(info.proc, info.args);
            emit finished (0);
            break;
        default:
            emit finished (0);
            break;
    }
}


void ProcessOneTime::onProcError (QProcess::ProcessError error)
{
    if (error == QProcess::FailedToStart) {
        cmdmsg()->addCmdMsg("Unable to start process");
    }
}

void ProcessOneTime::onProcessStdRead ()
{
    cmdmsg()->addCmdMsg(QString::fromLocal8Bit(readAllStandardOutput()));
}

void ProcessOneTime::onProcessErrRead ()
{
    cmdmsg()->addCmdMsg(QString::fromLocal8Bit(readAllStandardError()));
}

