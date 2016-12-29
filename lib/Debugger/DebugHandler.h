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
#include <QSharedPointer>

class DebugSocket;
class RequestExtra;
class ReqestPackage;

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
    void dbgEventRequestSet(JDWP::JdwpEventKind eventkind, JDWP::JdwpSuspendPolicy policy,
                            const std::vector<JDWP::JdwpEventMod>& mod = std::vector<JDWP::JdwpEventMod>());
    template  <typename Func>
    bool dbgGetRefTypeMethodsWithGeneric(JDWP::RefTypeId refTypeId, Func callback);
    template <typename Func>
    bool dbgGetClassBySignature(const QString& classSignature, Func callback);


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

    void onJDWPRequest(QByteArray data);

private:
    void handleReply(JDWP::Request &reply);
    void handleCommand(JDWP::Request & reply);

    bool sendNewRequest(QSharedPointer<ReqestPackage>& req);

private:
    DebugSocket* mSocket;
    QMap<int, QSharedPointer<ReqestPackage>> mRequestMap;
    int mSockId = 0;

public:
    QEventLoop m_event;

    // classsign - classinfo map
//    QMap<QString, JDWP::ClassInfo> mLoadedClassInfo;
//    QMap<JDWP::RefTypeId, QVector<JDWP::MethodInfo>> mMethodsInfo;
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


#endif //ANDROIDREVERSETOOLKIT_DEBUGHANDLER_H
