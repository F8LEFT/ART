//===- Op_UNUSED.h - ART-LEX -----------------------------------*- c++ -*-===//
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


#ifndef PROJECT_OP_UNUSED_H
#define PROJECT_OP_UNUSED_H

#include "OpCode.h"

namespace Analysis {
    /* UNUSED
     * */

    class Op_UNUSED: public OpCode {
    public:
        Op_UNUSED(Opcode o, StringPool* sp)
                : OpCode (o, sp)
        {
        }
        std::string toString() {
            std::string rel = "#unused";
            return move(rel);
        }

        void deleteThis() {
            delete this;
        }
    };
}
#endif //PROJECT_OP_UNUSED_H
