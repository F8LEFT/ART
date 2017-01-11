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
#include "FrameListView.h"
#include "VariableTreeView.h"

#include "utils/Configuration.h"
#include "utils/ScriptEngine.h"
#include <utils/CmdMsgUtil.h>
#include <Jdwp/JdwpHandler.h>
#include <ChooseProcess.h>

#include <QHostAddress>
#include <QDebug>

Debugger::Debugger(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Debugger),
    m_lastHost("localhost"),
    m_lastPort(8700),
    m_bindJdwp(false)
{
    ui->setupUi(this);

    m_frameListView = FrameListView::instance();
    ui->mFrameLayout->addWidget(m_frameListView);
    m_variableTreeView = new VariableTreeView(this);
    ui->mVariableLayout->addWidget(m_variableTreeView);

    // script
    auto* script = ScriptEngine::instance();
    connect(script, &ScriptEngine::debugStart, this, &Debugger::startNewTarget);

    mSocket = new DebugSocket(this);
    mDbgHandler = new DebugHandler(this, mSocket);
    mSocket->mDbgHandler = mDbgHandler;

    connect(m_variableTreeView, &VariableTreeView::itemExpanded, [this](VariableTreeItem* parent) {
        for(auto i = 0, count = parent->rowCount(); i < count; i++) {
            auto child = (VariableTreeItem*)parent->child(i, 0);
            if(child->value().tag == JDWP::JdwpTag::JT_OBJECT) {
                this->mDbgHandler->dumpObjectItemValue(child);
            }
        }
    });

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

    ChooseProcess chooseProcess(m_lastHost, m_lastPort, target, m_bindJdwp, nullptr);
    if(chooseProcess.exec() != QDialog::Accepted
        || !chooseProcess.isValid()) {
        return;
    }

    m_lastHost = chooseProcess.getHostname();
    m_lastPort = chooseProcess.getPort();
    m_bindJdwp = chooseProcess.bindJdwp();

    mSocket->startConnection(m_lastHost, m_lastPort,
                             chooseProcess.getTargetPid(), m_bindJdwp);
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

