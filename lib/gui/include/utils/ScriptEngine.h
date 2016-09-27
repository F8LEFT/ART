//===- ScriptEngine.h - ART-GUI utilpart ------------------------*- C++ -*-===//
//
//                     ANDROID REVERSE TOOLKIT
//
// This file is distributed under the GNU GENERAL PUBLIC LICENSE
// V3 License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// The file defines script for this soft.
//
//===----------------------------------------------------------------------===//
#ifndef SCRIPTENGINE_H
#define SCRIPTENGINE_H

#include <QObject>
#include <QString>
#include <QStringList>
#include <QMap>
#include <QProcess>
class MainWindow;


class ScriptEngine : public QObject
{
    Q_OBJECT

    typedef void (ScriptEngine::*scriptHandle)(QStringList);
public:
    explicit ScriptEngine(MainWindow *parent = 0);
    ~ScriptEngine();
    static ScriptEngine* instance();

    void exec(QString proc, QStringList args);

signals:
    void finished();
    void errorOccurred(QProcess::ProcessError error);
signals:
    // script(args) handleby
    // adb(args) ScriptEngine.cpp
    void adb(QStringList);

    // OpenProject(projectName)   ProjectTab.cpp
    void openProject(QStringList);
    // CloseProject()             ProjectTab.cpp
    void closeProject(QStringList);
    // ProjectOpened(projectName) ProjectTab.cpp, WorkSpace.cpp
    void projectOpened(QStringList);    // reserved by ART
    // ProjectClosed()            ProjectTab.cpp, WorkSpace.cpp
    void projectClosed(QStringList);    // reserved by ART

    // OpenFile(filePath1, ...)
    void openFile(QStringList);
    // CloseFile(filePath1, ...)
    void closeFile(QStringList);
    // SaveFile(filePath1, ...)
    void saveFile(QStringList);
    // SaveAllFile()
    void saveAllFile(QStringList);
    // CloseAllFile()
    void closeAllFile(QStringList);

public slots:
    void adbShell(QStringList);

private:
    QMap<QString, scriptHandle> scripts;
};

#endif // SCRIPTENGINE_H
