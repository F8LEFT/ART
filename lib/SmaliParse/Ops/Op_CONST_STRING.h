//===- Op_CONST_STRING.h - ART-LEX ------------------------------*- c++ -*-===//
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

#ifndef PROJECT_OP_CONST_STRING_H
#define PROJECT_OP_CONST_STRING_H

#include "OpCode.h"

namespace Analysis {
    /* const-string vx, "str"
     * const-string/jumbo vx, "str"
     * */

    class Op_CONST_STRING: public OpCode {
    public:
        Op_CONST_STRING(Opcode o, StringPool* sp,
                        int rx, const std::string& str)
                : OpCode (o, sp), r1(rx)
        {
            s = (*mStringPool)[str];
        }
        std::string toString() {
            std::string rel = "const-string";
            switch (op) {
                case OP_CONST_STRING_JUMBO:
                    rel += "/jumbo";
                    break;
                default:
                    break;
            }
            rel += " " + r1.toString () + ", " + (*mStringPool)[s];
            return move(rel);
         }


        RegisterX r1;
        int s;

        void deleteThis() {
            delete this;
        }
    };
}
#endif //PROJECT_OP_CONST_STRING_H
