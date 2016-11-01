//===- Op_X_FLOAT_2ADDR.h - ART-LEX -----------------------------*- c++ -*-===//
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

#ifndef PROJECT_OP_X_FLOAT_2ADDR_H
#define PROJECT_OP_X_FLOAT_2ADDR_H

#include "OpCode.h"

namespace Analysis {
    /* add-float/2addr
     * sub-float/2addr
     * mul-float/2addr
     * div-float/2addr
     * rem-float/2addr
     * */

    class Op_X_FLOAT_2ADDR: public OpCode {
    public:
        Op_X_FLOAT_2ADDR(Opcode o, StringPool* sp,
                        int reg1, int reg2)
                : OpCode (o, sp), r1(reg1), r2(reg2)
        {
        }
        std::string toString() {
            std::string rel = "";
            switch(op) {
                case OP_ADD_FLOAT_2ADDR:
                    rel = "add-float/2addr";
                    break;
                case OP_SUB_FLOAT_2ADDR:
                    rel = "sub-float/2addr";
                    break;
                case OP_MUL_FLOAT_2ADDR:
                    rel = "mul-float/2addr";
                    break;
                case OP_DIV_FLOAT_2ADDR:
                    rel = "div-float/2addr";
                    break;
                case OP_REM_FLOAT_2ADDR:
                    rel = "rem-float/2addr";
                    break;
                default:
                    break;
            }
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
#endif //PROJECT_OP_X_FLOAT_2ADDR_H
