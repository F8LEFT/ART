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

class CmdMsg: public QObject {
    Q_OBJECT

public:
    enum ProcType {
        cmd,
        python,
        script,
        unknown,
    };

    struct ProcInfo {
        QString proc;
        QStringList args;
        ProcType t;
        bool silence;
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
public slots:

};


#endif //PROJECT_CMDMSGUTIL_H
