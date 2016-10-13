//===- Op_SPUT.h - ART-LEX --------------------------------------*- c++ -*-===//
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

#ifndef PROJECT_OP_SPUT_H
#define PROJECT_OP_SPUT_H

#include "OpCode.h"

namespace Analysis {
    /* sput-object vx, classname->fieldname:classtype
     * sput-object-wide vx, classname->fieldname:classtype
     * sput-object-object vx, classname->fieldname:classtype
     * sput-object-boolean vx, classname->fieldname:classtype
     * sput-object-byte vx, classname->fieldname:classtype
     * sput-object-char vx, classname->fieldname:classtype
     * sput-object-short vx, classname->fieldname:classtype
     * */

    class Op_SPUT: public OpCode {
    public:
        Op_SPUT(Opcode o, StringPool* sp,
                int reg, std::string &fieldClass, std::string &fieldName, std::string &fieldType)
                : OpCode (o, sp), r1(reg)
        {
            fClass = (*mStringPool)[fieldClass];
            fName = (*mStringPool)[fieldName];
            fType = (*mStringPool)[fieldType];

        }
        std::string toString() {
            std::string rel = "sput";
            switch (op) {
                case OP_SPUT_WIDE:
                    rel += "-wide";
                    break;
                case OP_SPUT_OBJECT:
                    rel += "-object";
                    break;
                case OP_SPUT_BOOLEAN:
                    rel += "-boolean";
                    break;
                case OP_SPUT_BYTE:
                    rel += "-byte";
                    break;
                case OP_SPUT_CHAR:
                    rel += "-char";
                    break;
                case OP_SPUT_SHORT:
                    rel += "-short";
                    break;
                default:
                    break;
            }
            rel += " " + r1.toString () + ", "
                   + (*mStringPool)[fClass] + "->"
                   + (*mStringPool)[fName] + ":" + (*mStringPool)[fType];
            return move(rel);
        }
        RegisterX r1;
        int fClass;
        int fName;
        int fType;

        void deleteThis() {
            delete this;
        }
    };
}
#endif //PROJECT_OP_SPUT_H
