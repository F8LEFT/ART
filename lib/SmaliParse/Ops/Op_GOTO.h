//===- Op_GOTO.h - ART-LEX --------------------------------------*- c++ -*-===//
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


#ifndef PROJECT_OP_GOTO_H
#define PROJECT_OP_GOTO_H

#include "OpCode.h"

namespace Analysis {
    /* goto :label
     * goto/16 :label
     * goto/32 :label
     * */

    class Op_GOTO: public OpCode {
    public:
        Op_GOTO(Opcode o, StringPool* sp,
                       std::string& l)
                : OpCode (o, sp)
        {
            jmpLabel = (*mStringPool)[l];
        }
        std::string toString() {
            std::string rel = "goto";
            switch (op) {
                case OP_GOTO_16:
                    rel += "/16";
                    break;
                case OP_GOTO_32:
                    rel += "/32";
                    break;
                default:
                    break;
            }
            rel += std::string(" :") + (*mStringPool)[jmpLabel];
            return move(rel);
        }
        int jmpLabel;

        void deleteThis() {
            delete this;
        }
    };
}
#endif //PROJECT_OP_GOTO_H
