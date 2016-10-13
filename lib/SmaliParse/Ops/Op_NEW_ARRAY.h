//===- Op_NEW_ARRAY.h - ART-LEX ---------------------------------*- c++ -*-===//
//
//                     ANDROID REVERSE TOOLKIT
//
// This file is distributed under the GNU GENERAL PUBLIC LICENSE
// V3 License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// define for dalvik opcode.
//
//===----------------------------------------------------------------------===//

#ifndef PROJECT_OP_NEW_ARRAY_H
#define PROJECT_OP_NEW_ARRAY_H

#include "OpCode.h"

namespace Analysis {
    /* new-array rx, rx, [classType
     * */

    class Op_NEW_ARRAY: public OpCode {
    public:
        Op_NEW_ARRAY(Opcode o, StringPool* sp,
                     int reg1, int reg2, std::string &className)
                : OpCode (o, sp), r1(reg1),  r2(reg2)
        {
            mClassName = (*mStringPool)[className];
        }
        std::string toString() {
            std::string rel = "new-array";
            rel += " " + r1.toString () + ", " + r2.toString () + ", " + (*mStringPool)[mClassName];
            return move (rel);
        }
        RegisterX r1;
        RegisterX r2;
        int mClassName;

        void deleteThis() {
            delete this;
        }
    };
}
#endif //PROJECT_OP_NEW_ARRAY_H
