//===- Op_THROW.h - ART-LEX ------------------------------*- c++ -*-===//
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

#ifndef PROJECT_OP_THROW_H
#define PROJECT_OP_THROW_H

#include "OpCode.h"

namespace Analysis {
    /* throw rx
     * */

    class Op_THROW: public OpCode {
    public:
        Op_THROW(Opcode o, StringPool* sp, int reg)
                : OpCode (o, sp), rx(reg)
        {
        }
        std::string toString() {
            std::string rel = "throw " + rx.toString();
            return move(rel);
        }
        RegisterX rx;

        void deleteThis() {
            delete this;
        }
    };
}
#endif //PROJECT_OP_THROW_H
