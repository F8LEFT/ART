//===- ProjectInfo.h - ART-GUI utilpart -------------------------*- C++ -*-===//
//
//                     ANDROID REVERSE TOOLKIT
//
// This file is distributed under the GNU GENERAL PUBLIC LICENSE
// V3 License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file saves project information. Such as project name, compile cmd,
// decompile cmd, etc.
//
//===----------------------------------------------------------------------===//

#ifndef PROJECT_PROJECTINFO_H
#define PROJECT_PROJECTINFO_H

#include <QMap>
#include <QString>

class ProjectInfo {
public:
    // make sure this has only one instance
    static ProjectInfo* instance();

    QString getInfo(QString key);
    void setInfo(QString key, QString value);
    void reset();
    // such key can be used (key, set by)
    //projectName       OpenApk.cpp
    //apkToolPath       OpenApk.cpp
    //compileCmd        OpenApk.cpp
    //decompileCmd      OpenApk.cpp

private:
    ProjectInfo();
    QMap<QString, QString> mMap;
};

#endif //PROJECT_PROJECTINFO_H
