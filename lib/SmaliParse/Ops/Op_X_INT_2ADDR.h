//===- Op_X_INT_2ADDR.h - ART-LEX ------------------------------*- c++ -*-===//
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


#ifndef PROJECT_OP_X_INT_2ADDR_H
#define PROJECT_OP_X_INT_2ADDR_H

#include "OpCode.h"

namespace Analysis {
    /* add-int/2addr r1, r2
     * sub-int/2addr r1, r2
     * mul-int/2addr r1, r2
     * div-int/2addr r1, r2
     * rem-int/2addr r1, r2
     * and-int/2addr r1, r2
     * or-int/2addr r1, r2
     * xor-int/2addr r1, r2
     * shl-int/2addr r1, r2
     * shr-int/2addr r1, r2
     * ushr-int/2addr r1, r2
     * */

    class Op_X_INT_2ADDR: public OpCode {
    public:
        Op_X_INT_2ADDR(Opcode o, StringPool* sp,
                        int reg1, int reg2)
                : OpCode (o, sp), r1(reg1), r2(reg2)
        {
        }
        std::string toString() {
            std::string rel;
            switch(op) {
                case OP_ADD_INT_2ADDR:
                    rel = "add-int/2addr";
                    break;
                case OP_SUB_INT_2ADDR:
                    rel = "sub-int/2addr";
                    break;
                case OP_MUL_INT_2ADDR:
                    rel = "mul-int/2addr";
                    break;
                case OP_DIV_INT_2ADDR:
                    rel = "div-int/2addr";
                    break;
                case OP_REM_INT_2ADDR:
                    rel = "rem-int/2addr";
                    break;
                case OP_AND_INT_2ADDR:
                    rel = "and-int/2addr";
                    break;
                case OP_OR_INT_2ADDR:
                    rel = "or-int/2addr";
                    break;
                case OP_XOR_INT_2ADDR:
                    rel = "xor-int/2addr";
                    break;
                case OP_SHL_INT_2ADDR:
                    rel = "shl-int/2addr";
                    break;
                case OP_SHR_INT_2ADDR:
                    rel = "shr-int/2addr";
                    break;
                case OP_USHR_INT_2ADDR:
                    rel = "ushr-int/2addr";
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
#endif //PROJECT_OP_X_INT_2ADDR_H
