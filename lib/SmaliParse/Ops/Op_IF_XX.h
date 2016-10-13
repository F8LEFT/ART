//===- Op_IF.h - ART-LEX ----------------------------------------*- c++ -*-===//
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

#ifndef PROJECT_OP_IF_XX_H
#define PROJECT_OP_IF_XX_H

#include "OpCode.h"

namespace Analysis {
    /* if-eq r1, r2, : label
     * if-ne r1, r2, : label
     * if-lt r1, r2, : label
     * if-ge r1, r2, : label
     * if-gt r1, r2, : label
     * if-le r1, r2, : label
     * */

    class Op_IF_XX: public OpCode {
    public:
        Op_IF_XX(Opcode o, StringPool* sp,
                       int reg1, int reg2, std::string& l)
                : OpCode (o, sp), r1(reg1), r2(reg2)
        {
            jmpLabel = (*mStringPool)[l];
        }
        std::string toString() {
            std::string rel = "if-";
            switch (op) {
                case OP_IF_EQ:
                    rel += "eq";
                    break;
                case OP_IF_NE:
                    rel += "ne";
                    break;
                case OP_IF_LT:
                    rel += "lt";
                    break;
                case OP_IF_GE:
                    rel += "ge";
                    break;
                case OP_IF_GT:
                    rel += "gt";
                    break;
                case OP_IF_LE:
                    rel += "le";
                    break;
                default:
                    break;
            }
            rel += " " + r1.toString () + ", " + r2.toString () + ", :" + (*mStringPool)[jmpLabel];
            return move(rel);
        }
        RegisterX r1;
        RegisterX r2;
        int jmpLabel;

        void deleteThis() {
            delete this;
        }
    };
}
#endif //PROJECT_OP_IF_XX_H
