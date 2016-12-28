//===- JdwpHandler.cpp - ART-DEBUGGER ----------------------------*- C++ -*-===//
//
//                     ANDROID REVERSE TOOLKIT
//
// This file is distributed under the GNU GENERAL PUBLIC LICENSE
// V3 License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

#include "Jdwp/JdwpHandler.h"
#include "JdwpHeader.h"

#include <Jdwp/jdwp.h>
#include <QtEndian>
#include <QDebug>

using namespace JDWP;

VirtualMachine::Version::Version (const uint8_t *bytes,uint32_t available)
        : JdwpReader (bytes,available)
{
    version = ReadString ();
    major = Read4 ();
    minor = Read4 ();
    javaVersion = ReadString ();
    javaVmName = ReadString ();
}

QByteArray VirtualMachine::Version::buildReq (int id)
{
    QByteArray rel;
    return BuildReq (id, set_, cmd, rel);
}

VirtualMachine::ClassesBySignature::ClassesBySignature (
        const uint8_t *bytes,uint32_t available)
        : JdwpReader (bytes,available)
{
    mSize = Read4 ();
    mInfos.resize (mSize);
    // mSize > 0 ? why
    for(uint32_t i = 0; i < mSize; i++) {
        auto &info = mInfos[i];
        info.mRefTypeTag = Read1 ();
        info.mTypeId = ReadRefTypeId ();
        info.mStatus = Read4 ();
    }
}

QByteArray VirtualMachine::ClassesBySignature::buildReq (
        const QByteArray &classDescriptor, int id)
{
    QByteArray rel;
    WriteString (rel, classDescriptor);
    return BuildReq (id, set_, cmd, rel);
}

bool JDWP::Write1(QByteArray &s, uint8_t v)
{
    s.push_back ((char)v);
    return true;
}

bool JDWP::Write2(QByteArray &s, uint16_t v)
{
    uint16_t vn = qToBigEndian (v);
    s.append ((char*)&vn,sizeof (vn));
    return true;
}

bool JDWP::Write4(QByteArray &s, uint32_t v)
{
    uint32_t vn = qToBigEndian (v);
    s.append ((char*)&vn, sizeof(vn));
    return true;
}


bool JDWP::Write8 (QByteArray &s,uint64_t v)
{
    uint32_t high = v >> 32;
    uint32_t low = v & 0xffffffff;
    Write4 (s, high);
    Write4 (s, low);
    return true;
}

bool JDWP::WriteString(QByteArray &s, const QByteArray &v)
{
    auto vLen = v.length ();
    Write4 (s, vLen);
    s.append (v);
    return true;
}


bool ::JDWP::WriteFieldId (QByteArray &s,uint32_t v)
{
    return Write4 (s, v);
}

bool ::JDWP::WriteMethodId (QByteArray &s,uint32_t v)
{
    return Write4 (s, v);
}

bool ::JDWP::WriteObjectId (QByteArray &s,uint64_t v)
{
    return Write8 (s, v);
}

bool ::JDWP::WriteRefTypeId (QByteArray &s,uint64_t v)
{
    return Write8 (s, v);
}

bool ::JDWP::WriteFrameId (QByteArray &s,uint64_t v)
{
    return Write8 (s, v);
}

QByteArray JDWP::BuildReq (int id,int cmdset,int cmd,
                            const QByteArray &extra)
{
    QByteArray rel;
    auto len = extra.length () + kJDWPHeaderLen;
    Write4 (rel, len);
    Write4 (rel, id);
    Write1 (rel, 0);    // flag
    Write1 (rel, cmdset);
    Write1 (rel, cmd);
    rel.append (extra);
    return rel;
}

bool ::JDWP::WriteValue (QByteArray &s,uint64_t v,size_t width)
{
    switch (width) {
        case 1:
            return Write1 (s, v); break;
        case 2:
            return Write2 (s, v); break;
        case 4:
            return Write4 (s, v); break;
        case 8:
            return Write8 (s, v); break;
        default: break;
    }
    return false;
}

bool ::JDWP::WriteThreadId (QByteArray &s,uint64_t v)
{
    return Write8 (s, v);
}

bool ::JDWP::WriteJdwpLocation (QByteArray &s,const JdwpLocation &location)
{
    Write1 (s,location.type_tag);
    WriteObjectId (s,location.class_id);
    WriteMethodId (s,location.method_id);
    Write8 (s,location.dex_pc);
    return true;
}

VirtualMachine::AllClasses::AllClasses (
        const uint8_t *bytes,uint32_t available)
        : JdwpReader (bytes,available)
{
    mSize = Read4 ();
    mInfos.resize (mSize);
    for(uint32_t i = 0; i < mSize; i++) {
        auto &info = mInfos[i];

        info.mRefTypeTag = Read1 ();
        info.mTypeId = ReadRefTypeId ();
        info.mDescriptor = ReadString ();
        info.mStatus = Read4 ();
    }
}

QByteArray VirtualMachine::AllClasses::buildReq (int id)
{
    QByteArray rel;
    return BuildReq (id, set_, cmd, rel);
}

VirtualMachine::AllThreads::AllThreads (
        const uint8_t *bytes,uint32_t available)
        : JdwpReader (bytes,available)
{
    mSize = Read4 ();
    mThreadIds.resize (mSize);
    for(uint i = 0; i < mSize; i++) {
        mThreadIds[i] = ReadObjectId ();
    }
}

QByteArray VirtualMachine::AllThreads::buildReq (int id)
{
    QByteArray rel;
    return BuildReq (id, set_, cmd, rel);
}


VirtualMachine::TopLevelThreadGroups::TopLevelThreadGroups (
        const uint8_t *bytes,uint32_t available)
        : JdwpReader (bytes,available)
{
    mGroups = Read4 ();
    mThreadGroupId = ReadObjectId ();
}

QByteArray VirtualMachine::TopLevelThreadGroups::buildReq (int id)
{
    QByteArray rel;
    return BuildReq (id, set_, cmd, rel);
}

VirtualMachine::Dispose::Dispose (
        const uint8_t *bytes,uint32_t available)
        : JdwpReader (bytes,available)
{
}

QByteArray VirtualMachine::Dispose::buildReq (int id)
{
    QByteArray rel;
    return BuildReq (id, set_, cmd, rel);
}

VirtualMachine::IDSizes::IDSizes (
        const uint8_t *bytes,uint32_t available)
        : JdwpReader (bytes,available)
{
    mFieldIdSize = Read4 ();
    mMethodIdSize = Read4 ();
    mObjectIdSize = Read4 ();
    mRefTypeIdSize = Read4 ();
    mFrameIdSize = Read4 ();
}

QByteArray VirtualMachine::IDSizes::buildReq (int id)
{
    QByteArray rel;
    return BuildReq (id, set_, cmd, rel);
}

VirtualMachine::Suspend::Suspend (
        const uint8_t *bytes,uint32_t available)
        : JdwpReader (bytes,available)
{

}

QByteArray VirtualMachine::Suspend::buildReq (int id)
{
    QByteArray rel;
    return BuildReq (id, set_, cmd, rel);
}


VirtualMachine::Resume::Resume (
        const uint8_t *bytes,uint32_t available)
        : JdwpReader (bytes,available)
{

}

QByteArray VirtualMachine::Resume::buildReq (int id)
{
    QByteArray rel;
    return BuildReq (id, set_, cmd, rel);
}

VirtualMachine::Exit::Exit (
        const uint8_t *bytes,uint32_t available)
        : JdwpReader (bytes,available)
{

}

QByteArray VirtualMachine::Exit::buildReq (int id)
{
    QByteArray rel;
    return BuildReq (id, set_, cmd, rel);
}

VirtualMachine::CreateString::CreateString (
        const uint8_t *bytes,uint32_t available)
        : JdwpReader (bytes,available)
{
    mStringId = ReadObjectId ();
}

QByteArray VirtualMachine::CreateString::buildReq (
        const QByteArray str,int id)
{
    QByteArray rel;
    WriteString (rel, str);
    return BuildReq (id, set_, cmd, rel);
}


