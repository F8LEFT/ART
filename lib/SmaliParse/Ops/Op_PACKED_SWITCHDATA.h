//===- Op_PackedSwitchData.h - ART-LEX -------------------------*- c++ -*-===//
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


#ifndef PROJECT_OP_PACKEDSWITCHDATA_H
#define PROJECT_OP_PACKEDSWITCHDATA_H

#include "OpCode.h"

namespace Analysis {
    /* return-void
     * */

    class Op_PACKED_SWITCHDATA: public OpCode {
    public:
        Op_PACKED_SWITCHDATA(Opcode o, StringPool* sp, int id)
                : OpCode (o, sp)
        {
            md = id;
        }
        std::string toString() {
            std::string rel = ".packed-switch";
            rel += " " + formater::int2hexStr (md);
            for(auto l : table) {
                rel += "\n";
                rel += (*mStringPool)[l];
            }
            rel += "\n.end packed-switch";
            return move(rel);
        }
        void addLabels(const std::string l) {
            table.push_back ((*mStringPool)[l]);
        }
        int md;

        std::vector<int> table;
        void deleteThis() {
            delete this;
        }
    };
}
#endif //PROJECT_OP_PACKEDSWITCHDATA_H
