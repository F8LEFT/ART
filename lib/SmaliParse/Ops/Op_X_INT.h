//===- Op_X_INT.h - ART-LEX -------------------------------------*- c++ -*-===//
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


#ifndef PROJECT_OP_X_INT_H
#define PROJECT_OP_X_INT_H

#include "OpCode.h"

namespace Analysis {
    /* add-int r1, r2, r3
     * sub-int r1, r2, r3
     * mul-int r1, r2, r3
     * div-int r1, r2, r3
     * rem-int r1, r2, r3
     * and-int r1, r2, r3
     * or-int r1, r2, r3
     * xor-int r1, r2, r3
     * shl-int r1, r2, r3
     * shr-int r1, r2, r3
     * ushr-int r1, r2, r3
     * */

    class Op_X_INT: public OpCode {
    public:
        Op_X_INT(Opcode o, StringPool* sp,
                       int reg1, int reg2, int reg3)
                : OpCode (o, sp), r1(reg1), r2(reg2), r3(reg3)
        {
        }
        std::string toString() {
            std::string rel;
            switch(op) {
                case OP_ADD_INT:
                    rel = "add-int";
                    break;
                case OP_SUB_INT:
                    rel = "sub-int";
                    break;
                case OP_MUL_INT:
                    rel = "mul-int";
                    break;
                case OP_DIV_INT:
                    rel = "div-int";
                    break;
                case OP_REM_INT:
                    rel = "rem-int";
                    break;
                case OP_AND_INT:
                    rel = "and-int";
                    break;
                case OP_OR_INT:
                    rel = "or-int";
                    break;
                case OP_XOR_INT:
                    rel = "xor-int";
                    break;
                case OP_SHL_INT:
                    rel = "shl-int";
                    break;
                case OP_SHR_INT:
                    rel = "shr-int";
                    break;
                case OP_USHR_INT:
                    rel = "ushr-int";
                    break;
                default:
                    break;
            }
            rel += " " + r1.toString () +
                    ", " + r2.toString () +
                    ", " + r3.toString();
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
#endif //PROJECT_OP_X_INT_H
