//===- Op_APUT.h - ART-LEX --------------------------------------*- c++ -*-===//
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

#ifndef PROJECT_OP_APUT_H
#define PROJECT_OP_APUT_H
#include "OpCode.h"

namespace Analysis {
    /* aput r1, r2, r3
     * aput-wide r1, r2, r3
     * aput-object r1, r2, r3
     * aput-boolean r1, r2, r3
     * aput-byte r1, r2, r3
     * aput-char r1, r2, r3
     * aput-short r1, r2, r3
     * */

    class Op_APUT: public OpCode {
    public:
        Op_APUT(Opcode o, StringPool* sp,
                int reg1, int reg2, int reg3)
                : OpCode (o, sp), r1(reg1), r2(reg2), r3(reg3)
        {
        }
        std::string toString() {
            std::string rel = "aput";
            switch (op) {
                case OP_APUT_WIDE:
                    rel += "-wide";
                    break;
                case OP_APUT_OBJECT:
                    rel += "-object";
                    break;
                case OP_APUT_BOOLEAN:
                    rel += "-boolean";
                    break;
                case OP_APUT_BYTE:
                    rel += "-byte";
                    break;
                case OP_APUT_CHAR:
                    rel += "-char";
                    break;
                case OP_APUT_SHORT:
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
#endif //PROJECT_OP_APUT_H
