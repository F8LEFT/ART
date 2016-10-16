//===- Op_X_LONG_2ADDR.h - ART-LEX ------------------------------*- c++ -*-===//
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

#ifndef PROJECT_OP_X_LONG_2ADDR_H
#define PROJECT_OP_X_LONG_2ADDR_H

#include "OpCode.h"

namespace Analysis {
    /* add-long/2addr r1, r2
     * sub-long/2addr r1, r2
     * mul-long/2addr r1, r2
     * div-long/2addr r1, r2
     * rem-long/2addr r1, r2
     * and-long/2addr r1, r2
     * or-long/2addr r1, r2
     * xor-long/2addr r1, r2
     * shl-long/2addr r1, r2
     * shr-long/2addr r1, r2
     * ushr-long/2addr r1, r2
     * */

    class Op_X_LONG_2ADDR: public OpCode {
    public:
        Op_X_LONG_2ADDR(Opcode o, StringPool* sp,
                       int reg1, int reg2)
                : OpCode (o, sp), r1(reg1), r2(reg2)
        {
        }
        std::string toString() {
            std::string rel;
            switch(op) {
                case OP_ADD_LONG_2ADDR:
                    rel = "add-long/2addr";
                    break;
                case OP_SUB_LONG_2ADDR:
                    rel = "sub-long/2addr";
                    break;
                case OP_MUL_LONG_2ADDR:
                    rel = "mul-long/2addr";
                    break;
                case OP_DIV_LONG_2ADDR:
                    rel = "div-long/2addr";
                    break;
                case OP_REM_LONG_2ADDR:
                    rel = "rem-long/2addr";
                    break;
                case OP_AND_LONG_2ADDR:
                    rel = "and-long/2addr";
                    break;
                case OP_OR_LONG_2ADDR:
                    rel = "or-long/2addr";
                    break;
                case OP_XOR_LONG_2ADDR:
                    rel = "xor-long/2addr";
                    break;
                case OP_SHL_LONG_2ADDR:
                    rel = "shl-long/2addr";
                    break;
                case OP_SHR_LONG_2ADDR:
                    rel = "shr-long/2addr";
                    break;
                case OP_USHR_LONG_2ADDR:
                    rel = "ushr-long/2addr";
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

#endif //PROJECT_OP_X_LONG_2ADDR_H
