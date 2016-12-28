//===- DebugHandler.cpp - ART-DebugHandler --------------------------*- C++ -*-===//
//
//                     ANDROID REVERSE TOOLKIT
//
// This file is distributed under the GNU GENERAL PUBLIC LICENSE
// V3 License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
#include "DebugHandler.h"

#include "DebugSocket.h"

#include <QDebug>
#include <utils/CmdMsgUtil.h>
#include <Jdwp/jdwp.h>
#include <QTimer>

DebugHandler::DebugHandler(QObject *parent, DebugSocket* socket)
        : QObject(parent)
{
    mSocket = socket;
    setupHandleMap();

    connect(mSocket, &DebugSocket::newJDWPRequest, this, &DebugHandler::onJDWPRequest);

    connect(mSocket, &DebugSocket::error, this, &DebugHandler::onSocketError);
    connect(mSocket, &DebugSocket::connected, this, &DebugHandler::onSocketConnected);
    connect(mSocket, &DebugSocket::disconnected, this, &DebugHandler::onSocketDisconnected);

    connect(this, SIGNAL(sendBuffer(const char*,quint64)),
            mSocket->mSocketEvent, SLOT(onWrite(const char*,quint64)));
    connect(this, SIGNAL(sendBuffer(QByteArray)), mSocket->mSocketEvent, SLOT(onWrite(QByteArray)));

    connect(this, &DebugHandler::stopCurrentTarget, mSocket->mSocketEvent, &DebugSocketEvent::onStop);
}

DebugHandler::~DebugHandler()
{

}


void DebugHandler::onJDWPRequest (JDWP::Request* request)
{
    QSharedPointer<JDWP::Request> req(request);
    if(request->isReply ()) {
        handleReply (req);
    } else {
        handleCommand(req);
    }
}

void DebugHandler::handleReply (QSharedPointer<JDWP::Request> &reply)
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

void DebugHandler::handleCommand (QSharedPointer<JDWP::Request> &request)
{
    // Command is sended form VM to debugger,
    qDebug() << "Handle command for id " << request->GetId()
             << " CommandSet:" << request->GetCommandSet ()
             << " Command:" << request->GetCommand ();
    JDWP::Composite::ReflectedType composite(request->GetExtra(), request->GetExtraLen());
    qDebug() << "Composite suspend" << composite.mSuspendPolicy << "even count" << composite.mCount;
    for(auto &pevent: composite.mEventList) {
        auto eventKind = pevent->mEventKind;
        switch(eventKind) {
            case JDWP::JdwpEventKind::EK_SINGLE_STEP:
            case JDWP::JdwpEventKind::EK_BREAKPOINT:
            case JDWP::JdwpEventKind::EK_METHOD_ENTRY:
            case JDWP::JdwpEventKind::EK_METHOD_EXIT: {
                auto event = (JDWP::Composite::ReflectedType::EventLocationEvent*)pevent;
                qDebug() << "EventLocatoinEvent" << event->mLocation.dex_pc;
            }
                break;
//            case JdwpEventKind::EK_FRAME_POP:
//                Q_ASSERT(false);
//                break;
            case JDWP::JdwpEventKind::EK_EXCEPTION: {
                auto event = (JDWP::Composite::ReflectedType::EventException*)pevent;
                qDebug() << "EventException at" << event->mThrowLoc.dex_pc << "to" << event->mCatchLoc.dex_pc;
            }
                break;
//            case JdwpEventKind::EK_USER_DEFINED:
//                Q_ASSERT(false);
//                break;
            case JDWP::JdwpEventKind::EK_THREAD_START:
            case JDWP::JdwpEventKind::EK_THREAD_DEATH: {
                auto event = (JDWP::Composite::ReflectedType::EventThreadChange*)pevent;
                qDebug() << "EventThreadChange" << event->mThreadId;
            }
                break;
            case JDWP::JdwpEventKind::EK_CLASS_PREPARE: {
                auto event = (JDWP::Composite::ReflectedType::EventClassPrepare*)pevent;
                qDebug() << "EventClassPrepare" << event->mSignature << event->mStatus;
            }
                break;
//            case JdwpEventKind::EK_CLASS_UNLOAD:
//                Q_ASSERT(false);
//                break;
//            case JdwpEventKind::EK_CLASS_LOAD:
//                Q_ASSERT(false);
//                break;
//            case JdwpEventKind::EK_FIELD_ACCESS:
//                Q_ASSERT(false);
//                break;
//            case JdwpEventKind::EK_FIELD_MODIFICATION:
//                Q_ASSERT(false);
//                break;
//            case JdwpEventKind::EK_EXCEPTION_CATCH:
//                Q_ASSERT(false);
//                break;
//            case JdwpEventKind::EK_METHOD_EXIT_WITH_RETURN_VALUE:
//                Q_ASSERT(false);
//                break;
//            case JdwpEventKind::EK_MONITOR_CONTENDED_ENTER:
//                Q_ASSERT(false);
//                break;
//            case JdwpEventKind::EK_MONITOR_CONTENDED_ENTERED:
//                Q_ASSERT(false);
//                break;
//            case JdwpEventKind::EK_MONITOR_WAIT:
//                Q_ASSERT(false);
//                break;
//            case JdwpEventKind::EK_MONITOR_WAITED:
//                Q_ASSERT(false);
//                break;
            case JDWP::JdwpEventKind::EK_VM_START: {
                auto event = (JDWP::Composite::ReflectedType::EventVmStart*)pevent;
                qDebug() << "EventVmStart" << event->mThreadId;
            }
                break;
            case JDWP::JdwpEventKind::EK_VM_DEATH: {
                //auto event = (JDWP::Composite::ReflectedType::EventVmDeath*)pevent;
                qDebug() << "EventVmDeath";
            }
                break;
//            case JdwpEventKind::EK_VM_DISCONNECTED:
//                Q_ASSERT(false);
//                break;
            default:
                qDebug() << "Unknown EventKind?" << eventKind;
                break;
        }
    }
}

