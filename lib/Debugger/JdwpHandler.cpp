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

Method::LineTable::LineTable (const uint8_t *bytes,uint32_t available)
        : JdwpReader (bytes,available)
{
    mStart = Read8 ();
    mEnd = Read8();
    mNumLines = Read4();
    mItems.resize (mNumLines);
    for(auto i = 0; i < mNumLines; i++) {
        mItems[i].address = Read8 ();
        mItems[i].line_number = Read4 ();
    }
}

std::string Method::LineTable::buildReq (
        RefTypeId refTypeId,MethodId method_id,int id)
{
    std::string rel;
    WriteRefTypeId (rel, refTypeId);
    WriteMethodId (rel, method_id);
    return move(BuildReq (id, set_, cmd, rel));
}


Method::VariableTable::VariableTable (const uint8_t *bytes,uint32_t available)
        : JdwpReader (bytes,available)
{
    mNumArgRegisters = Read4 ();
    mVariableCount = Read4();
    mItems.resize (mVariableCount);
    for(auto i = 0; i < mVariableCount; i++) {
        mItems[i].startAddress = Read8 ();
        mItems[i].name = ReadString ();
        mItems[i].descriptor = ReadString ();
        mItems[i].size = Read4 ();
        mItems[i].slot = Read4 ();
    }
}

std::string Method::VariableTable::buildReq (
        RefTypeId class_id,MethodId method_id,int id)
{
    std::string rel;
    WriteRefTypeId (rel, class_id);
    WriteMethodId (rel, method_id);
    return move(BuildReq (id, set_, cmd, rel));
}


Method::Bytecodes::Bytecodes (const uint8_t *bytes,uint32_t available)
        : JdwpReader (bytes,available)
{
    mByteCodesSize = Read4();
    mByteCodes.resize (mByteCodesSize);
    for(auto i = 0; i < mByteCodesSize; i++) {
        mByteCodes[i] = Read1 ();
    }
}

std::string Method::Bytecodes::buildReq (
        RefTypeId class_id,MethodId method_id,int id)
{
    std::string rel;
    WriteRefTypeId (rel, class_id);
    WriteMethodId (rel, method_id);
    return move(BuildReq (id, set_, cmd, rel));
}


Method::IsObsolete::IsObsolete (const uint8_t *bytes,uint32_t available)
        : JdwpReader (bytes,available)
{

}

std::string Method::IsObsolete::buildReq (
        RefTypeId class_id,MethodId method_id,int id)
{
    std::string rel;
    WriteRefTypeId (rel, class_id);
    WriteMethodId (rel, method_id);
    return move(BuildReq (id, set_, cmd, rel));
}

Method::VariableTableWithGeneric::VariableTableWithGeneric (
        const uint8_t *bytes,uint32_t available)
        : JdwpReader (bytes,available)
{
    mNumArgRegisters = Read4 ();
    mVariableCount = Read4();
    mItems.resize (mVariableCount);
    for(auto i = 0; i < mVariableCount; i++) {
        mItems[i].startAddress = Read8 ();
        mItems[i].name = ReadString ();
        mItems[i].descriptor = ReadString ();
        mItems[i].signature = ReadString ();
        mItems[i].size = Read4 ();
        mItems[i].slot = Read4 ();
    }
}

std::string Method::VariableTableWithGeneric::buildReq (
        RefTypeId class_id,MethodId method_id,int id)
{
    std::string rel;
    WriteRefTypeId (rel, class_id);
    WriteMethodId (rel, method_id);
    return move(BuildReq (id, set_, cmd, rel));
}

ObjectReference::ReferenceType::ReferenceType (
        const uint8_t *bytes,uint32_t available)
        : JdwpReader (bytes,available)
{
    tag = (JdwpTypeTag) Read1 ();
    mTypeId = ReadRefTypeId ();
}

std::string ObjectReference::ReferenceType::buildReq (
        ObjectId object_id,int id)
{
    std::string rel;
    WriteObjectId (rel, object_id);
    return move(BuildReq (id, set_, cmd, rel));
}


ObjectReference::GetValues::GetValues (
        const uint8_t *bytes,uint32_t available)
        : JdwpReader (bytes,available)
{
    mValue.tag = (JdwpTag)Read1 ();
    mValue.L = ReadValue (GetTagWidth (mValue.tag));
}

