//===- JdwpReader.cpp - ART-DEBUGGER ----------------------------*- C++ -*-===//
//
//                     ANDROID REVERSE TOOLKIT
//
// This file is distributed under the GNU GENERAL PUBLIC LICENSE
// V3 License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

#include "Jdwp/JdwpReader.h"
#include <QtEndian>

using namespace JDWP;
JdwpReader::JdwpReader (const uint8_t *bytes,uint32_t available)
        : p_(bytes)
{
    end_ =  bytes + available;
}

void JdwpReader::reset (const uint8_t *bytes,uint32_t available)
{
    p_ = bytes;
    end_ = bytes + available;
}


uint8_t JdwpReader::Read1 ()
{
    if(error)
        return -1;
    if(size() >= 1)
        return *p_++;
    error = true;
    return 0;
}

uint16_t JdwpReader::Read2 ()
{
    if(error)
        return -1;
    if(size() >= 2) {
        uint16_t d = *((uint16_t *) p_);
        uint16_t result = qFromBigEndian (d);;
        p_ += 2;
        return result;
    }
    error = true;
    return 0;

}

uint32_t JdwpReader::Read4 ()
{
    if(error)
        return -1;
    if(size() >= 4) {
        uint32_t d = *((uint32_t *) p_);
        uint32_t result = qFromBigEndian (d);
        p_ += 4;
        return result;
    }
    error = true;
    return 0;
}

uint64_t JdwpReader::Read8 ()
{
    if(error)
        return -1;
    if(size() >= 8 ) {
        uint64_t high = Read4();
        uint64_t low = Read4 ();
        return (high << 32) | low;
    }
    error = true;
    return 0;
}

uint64_t JdwpReader::ReadValue (size_t width)
{
    uint64_t value = 0;
    switch (width) {
        case 0: value = 0; break;
        case 1: value = Read1(); break;
        case 2: value = Read2(); break;
        case 4: value = Read4(); break;
        case 8: value = Read8(); break;
        default: break;
    }
    return value;
}

QByteArray JdwpReader::ReadString ()
{
    if(error)
        return "";
    auto len = Read4 ();
    if(size() >= len) {
        QByteArray rel((char*)p_, len);
        p_+= len;
        return rel;
    }
    error = true;
    return "";
}

JdwpLocation JdwpReader::ReadJdwpLocation ()
{
    JdwpLocation location;
    location.type_tag = (JdwpTypeTag)Read1 ();
    location.class_id = ReadObjectId ();
    location.method_id = ReadMethodId ();
    location.dex_pc = Read8 ();
    return location;
}

