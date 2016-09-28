//
// Created by f8left on 16-9-28.
//
#include "utils/AdbUtil.h"
#include "utils/StringUtil.h"

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
    QString adbPath = GetThirdPartyPath ("adb") + "/" + GetSystemType() + "/adb";
    mProcess.start(adbPath, args);
    if (waitForRet) {
        mProcess.waitForFinished(-1);
        QString ret = QString().fromLatin1(mProcess.readAll());
        QStringList rel = ret.split(QRegExp("[\\r\\n]"), QString::SkipEmptyParts);
        return rel;
    }
    return QStringList();
}