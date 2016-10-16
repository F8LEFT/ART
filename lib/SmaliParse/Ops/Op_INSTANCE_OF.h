//===- Op_INSTANCE_OF.h - ART-LEX ------------------------------*- c++ -*-===//
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

#ifndef PROJECT_OP_INSTANCE_OF_H
#define PROJECT_OP_INSTANCE_OF_H

#include "OpCode.h"

namespace Analysis {
    /* instance-of r1, r2, classtype
     * */

    class Op_INSTANCE_OF: public OpCode {
    public:
        Op_INSTANCE_OF(Opcode o, StringPool* sp,
                        int reg1, int reg2, const std::string &classtype)
                : OpCode (o, sp), r1(reg1), r2(reg2)
        {
            mClassType = (*mStringPool)[classtype];
        }
        std::string toString() {
            std::string rel = "instance-of";
            rel += " " + r1.toString () + ", " + r2.toString () + ", "
                    + (*mStringPool)[mClassType];
            return move(rel);
        }
        RegisterX r1;
        RegisterX r2;
        int mClassType;
        void deleteThis() {
            delete this;
        }
    };
}
#endif //PROJECT_OP_INSTANCE_OF_H
