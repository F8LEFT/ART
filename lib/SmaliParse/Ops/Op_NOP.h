//===- Op_NOP.h - ART-LEX ---------------------------------------*- c++ -*-===//
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


#ifndef PROJECT_OP_NOP_H
#define PROJECT_OP_NOP_H

#include "OpCode.h"

namespace Analysis {
    /* return-void
     * */

    class Op_NOP: public OpCode {
    public:
        Op_NOP(Opcode o, StringPool* sp)
                : OpCode (o, sp)
        {
        }
        std::string toString() {
            std::string rel = "nop";
            return move(rel);
        }

        void deleteThis() {
            delete this;
        }
    };
}
#endif //PROJECT_OP_NOP_H