std::string ObjectReference::GetValues::buildReq (
        ObjectId object_id,const std::vector<FieldId > &fields,int id)
{
    std::string rel;
    WriteObjectId (rel, object_id);
    Write4 (rel, fields.size ());
    for(auto it = fields.begin (), itEnd = fields.end ();
            it != itEnd; it++) {
        WriteFieldId (rel, *it);
    }
    return move(BuildReq (id, set_, cmd, rel));
}

ObjectReference::SetValues::SetValues (
        const uint8_t *bytes,uint32_t available)
        : JdwpReader (bytes,available)
{
}

std::string ObjectReference::SetValues::buildReq (
        ObjectId object_id,const std::vector<FieldInfo> &fields,int id)
{
    std::string rel;
    WriteObjectId (rel, object_id);
    Write4 (rel, fields.size ());
    for(auto it = fields.begin (), itEnd = fields.end ();
        it != itEnd; it++) {
        WriteFieldId (rel, it->mFieldId);
        auto &value = it->mValue;
        Write1 (rel, value.tag);
        WriteValue (rel, value.L, GetTagWidth (value.tag));
    }
    return move(BuildReq (id, set_, cmd, rel));
}

ObjectReference::UNUSED::UNUSED (const uint8_t *bytes,uint32_t available)
        : JdwpReader (bytes,available)
{

}

std::string ObjectReference::UNUSED::buildReq (int id)
{
    std::string rel;
    return move(BuildReq (id, set_, cmd, rel));
}

ObjectReference::MonitorInfo::MonitorInfo (
        const uint8_t *bytes,uint32_t available)
        : JdwpReader (bytes,available)
{
    mMonitorInfo = ReadObjectId ();
    mEntryCount = Read4 ();
    mWaiterSize = Read4 ();
    mWaiters.resize (mWaiterSize);
    for(auto i = 0; i < mWaiterSize; i++) {
        mWaiters[i] = ReadObjectId ();
    }
}

