//===- Op_MOVE.h - ART-LEX --------------------------------------*- c++ -*-===//
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


#ifndef PROJECT_OP_MOVE_H
#define PROJECT_OP_MOVE_H

#include "OpCode.h"
namespace Analysis {
    /* move r1,r2
     * move/from16 r1,r2
     * move/16 r1,r2
     * move-wide r1,r2
     * move-wide/from16 r1,r2
     * move-wide/16 r1,r2
     * move-object r1,r2
     * move-object/from16 r1,r2
     * move-object/16 r1,r2
     * */
    class Op_MOVE: public OpCode {
    public:
        Op_MOVE(Opcode o, StringPool* sp, int reg1, int reg2)
                : OpCode (o, sp), r1(reg1), r2(reg2)
        {
        }
        std::string toString() {
            std::string rel = "move";
            switch(op) {
                case OP_MOVE_FROM16:
                    rel += "/from16";
                    break;
                case OP_MOVE_16:
                    rel += "/16";
                    break;
                case OP_MOVE_WIDE:
                    rel += "-wide";
                    break;
                case OP_MOVE_WIDE_FROM16:
                    rel += "-wide/from16";
                    break;
                case OP_MOVE_WIDE_16:
                    rel += "-wide/16";
                    break;
                case OP_MOVE_OBJECT:
                    rel += "-object";
                    break;
                case OP_MOVE_OBJECT_FROM16:
                    rel += "-object/from16";
                    break;
                case OP_MOVE_OBJECT_16:
                    rel += "-object/16";
                    break;
                default:
                    break;
            }
            rel += " " + r1.toString () + ", " + r2.toString ();
            return move(rel);
        }
        RegisterX r1;
        RegisterX r2;

        void deleteThis() {
            delete this;
        }
    };
}
#endif //PROJECT_OP_MOVE_H
