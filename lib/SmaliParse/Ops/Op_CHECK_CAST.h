//===- Op_CHECK_CAST.h - ART-LEX ------------------------------*- c++ -*-===//
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


#ifndef PROJECT_OP_CHECK_CAST_H
#define PROJECT_OP_CHECK_CAST_H

#include "OpCode.h"

namespace Analysis {
    /* check-cast rx, classtype;
     * */

    class Op_CHECK_CAST: public OpCode {
    public:
        Op_CHECK_CAST(Opcode o, StringPool* sp,
                        int reg, const std::string &ct)
                : OpCode (o, sp), rx(reg)
        {
            classtype = (*mStringPool)[ct];
        }
        std::string toString() {
            std::string rel = "check-cast";
            rel += " " + rx.toString () + ", "
                    + (*mStringPool)[classtype];
            return move(rel);
        }
        RegisterX rx;
        int classtype;
        void deleteThis() {
            delete this;
        }
    };
}
#endif //PROJECT_OP_CHECK_CAST_H
