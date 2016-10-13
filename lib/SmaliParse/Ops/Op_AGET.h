//===- Op_RETURN_VOID.h - ART-LEX ------------------------------*- c++ -*-===//
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



#ifndef PROJECT_OP_AGET_H
#define PROJECT_OP_AGET_H

#include "OpCode.h"

namespace Analysis {
    /* aget r1, r2, r3
     * aget-wide r1, r2, r3
     * aget-object r1, r2, r3
     * aget-boolean r1, r2, r3
     * aget-byte r1, r2, r3
     * aget-char r1, r2, r3
     * aget-short r1, r2, r3
     * */

    class Op_AGET: public OpCode {
    public:
        Op_AGET(Opcode o, StringPool* sp,
                int reg1, int reg2, int reg3)
                : OpCode (o, sp), r1(reg1), r2(reg2), r3(reg3)
        {
        }
        std::string toString() {
            std::string rel = "aget";
            switch (op) {
                case OP_AGET_WIDE:
                    rel += "-wide";
                    break;
                case OP_AGET_OBJECT:
                    rel += "-object";
                    break;
                case OP_AGET_BOOLEAN:
                    rel += "-boolean";
                    break;
                case OP_AGET_BYTE:
                    rel += "-byte";
                    break;
                case OP_AGET_CHAR:
                    rel += "-char";
                    break;
                case OP_AGET_SHORT:
                    rel += "-short";
                    break;
                default:
                    break;
            }
            rel += " " + r1.toString () + ", " + r2.toString ()
                   + ", " + r3.toString ();
            return move (rel);
        }
        RegisterX r1;
        RegisterX r2;
        RegisterX r3;

        void deleteThis() {
            delete this;
        }
    };
}
#endif //PROJECT_OP_AGET_H
