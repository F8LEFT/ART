//===- Op_FILLED_NEW_ARRAY.h - ART-LEX --------------------------*- c++ -*-===//
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


#ifndef PROJECT_OP_FILLED_NEW_ARRAY_H
#define PROJECT_OP_FILLED_NEW_ARRAY_H

#include "OpCode.h"

namespace Analysis {
    /* filled-new-array {r1, r2 ...}, type
     * filled-new-array/range {r1 .. r2}, type
     * */

    class Op_FILLED_NEW_ARRAY: public OpCode {
    public:
        Op_FILLED_NEW_ARRAY(Opcode o, StringPool* sp,
                            std::vector<int> r, const std::string& l)
                : OpCode (o, sp)
        {
            regs.clear ();
            for(auto i : r) {
                regs.push_back (i);
            }
            jmplabel = (*mStringPool)[l];
        }
        std::string toString() {
            std::string rel;
            switch(op) {
                case OP_FILLED_NEW_ARRAY:
                    rel = "filled-new-array";
                    rel += " {";
                    if (!regs.empty ()) {
                        rel += regs[0].toString ();
                    }
                    for(int i = 1; i < regs.size (); i++) {
                        rel += ", " + regs[i].toString ();
                    }
                    break;
                case OP_FILLED_NEW_ARRAY_RANGE:
                    rel = "filled-new-array/range";
                    if(regs.size () < 2) {
                        break;
                    }
                    rel += " {" + regs[0].toString () + " .. " + regs[1].toString ();
                    break;
                default:
                    break;
            }
            rel += std::string("}, ")
                   + (*mStringPool)[jmplabel];
            return move(rel);
        }

        std::vector<RegisterX> regs;        // 寄存器组
        int jmplabel;

        void deleteThis() {
            delete this;
        }
    };
}
#endif //PROJECT_OP_FILLED_NEW_ARRAY_H
