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
#include "FrameListView.h"
#include "VariableTreeView.h"

#include <SmaliAnalysis/SmaliAnalysis.h>

#include <utils/ProjectInfo.h>
#include <utils/CmdMsgUtil.h>
#include <utils/StringUtil.h>
#include <Jdwp/jdwp.h>
#include <Jdwp/JdwpHeader.h>

#include <QDebug>
#include <QTimer>


DebugHandler::DebugHandler(QObject *parent, DebugSocket* socket)
        : QObject(parent), mDebugStatus(NotActive)
{
    mSocket = socket;

    connect(mSocket, &DebugSocket::newJDWPRequest, this, &DebugHandler::onJDWPRequest);

    connect(mSocket, &DebugSocket::error, this, &DebugHandler::onSocketError);
    connect(mSocket, &DebugSocket::connected, this, &DebugHandler::onSocketConnected);
    connect(mSocket, &DebugSocket::disconnected, this, &DebugHandler::onSocketDisconnected);

    connect(this, SIGNAL(sendBuffer(const char*,quint64)),
            mSocket->mSocketEvent, SLOT(onWrite(const char*,quint64)));
    connect(this, SIGNAL(sendBuffer(QByteArray)), mSocket->mSocketEvent, SLOT(onWrite(QByteArray)));

    connect(this, &DebugHandler::stopCurrentTarget, mSocket->mSocketEvent, &DebugSocketEvent::onStop);

    connect(FrameListView::instance(), &FrameListView::frameItemClicked, this, &DebugHandler::dumpFrameInfo);

    mCommandVector.resize(CommandPackage::EventGroup::Unknown + 1);
}

DebugHandler::~DebugHandler()
{

}


void DebugHandler::onJDWPRequest (QByteArray data)
{
    JDWP::Request request((uint8_t*)data.data(), data.length());
    if(request.isReply ()) {
        handleReply (request);
    } else {
        handleCommand(request);
    }
}

void DebugHandler::handleReply (JDWP::Request &reply)
{
    auto id = reply.GetId ();

    auto it = mRequestMap.find (id);
    if(it == mRequestMap.end ()) {
        return;
    }
    auto request = it->data ();
    auto array = reply.GetExtraArray();
    request->handleReply(array);
    mRequestMap.erase (it);
}