VirtualMachine::Capabilities::Capabilities (
        const uint8_t *bytes,uint32_t available)
        : JdwpReader (bytes,available)
{
    mCanWatchFieldModification = Read1 ();
    mCanWatchFieldAccess = Read1 ();
    mCanGetBytecodes = Read1 ();
    mCanGetSyntheticAttribute = Read1 ();
    mCanGetOwnedMonitorInfo = Read1 ();
    mCanGetCurrentContendedMonitor = Read1 ();
    mCanGetMonitorInfo = Read1 ();
}

QByteArray VirtualMachine::Capabilities::buildReq (int id)
{
    QByteArray rel;
    return BuildReq (id, set_, cmd, rel);
}


VirtualMachine::ClassPaths::ClassPaths (
        const uint8_t *bytes,uint32_t available)
        : JdwpReader (bytes,available)
{
    mSlash = ReadString ();

    mClassPathSize = Read4 ();
    mClassPath.resize (mClassPathSize);
    for(uint i = 0; i < mClassPathSize; i++) {
        mClassPath[i] = ReadString ();
    }

    mBootClassPathSize = Read4 ();
    mBootClassPath.resize (mBootClassPathSize);
    for(uint32_t i = 0; i < mBootClassPathSize; i++) {
        mBootClassPath[i] = ReadString ();
    }
}

QByteArray VirtualMachine::ClassPaths::buildReq (int id)
{
    QByteArray rel;
    return BuildReq (id, set_, cmd, rel);
}


VirtualMachine::DisposeObjects::DisposeObjects (
        const uint8_t *bytes,uint32_t available)
        : JdwpReader (bytes,available)
{
}

QByteArray VirtualMachine::DisposeObjects::buildReq (
        const std::vector<DispObj> &objs,int id)
{
    QByteArray rel;
    Write4 (rel, objs.size ());
    for(auto it = objs.begin (), itEnd = objs.end ();
        it != itEnd; it++) {
        WriteObjectId (rel, it->id);
        Write4 (rel, it->refCount);
    }
    return BuildReq (id, set_, cmd, rel);
}


VirtualMachine::HoldEvents::HoldEvents (
        const uint8_t *bytes,uint32_t available)
        : JdwpReader (bytes,available)
{

}

QByteArray VirtualMachine::HoldEvents::buildReq (int id)
{
    QByteArray rel;
    return BuildReq (id, set_, cmd, rel);
}


VirtualMachine::ReleaseEvents::ReleaseEvents (
        const uint8_t *bytes,uint32_t available)
        : JdwpReader (bytes,available)
{

}

QByteArray VirtualMachine::ReleaseEvents::buildReq (int id)
{
    QByteArray rel;
    return BuildReq (id, set_, cmd, rel);
}


VirtualMachine::CapabilitiesNew::CapabilitiesNew (
        const uint8_t *bytes,uint32_t available)
        : Capabilities (bytes,available)
{
    mCanRedefineClasses = Read1 ();
    mCanAddMethod = Read1 ();
    mCanUnrestrictedlyRedefineClasses = Read1 ();
    mCanPopFrames = Read1 ();
    mCanUseInstanceFilters = Read1 ();
    mCanGetSourceDebugExtension = Read1 ();
    mCanRequestVMDeathEvent = Read1 ();
    mCanSetDefaultStratum = Read1 ();
    mCanGetInstanceInfo = Read1 ();
    mCanRequestMonitorEvents = Read1 ();
    mCanGetMonitorFrameInfo = Read1 ();
    mCanUseSourceNameFilters = Read1 ();
    mCanGetConstantPool = Read1 ();
    mCanForceEarlyReturn = Read1 ();

    // Fill in reserved22 through reserved32; note count started at 1.
    for (size_t i = 22; i <= 32; ++i) {
        /*auto reversed = */Read1 ();
    }
}

QByteArray VirtualMachine::CapabilitiesNew::buildReq (int id)
{
    QByteArray rel;
    return BuildReq (id, set_, cmd, rel);
}

VirtualMachine::RedefineClasses::RedefineClasses (
        const uint8_t *bytes,uint32_t available)
        : JdwpReader (bytes,available)
{

}

QByteArray VirtualMachine::RedefineClasses::buildReq (int id)
{
    QByteArray rel;
    return BuildReq (id, set_, cmd, rel);
}

VirtualMachine::SetDefaultStratum::SetDefaultStratum (
        const uint8_t *bytes,uint32_t available)
        : JdwpReader (bytes,available)
{

}

QByteArray VirtualMachine::SetDefaultStratum::buildReq (int id)
{
    QByteArray rel;
    return BuildReq (id, set_, cmd, rel);
}


VirtualMachine::AllClassesWithGeneric::AllClassesWithGeneric (
        const uint8_t *bytes,uint32_t available)
        : JdwpReader (bytes,available)
{
    mSize = Read4 ();
    mInfos.resize(mSize);
    for(uint32_t i = 0; i < mSize; i++) {
        auto &info = mInfos[i];

        info.mRefTypeTag = Read1 ();
        info.mTypeId = ReadRefTypeId ();
        info.mDescriptor = ReadString ();
        info.mGenericSignature = ReadString ();
        info.mStatus = Read4 ();
    }
    qSort(mInfos.begin(), mInfos.end(), [](const JDWP::ClassInfo & e1, const JDWP::ClassInfo & e2) {
        return qstrcmp(e1.mDescriptor, e2.mDescriptor);
    });
}

QByteArray VirtualMachine::AllClassesWithGeneric::buildReq (int id)
{
    QByteArray rel;
    return BuildReq (id, set_, cmd, rel);
}


VirtualMachine::InstanceCounts::InstanceCounts (
        const uint8_t *bytes,uint32_t available)
        : JdwpReader (bytes,available)
{
    mCountSize = Read4 ();
    mCounts.resize (mCountSize);
    for(uint32_t i = 0; i < mCountSize; i++) {
        mCounts[i] = Read8 ();
    }
}

QByteArray VirtualMachine::InstanceCounts::buildReq (
        const std::vector<RefTypeId> &class_ids,int id)
{
    QByteArray rel;
    Write4(rel, class_ids.size ());
    for(auto it = class_ids.begin (), itEnd = class_ids.end ();
        it != itEnd; it++) {
        WriteRefTypeId (rel, *it);
    }

    return BuildReq (id, set_, cmd, rel);
}

ReferenceType::Signature::Signature (
        const uint8_t *bytes,uint32_t available)
        : JdwpReader (bytes,available)
{
    mSignature = ReadString ();
}

QByteArray ReferenceType::Signature::buildReq (RefTypeId refTypeId,int id)
{
    QByteArray rel;
    WriteRefTypeId (rel, refTypeId);
    return BuildReq (id, set_, cmd, rel);
}


ReferenceType::ClassLoader::ClassLoader (
        const uint8_t *bytes,uint32_t available)
        : JdwpReader (bytes,available)
{
    mClassId = ReadObjectId ();
}

QByteArray ReferenceType::ClassLoader::buildReq (RefTypeId refTypeId,int id)
{
    QByteArray rel;
    WriteRefTypeId (rel, refTypeId);
    return BuildReq (id, set_, cmd, rel);
}

ReferenceType::Modifiers::Modifiers (
        const uint8_t *bytes,uint32_t available)
        : JdwpReader (bytes,available)
{
    mFlags = Read4 ();
}

QByteArray ReferenceType::Modifiers::buildReq (RefTypeId refTypeId,int id)
{
    QByteArray rel;
    WriteRefTypeId (rel, refTypeId);
    return BuildReq (id, set_, cmd, rel);
}

ReferenceType::Fields::Fields (
        const uint8_t *bytes,uint32_t available)
        : JdwpReader (bytes,available)
{
    mSize = Read4 ();
    mFields.resize (mSize);
    for (uint32_t i = 0; i<mSize; ++i)
    {
        mFields[i].mFieldId = ReadFieldId ();
        mFields[i].mName = ReadString ();
        mFields[i].mDescriptor = ReadString ();
        mFields[i].mFlags = Read4 ();
    }
}

QByteArray ReferenceType::Fields::buildReq (RefTypeId refTypeId,int id)
{
    QByteArray rel;
    WriteRefTypeId (rel, refTypeId);
    return BuildReq (id, set_, cmd, rel);
}

