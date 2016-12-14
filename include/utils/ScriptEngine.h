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
    QStringList getAllCommand();

signals:
    // script(args) handleby
    // adb(args) ScriptEngine.cpp
    void adb(QStringList);

    // ui
    // OpenWindow(windowName)
    void openWindow(QStringList);

    // ProjectManager
    // OpenProject(projectName)   ProjectTab.cpp
    void openProject(QStringList);
    // CloseProject()             ProjectTab.cpp
    void closeProject(QStringList);
    // ProjectOpened(projectName) ProjectTab.cpp, WorkSpace.cpp
    void projectOpened(QStringList);    // reserved by ART
    // ProjectClosed()            ProjectTab.cpp, WorkSpace.cpp
    void projectClosed(QStringList);    // reserved by ART

    // Editor Manager
    // OpenFile(filePath1, [filePath2, ...])
    void openFile(QStringList);
    // CloseFile(filePath1, [filePath2, ...])
    void closeFile(QStringList);
    // SaveFile(filePath1, [filePath2, ...])
    void saveFile(QStringList);
    // SaveAll()
    void saveAllFile(QStringList);
    // CloseAll()
    void closeAllFile(QStringList);
    // Undo();
    void undo(QStringList);
    // Redo();
    void redo(QStringList);
    // Cut();
    void cut(QStringList);
    // Copy();
    void copy(QStringList);
    // Paste();
    void paste(QStringList);
    // Delete();
    void deleteR(QStringList);
    // SelectAll();
    void selectAll(QStringList);
    // Find([subString, replacewith]); -- find or replace
    void find(QStringList);
    // GotoLine([line]);
    void gotoLine(QStringList);
    // FindAdvance()
    void findAdvance(QStringList);

    // project build, install, run, debug, stop
    // Build()      build and signed apk
    void build(QStringList);
    // Install()    install signed.apk
    void install(QStringList);
    // Run()        run target apk
    void run(QStringList);
    // Debug()      debug apk
    void debug(QStringList);
    // Stop()       force stop apk
    void stop(QStringList);
    // Devices()    open device window
    void devices(QStringList);

    // Debug option
    // DebugStart(packageName)
    void debugStart(QStringList);
    // DebugStop
    void debugStop(QStringList);

    // repaint
    void themeUpdate(QStringList);
public slots:
    void adbShell(QStringList);

private:
    QMap<QString, scriptHandle> scripts;
};

#endif // SCRIPTENGINE_H
