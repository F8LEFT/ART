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
    // Debugger interfaces
    void dbgVersion();
    void dbgResume();
    void dbgSetBreakPoint(const QString &classSignature,
                          const QString &methodName,
                          const QString &methodSign, uint64_t codeIdx);


    void dbgAllClassesWithGeneric();

    // Func(JDWP::JdwpEventKind eventkind, uint32_t requestId)
    template <typename Func>
    void dbgEventRequestSet(JDWP::JdwpEventKind eventkind, JDWP::JdwpSuspendPolicy policy,
                            const std::vector<JDWP::JdwpEventMod>& mod,
                            Func callback);
    void dbgEventRequestClear(JDWP::JdwpEventKind kind, uint32_t requestId);

    // Func(QVector<JDWP::MethodInfo> methods)
    template  <typename Func>
    void dbgGetRefTypeMethodsWithGeneric(JDWP::RefTypeId refTypeId,
                                         Func callback);

    // Func(JDWP::ClassInfo classinfo)
    template <typename Func>
    void dbgGetClassBySignature(const QString &classSignature, Func callback);

    // wait for class loaded, input signature must like java.lang.String
    // Func(JDWP::Composite::ReflectedType::EventClassPrepare* prepare)
    template <typename Func>
    void waitForClassPrepared(QString javaSignature, Func callback);

    // Func(JDWP::ThreadReference::Frames)
    template <typename Func>
    void dbgThreadReferenceFrames(JDWP::ObjectId thread_id, Func callback);
    void dbgReferenceTypeSignatureWithGeneric(JDWP::RefTypeId refTypeId);
    void dbgReferenceTypeMethodsWithGeneric(JDWP::RefTypeId refTypeId);

    void setCommandPackage(JDWP::JdwpEventKind eventkind, QSharedPointer<CommandPackage>& package);

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

private:
    void handleReply(JDWP::Request &reply);
    void handleCommand(JDWP::Request & reply);

    bool sendNewRequest(QSharedPointer<ReqestPackage>& req);

private:
    void breakPointHit(JDWP::JdwpSuspendPolicy  policy,
                       JDWP::Composite::ReflectedType::EventLocationEvent*event);
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



QString jniSigToJavaSig(QString sig);
QByteArray jniSigToJavaSig(QByteArray sig);

#endif //ANDROIDREVERSETOOLKIT_DEBUGHANDLER_H
