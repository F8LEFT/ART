//===- SmaliMethod.cpp - ART-GUI Analysis engine ----------------*- cpp -*-===//
//
//                     ANDROID REVERSE TOOLKIT
//
// This file is distributed under the GNU GENERAL PUBLIC LICENSE
// V3 License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
#include "SmaliMethod.h"
#define NUM_FLAGS   18

QString SmaliMethod::buildAccessFlag() {
    return buildAccessFlag(m_accessflag);
}

QString SmaliMethod::buildAccessFlag(u4 flags) {
    static QString kAccessStrings[] = {
        "PUBLIC",           /* 0x0001 */
        "PRIVATE",          /* 0x0002 */
        "PROTECTED",        /* 0x0004 */
        "STATIC",           /* 0x0008 */
        "FINAL",            /* 0x0010 */
        "SYNCHRONIZED",     /* 0x0020 */
        "BRIDGE",           /* 0x0040 */
        "VARARGS",          /* 0x0080 */
        "NATIVE",           /* 0x0100 */
        "?",                /* 0x0200 */
        "ABSTRACT",         /* 0x0400 */
        "STRICT",           /* 0x0800 */
        "SYNTHETIC",        /* 0x1000 */
        "?",                /* 0x2000 */
        "?",                /* 0x4000 */
        "MIRANDA",          /* 0x8000 */
        "CONSTRUCTOR",      /* 0x10000 */
        "DECLARED_SYNCHRONIZED", /* 0x20000 */
    };
    QString rel;
    for (auto i = 0; i < NUM_FLAGS; i++) {
        if (flags & 0x01) {
            rel += kAccessStrings[i];
            rel.push_back(' ');
        }
        flags >>= 1;
    }
    return rel;
}

u4 SmaliMethod::getAccessFlag(QString flags) {
    static QMap<QString, u4> kAccessMap = {
            {"PUBLIC",          ACC_PUBLIC},
            {"PRIVATE",         ACC_PRIVATE},
            {"PROTECTED",       ACC_PROTECTED},
            {"STATIC",          ACC_STATIC},
            {"FINAL",           ACC_FINAL},
            {"SYNCHRONIZED",    ACC_SYNCHRONIZED},
            {"BRIDGE",          ACC_BRIDGE},
            {"VARARGS",         ACC_VARARGS},
            {"NATIVE",          ACC_NATIVE},
            {"ABSTRACT",        ACC_ABSTRACT},
            {"STRICT",          ACC_STRICT},
            {"SYNTHETIC",       ACC_SYNTHETIC},
            {"CONSTRUCTOR",     ACC_CONSTRUCTOR},
            {"DECLARED_SYNCHRONIZED", ACC_DECLARED_SYNCHRONIZED}
    };

    u4 rel = 0;
    auto flagList = flags.split(' ', QString::SkipEmptyParts);
    for(auto &flag: flagList) {
        auto it = kAccessMap.constFind(flag.toUpper());
        if(it != kAccessMap.constEnd()) {
            rel |= it.value();
        }
    }

    return rel;
}