bool DebugHandler::sendNewRequest (const QByteArray &req)
{
    QSharedPointer<JDWP::Request> request(new JDWP::Request(
            (uint8_t*)req.data (), req.length ()));
    if(!request->isValid ()) {
        return false;
    }
    mRequestMap[request->GetId ()] = request;
    sendBuffer (req);
    return true;
}

bool DebugHandler::ProcessRequest (JDWP::Request *request,JDWP::Request *reply)
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


void DebugHandler::onSocketError(int error, const QString &message)
{
    qDebug() << "Socket error code : " << error << " msg: " << message;
}

void DebugHandler::onSocketConnected()
{
    cmdmsg()->addCmdMsg("DebugHandler connect to " + mSocket->hostName () + ":" +
                        QString::number(mSocket->port ()));
    mSockId = 1;
    mRequestMap.clear ();

//    dbgResume();
    // Init
    dbgEventRequestSet(JDWP::JdwpEventKind::EK_CLASS_PREPARE, JDWP::JdwpSuspendPolicy::SP_NONE);
    dbgEventRequestSet(JDWP::JdwpEventKind::EK_CLASS_UNLOAD, JDWP::JdwpSuspendPolicy::SP_NONE);
    {
        std::vector<JDWP::JdwpEventMod> mod;
        JDWP::JdwpEventMod m1;
        m1.modKind = JDWP::JdwpModKind::MK_CLASS_MATCH;
        std::string m1Class = "java.lang.Throwable";
        m1.classMatch.classPattern = (char*)m1Class.c_str();
        mod.push_back(m1);
        JDWP::JdwpEventMod m2;
        m2.modKind = JDWP::JdwpModKind::MK_COUNT;
        m2.count.count = 1;
        mod.push_back(m2);
        dbgEventRequestSet(JDWP::JdwpEventKind::EK_CLASS_PREPARE, JDWP::JdwpSuspendPolicy::SP_ALL, mod);
    }

    QTimer::singleShot(10000, [this]() {
        // wait for classloading finished
        dbgVersion();
        dbgAllClassesWithGeneric();
        // TODO set breakpoint and resume
        dbgResume();
    });
}

void DebugHandler::onSocketDisconnected()
{
    cmdmsg()->addCmdMsg("DebugHandler disconnected");
    m_event.exit();
    mSockId = 1;
    mRequestMap.clear ();
}