ReferenceType::Methods::Methods (
        const uint8_t *bytes,uint32_t available)
        : JdwpReader (bytes,available)
{
    mSize = Read4 ();
    mMethods.resize (mSize);
    for (uint i = 0; i<mSize; ++i)
    {
        mMethods[i].mMethodId = ReadMethodId ();
        mMethods[i].mName = ReadString ();
        mMethods[i].mSignature = ReadString ();
        mMethods[i].mFlags = Read4 ();
    }
}

QByteArray ReferenceType::Methods::buildReq (RefTypeId refTypeId,int id)
{
    QByteArray rel;
    WriteRefTypeId (rel, refTypeId);
    return BuildReq (id, set_, cmd, rel);
}

ReferenceType::GetValues::GetValues (
        const uint8_t *bytes,uint32_t available)
        : JdwpReader (bytes,available)
{
    JdwpTag tag = (JdwpTag)Read1 ();
    isPrimateTag = IsPrimitiveTag (tag);
    mValue.tag = tag;
    auto len = GetTagWidth (tag);
    mValue.L = ReadValue (len);
}

QByteArray ReferenceType::GetValues::buildReq (
        RefTypeId refTypeId,int32_t field_count,
        const std::vector<FieldId> &fieldids,int id)
{
    QByteArray rel;
    WriteRefTypeId (rel, refTypeId);
    Write4 (rel, field_count);
    for(auto it = fieldids.begin (), itEnd = fieldids.end ();
        it != itEnd; it++) {
        WriteFieldId (rel, *it);
    }
    return BuildReq (id, set_, cmd, rel);
}

ReferenceType::SourceFile::SourceFile (
        const uint8_t *bytes,uint32_t available)
        : JdwpReader (bytes,available)
{
    mSourceFile = ReadString ();
}

QByteArray ReferenceType::SourceFile::buildReq (RefTypeId refTypeId,int id)
{
    QByteArray rel;
    WriteRefTypeId (rel, refTypeId);
    return BuildReq (id, set_, cmd, rel);
}

ReferenceType::NestedTypes::NestedTypes (
        const uint8_t *bytes,uint32_t available)
        : JdwpReader (bytes,available)
{

}

QByteArray ReferenceType::NestedTypes::buildReq (RefTypeId refTypeId,int id)
{
    QByteArray rel;
    WriteRefTypeId (rel, refTypeId);
    return BuildReq (id, set_, cmd, rel);
}

ReferenceType::Status::Status (
        const uint8_t *bytes,uint32_t available)
        : JdwpReader (bytes,available)
{
    mClassStatus = Read4 ();
}

QByteArray ReferenceType::Status::buildReq (RefTypeId refTypeId,int id)
{
    QByteArray rel;
    WriteRefTypeId (rel, refTypeId);
    return BuildReq (id, set_, cmd, rel);
}


ReferenceType::Interfaces::Interfaces (
        const uint8_t *bytes,uint32_t available)
        : JdwpReader (bytes,available)
{
    mCounts = Read4 ();
    mDirectInterfaces.resize (mCounts);
    for(uint32_t i = 0; i < mCounts; i++) {
        mDirectInterfaces[i] = ReadRefTypeId ();
    }
}

QByteArray ReferenceType::Interfaces::buildReq (RefTypeId refTypeId,int id)
{
    QByteArray rel;
    WriteRefTypeId (rel, refTypeId);
    return BuildReq (id, set_, cmd, rel);
}

ReferenceType::ClassObject::ClassObject (
        const uint8_t *bytes,uint32_t available)
        : JdwpReader (bytes,available)
{
    mClassId = ReadObjectId ();
}

QByteArray ReferenceType::ClassObject::buildReq (RefTypeId refTypeId,int id)
{
    QByteArray rel;
    WriteRefTypeId (rel, refTypeId);
    return BuildReq (id, set_, cmd, rel);
}


ReferenceType::SourceDebugExtension::SourceDebugExtension (
        const uint8_t *bytes,uint32_t available)
        : JdwpReader (bytes,available)
{

}

QByteArray ReferenceType::SourceDebugExtension::buildReq (
        RefTypeId refTypeId,int id)
{
    QByteArray rel;
    WriteRefTypeId (rel, refTypeId);
    return BuildReq (id, set_, cmd, rel);
}

ReferenceType::SignatureWithGeneric::SignatureWithGeneric (
        const uint8_t *bytes,uint32_t available)
        : Signature (bytes,available)
{
    mSignatureGeneric = ReadString ();
}

QByteArray ReferenceType::SignatureWithGeneric::buildReq (
        RefTypeId refTypeId,int id)
{
    QByteArray rel;
    WriteRefTypeId (rel,refTypeId);
    return BuildReq (id,set_,cmd,rel);
}

ReferenceType::FieldsWithGeneric::FieldsWithGeneric (
        const uint8_t *bytes,uint32_t available)
        : JdwpReader (bytes,available)
{
    mSize = Read4 ();
    mFields.resize (mSize);
    for (uint32_t i = 0; i<mSize; ++i)
    {
        mFields[i].mFieldId = ReadFieldId ();
        mFields[i].mName = ReadString ();
        mFields[i].mDescriptor = ReadString ();
        mFields[i].mGenericSignature = ReadString ();
        mFields[i].mFlags = Read4 ();
    }
}

QByteArray ReferenceType::FieldsWithGeneric::buildReq (
        RefTypeId refTypeId,int id)
{
    QByteArray rel;
    WriteRefTypeId (rel, refTypeId);
    return BuildReq (id, set_, cmd, rel);
}

ReferenceType::MethodsWithGeneric::MethodsWithGeneric (
        const uint8_t *bytes,uint32_t available):
        JdwpReader (bytes,available)
{
    mSize = Read4 ();
    mMethods.resize (mSize);
    for (uint32_t i = 0; i<mSize; ++i)
    {
        mMethods[i].mMethodId = ReadMethodId ();
        mMethods[i].mName = ReadString ();
        mMethods[i].mSignature = ReadString ();
        mMethods[i].mGenericSignature = ReadString ();
        mMethods[i].mFlags = Read4 ();
    }
}

QByteArray ReferenceType::MethodsWithGeneric::buildReq (
        RefTypeId refTypeId,int id)
{
    QByteArray rel;
    WriteRefTypeId (rel, refTypeId);
    return BuildReq (id, set_, cmd, rel);
}

ReferenceType::Instances::Instances (
        const uint8_t *bytes,uint32_t available)
        : JdwpReader (bytes,available)
{
    mSize = Read4 ();
    mObjTags.resize (mSize);
    for(uint32_t i = 0; i < mSize; i++) {
        mObjTags[i].tag = (JDWP::JdwpTag)Read1 ();
        mObjTags[i].objectId = ReadObjectId ();
    }
}

QByteArray ReferenceType::Instances::buildReq (
        RefTypeId refTypeId, int32_t maxcount, int id)
{
    QByteArray rel;
    WriteRefTypeId (rel, refTypeId);
    Write4(rel, maxcount);
    return BuildReq (id, set_, cmd, rel);
}

ReferenceType::ClassFileVersion::ClassFileVersion (
        const uint8_t *bytes,uint32_t available)
        : JdwpReader (bytes,available)
{

}

QByteArray ReferenceType::ClassFileVersion::buildReq (
        RefTypeId refTypeId,int id)
{
    QByteArray rel;
    WriteRefTypeId (rel, refTypeId);
    return BuildReq (id, set_, cmd, rel);
}

ReferenceType::ConstantPool::ConstantPool (
        const uint8_t *bytes,uint32_t available)
        : JdwpReader (bytes,available)
{

}

QByteArray ReferenceType::ConstantPool::buildReq (RefTypeId refTypeId,int id)
{
    QByteArray rel;
    WriteRefTypeId (rel, refTypeId);
    return BuildReq (id, set_, cmd, rel);
}

ClassType::Superclass::Superclass (const uint8_t *bytes,uint32_t available)
        : JdwpReader (bytes,available)
{
    mSuperClassId = ReadRefTypeId ();
}

QByteArray ClassType::Superclass::buildReq (RefTypeId refTypeId,int id)
{
    QByteArray rel;
    WriteRefTypeId (rel, refTypeId);
    return BuildReq (id, set_, cmd, rel);
}

