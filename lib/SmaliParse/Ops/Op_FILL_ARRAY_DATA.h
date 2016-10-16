//===- Op_FILL_ARRAY_DATA.h - ART-LEX ---------------------------*- c++ -*-===//
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

#ifndef PROJECT_OP_FILL_ARRAY_DATA_H
#define PROJECT_OP_FILL_ARRAY_DATA_H

#include "OpCode.h"

namespace Analysis {
    /* fill-array-data rx, :label
     * */

    class Op_FILL_ARRAY_DATA: public OpCode {
    public:
        Op_FILL_ARRAY_DATA(Opcode o, StringPool* sp,
                    int reg, const std::string & l)
                : OpCode (o, sp), rx(reg)
        {
            label = (*mStringPool)[l];
        }
        std::string toString() {
            std::string rel = "fill-array-data";
            rel += " " + rx.toString () + ", :"
                    + (*mStringPool)[label];
            return move(rel);
        }
        RegisterX rx;
        int label;

        void deleteThis() {
            delete this;
        }
    };
}
#endif //PROJECT_OP_FILL_ARRAY_DATA_H
