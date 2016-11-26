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

#include <QWidget>

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
    void stopCurrentTarget();
signals:
    void sendBuffer(const QByteArray& array);
    void sendBuffer(const char*data, quint64 len);

public slots:
    void startNewTarget(QStringList args);

private slots:
    void onSocketError(int error, const QString &message);
    void onSocketConnected();
    void onSocketDisconnected();
    void onJDWPRequest(JDWP::Request* request);

private:
    Ui::Debugger *ui;

    DebugSocket* mSocket = nullptr;

};

#endif // DEBUGGER_H
