//===- Op_MOVE_RESULT.h - ART-LEX -------------------------------*- c++ -*-===//
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

#ifndef PROJECT_OP_MOVE_RESULT_H
#define PROJECT_OP_MOVE_RESULT_H

#include "OpCode.h"

namespace Analysis {
    /* move-result rx
     * move-result-wide rx
     * move-result-object rx
     * */

    class Op_MOVE_RESULT: public OpCode {
    public:
        Op_MOVE_RESULT(Opcode o, StringPool* sp, int reg)
                : OpCode (o, sp), rx(reg)
        {
        }
        std::string toString() {
            std::string rel = "move-result";
            switch (op) {
                case OP_MOVE_RESULT_WIDE:
                    rel += "-wide";
                    break;
                case OP_MOVE_RESULT_OBJECT:
                    rel += "-object";
                    break;
                default:
                    break;
            }
            rel += " " + rx.toString ();
            return move(rel);
        }

        RegisterX rx;

        void deleteThis() {
            delete this;
        }
    };
}
#endif //PROJECT_OP_MOVE_RESULT_H
