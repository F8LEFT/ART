//===- DebugSocket.cpp - ART-DEBUGGER ---------------------------*- C++ -*-===//
//
//                     ANDROID REVERSE TOOLKIT
//
// This file is distributed under the GNU GENERAL PUBLIC LICENSE
// V3 License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

#include "DebugSocket.h"
#include <Jdwp/JdwpHeader.h>
#include "Jdwp/Request.h"


#include <utils/ProjectInfo.h>
#include <utils/CmdMsgUtil.h>
#include <utils/AdbUtil.h>

#include <QHostAddress>
#include <QMutexLocker>
#include <QtCore/QEventLoop>

DebugSocket::DebugSocket (QObject *parent)
        : QThread (parent), mQuit(false), mConnected(false), mSocket(nullptr)
{
    connect(this, &DebugSocket::finished, this, &DebugSocket::onThreadfinish);
}

DebugSocket::~DebugSocket ()
{
    mQuit = true;
    wait ();
}

void DebugSocket::startConnection (const QString &hostName, int port,
                                   const QString &targetName)
{
    QMutexLocker locker(&mMutex);
    if(isRunning ())
        return;
    mHostName = hostName;
    mPort = port;
    mTargetName = targetName;
    start ();
}

void DebugSocket::stopConnection ()
{
    mQuit = true;
    if(mSocket != nullptr) {
        mSocket->close ();
        mSocket->deleteLater();
        mSocket = nullptr;
    }
}

void DebugSocket::run ()
{
    bool bindSuccess = false;
    for(auto trytime = 0; trytime < 3; trytime++) {
        bindSuccess = tryBindJdwp();
        if(bindSuccess) {
            break;
        }
        sleep(3);
    }
    if(!bindSuccess) {
        emit error(-1, tr("Unable to open debug port."));
        return;
    }
    mSocket = new QTcpSocket();
    connect(mSocket, &QTcpSocket::disconnected, this, &DebugSocket::onDisconnected);

    mSocket->connectToHost (mHostName, mPort);

    if(!mSocket->waitForConnected ()) {
        emit error (mSocket->error (), mSocket->errorString ());
        return;
    }
    if(!tryHandshake ()) {
        emit error(-1, tr("Unable to send handshake packet"));
        return;
    }

    QEventLoop loop;        // used to listen readwriteclose signal

    emit onConnected();

    QByteArray mBufPool;
    while(!mQuit && mConnected) {
        if(!mSocket->waitForReadyRead ()) {
            continue;
        }
        auto buffer = mSocket->readAll ();
        mBufPool += buffer;
        if(!JDWP::Request::isValid (
                (const uint8_t*)mBufPool.data (), mBufPool.length ())) {
            continue;
        }

        JDWP::Request* req = new JDWP::Request(
                (const uint8_t*)mBufPool.data (), mBufPool.length ());
        if(req->isValid ()) {
            emit newJDWPRequest (req);
            mBufPool.chop (req->GetLength ());
        }
    }
}

const QString &DebugSocket::hostName() const
{
    return mHostName;
}

const QString &DebugSocket::targetName() const
{
    return mTargetName;
}

const quint16 DebugSocket::port() const
{
    return mPort;
}

const bool DebugSocket::isConnected() const
{
    return mConnected;
}

bool DebugSocket::tryHandshake ()
{
    if(mSocket->write (kMagicHandshake, kMagicHandshakeLen) != kMagicHandshakeLen) {
        return false;
    }
    if(!mSocket->waitForReadyRead ()) {
        return false;
    }
    auto buffer = mSocket->readAll ();
    if(buffer.length () < kMagicHandshakeLen) {
        return false;
    }
    if(memcmp (buffer.data (), kMagicHandshake, kMagicHandshakeLen) != 0) {
        return false;
    }
    return true;
}

void DebugSocket::onDisconnected ()
{
    mConnected = false;
    emit error(0, tr("Debugger Socket closed"));
    emit disconnected ();
}

void DebugSocket::onConnected ()
{
    mQuit = false;
    mConnected = true;
    emit connected();
}

void DebugSocket::onThreadfinish ()
{
    if(mSocket != nullptr) {
        mSocket->close ();
        mSocket = nullptr;
    }
}

void DebugSocket::sendBuffer (const QByteArray& array)
{
    qDebug() << "SendBuffer: " << array.toHex();
    sendBuffer (array.data (), array.length ());
}

void DebugSocket::sendBuffer (const char *data,quint64 len)
{
    if(mSocket && mSocket->isWritable ()) {
        if(mSocket->write (data, len) != len) {
            qWarning() << "Send data failed";
        }
    }
}

bool DebugSocket::tryBindJdwp()
{
    // get Process pid
    int pid = 0;
    AdbUtil adbUtil;
    auto deviceId = projinfo("DeviceId");
    if(deviceId.isEmpty()) {
        return false;
    }
    QStringList pidList = adbUtil.execute("-s " + deviceId + " shell pidof " + mTargetName);
    foreach(const QString& s, pidList) {
            pid = s.toInt();
            if(pid != 0) {
                break;
            }
        }
    if(pid == 0)
        return false;

    // open Debug port
    QString bindConfig = "tcp:" +  QString::number(mPort) +
                    " jdwp:" +  QString::number(pid);
    adbUtil.execute("-s " + deviceId + " forward " + bindConfig);

    QStringList bindResult = adbUtil.execute("-s " + deviceId + " forward --list");

    QString bindCheck = deviceId + " " + bindConfig;
    foreach(const QString& s, bindResult) {
            if(bindCheck == s) {
                return true;
            }
        }
    return false;
}






