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
#include <ChooseProcess.h>

Debugger::Debugger(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Debugger),
    m_lastHost("localhost"),
    m_lastPort(8100)
{
    ui->setupUi(this);

    // script
    auto* script = ScriptEngine::instance();
    connect(script, &ScriptEngine::debugStart, this, &Debugger::startNewTarget);

    mSocket = new DebugSocket(this);
    mDbgHandler = mSocket->mDbgHandler;

    loadFromConfig();

    setupHandleMap();
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

    ChooseProcess chooseProcess(m_lastHost, m_lastPort, target);
    if(chooseProcess.exec() != QDialog::Accepted
        || !chooseProcess.isValid()) {
        return;
    }

    m_lastHost = chooseProcess.getHostname();
    m_lastPort = chooseProcess.getPort();

    mSocket->startConnection(m_lastHost, m_lastPort, chooseProcess.getTargetPid());
}

void Debugger::stopCurrentTarget()
{
    if(isDebugging()) {
        mDbgHandler->stopCurrentTarget();
    }
}


// for debug command
void Debugger::dbgResume() {
    if(isDebugging()) {
        mDbgHandler->dbgResume();
    }
}

// reply from Handler
void Debugger::dbgOnResume()
{

}

void Debugger::setupHandleMap()
{
    connect(mDbgHandler, &DebugHandler::dbgOnResume, this, &::Debugger::dbgOnResume);
}