std::string ObjectReference::MonitorInfo::buildReq (ObjectId object_id,int id)
{
    std::string rel;
    WriteObjectId (rel, object_id);
    return move(BuildReq (id, set_, cmd, rel));
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

std::string
ObjectReference::InvokeMethod::buildReq (
        ObjectId object_id,ObjectId thread_id,RefTypeId class_id,
        MethodId method_id, const std::vector<JValue> &argValues,
        uint32_t options,int id)
{
    std::string rel;
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
    return move(BuildReq (id, set_, cmd, rel));
}

ObjectReference::DisableCollection::DisableCollection (
        const uint8_t *bytes,uint32_t available)
        : JdwpReader (bytes,available)
{

}

std::string ObjectReference::DisableCollection::buildReq (
        ObjectId object_id,int id)
{
    std::string rel;
    WriteObjectId (rel, object_id);
    return move(BuildReq (id, set_, cmd, rel));
}

ObjectReference::EnableCollection::EnableCollection (
        const uint8_t *bytes,uint32_t available)
        : JdwpReader (bytes,available)
{

}

std::string ObjectReference::EnableCollection::buildReq (
        ObjectId object_id,int id)
{
    std::string rel;
    WriteObjectId (rel, object_id);
    return move(BuildReq (id, set_, cmd, rel));
}

ObjectReference::IsCollected::IsCollected (
        const uint8_t *bytes,uint32_t available)
        : JdwpReader (bytes,available)
{
    mIsCollected = Read1 ();
}

std::string ObjectReference::IsCollected::buildReq (ObjectId object_id,int id)
{
    std::string rel;
    WriteObjectId (rel, object_id);
    return move(BuildReq (id, set_, cmd, rel));
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

std::string ObjectReference::ReferringObjects::buildReq (
        ObjectId object_id,int32_t max_count,int id)
{
    std::string rel;
    WriteObjectId (rel, object_id);
    Write4(rel, max_count);
    return move(BuildReq (id, set_, cmd, rel));
}

StringReference::Value::Value (const uint8_t *bytes,uint32_t available)
        : JdwpReader (bytes,available)
{
    mStr = ReadString ();
}

std::string StringReference::Value::buildReq (ObjectId stringObject,int id)
{
    std::string rel;
    WriteObjectId (rel, stringObject);
    return move(BuildReq (id, set_, cmd, rel));
}

ThreadReference::Name::Name (const uint8_t *bytes,uint32_t available)
        : JdwpReader (bytes,available)
{
    mName = ReadString ();
}

std::string ThreadReference::Name::buildReq (ObjectId thread_id,int id)
{
    std::string rel;
    WriteObjectId (rel, thread_id);
    return move(BuildReq (id, set_, cmd, rel));
}


ThreadReference::Suspend::Suspend (const uint8_t *bytes,uint32_t available)
        : JdwpReader (bytes,available)
{

}

std::string ThreadReference::Suspend::buildReq (ObjectId thread_id,int id)
{
    std::string rel;
    WriteObjectId (rel, thread_id);
    return move(BuildReq (id, set_, cmd, rel));
}

ThreadReference::Resume::Resume (const uint8_t *bytes,uint32_t available)
        : JdwpReader (bytes,available)
{

}

std::string ThreadReference::Resume::buildReq (ObjectId thread_id,int id)
{
    std::string rel;
    WriteObjectId (rel, thread_id);
    return move(BuildReq (id, set_, cmd, rel));
}

ThreadReference::Status::Status (const uint8_t *bytes,uint32_t available)
        : JdwpReader (bytes,available)
{
    mThreadStatus = Read4 ();
    mSuspendStatus = Read4();
}

std::string ThreadReference::Status::buildReq (ObjectId thread_id,int id)
{
    std::string rel;
    WriteObjectId (rel, thread_id);
    return move(BuildReq (id, set_, cmd, rel));
}

ThreadReference::ThreadGroup::ThreadGroup (
        const uint8_t *bytes,uint32_t available)
        : JdwpReader (bytes,available)
{
    mThreadGroupId = ReadObjectId ();
}

std::string ThreadReference::ThreadGroup::buildReq (ObjectId thread_id,int id)
{
    std::string rel;
    WriteObjectId (rel, thread_id);
    return move(BuildReq (id, set_, cmd, rel));
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

std::string ThreadReference::Frames::buildReq (
        ObjectId thread_id,uint32_t start_frame,uint32_t length,int id)
{
    std::string rel;
    WriteObjectId (rel, thread_id);
    Write4 (rel, start_frame);
    Write4 (rel, length);
    return move(BuildReq (id, set_, cmd, rel));
}

ThreadReference::FrameCount::FrameCount (
        const uint8_t *bytes,uint32_t available)
        : JdwpReader (bytes,available)
{
    mFrameCount = Read4 ();
}

std::string ThreadReference::FrameCount::buildReq (ObjectId thread_id,int id)
{
    std::string rel;
    WriteObjectId (rel, thread_id);
    return move(BuildReq (id, set_, cmd, rel));
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


std::string ThreadReference::OwnedMonitors::buildReq (
        ObjectId thread_id,int id)
{
    std::string rel;
    WriteObjectId (rel, thread_id);
    return move(BuildReq (id, set_, cmd, rel));
}

ThreadReference::CurrentContendedMonitor::CurrentContendedMonitor (
        const uint8_t *bytes,uint32_t available)
        : JdwpReader (bytes,available)
{
    mContendedMonitor.tag = (JdwpTag)Read1 ();
    mContendedMonitor.L = ReadObjectId ();
}

std::string ThreadReference::CurrentContendedMonitor::buildReq (
        ObjectId thread_id,int id)
{
    std::string rel;
    WriteObjectId (rel, thread_id);
    return move(BuildReq (id, set_, cmd, rel));
}


ThreadReference::Stop::Stop (const uint8_t *bytes,uint32_t available)
        : JdwpReader (bytes,available)
{

}

std::string ThreadReference::Stop::buildReq (ObjectId thread_id,int id)
{
    std::string rel;
    WriteObjectId (rel, thread_id);
    return move(BuildReq (id, set_, cmd, rel));
}

ThreadReference::Interrupt::Interrupt (const uint8_t *bytes,uint32_t available)
        : JdwpReader (bytes,available)
{

}

std::string ThreadReference::Interrupt::buildReq (ObjectId thread_id,int id)
{
    std::string rel;
    WriteObjectId (rel, thread_id);
    return move(BuildReq (id, set_, cmd, rel));
}

ThreadReference::SuspendCount::SuspendCount (
        const uint8_t *bytes,uint32_t available)
        : JdwpReader (bytes,available)
{
    mSuspendCount = Read4 ();
}

std::string ThreadReference::SuspendCount::buildReq (
        ObjectId thread_id,int id)
{
    std::string rel;
    WriteObjectId (rel, thread_id);
    return move(BuildReq (id, set_, cmd, rel));
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

std::string ThreadReference::OwnedMonitorsStackDepthInfo::buildReq (
        ObjectId thread_id,int id)
{
    std::string rel;
    WriteObjectId (rel, thread_id);
    return move(BuildReq (id, set_, cmd, rel));
}


ThreadReference::ForceEarlyReturn::ForceEarlyReturn (
        const uint8_t *bytes,uint32_t available): JdwpReader (bytes,available)
{

}

std::string ThreadReference::ForceEarlyReturn::buildReq (
        ObjectId thread_id,int id)
{
    std::string rel;
    WriteObjectId (rel, thread_id);
    return move(BuildReq (id, set_, cmd, rel));
}

ThreadGroupReference::ForceEarlyReturn::ForceEarlyReturn (
        const uint8_t *bytes,uint32_t available)
        : JdwpReader (bytes,available)
{
    mThreadGroupName = ReadString ();
}

std::string ThreadGroupReference::ForceEarlyReturn::buildReq (
        ObjectId thread_group_id,int id)
{
    std::string rel;
    WriteObjectId (rel, thread_group_id);
    return move(BuildReq (id, set_, cmd, rel));
}

ThreadGroupReference::Parent::Parent (const uint8_t *bytes,uint32_t available)
        : JdwpReader (bytes,available)
{
    mThreadParentgroup = ReadObjectId ();
}

std::string ThreadGroupReference::Parent::buildReq (
        ObjectId thread_group_id,int id)
{
    std::string rel;
    WriteObjectId (rel, thread_group_id);
    return move(BuildReq (id, set_, cmd, rel));
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

std::string ThreadGroupReference::Children::buildReq (
        ObjectId thread_group_id,int id)
{
    std::string rel;
    WriteObjectId (rel, thread_group_id);
    return move(BuildReq (id, set_, cmd, rel));
}


ArrayReference::Length::Length (const uint8_t *bytes,uint32_t available)
        : JdwpReader (bytes,available)
{
    mLength = Read4 ();
}

std::string ArrayReference::Length::buildReq (ObjectId array_id,int id)
{
    std::string rel;
    WriteObjectId (rel, array_id);
    return move(BuildReq (id, set_, cmd, rel));
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

std::string ArrayReference::GetValues::buildReq (
        ObjectId array_id,uint32_t offset,uint32_t length,int id)
{
    std::string rel;
    WriteObjectId (rel, array_id);
    Write4 (rel, offset);
    Write4 (rel, length);
    return move(BuildReq (id, set_, cmd, rel));
}


ArrayReference::SetValues::SetValues (
        const uint8_t *bytes,uint32_t available)
        : JdwpReader (bytes,available)
{
}

std::string ArrayReference::SetValues::buildReq (
        ObjectId array_id,uint32_t offset,JdwpTag tag,
        const std::vector<JValue> &elements,int id)
{
    std::string rel;
    WriteObjectId (rel, array_id);
    Write4 (rel, offset);
    Write4 (rel, elements.size ());
    auto width = GetTagWidth (tag);
    for(auto it = elements.begin (), itEnd = elements.end ();
        it != itEnd; it++)
    {
        WriteValue (rel,it->L,width);
    }
    return move(BuildReq (id, set_, cmd, rel));
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

std::string ClassLoaderReference::VisibleClasses::buildReq (
        ObjectId classLoaderObject,int id)
{
    std::string rel;
    WriteObjectId (rel, classLoaderObject);
    return move(BuildReq (id, set_, cmd, rel));
}

EventRequest::Set::Set (const uint8_t *bytes,uint32_t available)
        : JdwpReader (bytes,available)
{
    mRequestId = Read4 ();
}

std::string EventRequest::Set::buildReq (int id)
{
    // TODO add request

//    JdwpEventKind event_kind = request.ReadEnum1<JdwpEventKind>("event kind");
//    JdwpSuspendPolicy suspend_policy = request.ReadEnum1<JdwpSuspendPolicy>("suspend policy");
//    int32_t modifier_count = request.ReadSigned32("modifier count");
//
//    CHECK_LT(modifier_count, 256);    /* reasonableness check */
//
//    JdwpEvent* pEvent = EventAlloc(modifier_count);
//    pEvent->eventKind = event_kind;
//    pEvent->suspend_policy = suspend_policy;
//    pEvent->modCount = modifier_count;
//
//    /*
//     * Read modifiers.  Ordering may be significant (see explanation of Count
//     * mods in JDWP doc).
//     */
//    for (int32_t i = 0; i < modifier_count; ++i) {
//        JdwpEventMod& mod = pEvent->mods[i];
//        mod.modKind = request.ReadModKind();
//        switch (mod.modKind) {
//            case MK_COUNT:
//            {
//                // Report once, when "--count" reaches 0.
//                uint32_t count = request.ReadUnsigned32("count");
//                if (count == 0) {
//                    return ERR_INVALID_COUNT;
//                }
//                mod.count.count = count;
//            }
//                break;
//            case MK_CONDITIONAL:
//            {
//                // Conditional on expression.
//                uint32_t exprId = request.ReadUnsigned32("expr id");
//                mod.conditional.exprId = exprId;
//            }
//                break;
//            case MK_THREAD_ONLY:
//            {
//                // Only report events in specified thread.
//                ObjectId thread_id = request.ReadThreadId();
//                mod.threadOnly.threadId = thread_id;
//            }
//                break;
//            case MK_CLASS_ONLY:
//            {
//                // For ClassPrepare, MethodEntry.
//                RefTypeId class_id = request.ReadRefTypeId();
//                mod.classOnly.refTypeId = class_id;
//            }
//                break;
//            case MK_CLASS_MATCH:
//            {
//                // Restrict events to matching classes.
//                // pattern is "java.foo.*", we want "java/foo/*".
//                std::string pattern(request.ReadUtf8String());
//                std::replace(pattern.begin(), pattern.end(), '.', '/');
//                mod.classMatch.classPattern = strdup(pattern.c_str());
//            }
//                break;
//            case MK_CLASS_EXCLUDE:
//            {
//                // Restrict events to non-matching classes.
//                // pattern is "java.foo.*", we want "java/foo/*".
//                std::string pattern(request.ReadUtf8String());
//                std::replace(pattern.begin(), pattern.end(), '.', '/');
//                mod.classExclude.classPattern = strdup(pattern.c_str());
//            }
//                break;
//            case MK_LOCATION_ONLY:
//            {
//                // Restrict certain events based on location.
//                JdwpLocation location = request.ReadLocation();
//                mod.locationOnly.loc = location;
//            }
//                break;
//            case MK_EXCEPTION_ONLY:
//            {
//                // Modifies EK_EXCEPTION events,
//                mod.exceptionOnly.refTypeId = request.ReadRefTypeId();  // null => all exceptions.
//                mod.exceptionOnly.caught = request.ReadEnum1<uint8_t>("caught");
//                mod.exceptionOnly.uncaught = request.ReadEnum1<uint8_t>("uncaught");
//            }
//                break;
//            case MK_FIELD_ONLY:
//            {
//                // For field access/modification events.
//                RefTypeId declaring = request.ReadRefTypeId();
//                FieldId fieldId = request.ReadFieldId();
//                mod.fieldOnly.refTypeId = declaring;
//                mod.fieldOnly.fieldId = fieldId;
//            }
//                break;
//            case MK_STEP:
//            {
//                // For use with EK_SINGLE_STEP.
//                ObjectId thread_id = request.ReadThreadId();
//                uint32_t size = request.ReadUnsigned32("step size");
//                uint32_t depth = request.ReadUnsigned32("step depth");
//                VLOG(jdwp) << StringPrintf("    Step: thread=%#llx", thread_id)
//                           << " size=" << JdwpStepSize(size) << " depth=" << JdwpStepDepth(depth);
//
//                mod.step.threadId = thread_id;
//                mod.step.size = size;
//                mod.step.depth = depth;
//            }
//                break;
//            case MK_INSTANCE_ONLY:
//            {
//                // Report events related to a specific object.
//                ObjectId instance = request.ReadObjectId();
//                mod.instanceOnly.objectId = instance;
//            }
//                break;
//            default:
//                LOG(WARNING) << "GLITCH: unsupported modKind=" << mod.modKind;
//                break;
//        }
//    }
    return std::__cxx11::string ();
}

EventRequest::Clear::Clear (const uint8_t *bytes,uint32_t available)
        : JdwpReader (bytes,available)
{
}

std::string EventRequest::Clear::buildReq (
        JdwpEventKind kind,uint32_t requestId, int id)
{
    std::string rel;
    Write1 (rel, kind);
    Write4 (rel, requestId);
    return move(BuildReq (id, set_, cmd, rel));
}

EventRequest::ClearAllBreakpoints::ClearAllBreakpoints (
        const uint8_t *bytes,uint32_t available)
        : JdwpReader (bytes,available)
{

}

std::string EventRequest::ClearAllBreakpoints::buildReq (int id)
{
    std::string rel;
    return move(BuildReq (id, set_, cmd, rel));
}

StackFrame::GetValues::GetValues (const uint8_t *bytes,uint32_t available)
        : JdwpReader (bytes,available)
{
    mSlotCount = Read4 ();
    mSlots.resize (mSlotCount);
    for(auto i = 0; i < mSlotCount; i++) {
        mSlots[i].tag = (JdwpTag)Read1 ();
        mSlots[i].L = ReadValue (GetTagWidth (mSlots[i].tag));
    }
}

std::string StackFrame::GetValues::buildReq (
        ObjectId thread_id,FrameId frame_id,const std::vector<uint32_t> &slots,
        const std::vector<JdwpTag> &reqSig,int id)
{
    if(slots.size () != reqSig.size ())
        return "";
    std::string rel;
    WriteThreadId (rel, thread_id);
    WriteFrameId (rel, frame_id);
    int count = slots.size ();
    Write4 (rel, count);
    for(auto i = 0; i < count; i++) {
        Write4 (rel, slots[i]);
        Write1 (rel, reqSig[i]);
    }
    return move(BuildReq (id, set_, cmd, rel));
}

StackFrame::SetValues::SetValues (const uint8_t *bytes,uint32_t available)
        : JdwpReader (bytes,available)
{
}

std::string StackFrame::SetValues::buildReq (
        ObjectId thread_id,FrameId frame_id,const std::vector<uint32_t> &slots,
         const std::vector<JValue> &reqSig,int id)
{
    if(slots.size () != reqSig.size ())
        return "";
    std::string rel;
    WriteThreadId (rel, thread_id);
    WriteFrameId (rel, frame_id);
    int count = slots.size ();
    Write4 (rel, count);
    for(auto i = 0; i < count; i++) {
        Write4 (rel, slots[i]);
        Write1 (rel, reqSig[i].tag);
        WriteValue (rel, reqSig[i].L, GetTagWidth (reqSig[i].tag));
    }
    return move(BuildReq (id, set_, cmd, rel));
}


StackFrame::ThisObject::ThisObject (const uint8_t *bytes,uint32_t available)
        : JdwpReader (bytes,available)
{
    mObject.tag = (JdwpTag)Read1 ();
    mObject.L = ReadValue (GetTagWidth (mObject.tag));
}

std::string StackFrame::ThisObject::buildReq (
        ObjectId thread_id,FrameId frame_id,int id)
{
    std::string rel;
    WriteThreadId (rel, thread_id);
    WriteFrameId (rel, frame_id);
    return move(BuildReq (id, set_, cmd, rel));
}


StackFrame::PopFrames::PopFrames (const uint8_t *bytes,uint32_t available)
        : JdwpReader (bytes,available)
{

}

std::string StackFrame::PopFrames::buildReq (
        ObjectId thread_id,FrameId frame_id,int id)
{
    std::string rel;
    WriteThreadId (rel, thread_id);
    WriteFrameId (rel, frame_id);
    return move(BuildReq (id, set_, cmd, rel));
}

ClassObjectReference::ReflectedType::ReflectedType (
        const uint8_t *bytes,uint32_t available)
        : JdwpReader (bytes,available)
{
    mClass.tag = (JdwpTag)Read1 ();
    mClass.L = ReadValue (GetTagWidth (mClass.tag));
}

std::string ClassObjectReference::ReflectedType::buildReq (
        RefTypeId class_object_id,int id)
{
    std::string rel;
    WriteRefTypeId (rel, class_object_id);
    return move(BuildReq (id, set_, cmd, rel));
}

Composite::ReflectedType::ReflectedType (
        const uint8_t *bytes,uint32_t available)
        : JdwpReader (bytes,available)
{

}

std::string Composite::ReflectedType::buildReq (int id)
{
    return std::__cxx11::string ();
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

std::string DDM::Chunk::buildReq (int id)
{
    // TODO Chunk
    return "";
}
