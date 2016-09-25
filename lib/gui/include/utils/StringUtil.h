//===- StringUtil.h - ART-GUI utilpart --------------------------*- C++ -*-===//
//
//                     ANDROID REVERSE TOOLKIT
//
// This file is distributed under the GNU GENERAL PUBLIC LICENSE
// V3 License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file defines string format.
//
//===----------------------------------------------------------------------===//

#ifndef PROJECT_STRINGUTIL_H_H
#define PROJECT_STRINGUTIL_H_H


#include <sstream>
#include <iomanip>
#include <QString>
#include <QDateTime>
#include <QLocale>

QString ToDateString (const QDate &date);

static QDate GetCompileDate ()
{
    return QLocale("en_US").toDate(QString(__DATE__).simplified(), "MMM d yyyy");
}

static QString GetCompileVersion ()
{
    return ARTGUI_VERSION;
}

static int GetCompileMajor ()
{
    return ARTGUI_MAJOR;
}

static int GetCompileMinor ()
{
    return ARTGUI_MINOR;
}

static int GetCompilePatch ()
{
    return ARTGUI_PATCH;
}
#endif //PROJECT_STRINGUTIL_H_H
