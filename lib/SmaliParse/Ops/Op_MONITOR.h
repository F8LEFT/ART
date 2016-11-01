//===- Op_MONITOR.h - ART-LEX ----------------------------------*- c++ -*-===//
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


#ifndef PROJECT_OP_MONITOR_H
#define PROJECT_OP_MONITOR_H

#include "OpCode.h"

namespace Analysis {
    /* monitor-enter rx
     * monitor-exit rx
     * */

    class Op_MONITOR: public OpCode {
    public:
        Op_MONITOR(Opcode o, StringPool* sp, int reg)
                : OpCode (o, sp), rx(reg)
        {
        }
        std::string toString() {
            std::string rel;
            switch(op) {
                case OP_MONITOR_ENTER:
                    rel = "monitor-enter";
                    break;
                case OP_MONITOR_EXIT:
                    rel = "monitor-exit";
                    break;
                default:
                    break;
            }
            rel += " " + rx.toString ();
            return move(rel);
        }
        RegisterX rx;
        void deleteThis() {
            delete this;
        }
    };
}
#endif //PROJECT_OP_MONITOR_H
