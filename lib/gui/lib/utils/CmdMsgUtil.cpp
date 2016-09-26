//===- CmdMsgUtil.cpp - ART-GUI utilpart ------------------------*- C++ -*-===//
//
//                     ANDROID REVERSE TOOLKIT
//
// This file is distributed under the GNU GENERAL PUBLIC LICENSE
// V3 License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
#include "utils/CmdMsgUtil.h"

CmdMsg::CmdMsg (QObject *parent): QObject (parent)
{
}

CmdMsg::~CmdMsg ()
{

}

CmdMsg *CmdMsg::instance ()
{
    static CmdMsg* mPtr = nullptr;
    if(mPtr == nullptr) {
        mPtr = new CmdMsg;
    }
    return mPtr;
}


void CmdMsg::executeCommand(QString cmd, ProcType t, bool silence)
{
    QStringList args = cmd.split(' ', QString::SkipEmptyParts);
    if (args.size() > 0) {
        QString proc = args.front();
        args.pop_front();       // just pop process
        executeCommand(proc, args, t, silence);
    }
}

void CmdMsg::executeCommand(QString proc, QString cmd, ProcType t, bool silence)
{
    QStringList args = cmd.split(' ', QString::SkipEmptyParts);
    executeCommand(proc, args, t, silence);
}

void CmdMsg::executeCommand(QString proc, QStringList args, ProcType t, bool silence)
{
    ProcInfo info;
    info.proc = proc;
    info.args = args;
    info.t = t;
    info.silence = silence;

    emit onExecuteCommand (info);
}


QString CmdMsg::procTypeDescription(CmdMsg::ProcType t)
{
    switch (t) {
        case ProcType::cmd:
            return QString("cmd");
        case ProcType::python:
            return QString("python");
        case ProcType::script:
            return QString("script");
        default:
            return QString("unknown");
    }
}

CmdMsg::ProcType CmdMsg::getProcType(QString p)
{
    if (p == "cmd")
        return ProcType::cmd;
    else if (p == "python")
        return ProcType::python;
    else if (p == "script")
        return ProcType::script;
    else
        return ProcType::unknown;
}