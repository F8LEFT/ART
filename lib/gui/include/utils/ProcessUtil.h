//===- ProcessUtil.h - ART-GUI utilpart -------------------------*- C++ -*-===//
//
//                     ANDROID REVERSE TOOLKIT
//
// This file is distributed under the GNU GENERAL PUBLIC LICENSE
// V3 License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// ProcessUtil can execute cmd, python and script.
//
//===----------------------------------------------------------------------===//
#ifndef PROCESSUTIL_H
#define PROCESSUTIL_H

#include <QProcess>
#include <QString>
#include <QList>
#include "CmdMsgUtil.h"
#include "ScriptEngine.h"

class ProcessUtil : public QProcess
{
    Q_OBJECT

public:
    ProcessUtil(QObject *parent = Q_NULLPTR);

signals:
    void ProcFinish(CmdMsg::ProcInfo info);
    void onExecNext();

protected slots:
    void addProc(CmdMsg::ProcInfo info);
    void onProcFinish();
    void onProcError(QProcess::ProcessError error);

private:
    void execNext();
    void exec(const CmdMsg::ProcInfo& info);

    QList<CmdMsg::ProcInfo> mProcList;
    bool isBusy = false;
    ScriptEngine* script;
};

class ProcessOneTime: public QProcess {
    Q_OBJECT

public:
    ProcessOneTime(CmdMsg::ProcInfo info, QObject *parent = Q_NULLPTR);
protected slots:
    void onProcFinish();
    void onProcError(QProcess::ProcessError error);
};

#endif // PROCESSUTIL_H
