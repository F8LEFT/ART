//===- AdbUtil.h - ART-GUI  ------------------------------------*- C++ -*-===//
//
//                     ANDROID REVERSE TOOLKIT
//
// This file is distributed under the GNU GENERAL PUBLIC LICENSE
// V3 License. See LICENSE.TXT for details.
//
//===---------------------------------------------------------------------===//
//
// AdbUtil will execute adb command.
//
//===----------------------------------------------------------------------===//
#ifndef PROJECT_ADBUTIL_H
#define PROJECT_ADBUTIL_H
#include <QString>
#include <QProcess>
#include <QVector>
class AdbUtil
{
public:
    struct ProcessInfo {
        QString user;
        uint32_t pid;
        uint32_t ppid;
        uint32_t vsize;
        uint32_t rss;
        QString wchan;
        uint32_t pc;
        QString status;
        QString name;
    };


    AdbUtil();

    QStringList execute(QString arg, bool waitForRet = true);
    QStringList execute(QStringList args, bool waitForRet = true);

    /* get current device process list.
     * ret map for <name, procinfo>
     * */
    QVector<ProcessInfo> getProcessInfo(QString deviceid = QString());
private:
    QProcess mProcess;
};
#endif //PROJECT_ADBUTIL_H
