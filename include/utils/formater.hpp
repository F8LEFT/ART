//===- formater.hpp - ART-utils ---------------------------------*- c++ -*-===//
//
//                     ANDROID REVERSE TOOLKIT
//
// This file is distributed under the GNU GENERAL PUBLIC LICENSE
// V3 License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// The file defines a formater to format string.
//
//===----------------------------------------------------------------------===//

#pragma once
#include <string>
#include <cassert>
#include "Defs.h"

#define NUM_FLAGS   18

class formater {
public:
    static std::string int2hexStr(int i) {
        char buf[12];
        if(i < 0) {
            sprintf (buf, "-0x%x",-i);
        } else {
            sprintf (buf, "0x%x",i);
        }
        return buf;
    }

    static std::string int2decStr(int i) {
        char buf[12];
        sprintf (buf, "%d", i);
        return buf;
    }

    static std::string getAccessFlagClass(u4 flags) {
        static const char *allFlags[NUM_FLAGS] = {
                "public",           /* 0x0001 -*/
                "private",          /* 0x0002 -*/
                "protected",        /* 0x0004 -*/
                "static",           /* 0x0008 -*/
                "final",            /* 0x0010 -*/
                "?",                /* 0x0020 */
                "?",                /* 0x0040 */
                "?",                /* 0x0080 */
                "?",                /* 0x0100 */
                "interface",        /* 0x0200 -*/
                "abstract",         /* 0x0400 -*/
                "?",                /* 0x0800 */
                "synthetic",        /* 0x1000 -*/
                "annotation",       /* 0x2000 -*/
                "enum",             /* 0x4000 -*/
                "?",                /* 0x8000 */
                "verified",         /* 0x10000 */
                "optimized",        /* 0x20000 */
        };
        return getAccessFlag(flags, allFlags);
    }

    static std::string getAccessFlagMethod(u4 flags) {
        static const char *allFlags[NUM_FLAGS] = {
                "public",           /* 0x0001 -*/
                "private",          /* 0x0002 -*/
                "protected",        /* 0x0004 -*/
                "static",           /* 0x0008 -*/
                "final",            /* 0x0010 -*/
                "synchronized",     /* 0x0020 -*/
                "bridge",           /* 0x0040 -*/
                "varargs",          /* 0x0080 -*/
                "native",           /* 0x0100 -*/
                "?",                /* 0x0200 */
                "abstract",         /* 0x0400 -*/
                "strict",           /* 0x0800 -*/
                "synthetic",        /* 0x1000 -*/
                "?",                /* 0x2000 */
                "?",                /* 0x4000 */
                "miranda",          /* 0x8000 */
                "constructor",      /* 0x10000 -*/
                "declared_synchronized", /* 0x20000 -*/
        };
        return getAccessFlag(flags, allFlags);
    }

    static std::string getAccessFlagField(u4 flags) {
        static const char *allFlags[NUM_FLAGS] = {
                "public",           /* 0x0001 -*/
                "private",          /* 0x0002 -*/
                "protected",        /* 0x0004 -*/
                "static",           /* 0x0008 -*/
                "final",            /* 0x0010 -*/
                "?",                /* 0x0020 */
                "volatile",         /* 0x0040 -*/
                "transient",        /* 0x0080 -*/
                "?",                /* 0x0100 */
                "?",                /* 0x0200 */
                "?",                /* 0x0400 */
                "?",                /* 0x0800 */
                "synthetic",        /* 0x1000 -*/
                "?",                /* 0x2000 */
                "enum",             /* 0x4000 -*/
                "?",                /* 0x8000 */
                "?",                /* 0x10000 */
                "?",                /* 0x20000 */
        };
        return getAccessFlag(flags, allFlags);
    }

private:
    static std::string getAccessFlag(u4 flags, const char *kAccessStrings[18]) {
        if(flags == 0)
            return "";
        std::string rel;
        const char **acceptFlags = kAccessStrings;
        assert (acceptFlags != nullptr);
        int i = 0;
        while(flags != 0) {
            if (flags & 0x01) {
                rel += acceptFlags[i];
                rel += " ";
            }
            flags >>= 1;
            ++i;
        }
        rel.pop_back();
        return move(rel);
    }
};

