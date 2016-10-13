//===- Op_IF_XXZ.h - ART-LEX ----------------------------------*- c++ -*-===//
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

#ifndef PROJECT_OP_IF_XXZ_H
#define PROJECT_OP_IF_XXZ_H

#include "OpCode.h"

namespace Analysis {
    /* if-eqz rx, :label
     * if-nez rx, :label
     * if-ltz rx, :label
     * if-gez rx, :label
     * if-gtz rx, :label
     * if-lez rx, :label
     * */

    class Op_IF_XXZ: public OpCode {
    public:
        Op_IF_XXZ(Opcode o, StringPool* sp,
                  int reg, std::string& l)
                : OpCode (o, sp), rx(reg)
        {
            jmpLabel = (*mStringPool)[l];
        }
        std::string toString() {
            std::string rel = "if-";
            switch (op) {
                case OP_IF_EQZ:
                    rel += "eqz";
                    break;
                case OP_IF_NEZ:
                    rel += "nez";
                    break;
                case OP_IF_LTZ:
                    rel += "ltz";
                    break;
                case OP_IF_GEZ:
                    rel += "gez";
                    break;
                case OP_IF_GTZ:
                    rel += "gtz";
                    break;
                case OP_IF_LEZ:
                    rel += "lez";
                    break;
                default:
                    break;
            }
            rel += " " + rx.toString () + ", :" + (*mStringPool)[jmpLabel];
            return move(rel);
        }

        RegisterX rx;
        int jmpLabel;

        void deleteThis() {
            delete this;
        }
    };
}
#endif //PROJECT_OP_IF_XXZ_H
