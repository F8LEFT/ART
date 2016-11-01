//===- Op_NETNOT_X.h - ART-LEX ------------------------------*- c++ -*-===//
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


#ifndef PROJECT_OP_NEGNOT_X_H
#define PROJECT_OP_NEGNOT_X_H

#include "OpCode.h"

namespace Analysis {
    /* neg-int r1, r2
     * not-int r1, r2
     * neg-long r1, r2
     * not-long r1, r2
     * neg-float r1, r2
     * neg-double r1, r2
     * */

    class Op_NEGNOT_X: public OpCode {
    public:
        Op_NEGNOT_X(Opcode o, StringPool* sp,
            int reg1, int reg2)
                : OpCode (o, sp), r1(reg1), r2(reg2)
        {
        }
        std::string toString() {
            std::string rel = "";
            switch(op) {
                case OP_NEG_INT:
                    rel = "neg-int";
                    break;
                case OP_NOT_INT:
                    rel = "not-int";
                    break;
                case OP_NEG_LONG:
                    rel = "neg-long";
                    break;
                case OP_NOT_LONG:
                    rel = "not-long";
                    break;
                case OP_NEG_FLOAT:
                    rel = "neg-float";
                    break;
                case OP_NEG_DOUBLE:
                    rel = "neg-double";
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
#endif //PROJECT_OP_NEGNOT_X_H
