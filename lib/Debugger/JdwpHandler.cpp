//===- JdwpHandler.cpp - ART-DEBUGGER ----------------------------*- C++ -*-===//
//
//                     ANDROID REVERSE TOOLKIT
//
// This file is distributed under the GNU GENERAL PUBLIC LICENSE
// V3 License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

#include "Debugger/JdwpHandler.h"
#include "JdwpHeader.h"
#include <netinet/in.h>

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

std::string VirtualMachine::Version::buildReq (int id)
{
    std::string rel;
    return move(BuildReq (id, set_, cmd, rel));
}

VirtualMachine::ClassesBySignature::ClassesBySignature (
        const uint8_t *bytes,uint32_t available)
        : JdwpReader (bytes,available)
{
    mSize = Read4 ();
    mInfos.resize (mSize);
    for(int i = 0; i < mSize; i++) {
        auto &info = mInfos[i];
        info.mRefTypeTag = Read1 ();
        info.mTypeId = ReadRefTypeId ();
        info.mStatus = Read4 ();
    }
}

std::string VirtualMachine::ClassesBySignature::buildReq (
        const std::string &classDescriptor, int id)
{
    std::string rel;
    WriteString (rel, classDescriptor);
    return move(BuildReq (id, set_, cmd, rel));
}

bool JDWP::Write1(std::string &s, uint8_t v)
{
    s.push_back ((char)v);
    return true;
}

bool JDWP::Write2(std::string &s, uint16_t v)
{
    uint16_t vn = htons (v);
    s.append (vn,sizeof (vn));
    return true;
}

bool JDWP::Write4(std::string &s, uint32_t v)
{
    uint32_t vn = htonl (v);
    s.append (vn, sizeof(vn));
    return true;
}


bool JDWP::Write8 (std::string &s,uint64_t v)
{
    uint32_t high = v >> 32;
    uint32_t low = v & 0xffffffff;
    Write4 (s, high);
    Write4 (s, low);
    return true;
}
bool JDWP::WriteString(std::string &s, const std::string &v)
{
    auto vLen = v.length ();
    Write4 (s, vLen);
    s.append (v);
    return true;
}


bool ::JDWP::WriteFieldId (std::string &s,uint32_t v)
{
    return Write4 (s, v);
}

bool ::JDWP::WriteMethodId (std::string &s,uint32_t v)
{
    return Write4 (s, v);
}

bool ::JDWP::WriteObjectId (std::string &s,uint64_t v)
{
    return Write8 (s, v);
}

bool ::JDWP::WriteRefTypeId (std::string &s,uint64_t v)
{
    return Write8 (s, v);
}

bool ::JDWP::WriteFrameId (std::string &s,uint64_t v)
{
    return Write8 (s, v);
}

std::string JDWP::BuildReq (int id,int cmdset,int cmd,
                              const std::string &extra)
{
    std::string rel;
    auto len = extra.length () + kJDWPHeaderLen;
    Write4 (rel, len);
    Write4 (rel, id);
    Write1 (rel, 0);    // flag
    Write1 (rel, cmdset);
    Write1 (rel, cmd);
    rel.append (extra);
    return move(rel);
}

bool ::JDWP::WriteValue (std::string &s,uint64_t v,size_t width)
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

bool ::JDWP::WriteThreadId (std::string &s,uint64_t v)
{
    return Write8 (s, v);
}

VirtualMachine::AllClasses::AllClasses (
        const uint8_t *bytes,uint32_t available)
        : JdwpReader (bytes,available)
{
    mSize = Read4 ();
    mInfos.resize (mSize);
    for(int i = 0; i < mSize; i++) {
        auto &info = mInfos[i];

        info.mRefTypeTag = Read1 ();
        info.mTypeId = ReadRefTypeId ();
        info.mDescriptor = ReadString ();
        info.mStatus = Read4 ();
    }
}

