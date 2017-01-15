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

#include "FrameListView.h"
#include "VariableTreeView.h"

#include <Jdwp/jdwp.h>
#include <Jdwp/Request.h>
#include <Jdwp/JdwpHandler.h>
#include <QEventLoop>
#include <QMultiMap>

#include <QObject>
#include <QMap>
#include <QSharedPointer>

class DebugSocket;
class RequestExtra;
class ReqestPackage;
class CommandPackage;

class DebugHandler: public QObject {
    Q_OBJECT
public:
    DebugHandler(QObject* parent = Q_NULLPTR, DebugSocket* socket = Q_NULLPTR);
    ~DebugHandler();

public:
    enum DebugStatus {
        NotActive,
        Active,
        Run,
        Stop,
        Step,
    };
    void updateThreadFrame(JDWP::ObjectId threadId);

public:
    // Debugger interfaces
    /*!
     * set a breakpoint in target app.
     * @param classSignature class name, like(Ljava/lang/Object;)
     * @param methodName method name, like(onCreate)
     * @param methodSign method signature, like ([B)V
     * @param codeIdx code index in method.
     */
    void dbgSetBreakPoint(const QString &classSignature,
                          const QString &methodName,
                          const QString &methodSign,
                          uint64_t codeIdx);

    /*!
     * wait for class loaded
     * @tparam Func(JDWP::Composite::ReflectedType::EventClassPrepare* prepare)
     * @param javaSignature
     * @param callback
     */
    template <typename Func>
    void waitForClassPrepared(QString javaSignature, Func callback);

    /*!
     * VirtualMachine::Version(1, 1)
     * Request for version info.
     */
    void dbgVirtualMachineVersion();

    /*!
     * VirtualMachine::ClassesBySignature (1, 2)
     * Given a class JNI signature (e.g. "Ljava/lang/Error;"), return the
     * referenceTypeID.  We need to send back more than one if the class has
     * been loaded by multiple class loaders.
     * @tparam Func(JDWP::ClassInfo classinfo)
     * @param classSignature
     * @param callback
     */
    template <typename Func>
    void dbgGetClassBySignature(const QString &classSignature, Func callback);

    /*!
     * VirtualMachine::Resume(1, 9)
     * Resume execution.  Decrements the "suspend count" of all threads.
     */
    void dbgVirtualMachineResume();


    /*!
     * VirtualMachine::AllClassesWithGeneric(1, 20)
     * Cough up the complete list of classes.
     */
    void dbgVirtualMachineAllClassesWithGeneric();

    /*!
     * ReferenctType::GetValues (2, 6)
     * Get values from static fields in a reference type.
     * @tparam Func(const QVector<JDWP::JValue>& values)
     * @param refTypeId
     * @param fieldids
     * @param callback
     */
    template <typename Func>
    void dbgReferenceTypeGetValues(JDWP::RefTypeId refTypeId,
                                   const QVector<JDWP::FieldId > &fieldids,
                                   Func callback);

    /*!
     * ReferenceType::ClassObject (2, 11)
     * Return the class object corresponding to this type.
     * @tparam Func(JDWP::ObjectId object)
     * @param refTypeId
     * @param callback
     */
    template <typename Func>
    void dbgReferenceTypeClassObject(JDWP::RefTypeId refTypeId, Func callback);

    /*!
     * ReferenctType::SignatureWithGeneric (2, 13)
     * Like RT_Signature but with the possibility of a "generic signature".
     * @tparam Func(QByteArray signature, QByteArray signatureWithGeneric)
     * @param refTypeId
     * @param callback
     */
    template <typename Func>
    void dbgReferenceTypeSignatureWithGeneric(JDWP::RefTypeId refTypeId, Func callback);

    /*!
     * ReferenctType::FieldsWithGeneric (2, 14)
     * Given a referenceTypeId, return a block of stuff that describes the
     * fields declared by a class.
     * @tparam Func(QVector<JDWP::FieldInfo>)
     * @param refTypeId referenctTypeId
     * @param callback the callback Func
     */
    template <typename Func>
    void dbgReferenceTypeFieldsWithGeneric(JDWP::RefTypeId refTypeId, Func callback);