ClassType::SetValues::SetValues (const uint8_t *bytes,uint32_t available)
        : JdwpReader (bytes,available)
{

}

QByteArray ClassType::SetValues::buildReq (
        RefTypeId refTypeId,const std::vector<FieldInfo> &infos,int id)
{
    QByteArray rel;
    WriteRefTypeId (rel, refTypeId);
    Write4 (rel, infos.size ());
    for(auto it = infos.begin (), itEnd = infos.end ();
        it != itEnd; it++) {
        WriteFieldId (rel, it->mFieldId);
        auto &value = it->mValue;
        WriteValue (rel, value.L, GetTagWidth (value.tag));
    }
    return BuildReq (id, set_, cmd, rel);
}

ClassType::InvokeMethod::InvokeMethod (
        const uint8_t *bytes,uint32_t available)
        : JdwpReader (bytes,available)
{
    mResult.tag = (JdwpTag)Read1 ();
    mResult.L = ReadValue (GetTagWidth (mResult.tag));
    mObject.tag = (JdwpTag)Read1 ();
    mObject.L = ReadObjectId ();
}

QByteArray ClassType::InvokeMethod::buildReq (
        RefTypeId class_id,ObjectId thread_id,MethodId method_id,
        const std::vector<JValue> &argValues,uint32_t options,int id)
{
    QByteArray rel;
    WriteRefTypeId (rel, class_id);
    WriteThreadId (rel, thread_id);
    WriteMethodId (rel, method_id);
    Write4 (rel, argValues.size ());
    for(auto it = argValues.begin (), itEnd = argValues.end ();
        it != itEnd; it ++) {
        Write1 (rel, it->tag);
        WriteValue (rel, it->L, GetTagWidth (it->tag));
    }
    Write4 (rel, options);
    return BuildReq (id, set_, cmd, rel);
}

ClassType::NewInstance::NewInstance (const uint8_t *bytes,uint32_t available)
        : JdwpReader (bytes,available)
{
    mResult.tag = (JdwpTag)Read1 ();
    mResult.L = ReadValue (GetTagWidth (mResult.tag));
    mObject.tag = (JdwpTag)Read1 ();
    mObject.L = ReadObjectId ();
}

QByteArray ClassType::NewInstance::buildReq (
        RefTypeId class_id,ObjectId thread_id,MethodId method_id,
        const std::vector<JValue> &argValues,uint32_t options,int id)
{
    QByteArray rel;
    WriteRefTypeId (rel, class_id);
    WriteThreadId (rel, thread_id);
    WriteMethodId (rel, method_id);
    Write4 (rel, argValues.size ());
    for(auto it = argValues.begin (), itEnd = argValues.end ();
        it != itEnd; it ++) {
        Write1 (rel, it->tag);
        WriteValue (rel, it->L, GetTagWidth (it->tag));
    }
    Write4 (rel, options);
    return BuildReq (id, set_, cmd, rel);
}

ArrayType::NewInstance::NewInstance (const uint8_t *bytes,uint32_t available)
        : JdwpReader (bytes,available)
{
    mObject.tag = (JdwpTag)Read1 ();
    mObject.L = ReadObjectId ();
}

QByteArray ArrayType::NewInstance::buildReq (
        RefTypeId arrayTypeId,uint32_t length,int id)
{
    QByteArray rel;
    WriteRefTypeId (rel, arrayTypeId);
    Write4 (rel, length);
    return BuildReq (id, set_, cmd, rel);
}

Method::LineTable::LineTable (const uint8_t *bytes,uint32_t available)
        : JdwpReader (bytes,available)
{
    mStart = Read8 ();
    mEnd = Read8();
    mNumLines = Read4();
    mItems.resize (mNumLines);
    for(size_t i = 0; i < mNumLines; i++) {
        mItems[i].address = Read8 ();
        mItems[i].line_number = Read4 ();
    }
}

QByteArray Method::LineTable::buildReq (
        RefTypeId refTypeId,MethodId method_id,int id)
{
    QByteArray rel;
    WriteRefTypeId (rel, refTypeId);
    WriteMethodId (rel, method_id);
    return BuildReq (id, set_, cmd, rel);
}


Method::VariableTable::VariableTable (const uint8_t *bytes,uint32_t available)
        : JdwpReader (bytes,available)
{
    mNumArgRegisters = Read4 ();
    mVariableCount = Read4();
    mItems.resize (mVariableCount);
    for(size_t i = 0; i < mVariableCount; i++) {
        mItems[i].startAddress = Read8 ();
        mItems[i].name = ReadString ();
        mItems[i].descriptor = ReadString ();
        mItems[i].size = Read4 ();
        mItems[i].slot = Read4 ();
    }
}

QByteArray Method::VariableTable::buildReq (
        RefTypeId class_id,MethodId method_id,int id)
{
    QByteArray rel;
    WriteRefTypeId (rel, class_id);
    WriteMethodId (rel, method_id);
    return BuildReq (id, set_, cmd, rel);
}


Method::Bytecodes::Bytecodes (const uint8_t *bytes,uint32_t available)
        : JdwpReader (bytes,available)
{
    mByteCodesSize = Read4();
    mByteCodes.resize (mByteCodesSize);
    for(uint32_t i = 0; i < mByteCodesSize; i++) {
        mByteCodes[i] = Read1 ();
    }
}

QByteArray Method::Bytecodes::buildReq (
        RefTypeId class_id,MethodId method_id,int id)
{
    QByteArray rel;
    WriteRefTypeId (rel, class_id);
    WriteMethodId (rel, method_id);
    return BuildReq (id, set_, cmd, rel);
}


Method::IsObsolete::IsObsolete (const uint8_t *bytes,uint32_t available)
        : JdwpReader (bytes,available)
{

}

QByteArray Method::IsObsolete::buildReq (
        RefTypeId class_id,MethodId method_id,int id)
{
    QByteArray rel;
    WriteRefTypeId (rel, class_id);
    WriteMethodId (rel, method_id);
    return BuildReq (id, set_, cmd, rel);
}

Method::VariableTableWithGeneric::VariableTableWithGeneric (
        const uint8_t *bytes,uint32_t available)
        : JdwpReader (bytes,available)
{
    mNumArgRegisters = Read4 ();
    mVariableCount = Read4();
    mItems.resize (mVariableCount);
    for(size_t i = 0; i < mVariableCount; i++) {
        mItems[i].startAddress = Read8 ();
        mItems[i].name = ReadString ();
        mItems[i].descriptor = ReadString ();
        mItems[i].signature = ReadString ();
        mItems[i].size = Read4 ();
        mItems[i].slot = Read4 ();
    }
}

QByteArray Method::VariableTableWithGeneric::buildReq (
        RefTypeId class_id,MethodId method_id,int id)
{
    QByteArray rel;
    WriteRefTypeId (rel, class_id);
    WriteMethodId (rel, method_id);
    return BuildReq (id, set_, cmd, rel);
}

ObjectReference::ReferenceType::ReferenceType (
        const uint8_t *bytes,uint32_t available)
        : JdwpReader (bytes,available)
{
    tag = (JdwpTypeTag) Read1 ();
    mTypeId = ReadRefTypeId ();
}

QByteArray ObjectReference::ReferenceType::buildReq (
        ObjectId object_id,int id)
{
    QByteArray rel;
    WriteObjectId (rel, object_id);
    return BuildReq (id, set_, cmd, rel);
}


ObjectReference::GetValues::GetValues (
        const uint8_t *bytes,uint32_t available)
        : JdwpReader (bytes,available)
{
    mValue.tag = (JdwpTag)Read1 ();
    mValue.L = ReadValue (GetTagWidth (mValue.tag));
}

QByteArray ObjectReference::GetValues::buildReq (
        ObjectId object_id,const std::vector<FieldId > &fields,int id)
{
    QByteArray rel;
    WriteObjectId (rel, object_id);
    Write4 (rel, fields.size ());
    for(auto it = fields.begin (), itEnd = fields.end ();
        it != itEnd; it++) {
        WriteFieldId (rel, *it);
    }
    return BuildReq (id, set_, cmd, rel);
}

ObjectReference::SetValues::SetValues (
        const uint8_t *bytes,uint32_t available)
        : JdwpReader (bytes,available)
{
}

