//===- Ops.h - ART-LEX ------------------------------------------*- c++ -*-===//
//
//                     ANDROID REVERSE TOOLKIT
//
// This file is distributed under the GNU GENERAL PUBLIC LICENSE
// V3 License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// Ops.h include header that contains all ops
//
//===----------------------------------------------------------------------===//

#ifndef SMALIPARSER_OPS_H
#define SMALIPARSER_OPS_H

#include "OpCode.h"

#include "Op_NOP.h"
#include "Op_MOVE.h"
#include "Op_MOVE_RESULT.h"
#include "Op_MOVE_EXCEPTION.h"
#include "Op_RETURN_VOID.h"
#include "Op_RETURN.h"
#include "Op_CONST.h"
#include "Op_CONST_STRING.h"
#include "Op_CONST_CLASS.h"
#include "Op_MONITOR.h"
#include "Op_CHECK_CAST.h"
#include "Op_INSTANCE_OF.h"
#include "Op_ARRAY_LENGTH.h"
#include "Op_NEW_INSTANCE.h"
#include "Op_NEW_ARRAY.h"
#include "Op_FILLED_NEW_ARRAY.h"
#include "Op_FILL_ARRAY_DATA.h"
#include "Op_THROW.h"
#include "Op_GOTO.h"
#include "Op_X_SWITCH.h"
#include "Op_CMP.h"
#include "Op_IF_XX.h"
#include "Op_IF_XXZ.h"
#include "Op_UNUSED.h"
#include "Op_AGET.h"
#include "Op_APUT.h"
#include "Op_IGET.h"
#include "Op_IPUT.h"
#include "Op_SGET.h"
#include "Op_SPUT.h"
#include "Op_INVOKE.h"
#include "Op_INVOKE_X_RANGE.h"
#include "Op_NEGNOT_X.h"
#include "Op_X_TO_Y.h"
#include "Op_X_INT.h"
#include "Op_X_LONG.h"
#include "Op_X_FLOAT.h"
#include "Op_X_DOUBLE.h"
#include "Op_X_INT_2ADDR.h"
#include "Op_X_LONG_2ADDR.h"
#include "Op_X_FLOAT_2ADDR.h"
#include "Op_X_DOUBLE_2ADDR.h"
#include "Op_X_INT_LIT.h"
//#include "OP_IGET_VOLATILE.h"
//#include "OP_IPUT_VOLATILE.h"
//#include "OP_SGET_VOLATILE.h"
//#include "OP_SPUT_VOLATILE.h"
//#include "OP_IGET_OBJECT_VOLATILE.h"
//#include "OP_IGET_WIDE_VOLATILE.h"
//#include "OP_IPUT_WIDE_VOLATILE.h"
//#include "OP_SGET_WIDE_VOLATILE.h"
//#include "OP_SPUT_WIDE_VOLATILE.h"
//#include "OP_BREAKPOINT.h"
//#include "OP_THROW_VERIFICATION_ERROR.h"
//#include "OP_EXECUTE_INLINE.h"
//#include "OP_EXECUTE_INLINE_RANGE.h"
//#include "OP_INVOKE_OBJECT_INIT_RANGE.h"
//#include "OP_RETURN_VOID_BARRIER.h"
//#include "OP_IGET_QUICK.h"
//#include "OP_IGET_WIDE_QUICK.h"
//#include "OP_IGET_OBJECT_QUICK.h"
//#include "OP_IPUT_QUICK.h"
//#include "OP_IPUT_WIDE_QUICK.h"
//#include "OP_IPUT_OBJECT_QUICK.h"
//#include "OP_INVOKE_VIRTUAL_QUICK.h"
//#include "OP_INVOKE_VIRTUAL_QUICK_RANGE.h"
//#include "OP_INVOKE_SUPER_QUICK.h"
//#include "OP_INVOKE_SUPER_QUICK_RANGE.h"
//#include "OP_IPUT_OBJECT_VOLATILE.h"
//#include "OP_SGET_OBJECT_VOLATILE.h"
//#include "OP_SPUT_OBJECT_VOLATILE.h"
#include "Op_JmpLabel.h"
#include "Op_CATCH.h"
#include "Op_PACKED_SWITCHDATA.h"
#include "Op_ARRAY_DATA.h"
#endif //SMALIPARSER_OPS_H
