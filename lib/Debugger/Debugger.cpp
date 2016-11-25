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

#include <QHostAddress>
#include <QDebug>

Debugger::Debugger(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Debugger)
{
    ui->setupUi(this);

    // script
    auto* script = ScriptEngine::instance();
    connect(script, &ScriptEngine::debugStart, this, &Debugger::startNewTarget);


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
void Debugger::stopCurrentTarget()
{
    mIsDebugging = false;
}
void Debugger::startNewTarget(QStringList args)
{
    if(args.empty() || mIsDebugging) {
        return;
    }

    mIsDebugging = true;
    auto& target = args.front();
    DebugSocket* sock = new DebugSocket(this);
    connect(sock, &DebugSocket::error, this, &Debugger::onSocketError);
    sock->startConnection("localhost", 8100, target);
}

void Debugger::onSocketError(int error, const QString &message)
{
    qDebug() << "Socket error code : " << error << " msg: " << message;
}