// -------------------for debug interface----------------------
void DebugHandler::dbgVersion() {
    auto request = JDWP::VirtualMachine::Version::buildReq (mSockId++);
    sendNewRequest (request);
}

void DebugHandler::dbgAllClasses() {
    auto request = JDWP::VirtualMachine::AllClasses::buildReq (mSockId++);
    sendNewRequest (request);
}


void DebugHandler::dbgAllClassesWithGeneric() {
    auto request = JDWP::VirtualMachine::AllClassesWithGeneric::buildReq (mSockId++);
    sendNewRequest (request);
}


void DebugHandler::dbgResume()
{
    auto request = JDWP::VirtualMachine::Resume::buildReq (mSockId++);
    sendNewRequest (request);
}

void DebugHandler::dbgSetBreakPoint(const QString& classSignature, const QString& methodName,
                                    const QString& methodSign, int32_t codeIdx)
{
//    QMetaObject::invokeMethod(this, "rehighlightBlock", Qt::QueuedConnection, Q_ARG(QTextBlock, nextBlock));

}

void DebugHandler::dbgEventRequestSet(JDWP::JdwpEventKind eventkind,
                                      JDWP::JdwpSuspendPolicy policy,
                                      const std::vector<JDWP::JdwpEventMod> &mod) {
    auto request = JDWP::EventRequest::Set::buildReq(eventkind, policy, mod, mSockId++);
    sendNewRequest(request);
}

JDWP::ClassInfo DebugHandler::dbgGetClassBySignature(const QString &classSignature) {
    auto request = JDWP::VirtualMachine::ClassesBySignature::buildReq(classSignature.toLocal8Bit(), mSockId++);
    sendNewRequest(request);
    return JDWP::ClassInfo();
}


