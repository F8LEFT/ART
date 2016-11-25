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

DebugSocket::DebugSocket (QObject *parent)
        : QThread (parent), mQuit(false), mConnected(false)
{
    connect(this, SIGNAL(finished()), this, SLOT(deleteLater()));

    mSocket.moveToThread (this);
    connect(&mSocket, SIGNAL(connected()), this, SLOT(onConnected()));
    connect(&mSocket, SIGNAL(disconnected()), this, SLOT(onDisconnected()));
}

DebugSocket::~DebugSocket ()
{

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
}

void DebugSocket::run ()
{
    if(!tryBindJdwp()) {
        emit error(-1, tr("Unable to open debug port."));
        return;
    }
    mSocket.connectToHost (mHostName, mPort);

    auto timeout = 10 * 1000;
    if(!mSocket.waitForConnected (timeout)) {
        emit error (mSocket.error (), mSocket.errorString ());
        return;
    }
    mSocket.waitForReadyRead();
    if(!tryHandshake ()) {
        emit error(-1, tr("Unable to send handshake packet"));
        return;
    }

    while(!mQuit && mConnected) {
        if(!mSocket.waitForReadyRead (timeout)) {
            continue;
        }
        auto buffer = mSocket.readAll ();
        mBufPool += buffer;
        if(!JDWP::Request::isValid (
                (const uint8_t*)mBufPool.data (), mBufPool.length ())) {
            continue;
        }

        auto req = new JDWP::Request((const uint8_t*)mBufPool.data (), mBufPool.length ());
        if(req->isValid ()) {
            emit newJDWPRequest (req);
            mBufPool.chop (req->GetLength ());
        }
    }
}

bool DebugSocket::tryHandshake ()
{
    auto timeout = 10 * 1000;

    mSocket.write (kMagicHandshake, kMagicHandshakeLen);
    if(!mSocket.waitForReadyRead (timeout)) {
        return false;
    }
    auto buffer = mSocket.readAll ();
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
}

void DebugSocket::onConnected ()
{
    mConnected = true;
}
bool DebugSocket::tryBindJdwp()
{
    return true;
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

