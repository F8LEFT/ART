//===- SmaliDex.h - ART-LEX ------------------------------------*- c++ -*-===//
//
//                     ANDROID REVERSE TOOLKIT
//
// This file is distributed under the GNU GENERAL PUBLIC LICENSE
// V3 License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// SmaliDex store smali data
//
//===----------------------------------------------------------------------===//


#ifndef SMALIPARSER_SMALIDEX_H
#define SMALIPARSER_SMALIDEX_H

#include "utils/StringPool.hpp"
#include <map>

namespace Analysis {
    class SmaliClass;
    class SmaliDex
    {

    private:
        StringPool mStringPool;
        std::map<int, SmaliClass*> mAllClass;
    };
}


#endif //SMALIPARSER_SMALIDEX_H
