//===- Op_X_INT_LIT.h - ART-LEX --------------------------------*- c++ -*-===//
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

#ifndef PROJECT_OP_X_INT_LIT_H
#define PROJECT_OP_X_INT_LIT_H

#include "OpCode.h"

namespace Analysis {
    /* add-int/lit16 r1, r2, dec
     * rsub-int r1, r2, dec
     * mul-int/lit16 r1, r2, dec
     * div-int/lit16 r1, r2, dec
     * rem-int/lit16 r1, r2, dec
     * and-int/lit16 r1, r2, dec
     * or-int/lit16 r1, r2, dec
     * xor-int/lit16 r1, r2, dec
     * add-int/lit8 r1, r2, dec
     * rsub-int/lit8 r1, r2, dec
     * mul-int/lit8 r1, r2, dec
     * div-int/lit8 r1, r2, dec
     * rem-int/lit8 r1, r2, dec
     * and-int/lit8 r1, r2, dec
     * or-int/lit8 r1, r2, dec
     * xor-int/lit8 r1, r2, dec
     * shl-int/lit8 r1, r2, dec
     * shr-int/lit8 r1, r2, dec
     * ushr-int/lit8 r1, r2, dec
     * */
    class Op_X_INT_LIT: public OpCode {
    public:
        Op_X_INT_LIT(Opcode o, StringPool* sp,
                     int reg1, int reg2, int val)
                : OpCode (o, sp), r1(reg1), r2(reg2), value(val)
        {
        }
        std::string toString() {
            std::string rel;
            switch (op) {
                case OP_ADD_INT_LIT16:
                    rel += "add-int/lit16";
                    break;
                case OP_RSUB_INT:
                    rel += "rsub-int";
                    break;
                case OP_MUL_INT_LIT16:
                    rel += "mul-int/lit16";
                    break;
                case OP_DIV_INT_LIT16:
                    rel += "div-int/lit16";
                    break;
                case OP_REM_INT_LIT16:
                    rel += "rem-int/lit16";
                    break;
                case OP_AND_INT_LIT16:
                    rel += "and-int/lit16";
                    break;
                case OP_OR_INT_LIT16:
                    rel += "or-int/lit16";
                    break;
                case OP_XOR_INT_LIT16:
                    rel += "xor-int/lit16";
                    break;
                case OP_ADD_INT_LIT8:
                    rel += "add-int/lit8";
                    break;
                case OP_RSUB_INT_LIT8:
                    rel += "rsub-int/lit8";
                    break;
                case OP_MUL_INT_LIT8:
                    rel += "mul-int/lit8";
                    break;
                case OP_DIV_INT_LIT8:
                    rel += "div-int/lit8";
                    break;
                case OP_REM_INT_LIT8:
                    rel += "rem-int/lit8";
                    break;
                case OP_AND_INT_LIT8:
                    rel += "and-int/lit8";
                    break;
                case OP_OR_INT_LIT8:
                    rel += "or-int/lit8";
                    break;
                case OP_XOR_INT_LIT8:
                    rel += "xor-int/lit8";
                    break;
                case OP_SHL_INT_LIT8:
                    rel += "shl-int/lit8";
                    break;
                case OP_SHR_INT_LIT8:
                    rel += "shr-int/lit8";
                    break;
                case OP_USHR_INT_LIT8:
                    rel += "ushr-int/lit8";
                    break;
                default:
                    break;
            }
            rel += " " + r1.toString () + ", " + r2.toString () + ", " + formater::int2hexStr (value);
            return move(rel);
        }
        RegisterX r1;
        RegisterX r2;
        int value;
        void deleteThis() {
            delete this;
        }
    };
}
#endif //PROJECT_OP_X_INT_LIT_H
