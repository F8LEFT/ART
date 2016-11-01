//===- Op_X_TO_Y.h - ART-LEX ------------------------------------*- c++ -*-===//
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


#ifndef PROJECT_OP_X_TO_Y_H
#define PROJECT_OP_X_TO_Y_H

#include "OpCode.h"

namespace Analysis {
    /* int-to-long r1, r2
     * int-to-float r1, r2
     * int-to-double r1, r2
     * long-to-int r1, r2
     * long-to-float r1, r2
     * long-to-double r1, r2
     * float-to-int r1, r2
     * float-to-long r1, r2
     * float-to-double r1, r2
     * double-to-int r1, r2
     * double-to-long r1, r2
     * double-to-float r1, r2
     * int-to-byte r1, r2
     * int-to-char r1, r2
     * int-to-short r1, r2
     * */

    class Op_X_TO_Y: public OpCode {
    public:
        Op_X_TO_Y(Opcode o, StringPool* sp,
                    int reg1, int reg2)
                : OpCode (o, sp), r1(reg1), r2(reg2)
        {
        }
        std::string toString() {
            std::string rel = "";
            switch (op) {
                case OP_INT_TO_LONG:
                    rel = "int-to-long";
                    break;
                case OP_INT_TO_FLOAT:
                    rel = "int-to-float";
                    break;
                case OP_INT_TO_DOUBLE:
                    rel = "int-to-double";
                    break;
                case OP_LONG_TO_INT:
                    rel = "long-to-int";
                    break;
                case OP_LONG_TO_FLOAT:
                    rel = "long-to-float";
                    break;
                case OP_LONG_TO_DOUBLE:
                    rel = "long-to-double";
                    break;
                case OP_FLOAT_TO_INT:
                    rel = "float-to-int";
                    break;
                case OP_FLOAT_TO_LONG:
                    rel = "float-to-long";
                    break;
                case OP_FLOAT_TO_DOUBLE:
                    rel = "float-to-double";
                    break;
                case OP_DOUBLE_TO_INT:
                    rel = "double-to-int";
                    break;
                case OP_DOUBLE_TO_LONG:
                    rel = "double-to-long";
                    break;
                case OP_DOUBLE_TO_FLOAT:
                    rel = "double-to-float";
                    break;
                case OP_INT_TO_BYTE:
                    rel = "int-to-byte";
                    break;
                case OP_INT_TO_CHAR:
                    rel = "int-to-char";
                    break;
                case OP_INT_TO_SHORT:
                    rel = "int-to-short";
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
#endif //PROJECT_OP_X_TO_Y_H
