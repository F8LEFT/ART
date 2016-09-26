//===- CmdMsgUtil.h - ART-GUI utilpart --------------------------*- C++ -*-===//
//
//                     ANDROID REVERSE TOOLKIT
//
// This file is distributed under the GNU GENERAL PUBLIC LICENSE
// V3 License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file defines CmdMsgUtil for executing command, script, and show
//  execution results for user.
//
//===----------------------------------------------------------------------===//
#ifndef PROJECT_CMDMSGUTIL_H
#define PROJECT_CMDMSGUTIL_H

#include <QString>
#include <QStringList>
#include <QtCore/QObject>

#define cmdmsg() CmdMsg::instance()
#define cmdexec cmdmsg()->executeCommand

class CmdMsg: public QObject {
    Q_OBJECT

public:
    enum ProcType {
        cmd,            // shell
        python,         // python script
        script,         // ART script, see ScriptEngine
        unknown,
    };

    struct ProcInfo {
        QString proc;
        QStringList args;
        ProcType t;
        bool silence;       // no message hint
        bool toqueue;       // add to queue, wait for last proc finish
    };
private:
    CmdMsg(QObject *parent = 0);

public:
    ~CmdMsg ();

    static CmdMsg* instance();
signals:
    void addCmdMsg(QString s);
    void setStatusMsg(QString s);
    void setLastLogMsg(QString s);
    void onExecuteCommand(ProcInfo info);
public:
    void executeCommand(QString cmd, ProcType t = script,
                        bool silence = true, bool toqueue = true);
    void executeCommand(QString proc, QString args, ProcType t = script,
                        bool silence = true, bool toqueue = true);
    void executeCommand(QString proc, QStringList args, ProcType t = script,
                        bool silence = true, bool toqueue = true);

    static QString procTypeDescription(ProcType t);
    static ProcType getProcType(QString p);
};


#endif //PROJECT_CMDMSGUTIL_H
