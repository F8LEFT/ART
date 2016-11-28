//===- Debugger.cpp - ART-DEBUGGER ------------------------------*- C++ -*-===//
//
//                     ANDROID REVERSE TOOLKIT
//
// This file is distributed under the GNU GENERAL PUBLIC LICENSE
// V3 License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

#include "Debugger/Debugger.h"
#include "ui_Debugger.h"

#include "DebugSocket.h"

#include "utils/Configuration.h"
#include "utils/ScriptEngine.h"
#include <utils/CmdMsgUtil.h>

#include <QHostAddress>
#include <QDebug>
#include <Jdwp/JdwpHandler.h>



Debugger::Debugger(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Debugger)
{
    ui->setupUi(this);

    // script
    auto* script = ScriptEngine::instance();
    connect(script, &ScriptEngine::debugStart, this, &Debugger::startNewTarget);

    mSocket = new DebugSocket(this);
    connect(mSocket, &DebugSocket::error, this, &Debugger::onSocketError);
    connect(mSocket, &DebugSocket::connected, this, &Debugger::onSocketConnected);
    connect(mSocket, &DebugSocket::disconnected, this, &Debugger::onSocketDisconnected);

    connect(this, SIGNAL(sendBuffer(const char*,quint64)),
            mSocket->mSocketEvent, SLOT(onWrite(const char*,quint64)));
    connect(this, SIGNAL(sendBuffer(QByteArray)), mSocket->mSocketEvent, SLOT(onWrite(QByteArray)));
    connect(this, &Debugger::stopCurrentTarget, mSocket->mSocketEvent, &DebugSocketEvent::onStop);

    connect(mSocket, &DebugSocket::newJDWPRequest, this, &Debugger::onJDWPRequest);

    loadFromConfig();
}

Debugger::~Debugger()
{
    saveToConfig();
    delete ui;
}

void Debugger::loadFromConfig()
{
    Configuration *config = Config();
    restoreGeometry(config->getByte("Debugger", "Geometry"));
    ui->mSplitter->restoreGeometry(config->getByte("Debugger", "SplitGeometry"));
    ui->mSplitter->restoreState(config->getByte("Debugger", "SplitState"));
}
void Debugger::saveToConfig()
{
    Configuration *config = Config();
    config->setByte("Debugger", "Geometry", saveGeometry());
    config->setByte("Debugger", "SplitGeometry", ui->mSplitter->saveGeometry());
    config->setByte("Debugger", "SplitState", ui->mSplitter->saveState());
}

bool Debugger::isDebugging ()
{
    return mSocket->isConnected ();
}

void Debugger::startNewTarget(QStringList args)
{
    if(args.empty() || mSocket->isConnected ()) {
        return;
    }

    auto& target = args.front();
    mSocket->startConnection("localhost", 8100, target);
}

void Debugger::onSocketError(int error, const QString &message)
{
    qDebug() << "Socket error code : " << error << " msg: " << message;
}

void Debugger::onSocketConnected()
{
    cmdmsg()->addCmdMsg("Debugger connect to " + mSocket->hostName () + ":" +
                                QString::number(mSocket->port ()));
    mSockId = 0;
    mRequestMap.clear ();

    // just run
    auto request = JDWP::VirtualMachine::Resume::buildReq (mSockId++);
    sendNewRequest (request);
}

void Debugger::onSocketDisconnected()
{
    cmdmsg()->addCmdMsg("Debugger disconnected");
    mSockId = 0;
    mRequestMap.clear ();
}

void Debugger::onJDWPRequest (JDWP::Request* request)
{
    QSharedPointer<JDWP::Request> req(request);
    if(request->isReply ()) {
        handleReply (req);
    } else {
        handleCommand(req);
    }

}

void Debugger::handleReply (QSharedPointer<JDWP::Request> &reply)
{
    auto id = reply->GetId ();

    auto it = mRequestMap.find (id);
    if(it == mRequestMap.end ()) {
        return;
    }
    auto request = it->data ();
    qDebug() << "Handle reply for id " << id
            << " CommandSet:" << request->GetCommandSet ()
            << " Command:" << request->GetCommand ();
    if(!ProcessRequest (request, reply.data ())) {
        qWarning() << "Unable to handle this reply";
    }

    mRequestMap.erase (it);
}

void Debugger::handleCommand (QSharedPointer<JDWP::Request> &reply)
{
    qDebug() << "Receive command!!!!!";
}

bool Debugger::sendNewRequest (const QByteArray &req)
{
    QSharedPointer<JDWP::Request> request(new JDWP::Request(
            (uint8_t*)req.data (), req.length ()));
    if(!request->isValid ()) {
        return false;
    }
    if(mRequestMap.find (request->GetId ()) != mRequestMap.end ()) {
        return false;
    }
    mRequestMap[request->GetId ()] = request;
    sendBuffer (req);
    return true;
}

bool Debugger::ProcessRequest (JDWP::Request *request,JDWP::Request *reply)
{

    return false;
}

