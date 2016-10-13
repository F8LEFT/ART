//===- Op_RETURN.h - ART-LEX ------------------------------------*- c++ -*-===//
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

#ifndef PROJECT_OP_RETURN_H
#define PROJECT_OP_RETURN_H

#include "OpCode.h"

namespace Analysis {
    /* return rx
     * return-wide rx
     * return-object rx
     * */

    class Op_RETURN: public OpCode {
    public:
        Op_RETURN(Opcode o, StringPool* sp, int reg)
                : OpCode (o, sp), rx(reg)
        {
        }
        std::string toString() {
            std::string rel = "return";
            switch (op) {
                case OP_RETURN_WIDE:
                    rel += "-wide";
                    break;
                case OP_RETURN_OBJECT:
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
#endif //PROJECT_OP_RETURN_H
