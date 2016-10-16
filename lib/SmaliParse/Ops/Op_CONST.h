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
     * const/16 rx, num
     * const rx, num
     * const/high16 rx, num
     * const-wide/16 rx, num
     * const-wide/32 rx, num
     * const-wide rx, num
     * const-wide/high16
     * */

    class Op_CONST: public OpCode {
    public:
        Op_CONST(Opcode o, StringPool* sp, int reg, int64_t value)
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
                case OP_CONST_HIGH16:
                    rel += "/high16";
                    break;
                case OP_CONST_WIDE_16:
                    rel += "-wide/16";
                    break;
                case OP_CONST_WIDE_32:
                    rel += "-wide/32";
                    break;
                case OP_CONST_WIDE:
                    rel += "-wide";
                    break;
                case OP_CONST_WIDE_HIGH16:
                    rel += "-wide/high16";
                    break;
                default:
                    break;
            }
            rel += " " + rx.toString () + ", " + formater::int2hexStr (val);
            return move(rel);
        }

        RegisterX rx;
        int64_t val;

        void deleteThis() {
            delete this;
        }
    };
}
#endif //PROJECT_OP_CONST_D_H
