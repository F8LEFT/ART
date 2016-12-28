//===- DebugHandler.h - ART-DEBUGGER ----------------------------*- C++ -*-===//
//
//                     ANDROID REVERSE TOOLKIT
//
// This file is distributed under the GNU GENERAL PUBLIC LICENSE
// V3 License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// DebugHandler is used to handle debug information.
//
//===----------------------------------------------------------------------===//


#ifndef ANDROIDREVERSETOOLKIT_DEBUGHANDLER_H
#define ANDROIDREVERSETOOLKIT_DEBUGHANDLER_H

#include <Jdwp/jdwp.h>
#include <Jdwp/Request.h>
#include <Jdwp/JdwpHandler.h>
#include <QEventLoop>

#include <QObject>
#include <QMap>

class DebugSocket;

class DebugHandler: public QObject {
    Q_OBJECT
public:
    DebugHandler(QObject* parent = Q_NULLPTR, DebugSocket* socket = Q_NULLPTR);
    ~DebugHandler();

    void setupHandleMap();

public:
    // Debugger interfaces
    void dbgVersion();
    void dbgAllClasses();   // not support for dalvik
    void dbgAllClassesWithGeneric();
    void dbgResume();
    void dbgSetBreakPoint(const QString& classSignature, const QString& methodName,
                          const QString& methodSign, int32_t codeIdx);

    void dbgEventRequestSet(JDWP::JdwpEventKind eventkind, JDWP::JdwpSuspendPolicy policy,
                            const std::vector<JDWP::JdwpEventMod>& mod = std::vector<JDWP::JdwpEventMod>() );

    JDWP::ClassInfo dbgGetClassBySignature(const QString& classSignature);

    void waitForResponse() {
        m_event.exec();
    }
    void requestResponse() {
        m_event.exit(0);
    }
signals:
    // handle request/reply result;
    void dbgOnResume();

    // handle socket event
    void sendBuffer(const QByteArray& array);
    void sendBuffer(const char*data, quint64 len);

    void stopCurrentTarget();

private slots:
    // connect to DebugSocket
    void onSocketError(int error, const QString &message);
    void onSocketConnected();
    void onSocketDisconnected();

    void onJDWPRequest(JDWP::Request *request);

private:
    void handleReply(QSharedPointer<JDWP::Request> & reply);
    void handleCommand(QSharedPointer<JDWP::Request> & reply);

    bool sendNewRequest(const QByteArray& req);

    bool ProcessRequest(JDWP::Request* request, JDWP::Request* reply);

private:
    DebugSocket* mSocket;
    QMap<int, QSharedPointer<JDWP::Request>> mRequestMap;
    int mSockId = 0;

private:
    typedef void (DebugHandler::*pkgHandle)(JDWP::Request*,JDWP::Request *);

