//===- DebugSocket.h - ART-DEBUGGER -----------------------------*- C++ -*-===//
//
//                     ANDROID REVERSE TOOLKIT
//
// This file is distributed under the GNU GENERAL PUBLIC LICENSE
// V3 License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// DebugSocket will create a new socket client in a new thread.
// If reconnect failed, it will be deleted automatic
// It will also be deleted when user call stopConnection.
// Please never use deleteLater to delete it.
//
//===----------------------------------------------------------------------===//


#ifndef PROJECT_DEBUGSOCKET_H
#define PROJECT_DEBUGSOCKET_H

#include <QThread>
#include <QTcpSocket>
#include <QMutex>
#include <QWaitCondition>
#include <QAtomicInteger>
#include <QByteArray>
#include <Jdwp/Request.h>

class DebugSocket: public QThread
{
    Q_OBJECT
public:
    DebugSocket(QObject *parent = 0);

    void startConnection(const QString &hostName, quint16 port);
    void stopConnection();

    void run() Q_DECL_OVERRIDE;

signals:
    void error(int socketError, const QString &message);

    // delete request after call.
    void newJDWPRequest(JDWP::Request* request);

private slots:
    void onDisconnected();
    void onConnected();
private:
    ~DebugSocket ();

private:
    bool tryHandshake();
private:
    QString mHostName;
    quint16 mPort;
    QMutex mMutex;
    QAtomicInteger<bool> mQuit;

    QTcpSocket mSocket;
    QByteArray mBufPool;
    bool mConnected;
};


#endif //PROJECT_DEBUGSOCKET_H
