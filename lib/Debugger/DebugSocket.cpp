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
        : QThread (parent), mQuit(false), mSocket(nullptr), mConnected(false)
{
    connect(this, &DebugSocket::finished, this, &DebugSocket::onThreadfinish);
    mSocketEvent = new DebugSocketEvent();
    mSocketEvent->moveToThread(this);
}

DebugSocket::~DebugSocket ()
{
    mQuit = true;
    wait ();
    mSocketEvent->deleteLater();
}

void DebugSocket::startConnection (const QString &hostName, int port,
                                    int pid)
{
    QMutexLocker locker(&mMutex);
    if(isRunning ())
        return;
    mHostName = hostName;
    mPort = port;
    mPid = pid;
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
//    bool bindSuccess = false;
//    for(auto trytime = 0; trytime < 3; trytime++) {
//        bindSuccess = tryBindJdwp();
//        if(bindSuccess) {
//            break;
//        }
//        sleep(3);
//    }
//    if(!bindSuccess) {
//         error(-1, tr("Unable to open debug port."));
//        return;
//    }
    mSocket = new QTcpSocket();
    connect(mSocket, &QTcpSocket::disconnected, this, &DebugSocket::onDisconnected);

    mSocket->connectToHost (mHostName, mPort);

    if(!mSocket->waitForConnected ()) {
         error (mSocket->error (), mSocket->errorString ());
        return;
    }
    if(!tryHandshake ()) {
         error(-1, tr("Unable to send handshake packet"));
        return;
    }

    QEventLoop loop;        // used to listen readwriteclose signal
    QByteArray mBufPool;

    connect(mSocketEvent, &DebugSocketEvent::newStatus, &loop, &QEventLoop::quit);

    connect(mSocket, &QTcpSocket::readyRead, [this, &mBufPool](){
        while(mSocket->isReadable()) {
            auto buffer = mSocket->readAll();
            if(buffer.isEmpty()) {
                qDebug() << "empty buffer read, exit loop";
                break;
            }
            qDebug() << "[DebugSocket] read: " << buffer.toHex();
            mBufPool += buffer;
            if(!JDWP::Request::isValid ((const uint8_t*)mBufPool.data (), mBufPool.length ())) {
                continue;
            }

            auto req = new JDWP::Request((const uint8_t*)mBufPool.data (), mBufPool.length ());
            if(req->isValid ()) {
                newJDWPRequest (req);
                mBufPool.chop (req->GetLength ());
            }
        }
    });
    onConnected();

    while(!mQuit && mConnected) {
        loop.exec();
        if(mSocketEvent->isReadyStop()) {
            qDebug() << "[DebugSocket] close" ;
            stopConnection();
        }
        if(mSocketEvent->isReadyWrite()) {
            auto &wbuf = mSocketEvent->mWBuffer;
            while(!wbuf.isEmpty()) {
                qDebug() << "[DebugSocket] send: " << wbuf.toHex();
                auto wLen = mSocket->write(wbuf);
                wbuf.chop(wLen);
                if(wLen == 0) {
                    break;
                }
            }
        }
        mSocketEvent->clearStatus();
    }
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
    if(buffer.length () < (int)kMagicHandshakeLen) {
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
    error(0, tr("Debugger Socket closed"));
    disconnected ();
    mSocketEvent->onStop();
}

void DebugSocket::onConnected ()
{
    mQuit = false;
    mConnected = true;
     connected();
}

void DebugSocket::onThreadfinish ()
{
    if(mSocket != nullptr) {
        mSocket->close ();
        mSocket = nullptr;
    }
}

bool DebugSocket::tryBindJdwp()
{
    // get Process pid
    int pid = mPid;
    AdbUtil adbUtil;
    auto deviceId = projinfo("DeviceId");
    auto prefix = deviceId.isEmpty() ?  QString() : "-s " + deviceId + " ";

    // open Debug port
    QString bindConfig = "tcp:" +  QString::number(mPort) +
                    " jdwp:" +  QString::number(pid);
    adbUtil.execute(prefix + "forward " + bindConfig);

    QStringList bindResult = adbUtil.execute(prefix + "forward --list");

    QString bindCheck = bindConfig;
    foreach(const QString& s, bindResult) {
            if(bindResult.contains(s)) {
                return true;
            }
        }
    return false;
}

void DebugSocketEvent::onStop()
{
    mStatus = mStatus | ReadyStop;
     newStatus();
}

void DebugSocketEvent::onWrite(const QByteArray &array)
{
    mWBuffer.append(array);
    mStatus = mStatus | ReadyWrite;
     newStatus();
}

void DebugSocketEvent::onWrite(const char *data, quint64 len)
{
    onWrite(QByteArray(data, len));
}

DebugSocketEvent::DebugSocketEvent(QObject *parent)
    : QObject(parent)
{

}


