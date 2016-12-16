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

#include <QDebug>

ProcessUtil::ProcessUtil(QObject *parent)
        : QThread(parent)
{
    mInfoSemaphore = new QSemaphore(0);

    connect(this, SIGNAL(finished()), this, SLOT(deleteLater()));

    auto cmdutil = cmdmsg ();
    connect(cmdutil, SIGNAL(onExecuteCommand(CmdMsg::ProcInfo)),
            this, SLOT(addProc(CmdMsg::ProcInfo)));

    auto script = ScriptEngine::instance();
    connect(script, SIGNAL(projectClosed(QStringList)),
            this, SLOT(onProjectClosed()));
}

ProcessUtil::~ProcessUtil ()
{
    mContinue = false;
    wait ();
    mProcess->deleteLater ();
    delete mInfoSemaphore;
}


void ProcessUtil::addProc(const CmdMsg::ProcInfo & info)
{
    if (info.toqueue) {
        mInfoMutex.lock();
        auto i = 0, size = mProcList.size();
        for(; i < size; i++) {
            if(mProcList.at(i).level < info.level) {
                break;
            }
        }
        mProcList.insert(i, info);
        mInfoMutex.unlock();

        mInfoSemaphore->release ();
        return;
    }

    // invokd directly
    if(info.t == CmdMsg::cmd) {
        auto process = new ProcessOneTime(this);
        connect(process, SIGNAL(finished(int)), process, SLOT(deleteLater()));
        connect(process, SIGNAL(errorOccurred(QProcess::ProcessError)),
                process, SLOT(deleteLater()));
        if(process->exec (info)) {
            process->deleteLater ();
        }
        return;
    }
    if(info.t == CmdMsg::script) {
        ScriptEngine::instance()->exec(info.proc, info.args);
        return;
    }
}

void ProcessUtil::onProjectClosed ()
{
    mInfoMutex.lock();
    int n = mProcList.size ();
    mInfoSemaphore->acquire (n);
    mProcList.clear ();
    mInfoMutex.unlock();
}

void ProcessUtil::run ()
{
    mProcess = new ProcessOneTime();
    while(mContinue) {
        mInfoSemaphore->acquire ();

        mInfoMutex.lock();
        mCurInfo = mProcList.front();
        mProcList.pop_front();
        mInfoMutex.unlock();

        qDebug() << "exec command " << mCurInfo.proc << mCurInfo.args;
        if(!mProcess->exec (mCurInfo)) {
            mProcess->waitForFinished (-1);
        }
        emit ProcFinish(mCurInfo);
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

bool ProcessOneTime::exec(const CmdMsg::ProcInfo &info)
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
            return false;
        case CmdMsg::python:
            break;
        case CmdMsg::script:
            mScript->exec(info.proc, info.args);
            break;
        default:
            break;
    }
    return true;
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