void DebugHandler::handleCommand (JDWP::Request &request)
{
    // Command is sended form VM to debugger,
    qDebug() << "Handle command for id " << request.GetId()
             << " CommandSet:" << request.GetCommandSet ()
             << " Command:" << request.GetCommand ();
    JDWP::Composite::ReflectedType composite(request.GetExtra(), request.GetExtraLen());
    qDebug() << "Composite suspend" << composite.mSuspendPolicy << "even count" << composite.mCount;
    for(auto &pevent: composite.mEventList) {
        auto eventKind = pevent->mEventKind;
        switch(eventKind) {
            case JDWP::JdwpEventKind::EK_SINGLE_STEP:
            case JDWP::JdwpEventKind::EK_BREAKPOINT:
            case JDWP::JdwpEventKind::EK_METHOD_ENTRY:
            case JDWP::JdwpEventKind::EK_METHOD_EXIT: {
                auto event = (JDWP::Composite::ReflectedType::EventLocationEvent*)pevent;
                breakPointHit(composite.mSuspendPolicy, event);
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
                JDWP::ClassInfo info;
                info.mDescriptor = event->mSignature;
                info.mStatus = event->mStatus;
                info.mTypeId = event->mTypeId;
                info.mRefTypeTag = event->mTag;
                if(!mLoadedClassInfo.contains(info.mTypeId)) {
                    mLoadedClassRef.insert(info.mDescriptor, info.mTypeId);
                }
                mLoadedClassInfo[info.mTypeId] = info;
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

        // find group matching
        auto group = CommandPackage::getEventGroup(eventKind);
        auto &commands = mCommandVector[group];
        for(auto it = commands.begin(); it != commands.end(); ) {
            auto command = it->data();
            command->match(pevent, composite.mSuspendPolicy);
            if(command->clear) {
                it = commands.erase(it);
            } else {
                it ++;
            }
        }
    }
}

bool DebugHandler::sendNewRequest (QSharedPointer<ReqestPackage>& req)
{
    mRequestMap[req->mRequest.GetId ()] = req;
    sendBuffer (req->mData);
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
    mDebugStatus = Active;

    // Init
    // get all loaded class information
    dbgAllClassesWithGeneric();
    dbgEventRequestSet(JDWP::JdwpEventKind::EK_CLASS_PREPARE, JDWP::JdwpSuspendPolicy::SP_NONE, std::vector<JDWP::JdwpEventMod>(),
                       [this](JDWP::JdwpEventKind eventkind, uint32_t requestId) {});
    dbgEventRequestSet(JDWP::JdwpEventKind::EK_CLASS_UNLOAD, JDWP::JdwpSuspendPolicy::SP_NONE, std::vector<JDWP::JdwpEventMod>(),
                       [this](JDWP::JdwpEventKind eventkind, uint32_t requestId) {});
    // suspend and set breakpoiont to catch exception
//    {
//        std::vector<JDWP::JdwpEventMod> mod;
//
//        JDWP::JdwpEventMod m1;
//        m1.modKind = JDWP::JdwpModKind::MK_CLASS_MATCH;
//        std::string m1Class = "java.lang.Throwable";
//        m1.classMatch.classPattern = (char*)m1Class.c_str();
//        mod.push_back(m1);
//
//        JDWP::JdwpEventMod m2;
//        m2.modKind = JDWP::JdwpModKind::MK_COUNT;
//        m2.count.count = 1;
//        mod.push_back(m2);
//
//        dbgEventRequestSet(JDWP::JdwpEventKind::EK_CLASS_PREPARE, JDWP::JdwpSuspendPolicy::SP_ALL, mod,
//                           [this](JDWP::JdwpEventKind eventkind, uint32_t requestId) {});
//    }
    // suspend and set breakpoint to process entry point
    stopOnProcessEntryPoint();
    setAllBreakpoint();

    QTimer::singleShot(10000, [this]() {
        // wait for classloading finished and breakpoint set
        dbgResume();
    });
}

void DebugHandler::onSocketDisconnected()
{
    cmdmsg()->addCmdMsg("DebugHandler disconnected");
    mSockId = 1;
    mRequestMap.clear ();
    for(auto & command: mCommandVector) {
        command.clear();
    }
    mLoadedClassRef.clear();
    mLoadedClassInfo.clear();
    mLoadedMethodsInfo.clear();
    mLoadedFieldsInfo.clear();
}

// -------------------for debug interface----------------------
void DebugHandler::dbgVersion() {
    auto request = JDWP::VirtualMachine::Version::buildReq (mSockId++);
    auto package = QSharedPointer<ReqestPackage>(new ReqestPackage(request));
    connect(package.data(), &ReqestPackage::onReply, [this](JDWP::Request *request,QByteArray& reply) {
        JDWP::VirtualMachine::Version ver((uint8_t*)reply.data(), reply.length());
        qDebug() << "VirtualMachine::Version";
        qDebug() << ver.version << "major" << ver.major << "monor" << ver.minor
                 << "javaVersion" << ver.javaVersion << "javaVmName" << ver.javaVmName;
    });
    sendNewRequest (package);
}

void DebugHandler::dbgAllClassesWithGeneric() {
    auto request = JDWP::VirtualMachine::AllClassesWithGeneric::buildReq (mSockId++);
    auto package = QSharedPointer<ReqestPackage>(new ReqestPackage(request));
    connect(package.data(), &ReqestPackage::onReply, [this](JDWP::Request *request,QByteArray& reply) {
        qDebug() << "VirtualMachine::AllClassesWithGeneric: ";
        JDWP::VirtualMachine::AllClassesWithGeneric signature((uint8_t*)reply.data(), reply.length());
        for(auto& info: signature.mInfos) {
            qDebug() << "RefTypeTag" << info.mRefTypeTag
                     << "RefTypeId" << info.mTypeId
                     << "Descriptor" << info.mDescriptor
                     << "GenericSignature" << info.mGenericSignature
                     << "Status" << info.mStatus;
            // Record classinfo
            if(!mLoadedClassInfo.contains(info.mTypeId)) {
                mLoadedClassRef.insert(info.mDescriptor, info.mTypeId);
            }
            mLoadedClassInfo[info.mTypeId] = info;
        }
    });
    sendNewRequest (package);
}

void DebugHandler::dbgResume()
{
    auto request = JDWP::VirtualMachine::Resume::buildReq (mSockId++);
    auto package = QSharedPointer<ReqestPackage>(new ReqestPackage(request));
    connect(package.data(), &ReqestPackage::onReply, [this](JDWP::Request *request,QByteArray& reply) {
        mDebugStatus = Run;
        dbgOnResume();
    });
    sendNewRequest (package);
}

void DebugHandler::dbgSetBreakPoint(const QString &classSignature,
                                    const QString &methodName,
                                    const QString &methodSign, uint64_t codeIdx)
{
    QSharedPointer<RequestExtraBreakPoint> extra(new RequestExtraBreakPoint(
            classSignature, methodName, methodSign, codeIdx));
    dbgGetClassBySignature(classSignature, [this, extra](JDWP::ClassInfo classinfo) {
        dbgReferenctTypeMethodsWithGeneric(classinfo.mTypeId,
                                           [this, extra, classinfo](
                                                   QVector<JDWP::MethodInfo> methods) {
                                               for (auto &method: methods) {
                                                   if (method.mName !=
                                                       extra->mMethodName ||
                                                       method.mSignature !=
                                                       extra->mMethodSign) {
                                                       continue;
                                                   }
                                                   qDebug()
                                                           << "set BreakPoint to "
                                                           << extra->mClassSignature
                                                           << extra->mMethodName
                                                           << extra->mMethodSign
                                                           << extra->mCodeIdx;
                                                   std::vector<JDWP::JdwpEventMod> mod;
                                                   JDWP::JdwpEventMod bpMod;
                                                   bpMod.modKind = JDWP::MK_LOCATION_ONLY;
                                                   bpMod.locationOnly.loc = JDWP::JdwpLocation{
                                                           JDWP::TT_CLASS,
                                                           classinfo.mTypeId,
                                                           method.mMethodId,
                                                           extra->mCodeIdx};
                                                   mod.push_back(bpMod);
                                                   dbgEventRequestSet(
                                                           JDWP::EK_BREAKPOINT,
                                                           JDWP::SP_ALL, mod,
                                                           [this](JDWP::JdwpEventKind eventkind,
                                                                  uint32_t requestId) {});
                                                   break;
                                               }
                                           });
    });
}

template <typename Func>
void DebugHandler::dbgEventRequestSet(JDWP::JdwpEventKind eventkind,
                                      JDWP::JdwpSuspendPolicy policy,
                                      const std::vector<JDWP::JdwpEventMod> &mod,
                                      Func callback) {
    auto request = JDWP::EventRequest::Set::buildReq(eventkind, policy, mod, mSockId++);
    auto package = QSharedPointer<ReqestPackage>(new ReqestPackage(request));
    connect(package.data(), &ReqestPackage::onReply, [this, eventkind, callback](JDWP::Request *request,QByteArray& reply) {
        JDWP::EventRequest::Set set((uint8_t*)reply.data(), reply.length());
        qDebug() << "EventRequestSet: " << set.mRequestId;
        // TODO Record event id
        callback(eventkind, set.mRequestId);
    });
    sendNewRequest (package);
}

void DebugHandler::dbgEventRequestClear(JDWP::JdwpEventKind kind, uint32_t requestId) {
    auto request = JDWP::EventRequest::Clear::buildReq(kind, requestId, mSockId++);
    auto package = QSharedPointer<ReqestPackage>(new ReqestPackage(request));
    connect(package.data(), &ReqestPackage::onReply, [this](JDWP::Request *request,QByteArray& reply) {
        qDebug() << "EventRequestClear";
    });
    sendNewRequest (package);
}

template  <typename Func>
void DebugHandler::dbgReferenctTypeMethodsWithGeneric(JDWP::RefTypeId refTypeId,
                                                      Func callback) {
    if(mLoadedMethodsInfo.contains(refTypeId)) {
        callback(mLoadedMethodsInfo[refTypeId]);
        return;
    }

    auto request = JDWP::ReferenceType::MethodsWithGeneric::buildReq(refTypeId, mSockId++);
    auto package = QSharedPointer<ReqestPackage>(new ReqestPackage(request));
    connect(package.data(), &ReqestPackage::onReply, [this, refTypeId, callback](JDWP::Request *request,QByteArray& reply) {
        qDebug() << "ReferenceType::MethodsWithGeneric: ";
        JDWP::ReferenceType::MethodsWithGeneric signature((uint8_t*)reply.data(), reply.length());;
        if(signature.mSize == 0) {
            return;
        }
        for(auto& info: signature.mMethods) {
            qDebug() << "MethodId" << info.mMethodId
                     << "Name" << info.mName
                     << "Signature" << info.mSignature
                     << "GenericSignature" << info.mGenericSignature
                     << "Flags" << info.mFlags;
        }
        mLoadedMethodsInfo[refTypeId] = signature.mMethods;
        callback(signature.mMethods);
    });
    sendNewRequest (package);
}

template <typename Func>
void DebugHandler::dbgGetClassBySignature(const QString &classSignature,
                                          Func callback) {
    if(mLoadedClassRef.contains(classSignature)) {
        auto id = mLoadedClassRef.value(classSignature);
        callback(mLoadedClassInfo[id]);
        return;
    }

    auto request = JDWP::VirtualMachine::ClassesBySignature::buildReq(classSignature.toLocal8Bit(), mSockId++);
    auto package = QSharedPointer<ReqestPackage>(new ReqestPackage(request));
    connect(package.data(), &ReqestPackage::onReply,
        [this, classSignature, callback](JDWP::Request *request,QByteArray& reply) {
        JDWP::VirtualMachine::ClassesBySignature signature((uint8_t*)reply.data(), reply.length());
        if(signature.mSize == 0) {
            // class has not been loaded, need to wait for loading.
            waitForClassPrepared(classSignature,
                [this, callback](JDWP::Composite::ReflectedType::EventClassPrepare* prepare) {
                callback(mLoadedClassInfo[prepare->mTypeId]);
            });
            return;
        }
        qDebug() << "VirtualMachine::ClassBySignature: ";
        for(auto& info: signature.mInfos) {
            qDebug() << info.mRefTypeTag << info.mTypeId << info.mStatus;
            // Record classinfo
            if(!mLoadedClassInfo.contains(info.mTypeId)) {
                mLoadedClassRef.insert(info.mDescriptor, info.mTypeId);
            }
            info.mDescriptor = classSignature.toLatin1();
            mLoadedClassInfo[info.mTypeId] = info;
        }
        auto info = signature.mInfos.front();
        if(info.mTypeId == 0) {
            return;
        }
        callback(info);
    });
    sendNewRequest (package);
}

template<typename Func>
void DebugHandler::waitForClassPrepared(QString javaSignature, Func callback) {
    std::vector<JDWP::JdwpEventMod> mod;

    JDWP::JdwpEventMod mMatch;
    mMatch.modKind = JDWP::JdwpModKind::MK_CLASS_MATCH;
    auto matchClass = jniSigToJavaSig(javaSignature).toLatin1();
    mMatch.classMatch.classPattern = matchClass.data();
    mod.push_back(mMatch);

    JDWP::JdwpEventMod mCount;
    mCount.modKind = JDWP::JdwpModKind::MK_COUNT;
    mCount.count.count = 1;
    mod.push_back(mCount);

    JDWP::JdwpEventModPad modPad(mMatch);

    dbgEventRequestSet(JDWP::JdwpEventKind::EK_CLASS_PREPARE, JDWP::JdwpSuspendPolicy::SP_ALL, mod,
          [this, modPad, callback](JDWP::JdwpEventKind eventkind, uint32_t requestId) {
              auto package = QSharedPointer<CommandPackage>(new CommandPackage(modPad, JDWP::JdwpSuspendPolicy::SP_ALL));
              connect(package.data(), &CommandPackage::onClassPrepare,
                  [this, requestId, callback](JDWP::Composite::ReflectedType::EventClassPrepare* prepare, JDWP::JdwpSuspendPolicy  policy, bool *clear) {
                      // classInfo has been recorded in DebugHandler::handleCommand
                      dbgEventRequestClear(JDWP::JdwpEventKind::EK_CLASS_PREPARE, requestId);
                      callback(prepare);
                      *clear = true;
              });
              setCommandPackage(eventkind, package);
    });
}

template<typename Func>
void DebugHandler::dbgThreadReferenceFrames(
        JDWP::ObjectId thread_id, Func callback) {
    auto request = JDWP::ThreadReference::Frames::buildReq(thread_id, 0, -1, mSockId++);
    auto package = QSharedPointer<ReqestPackage>(new ReqestPackage(request));
    connect(package.data(), &ReqestPackage::onReply, [this, callback](JDWP::Request *request,QByteArray& reply) {
        JDWP::ThreadReference::Frames frames((uint8_t*)reply.data(), reply.length());
        if(frames.mFrameCount == 0) {
            return;
        }
        callback(frames.mFrames);
    });
    sendNewRequest (package);
}


template <typename Func>
void DebugHandler::dbgReferenceTypeSignatureWithGeneric(JDWP::RefTypeId refTypeId, Func callback) {
    auto request = JDWP::ReferenceType::SignatureWithGeneric::buildReq(refTypeId, mSockId++);
    auto package = QSharedPointer<ReqestPackage>(new ReqestPackage(request));
    connect(package.data(), &ReqestPackage::onReply, [this, refTypeId, callback](JDWP::Request *request,QByteArray& reply) {
        JDWP::ReferenceType::SignatureWithGeneric signature((uint8_t*)reply.data(), reply.length());
        callback(signature.mSignature, signature.mSignatureGeneric);
    });
    sendNewRequest (package);
}

void DebugHandler::setCommandPackage(JDWP::JdwpEventKind eventkind, QSharedPointer<CommandPackage>& package)
{
    auto group = CommandPackage::getEventGroup(eventkind);
    auto &commands = mCommandVector[group];
    commands.push_back(package);
}

void DebugHandler::breakPointHit(JDWP::JdwpSuspendPolicy  policy,
                                 JDWP::Composite::ReflectedType::EventLocationEvent*event)
{
    if(policy == JDWP::JdwpSuspendPolicy::SP_NONE) {
        return;
    }
    auto threadId = event->mThreadId;
    updateThreadFrame(threadId);
    // TODO record stop state, and active threadId, if frame has been clicked, try to get frame variables.
//    auto location = event->mLocation;
//    dbgGetRefTypeMethodsWithGeneric(location.class_id, [this, threadId, location](QVector<JDWP::MethodInfo> methods){
//        if(mLoadedClassInfo.contains(location.class_id)) {
//            auto &info = mLoadedClassInfo[location.class_id];
//            qDebug() << "Stop at class " << info.mDescriptor;
//        }
//        for(auto method: methods) {
//            if(method.mMethodId != location.method_id) {
//                continue;
//            }
//            qDebug() << "Stop at method " << method.mSignature << "dex_pc" << location.dex_pc;
//        }
//        dbgThreadReferenceFrames(threadId, [this](QVector<JDWP::ThreadReference::Frames::Frame>& frames) {
//            qDebug() << "FrameRef callback";
//        });
//    });
}

void DebugHandler::stopOnProcessEntryPoint() {
    auto config = ProjectInfo::current();
    QString className, methodName, methodSig;
    bool found = false;
    if(config->config().m_applicationName != "Landroid/app/Application;") {
        // try to set breakpoint in application entry point
        auto filedata = SmaliAnalysis::instance()->getSmaliFileBySig(config->config().m_applicationName);
        if(!filedata.isNull()) {
            auto method = filedata->method("attachBaseContext", "(Landroid/content/Context;)V");
            if(method != nullptr && method->m_accessflag & ACC_NATIVE) {
                method = nullptr;
            }
            if(method == nullptr) {
                method = filedata->method("onCreate", "()V");
                if(method != nullptr && method->m_accessflag & ACC_NATIVE) {
                    method = nullptr;
                }
            }
            if(method != nullptr) {
                className = filedata->name();
                methodName = method->m_name;
                methodSig = method->buildProto();
                found = true;
            }
        }
    }
    if(!found) {
        // try to set breakpoint to activity entrypoint.
        auto filedata = SmaliAnalysis::instance()->getSmaliFileBySig(config->config().m_activityEntryName);
        if(!filedata.isNull()) {
            auto method = filedata->method("onCreate", "(Landroid/os/Bundle;)V");
            if(method != nullptr && !(method->m_accessflag & ACC_NATIVE)) {
                className = filedata->name();
                methodName = method->m_name;
                methodSig = method->buildProto();
                found = true;
            }
        }
    }
    if(found) {
        waitForClassPrepared(className, [this, className, methodName, methodSig](JDWP::Composite::ReflectedType::EventClassPrepare* prepare) {
            dbgSetBreakPoint(className, methodName, methodSig, 0);
        });
    }
}

void DebugHandler::setAllBreakpoint() {

}

void DebugHandler::updateThreadFrame(JDWP::ObjectId threadId) {
    auto *model = FrameListView::instance()->showModel(threadId);
    dbgThreadReferenceFrames(threadId,
        [this, model](QVector<JDWP::ThreadReference::Frames::Frame>& frames) {
        model->removeAllFramedatas();
        for(auto &frame: frames) {
            auto data = new FrameListModel::FrameData;
            data->frame_id = frame.frame_id;
            data->location = frame.location;
            model->addFrameData(data);
            dbgReferenceTypeSignatureWithGeneric(frame.location.class_id,
                [this, model, data](QByteArray sig, QByteArray sigGen) {
                data->classSig = sig;
                model->updateFrameData(data);
            });
            dbgReferenctTypeMethodsWithGeneric(frame.location.class_id, [this, model, data]
                    (QVector<JDWP::MethodInfo> methods) {
                for (auto method: methods) {
                    if (method.mMethodId !=
                        data->location.method_id) {
                        continue;
                    }
                    data->methodName = method.mName;
                    data->methodSig = method.mSignature;
                    model->updateFrameData(
                            data);
                }
            });
        }
    });
}

void DebugHandler::dumpFrameInfo(JDWP::ObjectId threadId, FrameListModel::FrameData *frame) {
    qDebug() << "dumpFrameInformation " << threadId << frame->display();

    // Debug : just get p0 value and try to show in variables
    QVector<JDWP::StackFrame::StackFrameData> frames;
    frames.push_back({0, JDWP::JdwpTag::JT_OBJECT});


    auto request = JDWP::StackFrame::GetValues::buildReq(threadId, frame->frame_id, frames, mSockId++);
    auto package = QSharedPointer<ReqestPackage>(new ReqestPackage(request));
    connect(package.data(), &ReqestPackage::onReply, [this](JDWP::Request *request,QByteArray& reply) {
        JDWP::StackFrame::GetValues value((uint8_t*)reply.data(), reply.length());

        auto model = VariableModel::instance();
        model->clear();
        auto root = model->invisibleRootItem();

        for(auto& val: value.mSlots) {
            auto item = new VariableTreeItem(val);
            root->appendRow(item);

//            switch (val.L) {
//                // TODO dump object information
//                case JDWP::JdwpTag::JT_OBJECT:
//                    dbgObjectReferenceReferenceType(val.L,
//                          [this](JDWP::JdwpTypeTag tag, JDWP::RefTypeId mTypeId) {
//                              dbgReferenceTypeFieldsWithGeneric(mTypeId, [this]
//                                      (QVector<JDWP::FieldInfo> fields) {
//
//                              });
//                          });
//                    break;
//                default:
//                    qDebug() << val.tag << val.L;
//                    break;
//            }
        }
    });
    sendNewRequest (package);
}

template<typename Func>
void DebugHandler::dbgObjectReferenceReferenceType(JDWP::ObjectId objectId,
                                                   Func callback) {

    auto request = JDWP::ObjectReference::ReferenceType::buildReq(objectId, mSockId++);
    auto package = QSharedPointer<ReqestPackage>(new ReqestPackage(request));
    connect(package.data(), &ReqestPackage::onReply, [this, callback](JDWP::Request *request,QByteArray& reply) {
        JDWP::ObjectReference::ReferenceType referenceType((uint8_t*)reply.data(), reply.length());
        callback(referenceType.tag, referenceType.mTypeId);
    });
    sendNewRequest (package);
}

template<typename Func>
void DebugHandler::dbgReferenceTypeFieldsWithGeneric(JDWP::RefTypeId refTypeId,
                                                     Func callback) {
    if(mLoadedFieldsInfo.contains(refTypeId)) {
        callback(mLoadedFieldsInfo[refTypeId]);
        return;
    }

    auto request = JDWP::ReferenceType::FieldsWithGeneric::buildReq(refTypeId, mSockId++);
    auto package = QSharedPointer<ReqestPackage>(new ReqestPackage(request));
    connect(package.data(), &ReqestPackage::onReply, [this, refTypeId, callback]
            (JDWP::Request *request,QByteArray& reply) {
        qDebug() << "ReferenceType::FieldsWithGeneric: ";
        JDWP::ReferenceType::FieldsWithGeneric signature((uint8_t*)reply.data(), reply.length());;
        if(signature.mSize == 0) {
            return;
        }
        for(auto& info: signature.mFields) {
            qDebug() << "FieldId" << info.mFieldId
                     << "Name" << info.mName
                     << "Descriptor" << info.mDescriptor
                     << "GenericSignature" << info.mGenericSignature
                     << "Flags" << info.mFlags;
        }
        mLoadedFieldsInfo[refTypeId] = signature.mFields;
        callback(signature.mFields);
    });
    sendNewRequest (package);
}


ReqestPackage::ReqestPackage(QByteArray& data,  QObject *parent)
        : QObject(parent),
          mData(data),
          mRequest((uint8_t*)data.data (), data.length())
{

}

ReqestPackage::~ReqestPackage()
{
}

void ReqestPackage::handleReply(QByteArray& reply)
{
    qDebug() << "[RequestPackage::handleReply] Handle reply for id " << mRequest.GetId()
             << " CommandSet:" << mRequest.GetCommandSet ()
             << " Command:" << mRequest.GetCommand ();
    onReply(&mRequest, reply);
}

CommandPackage::CommandPackage(JDWP::JdwpEventModPad mod, JDWP::JdwpSuspendPolicy policy, QObject* parent)
    : QObject(parent), mMod(mod), mSuspendPolicy(policy)
{

}

int CommandPackage::getEventGroup(JDWP::JdwpEventKind kind) {
    int egroup = (int)EventGroup::Unknown;
    switch(kind) {
        case JDWP::JdwpEventKind::EK_SINGLE_STEP:
        case JDWP::JdwpEventKind::EK_BREAKPOINT:
        case JDWP::JdwpEventKind::EK_METHOD_ENTRY:
        case JDWP::JdwpEventKind::EK_METHOD_EXIT:
            egroup = (int)EventGroup::Location;
            break;
//            case JdwpEventKind::EK_FRAME_POP:
//                Q_ASSERT(false);
//                break;
        case JDWP::JdwpEventKind::EK_EXCEPTION:
            egroup = (int)EventGroup::Exception;
            break;
//            case JdwpEventKind::EK_USER_DEFINED:
//                Q_ASSERT(false);
//                break;
        case JDWP::JdwpEventKind::EK_THREAD_START:
        case JDWP::JdwpEventKind::EK_THREAD_DEATH:
            egroup = (int)EventGroup::Thread;
            break;
        case JDWP::JdwpEventKind::EK_CLASS_PREPARE:
            egroup = (int)EventGroup::Prepare;
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
        case JDWP::JdwpEventKind::EK_VM_START:
            egroup = (int)EventGroup::VmStart;
            break;
        case JDWP::JdwpEventKind::EK_VM_DEATH:
            egroup = (int)EventGroup::VmDeath;
            break;
//            case JdwpEventKind::EK_VM_DISCONNECTED:
//                Q_ASSERT(false);
//                break;
        default:
            egroup = (int)EventGroup::Unknown;
            break;
    }
    return egroup;
}



bool CommandPackage::match(JDWP::Composite::ReflectedType::EventObject *pevent,
                           JDWP::JdwpSuspendPolicy  policy) {
    if(policy != mSuspendPolicy) {
        return false;
    }
    bool matched = false;
    auto eventKind = pevent->mEventKind;
    switch(eventKind) {
        case JDWP::JdwpEventKind::EK_SINGLE_STEP:
        case JDWP::JdwpEventKind::EK_BREAKPOINT:
        case JDWP::JdwpEventKind::EK_METHOD_ENTRY:
        case JDWP::JdwpEventKind::EK_METHOD_EXIT: {
            // TODO Hit Breakpoint, just try to get variable info
            auto event = (JDWP::Composite::ReflectedType::EventLocationEvent*)pevent;
            if(mMod.mMod.locationOnly.loc == event->mLocation) {
                onLocation(event, policy, &clear);
                matched = true;
            }
        }
            break;
//            case JdwpEventKind::EK_FRAME_POP:
//                Q_ASSERT(false);
//                break;
//        case JDWP::JdwpEventKind::EK_EXCEPTION: {
//            auto event = (JDWP::Composite::ReflectedType::EventException*)pevent;
//            qDebug() << "EventException at" << event->mThrowLoc.dex_pc << "to" << event->mCatchLoc.dex_pc;
//        }
//            break;
//            case JdwpEventKind::EK_USER_DEFINED:
//                Q_ASSERT(false);
//                break;
//        case JDWP::JdwpEventKind::EK_THREAD_START:
//        case JDWP::JdwpEventKind::EK_THREAD_DEATH: {
//            auto event = (JDWP::Composite::ReflectedType::EventThreadChange*)pevent;
//            qDebug() << "EventThreadChange" << event->mThreadId;
//        }
//            break;
        case JDWP::JdwpEventKind::EK_CLASS_PREPARE: {
            auto event = (JDWP::Composite::ReflectedType::EventClassPrepare*)pevent;
            auto sig = jniSigToJavaSig(event->mSignature);
            if(sig == mMod.mArray) {
                onClassPrepare(event, policy, &clear);
            }
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
//        case JDWP::JdwpEventKind::EK_VM_START: {
//            auto event = (JDWP::Composite::ReflectedType::EventVmStart*)pevent;
//            qDebug() << "EventVmStart" << event->mThreadId;
//        }
//            break;
//        case JDWP::JdwpEventKind::EK_VM_DEATH: {
//            auto event = (JDWP::Composite::ReflectedType::EventVmDeath*)pevent;
//            qDebug() << "EventVmDeath";
//        }
//            break;
//            case JdwpEventKind::EK_VM_DISCONNECTED:
//                Q_ASSERT(false);
//                break;
        default:
//            qDebug() << "Unknown EventKind?" << eventKind;
            break;
    }
    return matched;
}

CommandPackage::~CommandPackage() {
}


