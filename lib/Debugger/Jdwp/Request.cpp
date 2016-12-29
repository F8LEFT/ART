//===- Request.cpp - ART-DEBUGGER -------------------------------*- C++ -*-===//
//
//                     ANDROID REVERSE TOOLKIT
//
// This file is distributed under the GNU GENERAL PUBLIC LICENSE
// V3 License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
#include "Request.h"

#include "JdwpHeader.h"

#include <QDebug>
#include <QtEndian>
#include <cassert>

using namespace JDWP;

JDWP::Request::Request (const uint8_t *bytes,uint32_t available)
    : JdwpReader(bytes, available), reply(false), valid_(true)
{

    byte_count_ = Read4 ();
    if(byte_count_ < kJDWPHeaderLen || byte_count_ > available) {
        valid_ = false;
        return ;
    }

    id_ = Read4();
    int8_t flags = Read1();
    if ((flags & kJDWPFlagReply) != 0) {
        reply = true;
    }

    command_set_ = Read1();
    command_ = Read1();

    extra.append ((const char*)p_, byte_count_ - kJDWPHeaderLen);
    reset (GetExtra (), GetExtraLen ());

}

const uint8_t *Request::GetExtra () const
{
    return (const uint8_t*)extra.data ();
}

size_t Request::GetExtraLen () const
{
    return extra.length ();
}

QByteArray Request::GetExtraArray() const {
    return extra;
}

bool Request::isValid (const uint8_t *bytes,uint32_t available)
{
    if(available < kJDWPHeaderLen)
        return false;
    uint32_t d = *((uint32_t *) bytes);
    auto pkgSize = qFromBigEndian (d);
    return pkgSize >= kJDWPHeaderLen && pkgSize <= available;
}

size_t Request::GetPackageLength(const uint8_t *bytes,uint32_t available) {
    if(available < kJDWPHeaderLen)
        return 0;
    uint32_t d = *((uint32_t *) bytes);
    auto pkgSize = qFromBigEndian (d);
    if(pkgSize < kJDWPHeaderLen || pkgSize > available) {
        return 0;
    }
    return pkgSize;
}





