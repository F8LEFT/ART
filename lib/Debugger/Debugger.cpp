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
    connect(mSocket, &DebugSocket::error, this, &Debugger::onSocketError, Qt::QueuedConnection);
    connect(mSocket, &DebugSocket::connected, this, &Debugger::onSocketConnected, Qt::QueuedConnection);
    connect(mSocket, &DebugSocket::disconnected, this, &Debugger::onSocketDisconnected, Qt::QueuedConnection);
    connect(this, SIGNAL(sendBuffer(const char*,quint64)),
            mSocket, SLOT(sendBuffer(const char*,quint64)), Qt::QueuedConnection);
    connect(this, SIGNAL(sendBuffer(QByteArray)), mSocket, SLOT(sendBuffer(QByteArray)),
            Qt::QueuedConnection);

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

void Debugger::stopCurrentTarget()
{
    mSocket->stopConnection ();
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
    // just run
    auto req = JDWP::VirtualMachine::Resume::buildReq (0);
    sendBuffer (req);
}

void Debugger::onSocketDisconnected()
{
    cmdmsg()->addCmdMsg("Debugger disconnected");
}

void Debugger::onJDWPRequest (JDWP::Request *request)
{

    qDebug() << "receive new request Id:" << request->GetId ()
             << " Reply:" << request->isReply ()
             << " CommandSet:" << request->GetCommandSet ()
             << " Command:" << request->GetCommand ();
}

