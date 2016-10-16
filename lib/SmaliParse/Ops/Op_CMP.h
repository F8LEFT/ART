//===- Op_CMP.h - ART-LEX ---------------------------------------*- c++ -*-===//
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

#ifndef PROJECT_OP_CMP_H
#define PROJECT_OP_CMP_H
//#include "OP_CMPL_FLOAT.h"
//#include "OP_CMPG_FLOAT.h"
//#include "OP_CMPL_DOUBLE.h"
//#include "OP_CMPG_DOUBLE.h"
//#include "OP_CMP_LONG.h"

#include "OpCode.h"

namespace Analysis {
    /* cmpl-float r1,r2,r3
     * cmpg-float r1,r2,r3
     * cmpl-double r1,r2,r3
     * cmpg-double r1,r2,r3
     * cmp-long r1,r2,r3
     * */

    class Op_CMP: public OpCode {
    public:
        Op_CMP(Opcode o, StringPool* sp,
               int reg1, int reg2, int reg3)
                : OpCode (o, sp), r1(reg1), r2(reg2), r3(reg3)
        {
        }
        std::string toString() {
            std::string rel = "cmp";
            switch(op) {
                case OP_CMPL_FLOAT:
                    rel += "l-float";
                    break;
                case OP_CMPG_FLOAT:
                    rel += "g-float";
                    break;
                case OP_CMPL_DOUBLE:
                    rel += "l-double";
                    break;
                case OP_CMPG_DOUBLE:
                    rel += "g-double";
                    break;
                case OP_CMP_LONG:
                    rel += "-long";
                    break;
                default:
                    break;
            }
            rel += " " + r1.toString () +
                    ", " + r2.toString () +
                    ", " + r3.toString ();
            return move(rel);
        }
        RegisterX r1;
        RegisterX r2;
        RegisterX r3;

        void deleteThis() {
            delete this;
        }
    };
}
#endif //PROJECT_OP_CMP_H