// ------------------for handle map-------------------------
void DebugHandler::_handle_VirtualMachine_Version(JDWP::Request *request, JDWP::Request *reply)
{
    qDebug() << "VirtualMachine::Version";
    JDWP::VirtualMachine::Version ver(reply->GetExtra(), reply->GetExtraLen());
    qDebug() << ver.version << "major" << ver.major << "monor" << ver.minor
            << "javaVersion" << ver.javaVersion << "javaVmName" << ver.javaVmName;
}
void DebugHandler::_handle_VirtualMachine_ClassesBySignature(JDWP::Request *request, JDWP::Request *reply)
{
    qDebug() << "VirtualMachine::ClassesBySignature: ";
    JDWP::VirtualMachine::ClassesBySignature signature(reply->GetExtra(), reply->GetExtraLen());
    for(auto& info: signature.mInfos) {
        qDebug() << info.mRefTypeTag << info.mTypeId << info.mStatus;
    }
}
void DebugHandler::_handle_VirtualMachine_AllClasses(JDWP::Request *request, JDWP::Request *reply)
{
    qDebug() << "VirtualMachine::AllClasses: ";
    JDWP::VirtualMachine::AllClasses signature(reply->GetExtra(), reply->GetExtraLen());
    for(auto& info: signature.mInfos) {
        qDebug() << "RefTypeTag" << info.mRefTypeTag
                 << "RefTypeId" << info.mTypeId
                 << "Descriptor" << info.mDescriptor
                 << "Status" << info.mStatus;
    }

}
void DebugHandler::_handle_VirtualMachine_AllThreads(JDWP::Request *request, JDWP::Request *reply)
{

}
void DebugHandler::_handle_VirtualMachine_TopLevelThreadGroups(JDWP::Request *request, JDWP::Request *reply)
{

}
void DebugHandler::_handle_VirtualMachine_Dispose(JDWP::Request *request, JDWP::Request *reply)
{

}
void DebugHandler::_handle_VirtualMachine_IDSizes(JDWP::Request *request, JDWP::Request *reply)
{

}
void DebugHandler::_handle_VirtualMachine_Suspend(JDWP::Request *request, JDWP::Request *reply)
{

}
void DebugHandler::_handle_VirtualMachine_Resume(JDWP::Request *request, JDWP::Request *reply)
{

}
void DebugHandler::_handle_VirtualMachine_Exit(JDWP::Request *request, JDWP::Request *reply)
{

}
void DebugHandler::_handle_VirtualMachine_CreateString(JDWP::Request *request, JDWP::Request *reply)
{

}
void DebugHandler::_handle_VirtualMachine_Capabilities(JDWP::Request *request, JDWP::Request *reply)
{

}
void DebugHandler::_handle_VirtualMachine_ClassPaths(JDWP::Request *request, JDWP::Request *reply)
{

}
void DebugHandler::_handle_VirtualMachine_DisposeObjects(JDWP::Request *request, JDWP::Request *reply)
{

}
void DebugHandler::_handle_VirtualMachine_HoldEvents(JDWP::Request *request, JDWP::Request *reply)
{

}
void DebugHandler::_handle_VirtualMachine_ReleaseEvents(JDWP::Request *request, JDWP::Request *reply)
{

}
void DebugHandler::_handle_VirtualMachine_CapabilitiesNew(JDWP::Request *request, JDWP::Request *reply)
{

}
void DebugHandler::_handle_VirtualMachine_RedefineClasses(JDWP::Request *request, JDWP::Request *reply)
{

}
void DebugHandler::_handle_VirtualMachine_SetDefaultStratum(JDWP::Request *request, JDWP::Request *reply)
{

}
void DebugHandler::_handle_VirtualMachine_AllClassesWithGeneric(JDWP::Request *request, JDWP::Request *reply)
{
    qDebug() << "VirtualMachine::AllClassesWithGeneric: ";
    JDWP::VirtualMachine::AllClassesWithGeneric signature(reply->GetExtra(), reply->GetExtraLen());
    for(auto& info: signature.mInfos) {
        qDebug() << "RefTypeTag" << info.mRefTypeTag
                 << "RefTypeId" << info.mTypeId
                 << "Descriptor" << info.mDescriptor
                 << "GenericSignature" << info.mGenericSignature
                 << "Status" << info.mStatus;
    }
}
void DebugHandler::_handle_VirtualMachine_InstanceCounts(JDWP::Request *request, JDWP::Request *reply)
{

}
void DebugHandler::_handle_ReferenceType_Signature(JDWP::Request *request, JDWP::Request *reply)
{

}
void DebugHandler::_handle_ReferenceType_ClassLoader(JDWP::Request *request, JDWP::Request *reply)
{

}
void DebugHandler::_handle_ReferenceType_Modifiers(JDWP::Request *request, JDWP::Request *reply)
{

}
void DebugHandler::_handle_ReferenceType_Fields(JDWP::Request *request, JDWP::Request *reply)
{

}
void DebugHandler::_handle_ReferenceType_Methods(JDWP::Request *request, JDWP::Request *reply)
{

}
void DebugHandler::_handle_ReferenceType_GetValues(JDWP::Request *request, JDWP::Request *reply)
{

}
void DebugHandler::_handle_ReferenceType_SourceFile(JDWP::Request *request, JDWP::Request *reply)
{

}
void DebugHandler::_handle_ReferenceType_NestedTypes(JDWP::Request *request, JDWP::Request *reply)
{

}
void DebugHandler::_handle_ReferenceType_Status(JDWP::Request *request, JDWP::Request *reply)
{

}
void DebugHandler::_handle_ReferenceType_Interfaces(JDWP::Request *request, JDWP::Request *reply)
{

}
void DebugHandler::_handle_ReferenceType_ClassObject(JDWP::Request *request, JDWP::Request *reply)
{

}
void DebugHandler::_handle_ReferenceType_SourceDebugExtension(JDWP::Request *request, JDWP::Request *reply)
{

}
void DebugHandler::_handle_ReferenceType_SignatureWithGeneric(JDWP::Request *request, JDWP::Request *reply)
{

}
void DebugHandler::_handle_ReferenceType_FieldsWithGeneric(JDWP::Request *request, JDWP::Request *reply)
{

}
void DebugHandler::_handle_ReferenceType_MethodsWithGeneric(JDWP::Request *request, JDWP::Request *reply)
{

}
void DebugHandler::_handle_ReferenceType_Instances(JDWP::Request *request, JDWP::Request *reply)
{

}
void DebugHandler::_handle_ReferenceType_ClassFileVersion(JDWP::Request *request, JDWP::Request *reply)
{

}
void DebugHandler::_handle_ReferenceType_ConstantPool(JDWP::Request *request, JDWP::Request *reply)
{

}
void DebugHandler::_handle_ClassType_Superclass(JDWP::Request *request, JDWP::Request *reply)
{

}
void DebugHandler::_handle_ClassType_SetValues(JDWP::Request *request, JDWP::Request *reply)
{

}
void DebugHandler::_handle_ClassType_InvokeMethod(JDWP::Request *request, JDWP::Request *reply)
{

}
void DebugHandler::_handle_ClassType_NewInstance(JDWP::Request *request, JDWP::Request *reply)
{

}
void DebugHandler::_handle_ArrayType_NewInstance(JDWP::Request *request, JDWP::Request *reply)
{

}
void DebugHandler::_handle_Method_LineTable(JDWP::Request *request, JDWP::Request *reply)
{

}
void DebugHandler::_handle_Method_VariableTable(JDWP::Request *request, JDWP::Request *reply)
{

}
void DebugHandler::_handle_Method_Bytecodes(JDWP::Request *request, JDWP::Request *reply)
{

}
void DebugHandler::_handle_Method_IsObsolete(JDWP::Request *request, JDWP::Request *reply)
{

}
void DebugHandler::_handle_Method_VariableTableWithGeneric(JDWP::Request *request, JDWP::Request *reply)
{

}
void DebugHandler::_handle_ObjectReference_ReferenceType(JDWP::Request *request, JDWP::Request *reply)
{

}
void DebugHandler::_handle_ObjectReference_GetValues(JDWP::Request *request, JDWP::Request *reply)
{

}
void DebugHandler::_handle_ObjectReference_SetValues(JDWP::Request *request, JDWP::Request *reply)
{

}
void DebugHandler::_handle_ObjectReference_UNUSED(JDWP::Request *request, JDWP::Request *reply)
{

}
void DebugHandler::_handle_ObjectReference_MonitorInfo(JDWP::Request *request, JDWP::Request *reply)
{

}
void DebugHandler::_handle_ObjectReference_InvokeMethod(JDWP::Request *request, JDWP::Request *reply)
{

}
void DebugHandler::_handle_ObjectReference_DisableCollection(JDWP::Request *request, JDWP::Request *reply)
{

}
void DebugHandler::_handle_ObjectReference_EnableCollection(JDWP::Request *request, JDWP::Request *reply)
{

}
void DebugHandler::_handle_ObjectReference_IsCollected(JDWP::Request *request, JDWP::Request *reply)
{

}
void DebugHandler::_handle_ObjectReference_ReferringObjects(JDWP::Request *request, JDWP::Request *reply)
{

}
void DebugHandler::_handle_StringReference_Value(JDWP::Request *request, JDWP::Request *reply)
{

}
void DebugHandler::_handle_ThreadReference_Name(JDWP::Request *request, JDWP::Request *reply)
{

}
void DebugHandler::_handle_ThreadReference_Suspend(JDWP::Request *request, JDWP::Request *reply)
{

}
void DebugHandler::_handle_ThreadReference_Resume(JDWP::Request *request, JDWP::Request *reply)
{
    qDebug() << "Proecess Resumed";
    dbgOnResume();

}
void DebugHandler::_handle_ThreadReference_Status(JDWP::Request *request, JDWP::Request *reply)
{

}
void DebugHandler::_handle_ThreadReference_ThreadGroup(JDWP::Request *request, JDWP::Request *reply)
{

}
void DebugHandler::_handle_ThreadReference_Frames(JDWP::Request *request, JDWP::Request *reply)
{

}
void DebugHandler::_handle_ThreadReference_FrameCount(JDWP::Request *request, JDWP::Request *reply)
{

}
void DebugHandler::_handle_ThreadReference_OwnedMonitors(JDWP::Request *request, JDWP::Request *reply)
{

}
void DebugHandler::_handle_ThreadReference_CurrentContendedMonitor(JDWP::Request *request, JDWP::Request *reply)
{

}
void DebugHandler::_handle_ThreadReference_Stop(JDWP::Request *request, JDWP::Request *reply)
{

}
void DebugHandler::_handle_ThreadReference_Interrupt(JDWP::Request *request, JDWP::Request *reply)
{

}
void DebugHandler::_handle_ThreadReference_SuspendCount(JDWP::Request *request, JDWP::Request *reply)
{

}
void DebugHandler::_handle_ThreadReference_OwnedMonitorsStackDepthInfo(JDWP::Request *request, JDWP::Request *reply)
{

}
void DebugHandler::_handle_ThreadReference_ForceEarlyReturn(JDWP::Request *request, JDWP::Request *reply)
{

}
void DebugHandler::_handle_ThreadGroupReference_Name(JDWP::Request *request, JDWP::Request *reply)
{

}
void DebugHandler::_handle_ThreadGroupReference_Parent(JDWP::Request *request, JDWP::Request *reply)
{

}
void DebugHandler::_handle_ThreadGroupReference_Children(JDWP::Request *request, JDWP::Request *reply)
{

}
void DebugHandler::_handle_ArrayReference_Length(JDWP::Request *request, JDWP::Request *reply)
{

}
void DebugHandler::_handle_ArrayReference_GetValues(JDWP::Request *request, JDWP::Request *reply)
{

}
void DebugHandler::_handle_ArrayReference_SetValues(JDWP::Request *request, JDWP::Request *reply)
{

}
void DebugHandler::_handle_ClassLoaderReference_VisibleClasses(JDWP::Request *request, JDWP::Request *reply)
{

}
void DebugHandler::_handle_EventRequest_Set(JDWP::Request *request, JDWP::Request *reply)
{
    JDWP::EventRequest::Set set(reply->GetExtra(), reply->GetExtraLen());
    qDebug() << "EventRequestSet: " << set.mRequestId;
    // TODO record requestId
}
void DebugHandler::_handle_EventRequest_Clear(JDWP::Request *request, JDWP::Request *reply)
{

}
void DebugHandler::_handle_EventRequest_ClearAllBreakpoints(JDWP::Request *request, JDWP::Request *reply)
{

}
void DebugHandler::_handle_StackFrame_GetValues(JDWP::Request *request, JDWP::Request *reply)
{

}
void DebugHandler::_handle_StackFrame_SetValues(JDWP::Request *request, JDWP::Request *reply)
{

}
void DebugHandler::_handle_StackFrame_ThisObject(JDWP::Request *request, JDWP::Request *reply)
{

}
void DebugHandler::_handle_StackFrame_PopFrames(JDWP::Request *request, JDWP::Request *reply)
{

}
void DebugHandler::_handle_ClassObjectReference_ReflectedType(JDWP::Request *request, JDWP::Request *reply)
{

}
void DebugHandler::_handle_Event_Composite(JDWP::Request *request, JDWP::Request *reply)
{

}

void DebugHandler::setupHandleMap()
{
    mHandleMap[JDWP::VirtualMachine::set_][JDWP::VirtualMachine::Version::cmd] = &DebugHandler::_handle_VirtualMachine_Version;
    mHandleMap[JDWP::VirtualMachine::set_][JDWP::VirtualMachine::AllClasses::cmd] = &DebugHandler::_handle_VirtualMachine_AllClasses;
    mHandleMap[JDWP::VirtualMachine::set_][JDWP::VirtualMachine::AllClassesWithGeneric::cmd] = &DebugHandler::_handle_VirtualMachine_AllClassesWithGeneric;
    mHandleMap[JDWP::VirtualMachine::set_][JDWP::VirtualMachine::ClassesBySignature::cmd] = &DebugHandler::_handle_VirtualMachine_ClassesBySignature;
    mHandleMap[JDWP::VirtualMachine::set_][JDWP::VirtualMachine::Resume::cmd] = &DebugHandler::_handle_ThreadReference_Resume;

    mHandleMap[JDWP::EventRequest::set_][JDWP::EventRequest::Set::cmd] = &DebugHandler::_handle_EventRequest_Set;


}









// jdb classes
// VirtualMachine::IDSizes
