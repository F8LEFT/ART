//===- jdwp.cpp - ART-DEBUGGER ----------------------------------*- C++ -*-===//
//
//                     ANDROID REVERSE TOOLKIT
//
// This file is distributed under the GNU GENERAL PUBLIC LICENSE
// V3 License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
#include "Jdwp/jdwp.h"
#include "jdwp.h"

bool ::JDWP::IsPrimitiveTag (JDWP::JdwpTag tag)
{
    switch (tag) {
        case JDWP::JT_BOOLEAN:
        case JDWP::JT_BYTE:
        case JDWP::JT_CHAR:
        case JDWP::JT_FLOAT:
        case JDWP::JT_DOUBLE:
        case JDWP::JT_INT:
        case JDWP::JT_LONG:
        case JDWP::JT_SHORT:
        case JDWP::JT_VOID:
            return true;
        default:
            return false;
    }
}

size_t JDWP::GetTagWidth(JDWP::JdwpTag tag){
    switch (tag) {
        case JDWP::JT_VOID:
            return 0;
        case JDWP::JT_BYTE:
        case JDWP::JT_BOOLEAN:
            return 1;
        case JDWP::JT_CHAR:
        case JDWP::JT_SHORT:
            return 2;
        case JDWP::JT_FLOAT:
        case JDWP::JT_INT:
            return 4;
        case JDWP::JT_ARRAY:
        case JDWP::JT_OBJECT:
        case JDWP::JT_STRING:
        case JDWP::JT_THREAD:
        case JDWP::JT_THREAD_GROUP:
        case JDWP::JT_CLASS_LOADER:
        case JDWP::JT_CLASS_OBJECT:
            return sizeof(JDWP::ObjectId);
        case JDWP::JT_DOUBLE:
        case JDWP::JT_LONG:
            return 8;
        default:
            return 0;
    }
}

bool JDWP::JdwpLocation::operator==(const JDWP::JdwpLocation &location) {
    return type_tag == location.type_tag
           && class_id == location.class_id
           && method_id == location.method_id
           && dex_pc == location.dex_pc;
}

JDWP::JdwpEventModPad::JdwpEventModPad(JDWP::JdwpEventMod mod) {
    mMod = mod;
    if(mMod.modKind != MK_CLASS_EXCLUDE && mMod.modKind != MK_CLASS_MATCH) {
        return ;
    }
    mArray = mod.classMatch.classPattern;

}

JDWP::JdwpEventModPad::~JdwpEventModPad() {
}

