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

#include "CmdMsgUtil.h"
#include "ScriptEngine.h"

#include <QProcess>
#include <QString>
#include <QList>
#include <QTimer>
#include <QThread>
#include <QSemaphore>
#include <QMutex>

class ProcessOneTime;
class ProcessUtil : public QThread
{
    Q_OBJECT

public:
    ProcessUtil(QObject *parent = Q_NULLPTR);
    ~ProcessUtil ();
signals:
    void ProcFinish(const CmdMsg::ProcInfo &info);

protected slots:
    void addProc(const CmdMsg::ProcInfo &info);

    void onProjectClosed();
protected:
    void run();

private:

    QList<CmdMsg::ProcInfo> mProcList;

    CmdMsg::ProcInfo mCurInfo;
    ProcessOneTime *mProcess;
    QSemaphore *mInfoSemaphore;

    bool mContinue = true;
};


class ProcessOneTime: public QProcess {
    Q_OBJECT

public:
    ProcessOneTime(QObject *parent = Q_NULLPTR);

protected slots:
    void onProcError(QProcess::ProcessError error);
    void onProcessStdRead();
    void onProcessErrRead();
public slots:
    // the command is finished when return true
    bool exec(const CmdMsg::ProcInfo &info);

private:
    ScriptEngine* mScript;
};

#endif // PROCESSUTIL_H
