//
// Created by f8left on 16-9-28.
//

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