QByteArray ObjectReference::SetValues::buildReq (
        ObjectId object_id,const std::vector<FieldInfo> &fields,int id)
{
    QByteArray rel;
    WriteObjectId (rel, object_id);
    Write4 (rel, fields.size ());
    for(auto it = fields.begin (), itEnd = fields.end ();
        it != itEnd; it++) {
        WriteFieldId (rel, it->mFieldId);
        auto &value = it->mValue;
        Write1 (rel, value.tag);
        WriteValue (rel, value.L, GetTagWidth (value.tag));
    }
    return BuildReq (id, set_, cmd, rel);
}

ObjectReference::UNUSED::UNUSED (const uint8_t *bytes,uint32_t available)
        : JdwpReader (bytes,available)
{

}

QByteArray ObjectReference::UNUSED::buildReq (int id)
{
    QByteArray rel;
    return BuildReq (id, set_, cmd, rel);
}

ObjectReference::MonitorInfo::MonitorInfo (
        const uint8_t *bytes,uint32_t available)
        : JdwpReader (bytes,available)
{
    mMonitorInfo = ReadObjectId ();
    mEntryCount = Read4 ();
    mWaiterSize = Read4 ();
    mWaiters.resize (mWaiterSize);
    for(uint32_t i = 0; i < mWaiterSize; i++) {
        mWaiters[i] = ReadObjectId ();
    }
}

QByteArray ObjectReference::MonitorInfo::buildReq (ObjectId object_id,int id)
{
    QByteArray rel;
    WriteObjectId (rel, object_id);
    return BuildReq (id, set_, cmd, rel);
}


ObjectReference::InvokeMethod::InvokeMethod (
        const uint8_t *bytes,uint32_t available)
        : JdwpReader (bytes,available)
{
    mResult.tag = (JdwpTag)Read1 ();
    mResult.L = ReadValue (GetTagWidth (mResult.tag));
    mObject.tag = (JdwpTag)Read1 ();
    mObject.L = ReadObjectId ();
}

QByteArray
ObjectReference::InvokeMethod::buildReq (
        ObjectId object_id,ObjectId thread_id,RefTypeId class_id,
        MethodId method_id, const std::vector<JValue> &argValues,
        uint32_t options,int id)
{
    QByteArray rel;
    WriteObjectId (rel, object_id);
    WriteThreadId (rel, thread_id);

    WriteRefTypeId (rel, class_id);
    WriteMethodId (rel, method_id);

    Write4 (rel, argValues.size ());
    for(auto it = argValues.begin (), itEnd = argValues.end ();
        it != itEnd; it ++) {
        Write1 (rel, it->tag);
        WriteValue (rel, it->L, GetTagWidth (it->tag));
    }
    Write4 (rel, options);
    return BuildReq (id, set_, cmd, rel);
}

ObjectReference::DisableCollection::DisableCollection (
        const uint8_t *bytes,uint32_t available)
        : JdwpReader (bytes,available)
{

}

QByteArray ObjectReference::DisableCollection::buildReq (
        ObjectId object_id,int id)
{
    QByteArray rel;
    WriteObjectId (rel, object_id);
    return BuildReq (id, set_, cmd, rel);
}

ObjectReference::EnableCollection::EnableCollection (
        const uint8_t *bytes,uint32_t available)
        : JdwpReader (bytes,available)
{

}

QByteArray ObjectReference::EnableCollection::buildReq (
        ObjectId object_id,int id)
{
    QByteArray rel;
    WriteObjectId (rel, object_id);
    return BuildReq (id, set_, cmd, rel);
}

ObjectReference::IsCollected::IsCollected (
        const uint8_t *bytes,uint32_t available)
        : JdwpReader (bytes,available)
{
    mIsCollected = Read1 ();
}

QByteArray ObjectReference::IsCollected::buildReq (ObjectId object_id,int id)
{
    QByteArray rel;
    WriteObjectId (rel, object_id);
    return BuildReq (id, set_, cmd, rel);
}

ObjectReference::ReferringObjects::ReferringObjects (
        const uint8_t *bytes,uint32_t available)
        : JdwpReader (bytes,available)
{
    mSize = Read4 ();
    mObjs.resize (mSize);
    for(auto i = 0; i < mSize; i++) {
        mObjs[i].tag = (JdwpTag)Read1 ();
        mObjs[i].L = ReadValue (GetTagWidth (mObjs[i].tag));
    }
}

QByteArray ObjectReference::ReferringObjects::buildReq (
        ObjectId object_id,int32_t max_count,int id)
{
    QByteArray rel;
    WriteObjectId (rel, object_id);
    Write4(rel, max_count);
    return BuildReq (id, set_, cmd, rel);
}

StringReference::Value::Value (const uint8_t *bytes,uint32_t available)
        : JdwpReader (bytes,available)
{
    mStr = ReadString ();
}

QByteArray StringReference::Value::buildReq (ObjectId stringObject,int id)
{
    QByteArray rel;
    WriteObjectId (rel, stringObject);
    return BuildReq (id, set_, cmd, rel);
}

ThreadReference::Name::Name (const uint8_t *bytes,uint32_t available)
        : JdwpReader (bytes,available)
{
    mName = ReadString ();
}

QByteArray ThreadReference::Name::buildReq (ObjectId thread_id,int id)
{
    QByteArray rel;
    WriteObjectId (rel, thread_id);
    return BuildReq (id, set_, cmd, rel);
}


ThreadReference::Suspend::Suspend (const uint8_t *bytes,uint32_t available)
        : JdwpReader (bytes,available)
{

}

QByteArray ThreadReference::Suspend::buildReq (ObjectId thread_id,int id)
{
    QByteArray rel;
    WriteObjectId (rel, thread_id);
    return BuildReq (id, set_, cmd, rel);
}

ThreadReference::Resume::Resume (const uint8_t *bytes,uint32_t available)
        : JdwpReader (bytes,available)
{

}

QByteArray ThreadReference::Resume::buildReq (ObjectId thread_id,int id)
{
    QByteArray rel;
    WriteObjectId (rel, thread_id);
    return BuildReq (id, set_, cmd, rel);
}

ThreadReference::Status::Status (const uint8_t *bytes,uint32_t available)
        : JdwpReader (bytes,available)
{
    mThreadStatus = Read4 ();
    mSuspendStatus = Read4();
}

QByteArray ThreadReference::Status::buildReq (ObjectId thread_id,int id)
{
    QByteArray rel;
    WriteObjectId (rel, thread_id);
    return BuildReq (id, set_, cmd, rel);
}

ThreadReference::ThreadGroup::ThreadGroup (
        const uint8_t *bytes,uint32_t available)
        : JdwpReader (bytes,available)
{
    mThreadGroupId = ReadObjectId ();
}

QByteArray ThreadReference::ThreadGroup::buildReq (ObjectId thread_id,int id)
{
    QByteArray rel;
    WriteObjectId (rel, thread_id);
    return BuildReq (id, set_, cmd, rel);
}

ThreadReference::Frames::Frames (const uint8_t *bytes,uint32_t available)
        : JdwpReader (bytes,available)
{
    mFrameCount = Read4 ();
    mFrames.resize (mFrameCount);
    for(auto i = 0; i < mFrameCount; i++) {
        mFrames[i].frame_id = Read8 ();
        mFrames[i].location = ReadJdwpLocation ();
    }
}

QByteArray ThreadReference::Frames::buildReq (
        ObjectId thread_id,uint32_t start_frame,uint32_t length,int id)
{
    QByteArray rel;
    WriteObjectId (rel, thread_id);
    Write4 (rel, start_frame);
    Write4 (rel, length);
    return BuildReq (id, set_, cmd, rel);
}

ThreadReference::FrameCount::FrameCount (
        const uint8_t *bytes,uint32_t available)
        : JdwpReader (bytes,available)
{
    mFrameCount = Read4 ();
}

QByteArray ThreadReference::FrameCount::buildReq (ObjectId thread_id,int id)
{
    QByteArray rel;
    WriteObjectId (rel, thread_id);
    return BuildReq (id, set_, cmd, rel);
}

