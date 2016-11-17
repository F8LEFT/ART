//===- StringUtil.cpp - ART-GUI utilpart ------------------------*- C++ -*-===//
//
//                     ANDROID REVERSE TOOLKIT
//
// This file is distributed under the GNU GENERAL PUBLIC LICENSE
// V3 License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
#include "utils/StringUtil.h"

#include <QApplication>

#include <stdint.h>

QString ToDateString (const QDate &date)
{
    static const char* months[] =
            {
                    "Jan",
                    "Feb",
                    "Mar",
                    "Arp",
                    "May",
                    "Jun",
                    "Jul",
                    "Aug",
                    "Sep",
                    "Oct",
                    "Nov",
                    "Dec"
            };
    return QString().sprintf("%s %d %d", months[date.month() - 1], date.day(), date.year());
}

QString GetProjectsPath (const QString& expend)
{
    if(expend.isEmpty ()) {
        return "./Projects";
    } else {
        return "./Projects/" + expend;
    }
}

QString GetProjectsProjectPath (const QString &expend)
{
    Q_ASSERT (!expend.isEmpty () && "expend should be empty");
    return "./Projects/" + expend + "/Project";
}

QString GetThirdPartyPath (const QString& expend)
{
    if(expend.isEmpty ()) {
        return "./thirdparty";
    } else {
        return "./thirdparty/" + expend;
    }
}

QString GetCfgsPath (const QString &expend)
{
    if(expend.isEmpty ()) {
        return "./cfgs";
    } else {
        return "./cfgs/" + expend;
    }
}

QString GetSystemType ()
{
#if defined(UNIX)
    return "unix";
#elif defined(APPLE)
    return "mac";
#else
    return "win";
#endif
}




