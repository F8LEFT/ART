//===- Op_NEW_INSTANCE.h - ART-LEX -----------------------------*- c++ -*-===//
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


#ifndef PROJECT_OP_NEW_INSTANCE_H
#define PROJECT_OP_NEW_INSTANCE_H

#include "OpCode.h"

namespace Analysis {
    /* new-instance rx, classtype
     * */

    class Op_NEW_INSTANCE: public OpCode {
    public:
        Op_NEW_INSTANCE(Opcode o, StringPool* sp,
                int reg, std::string &className)
                : OpCode (o, sp), rx(reg)
        {
            mClassName = (*mStringPool)[className];
        }
        std::string toString() {
            std::string rel = "new-instance";
            rel += " " + rx.toString () + ", " + (*mStringPool)[mClassName];
            return move(rel);
        }
        RegisterX rx;
        int mClassName;

        void deleteThis() {
            delete this;
        }
    };
}
#endif //PROJECT_OP_NEW_INSTANCE_H
