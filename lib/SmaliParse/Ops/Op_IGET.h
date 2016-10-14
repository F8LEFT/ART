//===- Op_IGET.h - ART-LEX --------------------------------------*- c++ -*-===//
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


#ifndef PROJECT_OP_IGET_H
#define PROJECT_OP_IGET_H
#include "OpCode.h"

namespace Analysis {
    /* iget r1, r2, classname->fieldname:classtype
     * iget-wide r1, r2, classname->fieldname:classtype
     * iget-object r1, r2, classname->fieldname:classtype
     * iget-boolean r1, r2, classname->fieldname:classtype
     * iget-byte r1, r2, classname->fieldname:classtype
     * iget-char r1, r2, classname->fieldname:classtype
     * iget-short r1, r2, classname->fieldname:classtype
     * */

    class Op_IGET: public OpCode {
    public:
        Op_IGET(Opcode o, StringPool* sp,
                int reg1, int reg2, std::string &fieldClass, std::string &fieldName,
                std::string &fieldType)
                : OpCode (o, sp), r1(reg1), r2(reg2)
        {
            fClass = (*mStringPool)[fieldClass];
            fName = (*mStringPool)[fieldName];
            fType = (*mStringPool)[fieldType];
        }
        std::string toString() {
            std::string rel = "iget";
            switch(op) {
                case OP_IGET_WIDE:
                    rel += "-wide";
                    break;
                case OP_IGET_OBJECT:
                    rel += "-object";
                    break;
                case OP_IGET_BOOLEAN:
                    rel += "-boolean";
                    break;
                case OP_IGET_BYTE:
                    rel += "-byte";
                    break;
                case OP_IGET_CHAR:
                    rel += "-char";
                    break;
                case OP_IGET_SHORT:
                    rel += "-short";
                    break;
                default:
                    break;
            }
            rel += " " + r1.toString () + ", " + r2.toString () +", "
                   + (*mStringPool)[fClass] + "->"
                   + (*mStringPool)[fName] + ":" + (*mStringPool)[fType];
            return move(rel);
        }
        RegisterX r1;
        RegisterX r2;
        int fClass;
        int fName;
        int fType;
        void deleteThis() {
            delete this;
        }
    };
}
#endif //PROJECT_OP_IGET_H
