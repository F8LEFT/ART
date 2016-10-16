//===- Op_CONST_CLASS.h - ART-LEX ---------------------------0---*- c++ -*-===//
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

#ifndef PROJECT_OP_CONST_CLASS_H
#define PROJECT_OP_CONST_CLASS_H

#include "OpCode.h"

namespace Analysis {
    /* const-class rx, classtype
     * */

    class Op_CONST_CLASS: public OpCode {
    public:
        Op_CONST_CLASS(Opcode o, StringPool* sp,
                       int reg, const std::string& classtype)
                : OpCode (o, sp), rx(reg)
        {
            mClassType = (*mStringPool)[classtype];
        }
        std::string toString() {
            std::string rel = "const-class";
            rel += " " + rx.toString () + ", "
                    + (*mStringPool)[mClassType];
            return move(rel);
        }
        RegisterX rx;
        int mClassType;
        void deleteThis() {
            delete this;
        }
    };
}
#endif //PROJECT_OP_CONST_CLASS_H