    /*!
     * ReferenctType::MethodsWithGeneric (2, 15)
     * Given a referenceTypeID, return a block of goodies describing the
     * methods declared by a class.
     * @tparam Func(QVector<JDWP::MethodInfo> methods)
     * @param refTypeId referenctTypeID
     * @param callback the callback Func
     */
    template  <typename Func>
    void dbgReferenctTypeMethodsWithGeneric(JDWP::RefTypeId refTypeId,
                                            Func callback);

    /*!
     * ClassType::SuperClass (3, 1)
     * Return the immediate superclass of a class.
     * @tparam Func(JDWP::RefTypeId refId)
     * @param refTypeId
     * @param callback
     */
    template <typename Func>
    void dbgClassTypeSuperclass(JDWP::RefTypeId refTypeId, Func callback);

    /*!
     * ObjectReferenct::ReferenceType (9, 1)
     * Given an object reference, return the runtime type of the object
     * (class or array).
     * This can get called on different things, e.g. threadId gets
     * passed in here.
     * @tparam Func(JDWP::JdwpTypeTag tag, JDWP::RefTypeId mTypeId)
     * @param objectId
     * @param callback
     */
    template <typename Func>
    void dbgObjectReferenceReferenceType(JDWP::ObjectId objectId, Func callback);

    /*!
     * ObjectReference::GetValues (9, 2)
     * Get values from the fields of an object.
     * @tparam Func(const QVector<JDWP::JValue>& values)
     * @param objectId
     * @param fieldids
     * @param callback
     */
    template <typename Func>
    void dbgObjectReferenceGetValues(JDWP::RefTypeId objectId,
                                     const QVector<JDWP::FieldId > &fieldids,
                                     Func callback);

    /*!
     * StringRefreenct::Value (10, 1)
     * Return the string value in a string object.
     * @tparam Func(const QByteArray& str)
     * @param objectId
     * @param callback
     */
    template <typename Func>
    void dbgStringReferenceValue(JDWP::ObjectId objectId, Func callback);

    /*!
     * ThreadReference::Frames (11, 6)
     * Return the current call stack of a suspended thread.
     * If the thread isn't suspended, the error code isn't defined, but should
     * be THREAD_NOT_SUSPENDED.
     * @tparam Func(JDWP::ThreadReference::Frames)
     * @param thread_id
     * @param callback
     */
    template <typename Func>
    void dbgThreadReferenceFrames(JDWP::ObjectId thread_id, Func callback);

    /*!
     * ArrayReferenct::Length (13, 1)
     * Return the #of components in the array.
     * @tparam Func(int length)
     * @param objectId
     * @param callback
     */
    template <typename Func>
    void dbgArrayReferenceLength(JDWP::ObjectId objectId, Func callback);

    /*!
     * ArrayReference::GetValues (13, 1)
     * Return the values from an array.
     * @tparam Func(const QVector<JDWP::JValue>& values)
     * @param array_id
     * @param offset
     * @param length
     * @param callback
     */
    template <typename Func>
    void dbgArrayReferenceGetValues(JDWP::ObjectId array_id,
                                    uint32_t offset,
                                    uint32_t length,
                                    Func callback);

    /*!
     * EventRequest::Set (15, 1)
     * Set an event trigger. Reply with a requestID.
     * @tparam Func(JDWP::JdwpEventKind eventkind, uint32_t requestId)
     * @param eventkind event kind.
     * @param policy suspend policy.
     * @param mod eventmod typs
     * @param callback
     */
    template <typename Func>
    void dbgEventRequestSet(JDWP::JdwpEventKind eventkind,
                            JDWP::JdwpSuspendPolicy policy,
                            const std::vector<JDWP::JdwpEventMod>& mod,
                            Func callback);

    /*!
     * EventRequest::Clear (15, 2)
     * Clear an event.  Failure to find an event with a matching ID is a no-op
     * and does not return an error.
     * @param kind
     * @param requestId
     */
    void dbgEventRequestClear(JDWP::JdwpEventKind kind,
                              uint32_t requestId);


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

    void onJDWPRequest(QByteArray data);

public slots:
    void dumpFrameInfo(JDWP::ObjectId threadId, FrameListModel::FrameData* frame);

    void dumpFieldItemValue(VariableTreeItem* item);
private:
    void handleReply(JDWP::Request &reply);
    void handleCommand(JDWP::Request & reply);