std::string VirtualMachine::AllClasses::buildReq (int id)
{
    std::string rel;
    return move(BuildReq (id, set_, cmd, rel));
}

VirtualMachine::AllThreads::AllThreads (
        const uint8_t *bytes,uint32_t available)
        : JdwpReader (bytes,available)
{
    mSize = Read4 ();
    mThreadIds.resize (mSize);
    for(int i = 0; i < mSize; i++) {
        mThreadIds[i] = ReadObjectId ();
    }
}

std::string VirtualMachine::AllThreads::buildReq (int id)
{
    std::string rel;
    return move(BuildReq (id, set_, cmd, rel));
}


VirtualMachine::TopLevelThreadGroups::TopLevelThreadGroups (
        const uint8_t *bytes,uint32_t available)
        : JdwpReader (bytes,available)
{
    mGroups = Read4 ();
    mThreadGroupId = ReadObjectId ();
}

std::string VirtualMachine::TopLevelThreadGroups::buildReq (int id)
{
    std::string rel;
    return move(BuildReq (id, set_, cmd, rel));
}

VirtualMachine::Dispose::Dispose (
        const uint8_t *bytes,uint32_t available)
        : JdwpReader (bytes,available)
{
}

std::string VirtualMachine::Dispose::buildReq (int id)
{
    std::string rel;
    return move(BuildReq (id, set_, cmd, rel));
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

std::string VirtualMachine::IDSizes::buildReq (int id)
{
    std::string rel;
    return move(BuildReq (id, set_, cmd, rel));
}

VirtualMachine::Suspend::Suspend (
        const uint8_t *bytes,uint32_t available)
        : JdwpReader (bytes,available)
{

}

std::string VirtualMachine::Suspend::buildReq (int id)
{
    std::string rel;
    return move(BuildReq (id, set_, cmd, rel));
}


VirtualMachine::Resume::Resume (
        const uint8_t *bytes,uint32_t available)
        : JdwpReader (bytes,available)
{

}

std::string VirtualMachine::Resume::buildReq (int id)
{
    std::string rel;
    return move(BuildReq (id, set_, cmd, rel));
}

VirtualMachine::Exit::Exit (
        const uint8_t *bytes,uint32_t available)
        : JdwpReader (bytes,available)
{

}

std::string VirtualMachine::Exit::buildReq (int id)
{
    std::string rel;
    return move(BuildReq (id, set_, cmd, rel));
}

VirtualMachine::CreateString::CreateString (
        const uint8_t *bytes,uint32_t available)
        : JdwpReader (bytes,available)
{
    mStringId = ReadObjectId ();
}

std::string VirtualMachine::CreateString::buildReq (
        const std::string str,int id)
{
    std::string rel;
    WriteString (rel, str);
    return move(BuildReq (id, set_, cmd, rel));
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

std::string VirtualMachine::Capabilities::buildReq (int id)
{
    std::string rel;
    return move(BuildReq (id, set_, cmd, rel));
}


VirtualMachine::ClassPaths::ClassPaths (
        const uint8_t *bytes,uint32_t available)
        : JdwpReader (bytes,available)
{
    mSlash = ReadString ();

    mClassPathSize = Read4 ();
    mClassPath.resize (mClassPathSize);
    for(int i = 0; i < mClassPathSize; i++) {
        mClassPath[i] = ReadString ();
    }

    mBootClassPathSize = Read4 ();
    mBootClassPath.resize (mBootClassPathSize);
    for(int i = 0; i < mBootClassPathSize; i++) {
        mBootClassPath[i] = ReadString ();
    }
}

std::string VirtualMachine::ClassPaths::buildReq (int id)
{
    std::string rel;
    return move(BuildReq (id, set_, cmd, rel));
}


VirtualMachine::DisposeObjects::DisposeObjects (
        const uint8_t *bytes,uint32_t available)
        : JdwpReader (bytes,available)
{
}

std::string VirtualMachine::DisposeObjects::buildReq (
        const std::vector<DispObj> &objs,int id)
{
    std::string rel;
    Write4 (rel, objs.size ());
    for(auto it = objs.begin (), itEnd = objs.end ();
            it != itEnd; it++) {
        WriteObjectId (rel, it->id);
        Write4 (rel, it->refCount);
    }
    return move(BuildReq (id, set_, cmd, rel));
}


VirtualMachine::HoldEvents::HoldEvents (
        const uint8_t *bytes,uint32_t available)
        : JdwpReader (bytes,available)
{

}

std::string VirtualMachine::HoldEvents::buildReq (int id)
{
    std::string rel;
    return move(BuildReq (id, set_, cmd, rel));
}


VirtualMachine::ReleaseEvents::ReleaseEvents (
        const uint8_t *bytes,uint32_t available)
        : JdwpReader (bytes,available)
{

}

std::string VirtualMachine::ReleaseEvents::buildReq (int id)
{
    std::string rel;
    return move(BuildReq (id, set_, cmd, rel));
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
        auto reversed = Read1 ();
    }
}

std::string VirtualMachine::CapabilitiesNew::buildReq (int id)
{
    std::string rel;
    return move(BuildReq (id, set_, cmd, rel));
}

VirtualMachine::RedefineClasses::RedefineClasses (
        const uint8_t *bytes,uint32_t available)
        : JdwpReader (bytes,available)
{

}

std::string VirtualMachine::RedefineClasses::buildReq (int id)
{
    std::string rel;
    return move(BuildReq (id, set_, cmd, rel));
}

VirtualMachine::SetDefaultStratum::SetDefaultStratum (
        const uint8_t *bytes,uint32_t available)
        : JdwpReader (bytes,available)
{

}

std::string VirtualMachine::SetDefaultStratum::buildReq (int id)
{
    std::string rel;
    return move(BuildReq (id, set_, cmd, rel));
}


VirtualMachine::AllClassesWithGeneric::AllClassesWithGeneric (
        const uint8_t *bytes,uint32_t available)
        : JdwpReader (bytes,available)
{
    mSize = Read4 ();
    mInfos.resize (mSize);
    for(int i = 0; i < mSize; i++) {
        auto &info = mInfos[i];

        info.mRefTypeTag = Read1 ();
        info.mTypeId = ReadRefTypeId ();
        info.mDescriptor = ReadString ();
        info.mGenericSignature = ReadString ();
        info.mStatus = Read4 ();
    }
}

std::string VirtualMachine::AllClassesWithGeneric::buildReq (int id)
{
    std::string rel;
    return move(BuildReq (id, set_, cmd, rel));
}


VirtualMachine::InstanceCounts::InstanceCounts (
        const uint8_t *bytes,uint32_t available)
        : JdwpReader (bytes,available)
{
    mCountSize = Read4 ();
    mCounts.resize (mCountSize);
    for(auto i = 0; i < mCountSize; i++) {
        mCounts[i] = Read8 ();
    }
}

std::string VirtualMachine::InstanceCounts::buildReq (
        const std::vector<RefTypeId> &class_ids,int id)
{
    std::string rel;
    Write4(rel, class_ids.size ());
    for(auto it = class_ids.begin (), itEnd = class_ids.end ();
            it != itEnd; it++) {
        WriteRefTypeId (rel, *it);
    }

    return move(BuildReq (id, set_, cmd, rel));
}

ReferenceType::Signature::Signature (
        const uint8_t *bytes,uint32_t available)
        : JdwpReader (bytes,available)
{
    mSignature = ReadString ();
}

std::string ReferenceType::Signature::buildReq (RefTypeId refTypeId,int id)
{
    std::string rel;
    WriteRefTypeId (rel, refTypeId);
    return move(BuildReq (id, set_, cmd, rel));
}


ReferenceType::ClassLoader::ClassLoader (
        const uint8_t *bytes,uint32_t available)
        : JdwpReader (bytes,available)
{
    mClassId = ReadObjectId ();
}

std::string ReferenceType::ClassLoader::buildReq (RefTypeId refTypeId,int id)
{
    std::string rel;
    WriteRefTypeId (rel, refTypeId);
    return move(BuildReq (id, set_, cmd, rel));
}

ReferenceType::Modifiers::Modifiers (
        const uint8_t *bytes,uint32_t available)
        : JdwpReader (bytes,available)
{
    mFlags = Read4 ();
}

std::string ReferenceType::Modifiers::buildReq (RefTypeId refTypeId,int id)
{
    std::string rel;
    WriteRefTypeId (rel, refTypeId);
    return move(BuildReq (id, set_, cmd, rel));
}

ReferenceType::Fields::Fields (
        const uint8_t *bytes,uint32_t available)
        : JdwpReader (bytes,available)
{
    mSize = Read4 ();
    mFields.resize (mSize);
    for (int i = 0; i<mSize; ++i)
    {
        mFields[i].mFieldId = ReadFieldId ();
        mFields[i].mName = ReadString ();
        mFields[i].mDescriptor = ReadString ();
        mFields[i].mFlags = Read4 ();
    }
}

std::string ReferenceType::Fields::buildReq (RefTypeId refTypeId,int id)
{
    std::string rel;
    WriteRefTypeId (rel, refTypeId);
    return move(BuildReq (id, set_, cmd, rel));
}

ReferenceType::Methods::Methods (
        const uint8_t *bytes,uint32_t available)
        : JdwpReader (bytes,available)
{
    mSize = Read4 ();
    mMethods.resize (mSize);
    for (int i = 0; i<mSize; ++i)
    {
        mMethods[i].mMethodId = ReadMethodId ();
        mMethods[i].mName = ReadString ();
        mMethods[i].mSignature = ReadString ();
        mMethods[i].mFlags = Read4 ();
    }
}

std::string ReferenceType::Methods::buildReq (RefTypeId refTypeId,int id)
{
    std::string rel;
    WriteRefTypeId (rel, refTypeId);
    return move(BuildReq (id, set_, cmd, rel));
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

std::string ReferenceType::GetValues::buildReq (
        RefTypeId refTypeId,int32_t field_count,
        const std::vector<FieldId> &fieldids,int id)
{
    std::string rel;
    WriteRefTypeId (rel, refTypeId);
    Write4 (rel, field_count);
    for(auto it = fieldids.begin (), itEnd = fieldids.end ();
            it != itEnd; it++) {
        WriteFieldId (rel, *it);
    }
    return move(BuildReq (id, set_, cmd, rel));
}

ReferenceType::SourceFile::SourceFile (
        const uint8_t *bytes,uint32_t available)
        : JdwpReader (bytes,available)
{
    mSourceFile = ReadString ();
}

std::string ReferenceType::SourceFile::buildReq (RefTypeId refTypeId,int id)
{
    std::string rel;
    WriteRefTypeId (rel, refTypeId);
    return move(BuildReq (id, set_, cmd, rel));
}

ReferenceType::NestedTypes::NestedTypes (
        const uint8_t *bytes,uint32_t available)
        : JdwpReader (bytes,available)
{

}

std::string ReferenceType::NestedTypes::buildReq (RefTypeId refTypeId,int id)
{
    std::string rel;
    WriteRefTypeId (rel, refTypeId);
    return move(BuildReq (id, set_, cmd, rel));
}

ReferenceType::Status::Status (
        const uint8_t *bytes,uint32_t available)
        : JdwpReader (bytes,available)
{
    mClassStatus = Read4 ();
}

std::string ReferenceType::Status::buildReq (RefTypeId refTypeId,int id)
{
    std::string rel;
    WriteRefTypeId (rel, refTypeId);
    return move(BuildReq (id, set_, cmd, rel));
}


ReferenceType::Interfaces::Interfaces (
        const uint8_t *bytes,uint32_t available)
        : JdwpReader (bytes,available)
{
    mCounts = Read4 ();
    mDirectInterfaces.resize (mCounts);
    for(auto i = 0; i < mCounts; i++) {
        mDirectInterfaces[i] = ReadRefTypeId ();
    }
}

std::string ReferenceType::Interfaces::buildReq (RefTypeId refTypeId,int id)
{
    std::string rel;
    WriteRefTypeId (rel, refTypeId);
    return move(BuildReq (id, set_, cmd, rel));
}

ReferenceType::ClassObject::ClassObject (
        const uint8_t *bytes,uint32_t available)
        : JdwpReader (bytes,available)
{
    mClassId = ReadObjectId ();
}

std::string ReferenceType::ClassObject::buildReq (RefTypeId refTypeId,int id)
{
    std::string rel;
    WriteRefTypeId (rel, refTypeId);
    return move(BuildReq (id, set_, cmd, rel));
}


ReferenceType::SourceDebugExtension::SourceDebugExtension (
        const uint8_t *bytes,uint32_t available)
        : JdwpReader (bytes,available)
{

}

std::string ReferenceType::SourceDebugExtension::buildReq (
        RefTypeId refTypeId,int id)
{
    std::string rel;
    WriteRefTypeId (rel, refTypeId);
    return move(BuildReq (id, set_, cmd, rel));
}

ReferenceType::SignatureWithGeneric::SignatureWithGeneric (
        const uint8_t *bytes,uint32_t available)
    : Signature (bytes,available)
{
    mSignatureGeneric = ReadString ();
}

std::string ReferenceType::SignatureWithGeneric::buildReq (
        RefTypeId refTypeId,int id)
{
    std::string rel;
    WriteRefTypeId (rel,refTypeId);
    return move (BuildReq (id,set_,cmd,rel));
}

ReferenceType::FieldsWithGeneric::FieldsWithGeneric (
        const uint8_t *bytes,uint32_t available)
        : JdwpReader (bytes,available)
{
    mSize = Read4 ();
    mFields.resize (mSize);
    for (int i = 0; i<mSize; ++i)
    {
        mFields[i].mFieldId = ReadFieldId ();
        mFields[i].mName = ReadString ();
        mFields[i].mDescriptor = ReadString ();
        mFields[i].mGenericSignature = ReadString ();
        mFields[i].mFlags = Read4 ();
    }
}

std::string ReferenceType::FieldsWithGeneric::buildReq (
        RefTypeId refTypeId,int id)
{
    std::string rel;
    WriteRefTypeId (rel, refTypeId);
    return move(BuildReq (id, set_, cmd, rel));
}

ReferenceType::MethodsWithGeneric::MethodsWithGeneric (
        const uint8_t *bytes,uint32_t available):
        JdwpReader (bytes,available)
{
    mSize = Read4 ();
    mMethods.resize (mSize);
    for (int i = 0; i<mSize; ++i)
    {
        mMethods[i].mMethodId = ReadMethodId ();
        mMethods[i].mName = ReadString ();
        mMethods[i].mSignature = ReadString ();
        mMethods[i].mGenericSignature = ReadString ();
        mMethods[i].mFlags = Read4 ();
    }
}

std::string ReferenceType::MethodsWithGeneric::buildReq (
        RefTypeId refTypeId,int id)
{
    std::string rel;
    WriteRefTypeId (rel, refTypeId);
    return move(BuildReq (id, set_, cmd, rel));
}

ReferenceType::Instances::Instances (
        const uint8_t *bytes,uint32_t available)
        : JdwpReader (bytes,available)
{
    mSize = Read4 ();
    mObjTags.resize (mSize);
    for(auto i = 0; i < mSize; i++) {
        mObjTags[i].tag = (JDWP::JdwpTag)Read1 ();
        mObjTags[i].objectId = ReadObjectId ();
    }
}

std::string ReferenceType::Instances::buildReq (
        RefTypeId refTypeId, int32_t maxcount, int id)
{
    std::string rel;
    WriteRefTypeId (rel, refTypeId);
    Write4(rel, maxcount);
    return move(BuildReq (id, set_, cmd, rel));
}

ReferenceType::ClassFileVersion::ClassFileVersion (
        const uint8_t *bytes,uint32_t available)
        : JdwpReader (bytes,available)
{

}

std::string ReferenceType::ClassFileVersion::buildReq (
        RefTypeId refTypeId,int id)
{
    std::string rel;
    WriteRefTypeId (rel, refTypeId);
    return move(BuildReq (id, set_, cmd, rel));
}

ReferenceType::ConstantPool::ConstantPool (
        const uint8_t *bytes,uint32_t available)
        : JdwpReader (bytes,available)
{

}

std::string ReferenceType::ConstantPool::buildReq (RefTypeId refTypeId,int id)
{
    std::string rel;
    WriteRefTypeId (rel, refTypeId);
    return move(BuildReq (id, set_, cmd, rel));
}

ClassType::Superclass::Superclass (const uint8_t *bytes,uint32_t available)
        : JdwpReader (bytes,available)
{
    mSuperClassId = ReadRefTypeId ();
}

std::string ClassType::Superclass::buildReq (RefTypeId refTypeId,int id)
{
    std::string rel;
    WriteRefTypeId (rel, refTypeId);
    return move(BuildReq (id, set_, cmd, rel));
}

ClassType::SetValues::SetValues (const uint8_t *bytes,uint32_t available)
        : JdwpReader (bytes,available)
{

}

std::string ClassType::SetValues::buildReq (
        RefTypeId refTypeId,const std::vector<FieldInfo> &infos,int id)
{
    std::string rel;
    WriteRefTypeId (rel, refTypeId);
    Write4 (rel, infos.size ());
    for(auto it = infos.begin (), itEnd = infos.end ();
            it != itEnd; it++) {
        WriteFieldId (rel, it->mFieldId);
        auto &value = it->mValue;
        WriteValue (rel, value.L, GetTagWidth (value.tag));
    }
    return move(BuildReq (id, set_, cmd, rel));
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

std::string ClassType::InvokeMethod::buildReq (
        RefTypeId class_id,ObjectId thread_id,MethodId method_id,
        const std::vector<JValue> &argValues,uint32_t options,int id)
{
    std::string rel;
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
    return move(BuildReq (id, set_, cmd, rel));
}

ClassType::NewInstance::NewInstance (const uint8_t *bytes,uint32_t available)
        : JdwpReader (bytes,available)
{
    mResult.tag = (JdwpTag)Read1 ();
    mResult.L = ReadValue (GetTagWidth (mResult.tag));
    mObject.tag = (JdwpTag)Read1 ();
    mObject.L = ReadObjectId ();
}

std::string ClassType::NewInstance::buildReq (
        RefTypeId class_id,ObjectId thread_id,MethodId method_id,
         const std::vector<JValue> &argValues,uint32_t options,int id)
{
    std::string rel;
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
    return move(BuildReq (id, set_, cmd, rel));
}

ArrayType::NewInstance::NewInstance (const uint8_t *bytes,uint32_t available)
        : JdwpReader (bytes,available)
{
    mObject.tag = (JdwpTag)Read1 ();
    mObject.L = ReadObjectId ();
}

std::string ArrayType::NewInstance::buildReq (
        RefTypeId arrayTypeId,uint32_t length,int id)
{
    std::string rel;
    WriteRefTypeId (rel, arrayTypeId);
    Write4 (rel, length);
    return move(BuildReq (id, set_, cmd, rel));
}

