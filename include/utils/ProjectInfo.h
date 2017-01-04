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
#include <QObject>

class ProjectInfo: public QObject {
public:
    struct SConfig {
        QString m_deviceId;
    };
    struct PConfig {
        QString m_projectName;
        QString m_compileCmd;
        QString m_decompileCmd;

        QString m_packageName;
        QString m_activityEntryName;
    };
    struct BreakPoint {
        QString m_sourceFile;
        QString m_classSig;
        QString m_methodName;
        QString m_methodSign;
// codeIdx? or line number?
    };
private:
    Q_OBJECT
public:
    static ProjectInfo* openProject(QString name);
    static ProjectInfo* current() { return m_current; }
    static ProjectInfo* last() { return m_last; };
    static bool closeProject();
    static SConfig& sConfig() { return m_sconfig; }
    static void saveAllConfig();

    static bool isProjectOpened() { return m_current != nullptr; }

    PConfig& config() { return m_config; };

    QString getRootPath();
    QString getSourcePath();
    QString getBuildPath();
    QString getConfigPath();

private:
    ProjectInfo(QString name);
    static SConfig m_sconfig;

    static QMap<QString, ProjectInfo*> m_infoMap;
    static ProjectInfo* m_current;
    static ProjectInfo* m_last;

    PConfig m_config;
};



#endif //PROJECT_PROJECTINFO_H
