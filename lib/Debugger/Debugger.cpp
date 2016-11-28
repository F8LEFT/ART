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

    // init handlemap
    mHandleMap[JDWP::ThreadReference::set_][JDWP::ThreadReference::Resume::cmd] = &Debugger::_handle_ThreadReference_Resume;

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

void Debugger::handleCommand (QSharedPointer<JDWP::Request> &request)
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
    request->SetId(mSockId++);
    mRequestMap[request->GetId ()] = request;
    sendBuffer (req);
    return true;
}

bool Debugger::ProcessRequest (JDWP::Request *request,JDWP::Request *reply)
{
    auto set = request->GetCommandSet();
    auto cmd = request->GetCommand();
    auto itSets = mHandleMap.find(set);
    if(itSets == mHandleMap.end()) {
        return false;
    }
    auto it = itSets.value().find(cmd);
    if(it == itSets.value().end()) {
        return false;
    }
    (this->*(it.value()))(request, reply);
    return true;
}

// -------------------for debug command----------------------
void Debugger::dbgResume()
{
    auto request = JDWP::VirtualMachine::Resume::buildReq ();
    sendNewRequest (request);
}
void Debugger::_handle_VirtualMachine_Version(JDWP::Request *request, JDWP::Request *reply)
{

}
void Debugger::_handle_VirtualMachine_ClassesBySignature(JDWP::Request *request, JDWP::Request *reply)
{

}
void Debugger::_handle_VirtualMachine_AllClasses(JDWP::Request *request, JDWP::Request *reply)
{

}
void Debugger::_handle_VirtualMachine_AllThreads(JDWP::Request *request, JDWP::Request *reply)
{

}
void Debugger::_handle_VirtualMachine_TopLevelThreadGroups(JDWP::Request *request, JDWP::Request *reply)
{

}
void Debugger::_handle_VirtualMachine_Dispose(JDWP::Request *request, JDWP::Request *reply)
{

}
void Debugger::_handle_VirtualMachine_IDSizes(JDWP::Request *request, JDWP::Request *reply)
{

}
void Debugger::_handle_VirtualMachine_Suspend(JDWP::Request *request, JDWP::Request *reply)
{

}
void Debugger::_handle_VirtualMachine_Resume(JDWP::Request *request, JDWP::Request *reply)
{

}
void Debugger::_handle_VirtualMachine_Exit(JDWP::Request *request, JDWP::Request *reply)
{

}
void Debugger::_handle_VirtualMachine_CreateString(JDWP::Request *request, JDWP::Request *reply)
{

}
void Debugger::_handle_VirtualMachine_Capabilities(JDWP::Request *request, JDWP::Request *reply)
{

}
void Debugger::_handle_VirtualMachine_ClassPaths(JDWP::Request *request, JDWP::Request *reply)
{

}
void Debugger::_handle_VirtualMachine_DisposeObjects(JDWP::Request *request, JDWP::Request *reply)
{

}
void Debugger::_handle_VirtualMachine_HoldEvents(JDWP::Request *request, JDWP::Request *reply)
{

}
void Debugger::_handle_VirtualMachine_ReleaseEvents(JDWP::Request *request, JDWP::Request *reply)
{

}
void Debugger::_handle_VirtualMachine_CapabilitiesNew(JDWP::Request *request, JDWP::Request *reply)
{

}
void Debugger::_handle_VirtualMachine_RedefineClasses(JDWP::Request *request, JDWP::Request *reply)
{

}
void Debugger::_handle_VirtualMachine_SetDefaultStratum(JDWP::Request *request, JDWP::Request *reply)
{

}
void Debugger::_handle_VirtualMachine_AllClassesWithGeneric(JDWP::Request *request, JDWP::Request *reply)
{

}
void Debugger::_handle_VirtualMachine_InstanceCounts(JDWP::Request *request, JDWP::Request *reply)
{

}
void Debugger::_handle_ReferenceType_Signature(JDWP::Request *request, JDWP::Request *reply)
{

}
void Debugger::_handle_ReferenceType_ClassLoader(JDWP::Request *request, JDWP::Request *reply)
{

}
void Debugger::_handle_ReferenceType_Modifiers(JDWP::Request *request, JDWP::Request *reply)
{

}
void Debugger::_handle_ReferenceType_Fields(JDWP::Request *request, JDWP::Request *reply)
{

}
void Debugger::_handle_ReferenceType_Methods(JDWP::Request *request, JDWP::Request *reply)
{

}
void Debugger::_handle_ReferenceType_GetValues(JDWP::Request *request, JDWP::Request *reply)
{

}
void Debugger::_handle_ReferenceType_SourceFile(JDWP::Request *request, JDWP::Request *reply)
{

}
void Debugger::_handle_ReferenceType_NestedTypes(JDWP::Request *request, JDWP::Request *reply)
{

}
void Debugger::_handle_ReferenceType_Status(JDWP::Request *request, JDWP::Request *reply)
{

}
void Debugger::_handle_ReferenceType_Interfaces(JDWP::Request *request, JDWP::Request *reply)
{

}
void Debugger::_handle_ReferenceType_ClassObject(JDWP::Request *request, JDWP::Request *reply)
{

}
void Debugger::_handle_ReferenceType_SourceDebugExtension(JDWP::Request *request, JDWP::Request *reply)
{

}
void Debugger::_handle_ReferenceType_SignatureWithGeneric(JDWP::Request *request, JDWP::Request *reply)
{

}
void Debugger::_handle_ReferenceType_FieldsWithGeneric(JDWP::Request *request, JDWP::Request *reply)
{

}
void Debugger::_handle_ReferenceType_MethodsWithGeneric(JDWP::Request *request, JDWP::Request *reply)
{

}
void Debugger::_handle_ReferenceType_Instances(JDWP::Request *request, JDWP::Request *reply)
{

}
void Debugger::_handle_ReferenceType_ClassFileVersion(JDWP::Request *request, JDWP::Request *reply)
{

}
void Debugger::_handle_ReferenceType_ConstantPool(JDWP::Request *request, JDWP::Request *reply)
{

}
void Debugger::_handle_ClassType_Superclass(JDWP::Request *request, JDWP::Request *reply)
{

}
void Debugger::_handle_ClassType_SetValues(JDWP::Request *request, JDWP::Request *reply)
{

}
void Debugger::_handle_ClassType_InvokeMethod(JDWP::Request *request, JDWP::Request *reply)
{

}
void Debugger::_handle_ClassType_NewInstance(JDWP::Request *request, JDWP::Request *reply)
{

}
void Debugger::_handle_ArrayType_NewInstance(JDWP::Request *request, JDWP::Request *reply)
{

}
void Debugger::_handle_Method_LineTable(JDWP::Request *request, JDWP::Request *reply)
{

}
void Debugger::_handle_Method_VariableTable(JDWP::Request *request, JDWP::Request *reply)
{

}
void Debugger::_handle_Method_Bytecodes(JDWP::Request *request, JDWP::Request *reply)
{

}
void Debugger::_handle_Method_IsObsolete(JDWP::Request *request, JDWP::Request *reply)
{

}
void Debugger::_handle_Method_VariableTableWithGeneric(JDWP::Request *request, JDWP::Request *reply)
{

}
void Debugger::_handle_ObjectReference_ReferenceType(JDWP::Request *request, JDWP::Request *reply)
{

}
void Debugger::_handle_ObjectReference_GetValues(JDWP::Request *request, JDWP::Request *reply)
{

}
void Debugger::_handle_ObjectReference_SetValues(JDWP::Request *request, JDWP::Request *reply)
{

}
void Debugger::_handle_ObjectReference_UNUSED(JDWP::Request *request, JDWP::Request *reply)
{

}
void Debugger::_handle_ObjectReference_MonitorInfo(JDWP::Request *request, JDWP::Request *reply)
{

}
void Debugger::_handle_ObjectReference_InvokeMethod(JDWP::Request *request, JDWP::Request *reply)
{

}
void Debugger::_handle_ObjectReference_DisableCollection(JDWP::Request *request, JDWP::Request *reply)
{

}
void Debugger::_handle_ObjectReference_EnableCollection(JDWP::Request *request, JDWP::Request *reply)
{

}
void Debugger::_handle_ObjectReference_IsCollected(JDWP::Request *request, JDWP::Request *reply)
{

}
void Debugger::_handle_ObjectReference_ReferringObjects(JDWP::Request *request, JDWP::Request *reply)
{

}
void Debugger::_handle_StringReference_Value(JDWP::Request *request, JDWP::Request *reply)
{

}
void Debugger::_handle_ThreadReference_Name(JDWP::Request *request, JDWP::Request *reply)
{

}
void Debugger::_handle_ThreadReference_Suspend(JDWP::Request *request, JDWP::Request *reply)
{

}
void Debugger::_handle_ThreadReference_Resume(JDWP::Request *request, JDWP::Request *reply)
{
    emit dbgOnResume();
}
void Debugger::_handle_ThreadReference_Status(JDWP::Request *request, JDWP::Request *reply)
{

}
void Debugger::_handle_ThreadReference_ThreadGroup(JDWP::Request *request, JDWP::Request *reply)
{

}
void Debugger::_handle_ThreadReference_Frames(JDWP::Request *request, JDWP::Request *reply)
{

}
void Debugger::_handle_ThreadReference_FrameCount(JDWP::Request *request, JDWP::Request *reply)
{

}
void Debugger::_handle_ThreadReference_OwnedMonitors(JDWP::Request *request, JDWP::Request *reply)
{

}
void Debugger::_handle_ThreadReference_CurrentContendedMonitor(JDWP::Request *request, JDWP::Request *reply)
{

}
void Debugger::_handle_ThreadReference_Stop(JDWP::Request *request, JDWP::Request *reply)
{

}
void Debugger::_handle_ThreadReference_Interrupt(JDWP::Request *request, JDWP::Request *reply)
{

}
void Debugger::_handle_ThreadReference_SuspendCount(JDWP::Request *request, JDWP::Request *reply)
{

}
void Debugger::_handle_ThreadReference_OwnedMonitorsStackDepthInfo(JDWP::Request *request, JDWP::Request *reply)
{

}
void Debugger::_handle_ThreadReference_ForceEarlyReturn(JDWP::Request *request, JDWP::Request *reply)
{

}
void Debugger::_handle_ThreadGroupReference_Name(JDWP::Request *request, JDWP::Request *reply)
{

}
void Debugger::_handle_ThreadGroupReference_Parent(JDWP::Request *request, JDWP::Request *reply)
{

}
void Debugger::_handle_ThreadGroupReference_Children(JDWP::Request *request, JDWP::Request *reply)
{

}
void Debugger::_handle_ArrayReference_Length(JDWP::Request *request, JDWP::Request *reply)
{

}
void Debugger::_handle_ArrayReference_GetValues(JDWP::Request *request, JDWP::Request *reply)
{

}
void Debugger::_handle_ArrayReference_SetValues(JDWP::Request *request, JDWP::Request *reply)
{

}
void Debugger::_handle_ClassLoaderReference_VisibleClasses(JDWP::Request *request, JDWP::Request *reply)
{

}
void Debugger::_handle_EventRequest_Set(JDWP::Request *request, JDWP::Request *reply)
{

}
void Debugger::_handle_EventRequest_Clear(JDWP::Request *request, JDWP::Request *reply)
{

}
void Debugger::_handle_EventRequest_ClearAllBreakpoints(JDWP::Request *request, JDWP::Request *reply)
{

}
void Debugger::_handle_StackFrame_GetValues(JDWP::Request *request, JDWP::Request *reply)
{

}
void Debugger::_handle_StackFrame_SetValues(JDWP::Request *request, JDWP::Request *reply)
{

}
void Debugger::_handle_StackFrame_ThisObject(JDWP::Request *request, JDWP::Request *reply)
{

}
void Debugger::_handle_StackFrame_PopFrames(JDWP::Request *request, JDWP::Request *reply)
{

}
void Debugger::_handle_ClassObjectReference_ReflectedType(JDWP::Request *request, JDWP::Request *reply)
{

}
void Debugger::_handle_Event_Composite(JDWP::Request *request, JDWP::Request *reply)
{

}

