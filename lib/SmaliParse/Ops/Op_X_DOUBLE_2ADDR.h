//===- Op_X_DOUBLE_2ADDR.h - ART-LEX ----------------------------*- c++ -*-===//
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


#ifndef PROJECT_OP_X_DOUBLE_2ADDR_H
#define PROJECT_OP_X_DOUBLE_2ADDR_H

#include "OpCode.h"

namespace Analysis {
    /* add-double/2addr
     * sub-double/2addr
     * mul-double/2addr
     * div-double/2addr
     * rem-double/2addr
     * */

    class Op_X_DOUBLE_2ADDR: public OpCode {
    public:
        Op_X_DOUBLE_2ADDR(Opcode o, StringPool* sp,
                         int reg1, int reg2)
                : OpCode (o, sp), r1(reg1), r2(reg2)
        {
        }
        std::string toString() {
            std::string rel = "";
            switch(op) {
                case OP_ADD_DOUBLE_2ADDR:
                    rel = "add-double/2addr";
                    break;
                case OP_SUB_DOUBLE_2ADDR:
                    rel = "sub-double/2addr";
                    break;
                case OP_MUL_DOUBLE_2ADDR:
                    rel = "mul-double/2addr";
                    break;
                case OP_DIV_DOUBLE_2ADDR:
                    rel = "div-double/2addr";
                    break;
                case OP_REM_DOUBLE_2ADDR:
                    rel = "rem-double/2addr";
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
#endif //PROJECT_OP_X_DOUBLE_2ADDR_H
