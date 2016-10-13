//===- Op_CONST_Ds.h - ART-LEX ----------------------------------*- c++ -*-===//
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

#ifndef PROJECT_OP_CONST_D_H
#define PROJECT_OP_CONST_D_H

#include "OpCode.h"

namespace Analysis {
    /* const/4 rx, num
    /* const/16 rx, num
     * */

    class Op_CONST_D: public OpCode {
    public:
        Op_CONST_D(Opcode o, StringPool* sp, int reg, int value)
                : OpCode (o, sp), rx(reg), val(value)
        {
        }
        std::string toString() {
            std::string rel = "const";
            switch (op) {
                case OP_CONST_4:
                    rel += "/4";
                    break;
                case OP_CONST_16:
                    rel += "/16";
                    break;
                default:
                    break;
            }
            rel += " " + rx.toString () + ", " + formater::int2hexStr (val);
            return move(rel);
        }

        RegisterX rx;
        int val;

        void deleteThis() {
            delete this;
        }
    };
}
#endif //PROJECT_OP_CONST_D_H
