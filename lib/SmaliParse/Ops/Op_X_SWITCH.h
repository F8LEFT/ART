//===- Op_X_SWITCH.h - ART-LEX ---------------------------------*- c++ -*-===//
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

#ifndef PROJECT_OP_X_SWITCH_H
#define PROJECT_OP_X_SWITCH_H

#include "OpCode.h"

namespace Analysis {
    /* packed-switch rx, :label
     * sparse-switch rx, :label
     * */

    class Op_X_SWITCH: public OpCode {
    public:
        Op_X_SWITCH(Opcode o, StringPool* sp, int reg, const std::string &l)
                : OpCode (o, sp), rx(reg)
        {
            jmpLabel = (*mStringPool)[l];
        }
        std::string toString() {
            std::string rel;
            switch(op) {
                case OP_PACKED_SWITCH:
                    rel = "packed-switch";
                    break;
                case OP_SPARSE_SWITCH:
                    rel = "sparse-switch";
                    break;
                default:
                    break;
            }
            rel += " " + rx.toString () + ", :"
                    + (*mStringPool)[jmpLabel];
            return move(rel);
        }
        RegisterX rx;
        int jmpLabel;

        void deleteThis() {
            delete this;
        }
    };
}
#endif //PROJECT_OP_X_SWITCH_H
