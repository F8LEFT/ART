//===- Op_INVOKE.h - ART-LEX ------------------------------*- c++ -*-===//
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

#ifndef PROJECT_OP_INVOKE_H
#define PROJECT_OP_INVOKE_H

#include "OpCode.h"

namespace Analysis {
    /* invoke-virtual {px...}, classname->methodname(args)ret
     * invoke-super {px...}, classname->methodname(args)ret
     * invoke-direct {px...}, classname->methodname(args)ret
     * invoke-static {px...}, classname->methodname(args)ret
     * invoke-interface {px...}, classname->methodname(args)ret
     * */

    class Op_INVOKE: public OpCode {
    public:
        Op_INVOKE(Opcode o, StringPool* sp,
                  std::vector<int>& argXs, std::string &methodClass,
                  std::string &methodName, std::vector<std::string> &methodArg,
                  std::string &methodRet)
                : OpCode (o, sp)
        {
            args.clear ();
            for(auto i : argXs) {
                args.push_back (i);
            }
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
                case OP_INVOKE_VIRTUAL:
                    rel += "virtual";
                    break;
                case OP_INVOKE_SUPER:
                    rel += "super";
                    break;
                case OP_INVOKE_DIRECT:
                    rel += "direct";
                    break;
                case OP_INVOKE_STATIC:
                    rel += "static";
                    break;
                case OP_INVOKE_INTERFACE:
                    rel += "interface";
                    break;
                default:
                    break;
            }
            rel += " {";
            if (!args.empty ()) {
                rel += args[0].toString ();
            }
            for(uint32_t i = 1; i < args.size (); i++) {
                rel += ", " + args[i].toString ();
            }
            rel += std::string("}, ")
                   + (*mStringPool)[mClass] + "->" + (*mStringPool)[mName];
            rel += "(";
            for(uint32_t i = 0; i < mArgs.size (); i++) {
                rel += (*mStringPool)[mArgs[i]];
            }
            rel += ")";
            rel += (*mStringPool)[mRetType];
            return move(rel);
        }

        std::vector<RegisterX> args;        // 寄存器组
        int mClass;
        int mName;
        std::vector<int> mArgs;             // 函数参数
        int mRetType;

        void deleteThis() {
            delete this;
        }
    };
}
#endif //PROJECT_OP_INVOKE_H
