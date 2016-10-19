//===- Op_CATCH.h - ART-LEX -------------------------------------*- c++ -*-===//
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

#ifndef PROJECT_OP_CATCH_H
#define PROJECT_OP_CATCH_H

#include "OpCode.h"

namespace Analysis {
    /* .catch classtype {:labelstart .. :labelend} :label
     * .catchall {:labelstart .. :labelend} :label
     * */

    class Op_CATCH: public OpCode {
    public:
        Op_CATCH(Opcode o, StringPool* sp,
                std::string &expC, std::string &ts, std::string &te,
                 std::string &cs)
                : OpCode (o, sp)
        {
            expClass = (*mStringPool)[expC];
            tryStart = (*mStringPool)[ts];
            tryEnd = (*mStringPool)[te];
            catchStart = (*mStringPool)[cs];
        }
        std::string toString() {
            std::string rel = ".catch";
            switch(op) {
                case OP_CATCH:
                    rel += std::string(" ") + (*mStringPool)[expClass];
                    break;
                case OP_CATCHALL:
                    rel += "all";
                    break;
                default:
                    break;
            }

            rel += std::string(" {:") + (*mStringPool)[tryStart]
                   + " .. :" + (*mStringPool)[tryEnd] + "} :"
                   + (*mStringPool)[catchStart];
            return move(rel);
        }
        int expClass;
        int tryStart;
        int tryEnd;
        int catchStart;

        void deleteThis() {
            delete this;
        }
    };
}
#endif //PROJECT_OP_CATCH_H
