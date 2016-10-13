//===- Op_JmpLabel.h - ART-LEX ----------------------------------*- c++ -*-===//
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


#ifndef PROJECT_OP_JMPLABEL_H
#define PROJECT_OP_JMPLABEL_H

#include "OpCode.h"

namespace Analysis {
    /* : label
     * */

    class Op_JmpLabel: public OpCode {
    public:
        Op_JmpLabel(Opcode o, StringPool* sp, std::string &l)
                : OpCode (o, sp)
        {
            jmpLabel = (*mStringPool)[l];
        }
        std::string toString() {
            std::string rel = ":";
    rel += (*mStringPool)[jmpLabel];
    return move(rel);
        }
        int jmpLabel;

        void deleteThis() {
            delete this;
        }
    };
}
#endif //PROJECT_OP_JMPLABEL_H
