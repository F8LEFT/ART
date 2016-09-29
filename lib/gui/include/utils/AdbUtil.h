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
class AdbUtil
{
public:
    AdbUtil();

    QStringList execute(QString arg, bool waitForRet = true);
    QStringList execute(QStringList args, bool waitForRet = true);
private:
    QProcess mProcess;
};
#endif //PROJECT_ADBUTIL_H
