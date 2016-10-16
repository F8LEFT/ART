//===- Op_ARRAY_DATA.h - ART-LEX -------------------------------*- c++ -*-===//
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


#ifndef PROJECT_OP_ARRAY_DATA_H
#define PROJECT_OP_ARRAY_DATA_H

// TODO read array-data from smali
#include "OpCode.h"

namespace Analysis {
    /* .array-data len
     * data1
     * data2
     * ...
     * .end array-data
     * */

    class Op_ARRAY_DATA: public OpCode {
    public:
        Op_ARRAY_DATA(Opcode o, StringPool* sp)
                : OpCode (o, sp)
        {
        }
        std::string toString() {
            std::string rel = "return-void";
            return move(rel);
        }

        void deleteThis() {
            delete this;
        }
    };
}
#endif //PROJECT_OP_ARRAY_DATA_H
