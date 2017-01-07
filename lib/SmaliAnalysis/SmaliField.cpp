//===- SmaliField.cpp - ART-GUI Analysis engine -----------------*- cpp -*-===//
//
//                     ANDROID REVERSE TOOLKIT
//
// This file is distributed under the GNU GENERAL PUBLIC LICENSE
// V3 License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

#include "SmaliField.h"

#define NUM_FLAGS   18

QString SmaliField::buildAccessFlag() {
    return buildAccessFlag(m_accessflag);
}

QString SmaliField::buildAccessFlag(u4 flags) {
    static QString kAccessStrings[] = {
         "PUBLIC",           /* 0x0001 */
         "PRIVATE",          /* 0x0002 */
         "PROTECTED",        /* 0x0004 */
         "STATIC",           /* 0x0008 */
         "FINAL",            /* 0x0010 */
         "?",                /* 0x0020 */
         "VOLATILE",         /* 0x0040 */
         "TRANSIENT",        /* 0x0080 */
         "?",                /* 0x0100 */
         "?",                /* 0x0200 */
         "?",                /* 0x0400 */
         "?",                /* 0x0800 */
         "SYNTHETIC",        /* 0x1000 */
         "?",                /* 0x2000 */
         "ENUM",             /* 0x4000 */
         "?",                /* 0x8000 */
         "?",                /* 0x10000 */
         "?",                /* 0x20000 */
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

u4 SmaliField::getAccessFlag(QString flags) {
    static QMap<QString, u4> kAccessMap = {
            {"PUBLIC",          ACC_PUBLIC},
            {"PRIVATE",         ACC_PRIVATE},
            {"PROTECTED",       ACC_PROTECTED},
            {"STATIC",          ACC_STATIC},
            {"FINAL",           ACC_FINAL},
            {"VOLATILE",        ACC_VOLATILE},
            {"TRANSIENT",       ACC_TRANSIENT},
            {"SYNTHETIC",       ACC_SYNTHETIC},
            {"ENUM",            ACC_ENUM}

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
