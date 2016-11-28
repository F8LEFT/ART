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

#include <Jdwp/Request.h>


#include <QThread>
#include <QTcpSocket>
#include <QMutex>
#include <QWaitCondition>
#include <QAtomicInteger>
#include <QByteArray>
#include <QSharedPointer>

class DebugSocket: public QThread
{
    Q_OBJECT
public:
    DebugSocket(QObject *parent = 0);

    void startConnection(const QString &hostName, int port, const QString &targetName);
    void stopConnection();

    void run() Q_DECL_OVERRIDE;

    const QString &hostName() const;
    const QString &targetName() const;
    const quint16 port() const;
    const bool isConnected() const;
signals:
    void error(int socketError, const QString &message);

    // request need to be deleted in slot
    void newJDWPRequest(JDWP::Request* request);
    // this will be emited when handshake finished
    void connected();
    // this will be emited when connect close, and DebugSocket object will be deleted.
    void disconnected();
private slots:
    void onDisconnected();
    void onConnected();
    void onThreadfinish();

public slots:
    void sendBuffer(const QByteArray& array);
    void sendBuffer(const char*data, quint64 len);
private:
    ~DebugSocket ();

private:
    bool tryBindJdwp();
    bool tryHandshake();
private:
    QString mHostName;
    QString mTargetName;
    quint16 mPort;
    QMutex mMutex;
    QAtomicInteger<bool> mQuit;

    QTcpSocket *mSocket;

    bool mConnected;
};


#endif //PROJECT_DEBUGSOCKET_H
