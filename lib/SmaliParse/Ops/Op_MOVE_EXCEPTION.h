//===- Op_MOVE_EXCEPTION.h - ART-LEX ----------------------------*- c++ -*-===//
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


#ifndef PROJECT_OP_MOVE_EXCEPTION_H
#define PROJECT_OP_MOVE_EXCEPTION_H

#include "OpCode.h"

namespace Analysis {
    /* move-exception rx
     * */

    class Op_MOVE_EXCEPTION: public OpCode {
    public:
        Op_MOVE_EXCEPTION(Opcode o, StringPool* sp, int reg)
                : OpCode (o, sp), rx(reg)
        {
        }
        std::string toString() {
            std::string rel = "move-exception ";
            rel += rx.toString ();
            return move(rel);
        }
        RegisterX rx;

        void deleteThis() {
            delete this;
        }
    };
}
#endif //PROJECT_OP_MOVE_EXCEPTION_H