ThreadReference::OwnedMonitors::OwnedMonitors (
        const uint8_t *bytes,uint32_t available)
        : JdwpReader (bytes,available)
{

    mMonitorSize = Read4 ();
    mMonitors.resize (mMonitorSize);
    for(auto i = 0; i < mMonitorSize; i++) {
        mMonitors[i].tag = (JdwpTag)Read1 ();
        mMonitors[i].L = ReadObjectId ();
    }
}


QByteArray ThreadReference::OwnedMonitors::buildReq (
        ObjectId thread_id,int id)
{
    QByteArray rel;
    WriteObjectId (rel, thread_id);
    return BuildReq (id, set_, cmd, rel);
}

ThreadReference::CurrentContendedMonitor::CurrentContendedMonitor (
        const uint8_t *bytes,uint32_t available)
        : JdwpReader (bytes,available)
{
    mContendedMonitor.tag = (JdwpTag)Read1 ();
    mContendedMonitor.L = ReadObjectId ();
}

QByteArray ThreadReference::CurrentContendedMonitor::buildReq (
        ObjectId thread_id,int id)
{
    QByteArray rel;
    WriteObjectId (rel, thread_id);
    return BuildReq (id, set_, cmd, rel);
}


ThreadReference::Stop::Stop (const uint8_t *bytes,uint32_t available)
        : JdwpReader (bytes,available)
{

}

QByteArray ThreadReference::Stop::buildReq (ObjectId thread_id,int id)
{
    QByteArray rel;
    WriteObjectId (rel, thread_id);
    return BuildReq (id, set_, cmd, rel);
}

ThreadReference::Interrupt::Interrupt (const uint8_t *bytes,uint32_t available)
        : JdwpReader (bytes,available)
{

}

QByteArray ThreadReference::Interrupt::buildReq (ObjectId thread_id,int id)
{
    QByteArray rel;
    WriteObjectId (rel, thread_id);
    return BuildReq (id, set_, cmd, rel);
}

ThreadReference::SuspendCount::SuspendCount (
        const uint8_t *bytes,uint32_t available)
        : JdwpReader (bytes,available)
{
    mSuspendCount = Read4 ();
}

QByteArray ThreadReference::SuspendCount::buildReq (
        ObjectId thread_id,int id)
{
    QByteArray rel;
    WriteObjectId (rel, thread_id);
    return BuildReq (id, set_, cmd, rel);
}


ThreadReference::OwnedMonitorsStackDepthInfo::OwnedMonitorsStackDepthInfo (
        const uint8_t *bytes,uint32_t available)
        : JdwpReader (bytes,available)
{
    mMonitorSize = Read4 ();
    mMonitors.resize (mMonitorSize);
    for(auto i = 0; i < mMonitorSize; i++) {
        mMonitors[i].monitor.tag = (JdwpTag)Read1 ();
        mMonitors[i].monitor.L = ReadObjectId ();
        mMonitors[i].depth = Read4 ();
    }
}

QByteArray ThreadReference::OwnedMonitorsStackDepthInfo::buildReq (
        ObjectId thread_id,int id)
{
    QByteArray rel;
    WriteObjectId (rel, thread_id);
    return BuildReq (id, set_, cmd, rel);
}


ThreadReference::ForceEarlyReturn::ForceEarlyReturn (
        const uint8_t *bytes,uint32_t available): JdwpReader (bytes,available)
{

}

QByteArray ThreadReference::ForceEarlyReturn::buildReq (
        ObjectId thread_id,int id)
{
    QByteArray rel;
    WriteObjectId (rel, thread_id);
    return BuildReq (id, set_, cmd, rel);
}

ThreadGroupReference::ForceEarlyReturn::ForceEarlyReturn (
        const uint8_t *bytes,uint32_t available)
        : JdwpReader (bytes,available)
{
    mThreadGroupName = ReadString ();
}

QByteArray ThreadGroupReference::ForceEarlyReturn::buildReq (
        ObjectId thread_group_id,int id)
{
    QByteArray rel;
    WriteObjectId (rel, thread_group_id);
    return BuildReq (id, set_, cmd, rel);
}

ThreadGroupReference::Parent::Parent (const uint8_t *bytes,uint32_t available)
        : JdwpReader (bytes,available)
{
    mThreadParentgroup = ReadObjectId ();
}

QByteArray ThreadGroupReference::Parent::buildReq (
        ObjectId thread_group_id,int id)
{
    QByteArray rel;
    WriteObjectId (rel, thread_group_id);
    return BuildReq (id, set_, cmd, rel);
}


ThreadGroupReference::Children::Children (
        const uint8_t *bytes,uint32_t available)
        : JdwpReader (bytes,available)
{
    mThreadIdSize = Read4 ();
    mThreadIds.resize (mThreadIdSize);
    for(auto i = 0; i < mThreadIdSize; i++) {
        mThreadIds[i] = ReadObjectId ();
    }

    mChildThreadGroupIdSize = Read4 ();
    for(auto i = 0; i < mChildThreadGroupIdSize; i++) {
        mChildThreadGroupsIds[i] = ReadObjectId ();
    }
}

QByteArray ThreadGroupReference::Children::buildReq (
        ObjectId thread_group_id,int id)
{
    QByteArray rel;
    WriteObjectId (rel, thread_group_id);
    return BuildReq (id, set_, cmd, rel);
}


ArrayReference::Length::Length (const uint8_t *bytes,uint32_t available)
        : JdwpReader (bytes,available)
{
    mLength = Read4 ();
}

QByteArray ArrayReference::Length::buildReq (ObjectId array_id,int id)
{
    QByteArray rel;
    WriteObjectId (rel, array_id);
    return BuildReq (id, set_, cmd, rel);
}


ArrayReference::GetValues::GetValues (const uint8_t *bytes,uint32_t available)
        : JdwpReader (bytes,available)
{
    mTag = (JdwpTag)Read1 ();
    mCount = Read4 ();
    mElements.resize (mCount);
    bool primateTag = IsPrimitiveTag (mTag);
    size_t width = GetTagWidth (mTag);
    if(primateTag) {
        for(auto i = 0; i < mCount; i++) {
            mElements[i].tag = mTag;
            mElements[i].L = ReadValue (width);
        }
    } else {
        for(auto i = 0; i < mCount; i++) {
            mElements[i].tag = (JdwpTag)Read1 ();
            mElements[i].L = ReadObjectId ();
        }
    }
}

QByteArray ArrayReference::GetValues::buildReq (
        ObjectId array_id,uint32_t offset,uint32_t length,int id)
{
    QByteArray rel;
    WriteObjectId (rel, array_id);
    Write4 (rel, offset);
    Write4 (rel, length);
    return BuildReq (id, set_, cmd, rel);
}


ArrayReference::SetValues::SetValues (
        const uint8_t *bytes,uint32_t available)
        : JdwpReader (bytes,available)
{
}

QByteArray ArrayReference::SetValues::buildReq (
        ObjectId array_id,uint32_t offset,JdwpTag tag,
        const std::vector<JValue> &elements,int id)
{
    QByteArray rel;
    WriteObjectId (rel, array_id);
    Write4 (rel, offset);
    Write4 (rel, elements.size ());
    auto width = GetTagWidth (tag);
    for(auto it = elements.begin (), itEnd = elements.end ();
        it != itEnd; it++)
    {
        WriteValue (rel,it->L,width);
    }
    return BuildReq (id, set_, cmd, rel);
}


ClassLoaderReference::VisibleClasses::VisibleClasses (
        const uint8_t *bytes,uint32_t available):
        JdwpReader (bytes,available)
{
    mClassSize = Read4 ();
    mClasses.resize (mClassSize);
    for(auto i = 0; i < mClassSize; i++) {
        mClasses[i].tag = (JdwpTag)Read1 ();
        mClasses[i].L = ReadRefTypeId ();
    }
}

QByteArray ClassLoaderReference::VisibleClasses::buildReq (
        ObjectId classLoaderObject,int id)
{
    QByteArray rel;
    WriteObjectId (rel, classLoaderObject);
    return BuildReq (id, set_, cmd, rel);
}

EventRequest::Set::Set (const uint8_t *bytes,uint32_t available)
        : JdwpReader (bytes,available)
{
    mRequestId = Read4 ();
}

