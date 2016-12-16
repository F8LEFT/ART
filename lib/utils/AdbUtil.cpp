//===- AdbUtil.cpp - ART-GUI  ----------------------------------*- C++ -*-===//
//
//                     ANDROID REVERSE TOOLKIT
//
// This file is distributed under the GNU GENERAL PUBLIC LICENSE
// V3 License. See LICENSE.TXT for details.
//
//===---------------------------------------------------------------------===//
#include "utils/AdbUtil.h"
#include "utils/StringUtil.h"

#include <utils/Configuration.h>
#include <utils/ProjectInfo.h>


AdbUtil::AdbUtil()
{

}

QStringList AdbUtil::execute(QString arg, bool waitForRet)
{
    QStringList args = arg.split(' ', QString::SkipEmptyParts);
    return execute(args, waitForRet);
}

QStringList AdbUtil::execute(QStringList args, bool waitForRet)
{
    QString adbPath;
    if(ConfigBool("System", "UseDefaultAdb")) {
        adbPath = GetThirdPartyPath ("adb") + "/adb";
    } else {
        adbPath = "adb";
    }
    mProcess.start(adbPath, args);
    if (waitForRet) {
        mProcess.waitForFinished(-1);
        QString ret = QString().fromLatin1(mProcess.readAll());
        QStringList rel = ret.split(QRegExp("[\\r\\n]"), QString::SkipEmptyParts);
        return rel;
    }
    return QStringList();
}

QVector<AdbUtil::ProcessInfo> AdbUtil::getProcessInfo(QString deviceid)
{
    QStringList pidList = deviceid.isEmpty() ?
                          execute("shell ps"):
                          execute("-s " + deviceid + " shell ps");
    QVector<AdbUtil::ProcessInfo> vector;

    for(auto &info : pidList) {
        QStringList procInfo = info.split(QRegExp("\\s+"), QString::SkipEmptyParts);
        if(procInfo.size() != 9) {
            continue;
        }
        vector.push_back({procInfo[0],            // user
                          procInfo[1].toUInt(),   // pid
                          procInfo[2].toUInt(),   // ppid
                          procInfo[3].toUInt(),   // vsize
                          procInfo[4].toUInt(),   // rss
                          procInfo[5],            // wchan
                          procInfo[6].toUInt(nullptr, 16),    // PC
                          procInfo[7],            // status
                          procInfo[8]             // name
                         });

    }
    return vector;
}
