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
#include "art_version.h"

QString ToDateString (const QDate &date);

static QDate GetCompileDate ()
{
    return QLocale("en_US").toDate(QString(__DATE__).simplified(), "MMM d yyyy");
}

static QString GetCompileVersion ()
{
    return ART_VERSION_STRING;
}

static int GetCompileMajor ()
{
    return ART_VERSION_MAJOR;
}

static int GetCompileMinor ()
{
    return ART_VERSION_MINOR;
}

static int GetCompilePatch ()
{
    return ART_VERSION_PATCH;
}

#define GetSoftPath QApplication::applicationDirPath

QString GetProjectsPath(const QString& expend = QString());
QString GetProjectsProjectPath(const QString& expend);
QString GetThirdPartyPath(const QString& expend = QString());
QString GetCfgsPath(const QString& expend = QString());

QString GetSystemType();

#endif //PROJECT_STRINGUTIL_H_H
