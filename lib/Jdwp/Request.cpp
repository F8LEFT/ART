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

#include <cassert>

using namespace JDWP;

JDWP::Request::Request (const uint8_t *bytes,uint32_t available)
    : JdwpReader(bytes, available)
{

    byte_count_ = Read4 ();
    if(byte_count_ > available) {
        // TODO Error
        return ;
    }

    id_ = Read4();
    int8_t flags = Read1();
    if ((flags & kJDWPFlagReply) != 0) {
        reply = true;
    }

    command_set_ = Read1();
    command_ = Read1();

    // for jdwp response only
    assert(reply);

}

