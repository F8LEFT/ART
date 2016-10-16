//===- Op_X_DOUBLE.h - ART-LEX ---------------------------------*- c++ -*-===//
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

#ifndef PROJECT_OP_X_DOUBLE_H
#define PROJECT_OP_X_DOUBLE_H

#include "OpCode.h"

namespace Analysis {
    /* add-double r1, r2, r3
     * sub-double r1, r2, r3
     * mul-double r1, r2, r3
     * div-double r1, r2, r3
     * rem-double r1, r2, r3
     * */

    class Op_X_DOUBLE: public OpCode {
    public:
        Op_X_DOUBLE(Opcode o, StringPool* sp,
                   int reg1, int reg2, int reg3)
                : OpCode (o, sp), r1(reg1), r2(reg2), r3(reg3)
        {
        }
        std::string toString() {
            std::string rel;
            switch(op) {
                case OP_ADD_DOUBLE:
                    rel = "add-double";
                    break;
                case OP_SUB_DOUBLE:
                    rel = "sub-double";
                    break;
                case OP_MUL_DOUBLE:
                    rel = "mul-double";
                    break;
                case OP_DIV_DOUBLE:
                    rel = "div-double";
                    break;
                case OP_REM_DOUBLE:
                    rel = "rem-double";
                    break;
            }
            rel += " " + r1.toString ()
                   + ", " + r2.toString ()
                   + ", " + r3.toString ();
            return move(rel);
        }
        RegisterX r1;
        RegisterX r2;
        RegisterX r3;

        void deleteThis() {
            delete this;
        }
    };
}
#endif //PROJECT_OP_X_DOUBLE_H
