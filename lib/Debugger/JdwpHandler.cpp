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
        info.mTypeId = Read8 ();
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


VirtualMachine::AllClasses::AllClasses (const uint8_t *bytes,uint32_t available): JdwpReader (bytes,available)
{
    mSize = Read4 ();
    mInfos.resize (mSize);
    for(int i = 0; i < mSize; i++) {
        auto &info = mInfos[i];

        info.mRefTypeTag = Read1 ();
        info.mTypeId = Read8 ();
        info.mDescriptor = ReadString ();
        info.mStatus = Read4 ();
    }
}

std::string VirtualMachine::AllClasses::buildReq (int id)
{
    std::string rel;
    return move(BuildReq (id, set_, cmd, rel));
}
