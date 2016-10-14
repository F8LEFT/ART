//===- Op_PackedSwitchDataEnd.h - ART-LEX -----------------------*- c++ -*-===//
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


#ifndef PROJECT_OP_PACKEDSWITCHDATAEND_H
#define PROJECT_OP_PACKEDSWITCHDATAEND_H

#include "OpCode.h"

namespace Analysis {
    /* .end packed-switch
     * */

    class Op_PACKED_SWITCHDATA_END: public OpCode {
    public:
        Op_PACKED_SWITCHDATA_END(Opcode o, StringPool* sp)
                : OpCode (o, sp)
        {
        }
        std::string toString() {
            std::string rel = ".end packed-switch";
            return move(rel);
        }
        void deleteThis() {
            delete this;
        }
    };
}
#endif //PROJECT_OP_PACKEDSWITCHDATAEND_H
