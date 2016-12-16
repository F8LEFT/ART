//===- Op_INVOKE_X_RANGE.h - ART-LEX ----------------------------*- c++ -*-===//
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


#ifndef PROJECT_OP_INVOKE_X_RANGE_H
#define PROJECT_OP_INVOKE_X_RANGE_H
#include "OpCode.h"

namespace Analysis {
    /* invoke-virtual/range {r1 .. r2}, classname->methodname(args)ret
     * invoke-super/range {r1 .. r2}, classname->methodname(args)ret
     * invoke-direct/range {r1 .. r2}, classname->methodname(args)ret
     * invoke-static/range {r1 .. r2}, classname->methodname(args)ret
     * invoke-interface/range {r1 .. r2}, classname->methodname(args)ret
     * */

    class Op_INVOKE_X_RANGE: public OpCode {
    public:
        Op_INVOKE_X_RANGE(Opcode o, StringPool* sp,
                    int reg1, int reg2, std::string &methodClass,
                          std::string &methodName,
                          std::vector<std::string> &methodArg,
                          std::string &methodRet)
                : OpCode (o, sp), r1(reg1), r2(reg2)
        {
            mClass = (*mStringPool)[methodClass];
            mName = (*mStringPool)[methodName];
            mArgs.clear ();
            for(auto &s: methodArg) {
                mArgs.push_back ((*mStringPool)[s]);
            }
            mRetType = (*mStringPool)[methodRet];
        }
        std::string toString() {
            std::string rel = "invoke-";
            switch (op) {
                case OP_INVOKE_VIRTUAL_RANGE:
                    rel += "virtual/range";
                    break;
                case OP_INVOKE_SUPER_RANGE:
                    rel += "super/range";
                    break;
                case OP_INVOKE_DIRECT_RANGE:
                    rel += "direct/range";
                    break;
                case OP_INVOKE_STATIC_RANGE:
                    rel += "static/range";
                    break;
                case OP_INVOKE_INTERFACE_RANGE:
                    rel += "interface/range";
                    break;
                default:
                    break;
            }
            rel += " {" + r1.toString () + " .. " + r2.toString ()+ "}, "
                   + (*mStringPool)[mClass] + "->" + (*mStringPool)[mName];
            rel += "(";
            for(uint32_t i = 0; i < mArgs.size (); i++) {
                rel += (*mStringPool)[mArgs[i]];
            }
            rel += ")";
            rel += (*mStringPool)[mRetType];
            return move(rel);
        }
        RegisterX r1;
        RegisterX r2;
        int mClass;
        int mName;
        std::vector<int> mArgs;
        int mRetType;
        void deleteThis() {
            delete this;
        }
    };
}
#endif //PROJECT_OP_INVOKE_X_RANGE_H