QByteArray EventRequest::Set::buildReq (
        JdwpEventKind eventkind,JdwpSuspendPolicy policy,
        const std::vector<JdwpEventMod>& mod, int id)
{
    QByteArray rel;
    Write1 (rel,eventkind);
    Write1 (rel, policy);
    Write4 (rel, mod.size ());
    for(auto it = mod.begin (), itEnd = mod.end ();
        it != itEnd; it++) {
        Write1 (rel, it->modKind);
        switch(it->modKind) {
            case MK_COUNT:
            {
                // Report once, when "--count" reaches 0.
                Write4 (rel, it->count.count);
            }
                break;
            case MK_CONDITIONAL:
            {
                // Conditional on expression.
                Write4 (rel, it->conditional.exprId);
            }
                break;
            case MK_THREAD_ONLY:
            {
                // Only report events in specified thread.
                WriteThreadId (rel, it->threadOnly.threadId);
            }
                break;
            case MK_CLASS_ONLY:
            {
                // For ClassPrepare, MethodEntry.
                WriteRefTypeId (rel,it->classOnly.refTypeId);
            }
                break;
            case MK_CLASS_MATCH:
            {
                // Restrict events to matching classes.
                // pattern is "java.foo.*", we want "java/foo/*".
                WriteString (rel,it->classMatch.classPattern);
            }
                break;
            case MK_CLASS_EXCLUDE:
            {
                // Restrict events to non-matching classes.
                // pattern is "java.foo.*", we want "java/foo/*".
                WriteString (rel,it->classExclude.classPattern);
            }
                break;
            case MK_LOCATION_ONLY:
            {
                // Restrict certain events based on location.
                WriteJdwpLocation (rel, it->locationOnly.loc);
            }
                break;
            case MK_EXCEPTION_ONLY:
            {
                // Modifies EK_EXCEPTION events,
                WriteRefTypeId (rel,it->exceptionOnly.refTypeId);
                Write1 (rel,it->exceptionOnly.caught);
                Write1 (rel,it->exceptionOnly.uncaught);
            }
                break;
            case MK_FIELD_ONLY:
            {
                // For field access/modification events.
                WriteRefTypeId (rel, it->fieldOnly.refTypeId);
                WriteFieldId (rel, it->fieldOnly.fieldId);
            }
                break;
            case MK_STEP:
            {
                // For use with EK_SINGLE_STEP.
                WriteThreadId (rel,it->step.threadId);
                Write4 (rel,it->step.size);
                Write4 (rel,it->step.depth);
            }
                break;
            case MK_INSTANCE_ONLY:
            {
                // Report events related to a specific object.
                WriteObjectId (rel,it->instanceOnly.objectId);
            }
                break;
            default:
                break;
        }
    }
    return BuildReq (id, set_, cmd, rel);
}

EventRequest::Clear::Clear (const uint8_t *bytes,uint32_t available)
        : JdwpReader (bytes,available)
{
}

QByteArray EventRequest::Clear::buildReq (
        JdwpEventKind kind,uint32_t requestId, int id)
{
    QByteArray rel;
    Write1 (rel, kind);
    Write4 (rel, requestId);
    return BuildReq (id, set_, cmd, rel);
}

EventRequest::ClearAllBreakpoints::ClearAllBreakpoints (
        const uint8_t *bytes,uint32_t available)
        : JdwpReader (bytes,available)
{

}

QByteArray EventRequest::ClearAllBreakpoints::buildReq (int id)
{
    QByteArray rel;
    return BuildReq (id, set_, cmd, rel);
}

StackFrame::GetValues::GetValues (const uint8_t *bytes,uint32_t available)
        : JdwpReader (bytes,available)
{
    mSlotCount = Read4 ();
    mSlots.resize (mSlotCount);
    for(uint32_t i = 0; i < mSlotCount; i++) {
        mSlots[i].tag = (JdwpTag)Read1 ();
        mSlots[i].L = ReadValue (GetTagWidth (mSlots[i].tag));
    }
}

QByteArray StackFrame::GetValues::buildReq (
        ObjectId thread_id,FrameId frame_id,const std::vector<uint32_t> &fslots,
        const std::vector<JdwpTag> &reqSig,int id)
{
    if(fslots.size () != reqSig.size ())
        return "";
    QByteArray rel;
    WriteThreadId (rel, thread_id);
    WriteFrameId (rel, frame_id);
    int count = fslots.size ();
    Write4 (rel, count);
    for(auto i = 0; i < count; i++) {
        Write4 (rel, fslots[i]);
        Write1 (rel, reqSig[i]);
    }
    return BuildReq (id, set_, cmd, rel);
}

StackFrame::SetValues::SetValues (const uint8_t *bytes,uint32_t available)
        : JdwpReader (bytes,available)
{
}

QByteArray StackFrame::SetValues::buildReq (
        ObjectId thread_id,FrameId frame_id,const std::vector<uint32_t> &fslots,
        const std::vector<JValue> &reqSig,int id)
{
    if(fslots.size () != reqSig.size ())
        return "";
    QByteArray rel;
    WriteThreadId (rel, thread_id);
    WriteFrameId (rel, frame_id);
    int count = fslots.size ();
    Write4 (rel, count);
    for(auto i = 0; i < count; i++) {
        Write4 (rel, fslots[i]);
        Write1 (rel, reqSig[i].tag);
        WriteValue (rel, reqSig[i].L, GetTagWidth (reqSig[i].tag));
    }
    return BuildReq (id, set_, cmd, rel);
}


StackFrame::ThisObject::ThisObject (const uint8_t *bytes,uint32_t available)
        : JdwpReader (bytes,available)
{
    mObject.tag = (JdwpTag)Read1 ();
    mObject.L = ReadValue (GetTagWidth (mObject.tag));
}

QByteArray StackFrame::ThisObject::buildReq (
        ObjectId thread_id,FrameId frame_id,int id)
{
    QByteArray rel;
    WriteThreadId (rel, thread_id);
    WriteFrameId (rel, frame_id);
    return BuildReq (id, set_, cmd, rel);
}


StackFrame::PopFrames::PopFrames (const uint8_t *bytes,uint32_t available)
        : JdwpReader (bytes,available)
{

}

QByteArray StackFrame::PopFrames::buildReq (
        ObjectId thread_id,FrameId frame_id,int id)
{
    QByteArray rel;
    WriteThreadId (rel, thread_id);
    WriteFrameId (rel, frame_id);
    return BuildReq (id, set_, cmd, rel);
}

ClassObjectReference::ReflectedType::ReflectedType (
        const uint8_t *bytes,uint32_t available)
        : JdwpReader (bytes,available)
{
    mClass.tag = (JdwpTag)Read1 ();
    mClass.L = ReadValue (GetTagWidth (mClass.tag));
}

QByteArray ClassObjectReference::ReflectedType::buildReq (
        RefTypeId class_object_id,int id)
{
    QByteArray rel;
    WriteRefTypeId (rel, class_object_id);
    return BuildReq (id, set_, cmd, rel);
}

