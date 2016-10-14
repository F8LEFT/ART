//===- Op_PackedSwitchDataBeg.h - ART-LEX -----------------------*- c++ -*-===//
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


#ifndef PROJECT_OP_PACKEDSWITCHDATABEG_H
#define PROJECT_OP_PACKEDSWITCHDATABEG_H

#include "OpCode.h"

namespace Analysis {
    /* .packed-switch 0x1
     * */

    class Op_PACKED_SWITCHDATA_BEG: public OpCode {
    public:
        Op_PACKED_SWITCHDATA_BEG(Opcode o, StringPool* sp, int id)
                : OpCode (o, sp)
        {
            md = id;
        }
        std::string toString() {
            std::string rel = ".packed-switch";
            rel += " " + formater::int2hexStr (md);
            return move(rel);
        }
        int md;
        void deleteThis() {
            delete this;
        }
    };
}
#endif //PROJECT_OP_PACKEDSWITCHDATABEG_H
