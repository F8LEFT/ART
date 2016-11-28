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

class DebugSocketEvent;
class Debugger;

class DebugSocket: public QThread
{
    Q_OBJECT
public:
    DebugSocket(QObject *parent = 0);

    void startConnection(const QString &hostName, int port, const QString &targetName);

    void run() Q_DECL_OVERRIDE;

    const QString &hostName() const { return mHostName; }
    const QString &targetName() const { return mTargetName; }
    const quint16 port() const { return mPort; }
    const bool isConnected() const { return mConnected; }
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


private:
    ~DebugSocket ();

private:
    bool tryBindJdwp();
    bool tryHandshake();

    void stopConnection();

private:
    QString mHostName;
    QString mTargetName;
    quint16 mPort;
    QMutex mMutex;
    QAtomicInteger<bool> mQuit;

    QTcpSocket *mSocket;

    bool mConnected;

    friend class Debugger;
    DebugSocketEvent* mSocketEvent;
};

class DebugSocketEvent: public QObject {
    Q_OBJECT
public:
    enum Status {
        Empty,
        ReadyRead = 1,
        ReadyWrite = 1 << 1 ,
        ReadyStop = 1<< 2,
    };
public:
    DebugSocketEvent(QObject* parent = nullptr);
    int status() { return mStatus; }
    bool isReadyRead() { return mStatus & ReadyRead;}
    bool isReadyWrite() { return mStatus & ReadyWrite; }
    bool isReadyStop() { return mStatus & ReadyStop; }
    void clearStatus() { mStatus = Empty; }
signals:
    void newStatus();
public slots:
    void onStop();
    void onWrite(const QByteArray& array);
    void onWrite(const char*data, quint64 len);
    void onRead();  // read data is not saved by event
private:
    int mStatus = 0;
    QByteArray mWBuffer;

    friend class DebugSocket;
};

#endif //PROJECT_DEBUGSOCKET_H
