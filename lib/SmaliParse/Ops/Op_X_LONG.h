//===- Op_X_LONG.h - ART-LEX -----------------------------------*- c++ -*-===//
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


#ifndef PROJECT_OP_X_LONG_H
#define PROJECT_OP_X_LONG_H
#include "OpCode.h"

namespace Analysis {
    /* add-long r1, r2, r3
     * sub-long r1, r2, r3
     * mul-long r1, r2, r3
     * div-long r1, r2, r3
     * rem-long r1, r2, r3
     * and-long r1, r2, r3
     * or-long r1, r2, r3
     * xor-long r1, r2, r3
     * shl-long r1, r2, r3
     * shr-long r1, r2, r3
     * ushr-long r1, r2, r3
     * */

    class Op_X_LONG: public OpCode {
    public:
        Op_X_LONG(Opcode o, StringPool* sp,
                 int reg1, int reg2, int reg3)
                : OpCode (o, sp), r1(reg1), r2(reg2), r3(reg3)
        {
        }
        std::string toString() {
            std::string rel;
            switch(op) {
                case OP_ADD_LONG:
                    rel = "add-long";
                    break;
                case OP_SUB_LONG:
                    rel = "sub-long";
                    break;
                case OP_MUL_LONG:
                    rel = "mul-long";
                    break;
                case OP_DIV_LONG:
                    rel = "div-long";
                    break;
                case OP_REM_LONG:
                    rel = "rem-long";
                    break;
                case OP_AND_LONG:
                    rel = "and-long";
                    break;
                case OP_OR_LONG:
                    rel = "or-long";
                    break;
                case OP_XOR_LONG:
                    rel = "xor-long";
                    break;
                case OP_SHL_LONG:
                    rel = "shl-long";
                    break;
                case OP_SHR_LONG:
                    rel = "shr-long";
                    break;
                case OP_USHR_LONG:
                    rel = "ushr-long";
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
#endif //PROJECT_OP_X_LONG_H
