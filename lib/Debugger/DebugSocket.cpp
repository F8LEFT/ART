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

void DebugSocket::startConnection (const QString &hostName,quint16 port)
{
    QMutexLocker locker(&mMutex);
    if(isRunning ())
        return;
    mHostName = hostName;
    mPort = port;
    start ();
}

void DebugSocket::stopConnection ()
{
    mQuit = true;
}

void DebugSocket::run ()
{
    mSocket.connectToHost (mHostName, mPort);
    auto timeout = 10 * 1000;
    if(!mSocket.waitForConnected (timeout)) {
        emit error (mSocket.error (), mSocket.errorString ());
        return;
    }
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

