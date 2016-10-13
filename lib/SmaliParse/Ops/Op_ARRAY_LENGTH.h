//===- Op_ARRAY_LENGTH.h - ART-LEX ------------------------------*- c++ -*-===//
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

#ifndef PROJECT_OP_ARRAY_LENGTH_H
#define PROJECT_OP_ARRAY_LENGTH_H

#include "OpCode.h"

namespace Analysis {
    /* array-length r1, r2
     * */

    class Op_ARRAY_LENGTH: public OpCode {
    public:
        Op_ARRAY_LENGTH(Opcode o, StringPool* sp,
                        int reg1, int reg2)
                : OpCode (o, sp), r1(reg1), r2(reg2)
        {
        }
        std::string toString() {
            std::string rel = "array-length";
            rel += " " + r1.toString () + ", " + r2.toString ();
            return move(rel);
        }
        RegisterX r1;
        RegisterX r2;
        void deleteThis() {
            delete this;
        }
    };
}
#endif //PROJECT_OP_ARRAY_LENGTH_H
