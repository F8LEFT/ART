//===- Debugger.h - ART-DEBUGGER --------------------------------*- C++ -*-===//
//
//                     ANDROID REVERSE TOOLKIT
//
// This file is distributed under the GNU GENERAL PUBLIC LICENSE
// V3 License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// Debugger handle socket packet between host and client.
//
//===----------------------------------------------------------------------===//

#ifndef DEBUGGER_H
#define DEBUGGER_H

#include "DebugHandler.h"

#include <QWidget>
#include <QMap>
#include <QSharedPointer>

class FrameListView;
class VariableTreeView;
namespace Ui {
class Debugger;
}
class DebugSocket;

namespace JDWP {
    class Request;
}

class Debugger : public QWidget
{
    Q_OBJECT

public:
    explicit Debugger(QWidget *parent = 0);
    ~Debugger();

    // configuration
    void loadFromConfig();
    void saveToConfig();

    bool isDebugging();

    void setupHandleMap();

public:
    // Debug request
    void dbgResume();

public slots:
    // Debug Reply
    void dbgOnResume();

    // for debug option
private:

public slots:
    void startNewTarget(QStringList args);
    void stopCurrentTarget();

private:
    Ui::Debugger *ui;

    DebugSocket* mSocket = nullptr;
    DebugHandler* mDbgHandler = Q_NULLPTR;

    QString m_lastHost;
    int m_lastPort;
    bool m_bindJdwp;

    FrameListView* m_frameListView;
    VariableTreeView *m_variableTreeView;
};

#endif // DEBUGGER_H