Composite::ReflectedType::ReflectedType (
        const uint8_t *bytes,uint32_t available)
        : JdwpReader (bytes,available)
{
    mSuspendPolicy = (JdwpSuspendPolicy)Read1();
    mCount = Read4();
    mEventList.resize(mCount);
    for(auto i = 0; i < mCount; i++) {
        JdwpEventKind eventKind = (JdwpEventKind)Read1();
        auto requestId = Read4();
        switch(eventKind) {
            case JdwpEventKind::EK_SINGLE_STEP:
            case JdwpEventKind::EK_BREAKPOINT:
            case JdwpEventKind::EK_METHOD_ENTRY:
            case JdwpEventKind::EK_METHOD_EXIT: {
                auto event = new EventLocationEvent();
                event->mEventKind = eventKind;
                event->mRequestId = requestId;
                event->mThreadId = ReadThreadId();
                event->mLocation = ReadJdwpLocation();
                mEventList[i] = event;
            }
                break;
            case JdwpEventKind::EK_FRAME_POP:Q_ASSERT(false);
                break;
            case JdwpEventKind::EK_EXCEPTION: {
                auto event = new EventException();
                event->mEventKind = eventKind;
                event->mRequestId = requestId;
                event->mThreadId = ReadThreadId();
                event->mThrowLoc = ReadJdwpLocation();
                event->mTag = (JdwpTag)Read1(); // it should be JT_OBJECT
                event->mExceptionId = ReadRefTypeId();
                event->mCatchLoc = ReadJdwpLocation();
                mEventList[i] = event;
            }
                break;
            case JdwpEventKind::EK_USER_DEFINED:Q_ASSERT(false);
                break;
            case JdwpEventKind::EK_THREAD_START:
            case JdwpEventKind::EK_THREAD_DEATH: {
                auto event = new EventThreadChange();
                event->mEventKind = eventKind;
                event->mRequestId = requestId;
                event->mThreadId = ReadThreadId();
                mEventList[i] = event;
            }
                break;
            case JdwpEventKind::EK_CLASS_PREPARE: {
                auto event = new EventClassPrepare();
                event->mEventKind = eventKind;
                event->mRequestId = requestId;
                event->mThreadId = ReadThreadId();
                event->mTag = (JdwpTag)Read1();
                event->mTypeId = ReadRefTypeId();
                event->mSignature = ReadString();
                event->mStatus = Read4();
                mEventList[i] = event;
            }
                break;
            case JdwpEventKind::EK_CLASS_UNLOAD:Q_ASSERT(false);
                break;
            case JdwpEventKind::EK_CLASS_LOAD:Q_ASSERT(false);
                break;
            case JdwpEventKind::EK_FIELD_ACCESS:Q_ASSERT(false);
                break;
            case JdwpEventKind::EK_FIELD_MODIFICATION:Q_ASSERT(false);
                break;
            case JdwpEventKind::EK_EXCEPTION_CATCH:Q_ASSERT(false);
                break;
            case JdwpEventKind::EK_METHOD_EXIT_WITH_RETURN_VALUE:Q_ASSERT(false);
                break;
            case JdwpEventKind::EK_MONITOR_CONTENDED_ENTER:Q_ASSERT(false);
                break;
            case JdwpEventKind::EK_MONITOR_CONTENDED_ENTERED:Q_ASSERT(false);
                break;
            case JdwpEventKind::EK_MONITOR_WAIT:Q_ASSERT(false);
                break;
            case JdwpEventKind::EK_MONITOR_WAITED:Q_ASSERT(false);
                break;
            case JdwpEventKind::EK_VM_START: {
                auto event = new EventVmStart();
                event->mEventKind = eventKind;
                event->mRequestId = requestId;
                event->mThreadId = ReadThreadId();
                mEventList[i] = event;
            }
                break;
            case JdwpEventKind::EK_VM_DEATH: {
                auto event = new EventVmDeath();
                event->mEventKind = eventKind;
                event->mRequestId = requestId;
                mEventList[i] = event;
            }
                break;
            case JdwpEventKind::EK_VM_DISCONNECTED:Q_ASSERT(false);
                break;
            default:
                qDebug() << "Unknown EventKind?" << eventKind;
                break;
        }
    }

    /*
 * A location of interest has been reached.  This handles:
 *   Breakpoint
 *   SingleStep
 *   MethodEntry
 *   MethodExit
 * These four types must be grouped together in a single response.  The
 * "eventFlags" indicates the type of event(s) that have happened.
 *
 * Valid mods:
 *   Count, ThreadOnly, ClassOnly, ClassMatch, ClassExclude, InstanceOnly
 *   LocationOnly (for breakpoint/step only)
 *   Step (for step only)
 *
 * Interesting test cases:
 *  - Put a breakpoint on a native method.  Eclipse creates METHOD_ENTRY
 *    and METHOD_EXIT events with a ClassOnly mod on the method's class.
 *  - Use "run to line".  Eclipse creates a BREAKPOINT with Count=1.
 *  - Single-step to a line with a breakpoint.  Should get a single
 *    event message with both events in it.
 */
    // dvmJdwpPostLocationEvent



}

Composite::ReflectedType::~ReflectedType() {
    qDeleteAll(mEventList);
}


QByteArray Composite::ReflectedType::buildReq (int id)
{
    Q_ASSERT(false && "This handle is not used by debugger");
    return QByteArray();
}


DDM::Chunk::Chunk (const uint8_t *bytes,uint32_t available)
        : JdwpReader (bytes,available)
{
//    Thread* self = Thread::Current();
//    JNIEnv* env = self->GetJniEnv();
//
//    uint32_t type = request.ReadUnsigned32("type");
//    uint32_t length = request.ReadUnsigned32("length");
//
//    // Create a byte[] corresponding to 'request'.
//    size_t request_length = request.size();
//    ScopedLocalRef<jbyteArray> dataArray(env, env->NewByteArray(request_length));
//    if (dataArray.get() == NULL) {
//        LOG(WARNING) << "byte[] allocation failed: " << request_length;
//        env->ExceptionClear();
//        return false;
//    }
//    env->SetByteArrayRegion(dataArray.get(), 0, request_length, reinterpret_cast<const jbyte*>(request.data()));
//    request.Skip(request_length);
//
//    // Run through and find all chunks.  [Currently just find the first.]
//    ScopedByteArrayRO contents(env, dataArray.get());
//    if (length != request_length) {
//        LOG(WARNING) << StringPrintf("bad chunk found (len=%u pktLen=%d)", length, request_length);
//        return false;
//    }
//
//    // Call "private static Chunk dispatch(int type, byte[] data, int offset, int length)".
//    ScopedLocalRef<jobject> chunk(env, env->CallStaticObjectMethod(WellKnownClasses::org_apache_harmony_dalvik_ddmc_DdmServer,
//                                                                   WellKnownClasses::org_apache_harmony_dalvik_ddmc_DdmServer_dispatch,
//                                                                   type, dataArray.get(), 0, length));
//    if (env->ExceptionCheck()) {
//        LOG(INFO) << StringPrintf("Exception thrown by dispatcher for 0x%08x", type);
//        env->ExceptionDescribe();
//        env->ExceptionClear();
//        return false;
//    }
//
//    if (chunk.get() == NULL) {
//        return false;
//    }
//
//    /*
//     * Pull the pieces out of the chunk.  We copy the results into a
//     * newly-allocated buffer that the caller can free.  We don't want to
//     * continue using the Chunk object because nothing has a reference to it.
//     *
//     * We could avoid this by returning type/data/offset/length and having
//     * the caller be aware of the object lifetime issues, but that
//     * integrates the JDWP code more tightly into the rest of the runtime, and doesn't work
//     * if we have responses for multiple chunks.
//     *
//     * So we're pretty much stuck with copying data around multiple times.
//     */
//    ScopedLocalRef<jbyteArray> replyData(env, reinterpret_cast<jbyteArray>(env->GetObjectField(chunk.get(), WellKnownClasses::org_apache_harmony_dalvik_ddmc_Chunk_data)));
//    jint offset = env->GetIntField(chunk.get(), WellKnownClasses::org_apache_harmony_dalvik_ddmc_Chunk_offset);
//    length = env->GetIntField(chunk.get(), WellKnownClasses::org_apache_harmony_dalvik_ddmc_Chunk_length);
//    type = env->GetIntField(chunk.get(), WellKnownClasses::org_apache_harmony_dalvik_ddmc_Chunk_type);
//
//    VLOG(jdwp) << StringPrintf("DDM reply: type=0x%08x data=%p offset=%d length=%d", type, replyData.get(), offset, length);
//    if (length == 0 || replyData.get() == NULL) {
//        return false;
//    }
//
//    const int kChunkHdrLen = 8;
//    uint8_t* reply = new uint8_t[length + kChunkHdrLen];
//    if (reply == NULL) {
//        LOG(WARNING) << "malloc failed: " << (length + kChunkHdrLen);
//        return false;
//    }
//    JDWP::Set4BE(reply + 0, type);
//    JDWP::Set4BE(reply + 4, length);
//    env->GetByteArrayRegion(replyData.get(), offset, length, reinterpret_cast<jbyte*>(reply + kChunkHdrLen));
//
//    *pReplyBuf = reply;
//    *pReplyLen = length + kChunkHdrLen;
//
//    VLOG(jdwp) << StringPrintf("dvmHandleDdm returning type=%.4s %p len=%d", reinterpret_cast<char*>(reply), reply, length);
//    return true;
}

QByteArray DDM::Chunk::buildReq (int id)
{
    // TODO Chunk
    return "";
}
