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

QString GetSoftPath ()
{
    return QApplication::applicationDirPath();
}
