//===- Op_X_FLOAT.h - ART-LEX -----------------------------------*- c++ -*-===//
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

#ifndef PROJECT_OP_X_FLOAT_H
#define PROJECT_OP_X_FLOAT_H


#include "OpCode.h"

namespace Analysis {
    /* add-float r1, r2, r3
     * sub-float r1, r2, r3
     * mul-float r1, r2, r3
     * div-float r1, r2, r3
     * rem-float r1, r2, r3
     * */

    class Op_X_FLOAT: public OpCode {
    public:
        Op_X_FLOAT(Opcode o, StringPool* sp,
                int reg1, int reg2, int reg3)
                : OpCode (o, sp), r1(reg1), r2(reg2), r3(reg3)
        {
        }
        std::string toString() {
            std::string rel;
            switch(op) {
                case OP_ADD_FLOAT:
                    rel = "add-float";
                    break;
                case OP_SUB_FLOAT:
                    rel = "sub-float";
                    break;
                case OP_MUL_FLOAT:
                    rel = "mul-float";
                    break;
                case OP_DIV_FLOAT:
                    rel = "div-float";
                    break;
                case OP_REM_FLOAT:
                    rel = "rem-float";
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
#endif //PROJECT_OP_X_FLOAT_H