    bool sendNewRequest(QSharedPointer<ReqestPackage>& req);
    void setCommandPackage(JDWP::JdwpEventKind eventkind, QSharedPointer<CommandPackage>& package);

private:
    void breakPointHit(JDWP::JdwpSuspendPolicy  policy,
                       JDWP::Composite::ReflectedType::EventLocationEvent*event);

    void stopOnProcessEntryPoint();
    void setAllBreakpoint();

    void dumpObjectItemValue(VariableTreeItem* item);
    void dumpArrayItemValue(VariableTreeItem *item);
    void dumpStringItemValue(VariableTreeItem* item);

    void dumpObjectValueWithRef(VariableTreeItem* item);
    void setItemValue(VariableTreeItem *parent, const JDWP::FieldInfo* fieldInfo,
                      const JDWP::JValue* value);
private:
    DebugSocket* mSocket;
    QMap<int, QSharedPointer<ReqestPackage>> mRequestMap;
    QVector<QVector<QSharedPointer<CommandPackage>>> mCommandVector;    // [EventGroup][CommandPackage]
    int mSockId = 0;
public:
    // classsign - classinfo map
    QMultiMap<QString, JDWP::RefTypeId> mLoadedClassRef;
    QMap<JDWP::RefTypeId, JDWP::ClassInfo> mLoadedClassInfo;
    QMap<JDWP::RefTypeId, QVector<JDWP::MethodInfo>> mLoadedMethodsInfo;    // map to ClassId, methodinfo
    QMap<JDWP::RefTypeId, QVector<JDWP::FieldInfo>> mLoadedFieldsInfo;      // map to ClassId, fieldinfo

    DebugStatus mDebugStatus;
};

struct RequestExtraBreakPoint{
    RequestExtraBreakPoint(const QString &classSignature,
                           const QString &methodName,
                           const QString &methodSign,
                           uint64_t codeIdx)
            : mClassSignature(classSignature),
              mMethodName(methodName),
              mMethodSign(methodSign),
              mCodeIdx(codeIdx) {}
    QString mClassSignature;
    QString mMethodName;
    QString mMethodSign;
    uint64_t mCodeIdx;
};

// for JDWP package request and reply
class ReqestPackage: public QObject {
    Q_OBJECT
public:
    ReqestPackage(QByteArray& data, QObject* parent = nullptr);
    ~ReqestPackage();
signals:
    void onReply(JDWP::Request *request,QByteArray& reply);

public:
    void handleReply(QByteArray& reply);

    QByteArray mData;
    JDWP::Request mRequest;
};

// for JDWP package command. set command hook and wait for match command.
class CommandPackage: public QObject {
    Q_OBJECT

public:
    CommandPackage(JDWP::JdwpEventModPad mod, JDWP::JdwpSuspendPolicy policy, QObject* parent = nullptr);
    ~CommandPackage();
signals:
    void onLocation(JDWP::Composite::ReflectedType::EventLocationEvent* location, JDWP::JdwpSuspendPolicy  policy, bool *clear);
    void onException(JDWP::Composite::ReflectedType::EventException* exception, JDWP::JdwpSuspendPolicy  policy, bool *clear);
    void onThreadChange(JDWP::Composite::ReflectedType::EventThreadChange* thread, JDWP::JdwpSuspendPolicy  policy, bool *clear);
    void onClassPrepare(JDWP::Composite::ReflectedType::EventClassPrepare* prepare, JDWP::JdwpSuspendPolicy  policy, bool *clear);
    void onVmStart(JDWP::Composite::ReflectedType::EventVmStart* vmStart, JDWP::JdwpSuspendPolicy  policy, bool *clear);
    void onVmDeath(bool *clear);
public:
    bool match(JDWP::Composite::ReflectedType::EventObject* pevent, JDWP::JdwpSuspendPolicy  policy);
public:
    enum EventGroup {
        Location = 0,
        Exception,
        Thread,
        Prepare,
        VmStart,
        VmDeath,
        Unknown,
    };
    static int getEventGroup(JDWP::JdwpEventKind kind);
public:
    JDWP::JdwpEventModPad mMod;
    JDWP::JdwpSuspendPolicy  mSuspendPolicy;
    bool clear = false;
};





#endif //ANDROIDREVERSETOOLKIT_DEBUGHANDLER_H
