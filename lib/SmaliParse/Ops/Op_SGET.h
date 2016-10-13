//===- Op_SGET.h - ART-LEX -------------------------------------*- c++ -*-===//
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


#ifndef PROJECT_OP_SGET_H
#define PROJECT_OP_SGET_H

#include "OpCode.h"

namespace Analysis {
    /* sget rx, classname->fieldname:classtype;
     * sget-wide rx, classname->fieldname:classtype;
     * sget-object rx, classname->fieldname:classtype;
     * sget-boolean rx, classname->fieldname:classtype;
     * sget-byte rx, classname->fieldname:classtype;
     * sget-char rx, classname->fieldname:classtype;
     * sget-short rx, classname->fieldname:classtype;
     * */

    class Op_SGET: public OpCode {
    public:
        Op_SGET(Opcode o, StringPool* sp,
                int reg, std::string &fieldClass, std::string &fieldName,
                std::string &fieldType)
                : OpCode (o, sp), rx(reg)
        {
            fClass = (*mStringPool)[fieldClass];
            fName = (*mStringPool)[fieldName];
            fType = (*mStringPool)[fieldType];
        }
        std::string toString() {
            std::string rel = "sget";
            switch (op) {
                case OP_SGET_WIDE:
                    rel += "-wide";
                    break;
                case OP_SGET_OBJECT:
                    rel += "-object";
                    break;
                case OP_SGET_BOOLEAN:
                    rel += "-boolean";
                    break;
                case OP_SGET_BYTE:
                    rel += "-byte";
                    break;
                case OP_SGET_CHAR:
                    rel += "-char";
                    break;
                case OP_SGET_SHORT:
                    rel += "-short";
                    break;
                default:
                    break;
            }
            rel += " " + rx.toString () + ", "
                   + (*mStringPool)[fClass] + "->"
                   + (*mStringPool)[fName] + ":" + (*mStringPool)[fType];
            return move(rel);
        }
        RegisterX rx;
        int fClass;
        int fName;
        int fType;
        void deleteThis() {
            delete this;
        }
    };
}
#endif //PROJECT_OP_SGET_H