    // * VirtualMachine command set (1)
    void _handle_VirtualMachine_Version(JDWP::Request *request,JDWP::Request *reply);
    void _handle_VirtualMachine_ClassesBySignature(JDWP::Request *request,JDWP::Request *reply);
    void _handle_VirtualMachine_AllClasses(JDWP::Request *request,JDWP::Request *reply);
    void _handle_VirtualMachine_AllThreads(JDWP::Request *request,JDWP::Request *reply);
    void _handle_VirtualMachine_TopLevelThreadGroups(JDWP::Request *request,JDWP::Request *reply);
    void _handle_VirtualMachine_Dispose(JDWP::Request *request,JDWP::Request *reply);
    void _handle_VirtualMachine_IDSizes(JDWP::Request *request,JDWP::Request *reply);
    void _handle_VirtualMachine_Suspend(JDWP::Request *request,JDWP::Request *reply);
    void _handle_VirtualMachine_Resume(JDWP::Request *request,JDWP::Request *reply);
    void _handle_VirtualMachine_Exit(JDWP::Request *request,JDWP::Request *reply);
    void _handle_VirtualMachine_CreateString(JDWP::Request *request,JDWP::Request *reply);
    void _handle_VirtualMachine_Capabilities(JDWP::Request *request,JDWP::Request *reply);
    void _handle_VirtualMachine_ClassPaths(JDWP::Request *request,JDWP::Request *reply);
    void _handle_VirtualMachine_DisposeObjects(JDWP::Request *request,JDWP::Request *reply);
    void _handle_VirtualMachine_HoldEvents(JDWP::Request *request,JDWP::Request *reply);
    void _handle_VirtualMachine_ReleaseEvents(JDWP::Request *request,JDWP::Request *reply);
    void _handle_VirtualMachine_CapabilitiesNew(JDWP::Request *request,JDWP::Request *reply);
    void _handle_VirtualMachine_RedefineClasses(JDWP::Request *request,JDWP::Request *reply);
    void _handle_VirtualMachine_SetDefaultStratum(JDWP::Request *request,JDWP::Request *reply);
    void _handle_VirtualMachine_AllClassesWithGeneric(JDWP::Request *request,JDWP::Request *reply);
    void _handle_VirtualMachine_InstanceCounts(JDWP::Request *request,JDWP::Request *reply);
//        * ReferenceType command set (2)
    void _handle_ReferenceType_Signature(JDWP::Request *request,JDWP::Request *reply);
    void _handle_ReferenceType_ClassLoader(JDWP::Request *request,JDWP::Request *reply);
    void _handle_ReferenceType_Modifiers(JDWP::Request *request,JDWP::Request *reply);
    void _handle_ReferenceType_Fields(JDWP::Request *request,JDWP::Request *reply);
    void _handle_ReferenceType_Methods(JDWP::Request *request,JDWP::Request *reply);
    void _handle_ReferenceType_GetValues(JDWP::Request *request,JDWP::Request *reply);
    void _handle_ReferenceType_SourceFile(JDWP::Request *request,JDWP::Request *reply);
    void _handle_ReferenceType_NestedTypes(JDWP::Request *request,JDWP::Request *reply);
    void _handle_ReferenceType_Status(JDWP::Request *request,JDWP::Request *reply);
    void _handle_ReferenceType_Interfaces(JDWP::Request *request,JDWP::Request *reply);
    void _handle_ReferenceType_ClassObject(JDWP::Request *request,JDWP::Request *reply);
    void _handle_ReferenceType_SourceDebugExtension(JDWP::Request *request,JDWP::Request *reply);
    void _handle_ReferenceType_SignatureWithGeneric(JDWP::Request *request,JDWP::Request *reply);
    void _handle_ReferenceType_FieldsWithGeneric(JDWP::Request *request,JDWP::Request *reply);
    void _handle_ReferenceType_MethodsWithGeneric(JDWP::Request *request,JDWP::Request *reply);
    void _handle_ReferenceType_Instances(JDWP::Request *request,JDWP::Request *reply);
    void _handle_ReferenceType_ClassFileVersion(JDWP::Request *request,JDWP::Request *reply);
    void _handle_ReferenceType_ConstantPool(JDWP::Request *request,JDWP::Request *reply);
//        * ClassType command set (3)
    void _handle_ClassType_Superclass(JDWP::Request *request,JDWP::Request *reply);
    void _handle_ClassType_SetValues(JDWP::Request *request,JDWP::Request *reply);
    void _handle_ClassType_InvokeMethod(JDWP::Request *request,JDWP::Request *reply);
    void _handle_ClassType_NewInstance(JDWP::Request *request,JDWP::Request *reply);
//        * ArrayType command set (4)
    void _handle_ArrayType_NewInstance(JDWP::Request *request,JDWP::Request *reply);
//        * InterfaceType command set (5)
//    * Method command set (6)
    void _handle_Method_LineTable(JDWP::Request *request,JDWP::Request *reply);
    void _handle_Method_VariableTable(JDWP::Request *request,JDWP::Request *reply);
    void _handle_Method_Bytecodes(JDWP::Request *request,JDWP::Request *reply);
    void _handle_Method_IsObsolete(JDWP::Request *request,JDWP::Request *reply);
    void _handle_Method_VariableTableWithGeneric(JDWP::Request *request,JDWP::Request *reply);
//        * Field command set (8)
//    * ObjectReference command set (9)
    void _handle_ObjectReference_ReferenceType(JDWP::Request *request,JDWP::Request *reply);
    void _handle_ObjectReference_GetValues(JDWP::Request *request,JDWP::Request *reply);
    void _handle_ObjectReference_SetValues(JDWP::Request *request,JDWP::Request *reply);
    void _handle_ObjectReference_UNUSED(JDWP::Request *request,JDWP::Request *reply);
    void _handle_ObjectReference_MonitorInfo(JDWP::Request *request,JDWP::Request *reply);
    void _handle_ObjectReference_InvokeMethod(JDWP::Request *request,JDWP::Request *reply);
    void _handle_ObjectReference_DisableCollection(JDWP::Request *request,JDWP::Request *reply);
    void _handle_ObjectReference_EnableCollection(JDWP::Request *request,JDWP::Request *reply);
    void _handle_ObjectReference_IsCollected(JDWP::Request *request,JDWP::Request *reply);
    void _handle_ObjectReference_ReferringObjects(JDWP::Request *request,JDWP::Request *reply);
//        * StringReference command set (10)
    void _handle_StringReference_Value(JDWP::Request *request,JDWP::Request *reply);
//        * ThreadReference command set (11)
    void _handle_ThreadReference_Name(JDWP::Request *request,JDWP::Request *reply);
    void _handle_ThreadReference_Suspend(JDWP::Request *request,JDWP::Request *reply);
    void _handle_ThreadReference_Resume(JDWP::Request *request,JDWP::Request *reply);
    void _handle_ThreadReference_Status(JDWP::Request *request,JDWP::Request *reply);
    void _handle_ThreadReference_ThreadGroup(JDWP::Request *request,JDWP::Request *reply);
    void _handle_ThreadReference_Frames(JDWP::Request *request,JDWP::Request *reply);
    void _handle_ThreadReference_FrameCount(JDWP::Request *request,JDWP::Request *reply);
    void _handle_ThreadReference_OwnedMonitors(JDWP::Request *request,JDWP::Request *reply);
    void _handle_ThreadReference_CurrentContendedMonitor(JDWP::Request *request,JDWP::Request *reply);
    void _handle_ThreadReference_Stop(JDWP::Request *request,JDWP::Request *reply);
    void _handle_ThreadReference_Interrupt(JDWP::Request *request,JDWP::Request *reply);
    void _handle_ThreadReference_SuspendCount(JDWP::Request *request,JDWP::Request *reply);
    void _handle_ThreadReference_OwnedMonitorsStackDepthInfo(JDWP::Request *request,JDWP::Request *reply);
    void _handle_ThreadReference_ForceEarlyReturn(JDWP::Request *request,JDWP::Request *reply);
//        * ThreadGroupReference command set (12)
    void _handle_ThreadGroupReference_Name(JDWP::Request *request,JDWP::Request *reply);
    void _handle_ThreadGroupReference_Parent(JDWP::Request *request,JDWP::Request *reply);
    void _handle_ThreadGroupReference_Children(JDWP::Request *request,JDWP::Request *reply);
//        * ArrayReference command set (13)
    void _handle_ArrayReference_Length(JDWP::Request *request,JDWP::Request *reply);
    void _handle_ArrayReference_GetValues(JDWP::Request *request,JDWP::Request *reply);
    void _handle_ArrayReference_SetValues(JDWP::Request *request,JDWP::Request *reply);
//        * ClassLoaderReference command set (14)
    void _handle_ClassLoaderReference_VisibleClasses(JDWP::Request *request,JDWP::Request *reply);
//        * EventRequest command set (15)
    void _handle_EventRequest_Set(JDWP::Request *request,JDWP::Request *reply);
    void _handle_EventRequest_Clear(JDWP::Request *request,JDWP::Request *reply);
    void _handle_EventRequest_ClearAllBreakpoints(JDWP::Request *request,JDWP::Request *reply);
//        * StackFrame command set (16)
    void _handle_StackFrame_GetValues(JDWP::Request *request,JDWP::Request *reply);
    void _handle_StackFrame_SetValues(JDWP::Request *request,JDWP::Request *reply);
    void _handle_StackFrame_ThisObject(JDWP::Request *request,JDWP::Request *reply);
    void _handle_StackFrame_PopFrames(JDWP::Request *request,JDWP::Request *reply);
//        * ClassObjectReference command set (17)
    void _handle_ClassObjectReference_ReflectedType(JDWP::Request *request,JDWP::Request *reply);
//        * Event command set (64)
    void _handle_Event_Composite(JDWP::Request *request,JDWP::Request *reply);

    QMap<int, QMap<int, pkgHandle >> mHandleMap;

public:
//  stack for
    QEventLoop m_event;
};


#endif //ANDROIDREVERSETOOLKIT_DEBUGHANDLER_H
