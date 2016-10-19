%skeleton "lalr1.cc" /* -*- C++ -*- */
%require "3.0"
%defines
%define parser_class_name { SmaliParser }

%define api.token.constructor
%define api.value.type variant
%define parse.assert
%define api.namespace { Analysis }
%code requires
{
//===- Parser.yy - ART-Parser ---------------------------------*- bison -*-===//
//
//                     ANDROID REVERSE TOOLKIT
//
// This file is distributed under the GNU GENERAL PUBLIC LICENSE
// V3 License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// The file defines a Parser for smali language. Please use
// bison -o SmaliParser.cpp SmaliParser.yy
// to generate parser source file
// or
// bison -v -o SmaliParser.cpp SmaliParser.yy
// to debug.
//===----------------------------------------------------------------------===//
    #include <iostream>
    #include <string>
    #include <vector>
    #include <stdint.h>
    #include "Ops/Ops.h"

    namespace Analysis {
        class SmaliLexer;
        class Interpreter;
    }
}

%code top
{
    #include <iostream>
    #include "SmaliParser.hpp"
    #include "location.hh"
    #include "Interpreter.h"
    #include "SmaliLexer.h"
    #include "utils/Defs.h"

    static Analysis::SmaliParser::symbol_type yylex(Analysis::SmaliLexer &lexer
                                    , Analysis::Interpreter &driver ) {
        return lexer.get_next_token();
    }
    using namespace std;
    using namespace Analysis;
}

%lex-param { Analysis::SmaliLexer &lexer }
%lex-param { Analysis::Interpreter &driver }

%parse-param { Analysis::SmaliLexer &lexer }
%parse-param { Analysis::Interpreter &driver }

%locations
%define parse.trace
%define parse.error verbose

%debug

%define api.token.prefix {TOKEN_}

%token END 0 "end of file";
%token EOL "end of line";
%token <std::string> ERROR "lex error"

%token KEYWORD_BEGIN "begin of keywords"

%token CLASS_DIRECTIVE ".class"
%token SUPER_DIRECTIVE ".super"
%token IMPLEMENTS_DIRECTIVE ".implements"
%token SOURCE_DIRECTIVE ".source"
%token FIELD_DIRECTIVE ".field"
%token END_FIELD_DIRECTIVE ".end field"
%token SUBANNOTATION_DIRECTIVE ".subannotation"
%token END_SUBANNOTATION_DIRECTIVE ".end subannotation"
%token ANNOTATION_DIRECTIVE ".annotation"
%token END_ANNOTATION_DIRECTIVE ".end annotation"
%token ENUM_DIRECTIVE ".enum"
%token METHOD_DIRECTIVE ".method"
%token END_METHOD_DIRECTIVE ".end method"
%token REGISTERS_DIRECTIVE ".registers"
%token LOCALS_DIRECTIVE ".locals"
%token ARRAY_DATA_DIRECTIVE ".array-data"
%token END_ARRAY_DATA_DIRECTIVE ".end array-data"
%token PACKED_SWITCH_DIRECTIVE ".packed-switch"
%token END_PACKED_SWITCH_DIRECTIVE ".end packed-switch"
%token SPARSE_SWITCH_DIRECTIVE ".sparse-switch"
%token END_SPARSE_SWITCH_DIRECTIVE ".end sparse-switch"
%token CATCH_DIRECTIVE ".catch"
%token CATCHALL_DIRECTIVE ".catchall"
%token LINE_DIRECTIVE ".line"
%token PARAMETER_DIRECTIVE ".param"
%token END_PARAMETER_DIRECTIVE ".end param"
%token LOCAL_DIRECTIVE ".local"
%token END_LOCAL_DIRECTIVE ".end local"
%token RESTART_LOCAL_DIRECTIVE ".restart local"
%token PROLOGUE_DIRECTIVE ".prologue"
%token EPILOGUE_DIRECTIVE ".epilogue"

%token KEYWORD_END "end of keywords"

%token NUMBER_BEGIN "begin of numbers"

%token <std::string> POSITIVE_INTEGER_LITERAL "Integer"
%token <std::string> NEGATIVE_INTEGER_LITERAL "- Integer"
%token <std::string> LONG_LITERAL "- Integer L"
%token <std::string> SHORT_LITERAL "- Integer S"
%token <std::string> BYTE_LITERAL "- Integer T"

%token <std::string> FLOAT_LITERAL_OR_ID "FloatOrID F"
%token <std::string> DOUBLE_LITERAL_OR_ID "FloatOrID D"
%token <std::string> FLOAT_LITERAL "Float F"
%token <std::string> DOUBLE_LITERAL "Float D"

%token <int>         BOOL_LITERAL "true|false"
%token               NULL_LITERAL "null"

%token NUMBER_END "end of numbers"

%token <int> FLAG "flag"
%token <int> REGISTER "v(p)x"

%token PARAM_BEGIN "begin of param"

%token <std::string> PARAM_LIST_OR_ID_PRIMITIVE_TYPE "ZBSCIJFDLIT"
%token <std::string> PRIMITIVE_TYPE "ZBSCIJFD"
%token <std::string> CLASS_DESCRIPTOR "Lxxx;"
%token <std::string> ARRAY_TYPE_PREFIX "[["
%token VOID_TYPE "V"

%token PARAM_END "end of param"

%token <std::string> SIMPLE_NAME "simple name"
%token <std::string> MEMBER_NAME "member name"

%token <std::string> STRING_LITERAL "string"
%token <std::string> CHAR_LITERAL "char"

%token MISC_BEGIN

%token <std::string> ANNOTATION_VISIBILITY "build runtime system"
%token <std::string> VERIFICATION_ERROR_TYPE "ver type error"

%token <std::string> INLINE_INDEX "inline@0x"
%token <std::string> VTABLE_INDEX "vtable@0x"
%token <std::string> FIELD_OFFSET "field@0x"

%token MISC_END

%token <std::string> LINE_COMMENT "# comments"

%token OP_BEGIN "begin of opcodes"

%token OP_NOP "nop"
%token OP_MOVE "move"
%token OP_MOVE_FROM16 "move/from16"
%token OP_MOVE_16 "move/16"
%token OP_MOVE_WIDE "move-wide"
%token OP_MOVE_WIDE_FROM16 "move-wide/from16"
%token OP_MOVE_WIDE_16 "move-wide/16"
%token OP_MOVE_OBJECT "move-object"
%token OP_MOVE_OBJECT_FROM16 "move-object/from16"
%token OP_MOVE_OBJECT_16 "move-object/16"
%token OP_MOVE_RESULT "move-result"
%token OP_MOVE_RESULT_WIDE "move-result-wide"
%token OP_MOVE_RESULT_OBJECT "move-result-object"
%token OP_MOVE_EXCEPTION "move-exception"
%token OP_RETURN_VOID "return-void"
%token OP_RETURN "return"
%token OP_RETURN_WIDE "return-wide"
%token OP_RETURN_OBJECT "return-object"
%token OP_CONST_4 "const/4"
%token OP_CONST_16 "const/16"
%token OP_CONST "const"
%token OP_CONST_HIGH16 "const/high16"
%token OP_CONST_WIDE_16 "const-wide/16"
%token OP_CONST_WIDE_32 "const-wide/32"
%token OP_CONST_WIDE "const-wide"
%token OP_CONST_WIDE_HIGH16 "const-wide/high16"
%token OP_CONST_STRING "const-string"
%token OP_CONST_STRING_JUMBO "const-string/jumbo"
%token OP_CONST_CLASS "const-class"
%token OP_MONITOR_ENTER "monitor-enter"
%token OP_MONITOR_EXIT "monitor-exit"
%token OP_CHECK_CAST "check-cast"
%token OP_INSTANCE_OF "instance-of"
%token OP_ARRAY_LENGTH "array-length"
%token OP_NEW_INSTANCE "new-instance"
%token OP_NEW_ARRAY "new-array"
%token OP_FILLED_NEW_ARRAY "filled-new-array"
%token OP_FILLED_NEW_ARRAY_RANGE "filled-new-array/range"
%token OP_FILL_ARRAY_DATA "fill-array-data"
%token OP_THROW "throw"
%token OP_GOTO "goto"
%token OP_GOTO_16 "goto/16"
%token OP_GOTO_32 "goto/32"
%token OP_PACKED_SWITCH "packed-switch"
%token OP_SPARSE_SWITCH "sparse-switch"
%token OP_CMPL_FLOAT "cmpl-float"
%token OP_CMPG_FLOAT "cmpg-float"
%token OP_CMPL_DOUBLE "cmpl-double"
%token OP_CMPG_DOUBLE "cmpg-double"
%token OP_CMP_LONG "cmp-long"
%token OP_IF_EQ "if-eq"
%token OP_IF_NE "if-ne"
%token OP_IF_LT "if-lt"
%token OP_IF_GE "if-ge"
%token OP_IF_GT "if-gt"
%token OP_IF_LE "if-le"
%token OP_IF_EQZ "if-eqz"
%token OP_IF_NEZ "if-nez"
%token OP_IF_LTZ "if-ltz"
%token OP_IF_GEZ "if-gez"
%token OP_IF_GTZ "if-gtz"
%token OP_IF_LEZ "if-lez"
%token OP_UNUSED_3E "unused-3e"
%token OP_UNUSED_3F "unused-3f"
%token OP_UNUSED_40 "unused-40"
%token OP_UNUSED_41 "unused-41"
%token OP_UNUSED_42 "unused-42"
%token OP_UNUSED_43 "unused-43"
%token OP_AGET "aget"
%token OP_AGET_WIDE "aget-wide"
%token OP_AGET_OBJECT "aget-object"
%token OP_AGET_BOOLEAN "aget-boolean"
%token OP_AGET_BYTE "aget-byte"
%token OP_AGET_CHAR "aget-char"
%token OP_AGET_SHORT "aget-short"
%token OP_APUT "aput"
%token OP_APUT_WIDE "aput-wide"
%token OP_APUT_OBJECT "aput-object"
%token OP_APUT_BOOLEAN "aput-boolean"
%token OP_APUT_BYTE "aput-byte"
%token OP_APUT_CHAR "aput-char"
%token OP_APUT_SHORT "aput-short"
%token OP_IGET "iget"
%token OP_IGET_WIDE "iget-wide"
%token OP_IGET_OBJECT "iget-object"
%token OP_IGET_BOOLEAN "iget-boolean"
%token OP_IGET_BYTE "iget-byte"
%token OP_IGET_CHAR "iget-char"
%token OP_IGET_SHORT "iget-short"
%token OP_IPUT "iput"
%token OP_IPUT_WIDE "iput-wide"
%token OP_IPUT_OBJECT "iput-object"
%token OP_IPUT_BOOLEAN "iput-boolean"
%token OP_IPUT_BYTE "iput-byte"
%token OP_IPUT_CHAR "iput-char"
%token OP_IPUT_SHORT "iput-short"
%token OP_SGET "sget"
%token OP_SGET_WIDE "sget-wide"
%token OP_SGET_OBJECT "sget-object"
%token OP_SGET_BOOLEAN "sget-boolean"
%token OP_SGET_BYTE "sget-byte"
%token OP_SGET_CHAR "sget-char"
%token OP_SGET_SHORT "sget-short"
%token OP_SPUT "sput"
%token OP_SPUT_WIDE "sput-wide"
%token OP_SPUT_OBJECT "sput-object"
%token OP_SPUT_BOOLEAN "sput-boolean"
%token OP_SPUT_BYTE "sput-byte"
%token OP_SPUT_CHAR "sput-char"
%token OP_SPUT_SHORT "sput-short"
%token OP_INVOKE_VIRTUAL "invoke-virtual"
%token OP_INVOKE_SUPER "invoke-super"
%token OP_INVOKE_DIRECT "invoke-direct"
%token OP_INVOKE_STATIC "invoke-static"
%token OP_INVOKE_INTERFACE "invoke-interface"
%token OP_UNUSED_73 "unused-73"
%token OP_INVOKE_VIRTUAL_RANGE "invoke-virtual/range"
%token OP_INVOKE_SUPER_RANGE "invoke-super/range"
%token OP_INVOKE_DIRECT_RANGE "invoke-direct/range"
%token OP_INVOKE_STATIC_RANGE "invoke-static/range"
%token OP_INVOKE_INTERFACE_RANGE "invoke-interface/range"
%token OP_UNUSED_79 "unused-79"
%token OP_UNUSED_7A "unused-7a"
%token OP_NEG_INT "neg-int"
%token OP_NOT_INT "not-int"
%token OP_NEG_LONG "neg-long"
%token OP_NOT_LONG "not-long"
%token OP_NEG_FLOAT "neg-float"
%token OP_NEG_DOUBLE "neg-double"
%token OP_INT_TO_LONG "int-to-long"
%token OP_INT_TO_FLOAT "int-to-float"
%token OP_INT_TO_DOUBLE "int-to-double"
%token OP_LONG_TO_INT "long-to-int"
%token OP_LONG_TO_FLOAT "long-to-float"
%token OP_LONG_TO_DOUBLE "long-to-double"
%token OP_FLOAT_TO_INT "float-to-int"
%token OP_FLOAT_TO_LONG "float-to-long"
%token OP_FLOAT_TO_DOUBLE "float-to-double"
%token OP_DOUBLE_TO_INT "double-to-int"
%token OP_DOUBLE_TO_LONG "double-to-long"
%token OP_DOUBLE_TO_FLOAT "double-to-float"
%token OP_INT_TO_BYTE "int-to-byte"
%token OP_INT_TO_CHAR "int-to-char"
%token OP_INT_TO_SHORT "int-to-short"
%token OP_ADD_INT "add-int"
%token OP_SUB_INT "sub-int"
%token OP_MUL_INT "mul-int"
%token OP_DIV_INT "div-int"
%token OP_REM_INT "rem-int"
%token OP_AND_INT "and-int"
%token OP_OR_INT "or-int"
%token OP_XOR_INT "xor-int"
%token OP_SHL_INT "shl-int"
%token OP_SHR_INT "shr-int"
%token OP_USHR_INT "ushr-int"
%token OP_ADD_LONG "add-long"
%token OP_SUB_LONG "sub-long"
%token OP_MUL_LONG "mul-long"
%token OP_DIV_LONG "div-long"
%token OP_REM_LONG "rem-long"
%token OP_AND_LONG "and-long"
%token OP_OR_LONG "or-long"
%token OP_XOR_LONG "xor-long"
%token OP_SHL_LONG "shl-long"
%token OP_SHR_LONG "shr-long"
%token OP_USHR_LONG "ushr-long"
%token OP_ADD_FLOAT "add-float"
%token OP_SUB_FLOAT "sub-float"
%token OP_MUL_FLOAT "mul-float"
%token OP_DIV_FLOAT "div-float"
%token OP_REM_FLOAT "rem-float"
%token OP_ADD_DOUBLE "add-double"
%token OP_SUB_DOUBLE "sub-double"
%token OP_MUL_DOUBLE "mul-double"
%token OP_DIV_DOUBLE "div-double"
%token OP_REM_DOUBLE "rem-double"
%token OP_ADD_INT_2ADDR "add-int/2addr"
%token OP_SUB_INT_2ADDR "sub-int/2addr"
%token OP_MUL_INT_2ADDR "mul-int/2addr"
%token OP_DIV_INT_2ADDR "div-int/2addr"
%token OP_REM_INT_2ADDR "rem-int/2addr"
%token OP_AND_INT_2ADDR "and-int/2addr"
%token OP_OR_INT_2ADDR "or-int/2addr"
%token OP_XOR_INT_2ADDR "xor-int/2addr"
%token OP_SHL_INT_2ADDR "shl-int/2addr"
%token OP_SHR_INT_2ADDR "shr-int/2addr"
%token OP_USHR_INT_2ADDR "ushr-int/2addr"
%token OP_ADD_LONG_2ADDR "add-long/2addr"
%token OP_SUB_LONG_2ADDR "sub-long/2addr"
%token OP_MUL_LONG_2ADDR "mul-long/2addr"
%token OP_DIV_LONG_2ADDR "div-long/2addr"
%token OP_REM_LONG_2ADDR "rem-long/2addr"
%token OP_AND_LONG_2ADDR "and-long/2addr"
%token OP_OR_LONG_2ADDR "or-long/2addr"
%token OP_XOR_LONG_2ADDR "xor-long/2addr"
%token OP_SHL_LONG_2ADDR "shl-long/2addr"
%token OP_SHR_LONG_2ADDR "shr-long/2addr"
%token OP_USHR_LONG_2ADDR "ushr-long/2addr"
%token OP_ADD_FLOAT_2ADDR "add-float/2addr"
%token OP_SUB_FLOAT_2ADDR "sub-float/2addr"
%token OP_MUL_FLOAT_2ADDR "mul-float/2addr"
%token OP_DIV_FLOAT_2ADDR "div-float/2addr"
%token OP_REM_FLOAT_2ADDR "rem-float/2addr"
%token OP_ADD_DOUBLE_2ADDR "add-double/2addr"
%token OP_SUB_DOUBLE_2ADDR "sub-double/2addr"
%token OP_MUL_DOUBLE_2ADDR "mul-double/2addr"
%token OP_DIV_DOUBLE_2ADDR "div-double/2addr"
%token OP_REM_DOUBLE_2ADDR "rem-double/2addr"
%token OP_ADD_INT_LIT16 "add-int/lit16"
%token OP_RSUB_INT "rsub-int"
%token OP_MUL_INT_LIT16 "mul-int/lit16"
%token OP_DIV_INT_LIT16 "div-int/lit16"
%token OP_REM_INT_LIT16 "rem-int/lit16"
%token OP_AND_INT_LIT16 "and-int/lit16"
%token OP_OR_INT_LIT16 "or-int/lit16"
%token OP_XOR_INT_LIT16 "xor-int/lit16"
%token OP_ADD_INT_LIT8 "add-int/lit8"
%token OP_RSUB_INT_LIT8 "rsub-int/lit8"
%token OP_MUL_INT_LIT8 "mul-int/lit8"
%token OP_DIV_INT_LIT8 "div-int/lit8"
%token OP_REM_INT_LIT8 "rem-int/lit8"
%token OP_AND_INT_LIT8 "and-int/lit8"
%token OP_OR_INT_LIT8 "or-int/lit8"
%token OP_XOR_INT_LIT8 "xor-int/lit8"
%token OP_SHL_INT_LIT8 "shl-int/lit8"
%token OP_SHR_INT_LIT8 "shr-int/lit8"
%token OP_USHR_INT_LIT8 "ushr-int/lit8"
%token OP_IGET_VOLATILE "+iget-volatile"
%token OP_IPUT_VOLATILE "+iput-volatile"
%token OP_SGET_VOLATILE "+sget-volatile"
%token OP_SPUT_VOLATILE "+sput-volatile"
%token OP_IGET_OBJECT_VOLATILE "+iget-object-volatile"
%token OP_IGET_WIDE_VOLATILE "+iget-wide-volatile"
%token OP_IPUT_WIDE_VOLATILE "+iput-wide-volatile"
%token OP_SGET_WIDE_VOLATILE "+sget-wide-volatile"
%token OP_SPUT_WIDE_VOLATILE "+sput-wide-volatile"
%token OP_BREAKPOINT "^breakpoint"
%token OP_THROW_VERIFICATION_ERROR "^throw-verification-error"
%token OP_EXECUTE_INLINE "+execute-inline"
%token OP_EXECUTE_INLINE_RANGE "+execute-inline/range"
%token OP_INVOKE_OBJECT_INIT_RANGE "+invoke-object-init/range"
%token OP_RETURN_VOID_BARRIER "+return-void-barrier"
%token OP_IGET_QUICK "+iget-quick"
%token OP_IGET_WIDE_QUICK "+iget-wide-quick"
%token OP_IGET_OBJECT_QUICK "+iget-object-quick"
%token OP_IPUT_QUICK "+iput-quick"
%token OP_IPUT_WIDE_QUICK "+iput-wide-quick"
%token OP_IPUT_OBJECT_QUICK "+iput-object-quick"
%token OP_INVOKE_VIRTUAL_QUICK "+invoke-virtual-quick"
%token OP_INVOKE_VIRTUAL_QUICK_RANGE "+invoke-virtual-quick/range"
%token OP_INVOKE_SUPER_QUICK "+invoke-super-quick"
%token OP_INVOKE_SUPER_QUICK_RANGE "+invoke-super-quick/range"
%token OP_IPUT_OBJECT_VOLATILE "+iput-object-volatile"
%token OP_SGET_OBJECT_VOLATILE "+sget-object-volatile"
%token OP_SPUT_OBJECT_VOLATILE "+sput-object-volatile"
%token OP_UNUSED_FF "unused-ff"

%token OP_END "end of opcodes"

%token SYMBOL_BEGIN "begin of symbol"

%token DOTDOT ".."
%token ARROW "->"
%token EQUAL "="
%token COLON ":"
%token COMMA ","
%token OPEN_BRACE "{"
%token CLOSE_BRACE "}"
%token OPEN_PAREN "("
%token CLOSE_PAREN ")"

%token SYMBOL_END "end of symbol"

%type <int> exp classdef superdef srcdef fielddef methoddef
%type <int> registers
%type <std::string> comment;
%type <int> flags;
%type <std::vector<std::string>> args;
%type <std::vector<int>> regs;
%type <OpCode*> instruction;
%type <std::string> jmplabel;
%type <long long int> integer "integer";
%type <std::string> classtype "classtype"
%type <std::string> classtypeOrArray "[classtype"
%type <std::string> namestring "field or class name"
%type <std::string> INTEGER_LITERAL "integer-str"

%start program

%%

program :
          %empty
        | program EOL
        | program comment
        | program exp
        | program error EOL {yyerrok; driver.mLexer->yyBegin(0);}
        ;

exp : classdef
    | superdef
    | srcdef
    | fielddef
    | methoddef
    | registers
    | instruction {$$ = 1; driver.addOpcode($1);}
    | END_METHOD_DIRECTIVE {$$ = 1; driver.endMethod();}
     ;


classdef : CLASS_DIRECTIVE flags CLASS_DESCRIPTOR { $$ = 1;
        driver.setClassDefine($2, $3);
    } ;

superdef : SUPER_DIRECTIVE CLASS_DESCRIPTOR { $$ = 1;
        driver.setSuperDefine($2);
    };

srcdef : SOURCE_DIRECTIVE STRING_LITERAL { $$ = 1;
        driver.setSourceDefine($2);
    };

fielddef: FIELD_DIRECTIVE flags namestring COLON classtypeOrArray { $$ = 1;
        driver.addField($3, $2, $5);
    };

methoddef: METHOD_DIRECTIVE flags namestring OPEN_PAREN args CLOSE_PAREN classtypeOrArray { $$ = 1;
        driver.addMethod($3, $2, $7, $5);
    };

flags: %empty {$$ = 0;}
    | FLAG {
        $$ = $1;
    }
    | flags FLAG {
        $$ = $1;
        $$ |= $2;
    }
    ;

namestring :
      SIMPLE_NAME { $$ = $1; }
    | MEMBER_NAME { $$ = $1; }
    ;

classtype:
      CLASS_DESCRIPTOR { $$ = $1; }
    | PRIMITIVE_TYPE { $$ = $1; }
    | PARAM_LIST_OR_ID_PRIMITIVE_TYPE { $$ = $1; }
    | VOID_TYPE { $$ = "V"; }
    ;

classtypeOrArray:
      classtype { $$ = $1; }
    | ARRAY_TYPE_PREFIX classtype { $$ = $1 + $2; }
    ;


args: %empty { $$ = std::vector<std::string>();}
    | classtypeOrArray {
        $$ = std::vector<std::string>();
        $$.push_back($1);
    }
    | args classtypeOrArray {
        $$ = $1;
        $$.push_back($2);
    }
    ;

regs: %empty { $$ = std::vector<int>();}
    | REGISTER {
        $$ = std::vector<int>();
        $$.push_back($1);
    }
    | regs COMMA REGISTER {
        $$ = $1;
        $$.push_back($3);
    }
    ;

comment : LINE_COMMENT {
        $$ = $1;
    }
    ;

    /*      define a method */
registers : REGISTERS_DIRECTIVE integer {
        driver.setCurMethodRegSize($2);
     }
    | LOCALS_DIRECTIVE integer {
        // TODO Register size should be integer + argsize
        driver.setCurMethodRegSize($2);
     }
    ;


jmplabel : COLON namestring {
        $$ = $2;
    }

integer : POSITIVE_INTEGER_LITERAL {
        $$ = driver.parseLongInt($1);
     }
    | NEGATIVE_INTEGER_LITERAL {
        $$ = driver.parseLongInt($1);
     }
    | LONG_LITERAL {
        $$ = driver.parseLongInt($1);
     }
    | SHORT_LITERAL {
        $$ = driver.parseLongInt($1);
     }
    | BYTE_LITERAL {
        $$ = driver.parseLongInt($1);
     }
    ;

INTEGER_LITERAL :
     POSITIVE_INTEGER_LITERAL { $$ = $1; }
    | NEGATIVE_INTEGER_LITERAL { $$ = $1; }
    ;


instruction :
     OP_NOP {
       $$ = new Op_NOP(OP_NOP, driver.stringPool());
    }
   | OP_MOVE REGISTER COMMA REGISTER {
       $$ = new Op_MOVE(OP_MOVE, driver.stringPool(), $2, $4);
    }
   | OP_MOVE_FROM16 REGISTER COMMA REGISTER {
       $$ = new Op_MOVE(OP_MOVE_FROM16, driver.stringPool(), $2, $4);
    }
   | OP_MOVE_16 REGISTER COMMA REGISTER {
       $$ = new Op_MOVE(OP_MOVE_16, driver.stringPool(), $2, $4);
    }
   | OP_MOVE_WIDE REGISTER COMMA REGISTER {
       $$ = new Op_MOVE(OP_MOVE_WIDE, driver.stringPool(), $2, $4);
    }
   | OP_MOVE_WIDE_FROM16 REGISTER COMMA REGISTER {
       $$ = new Op_MOVE(OP_MOVE_WIDE_FROM16, driver.stringPool(), $2, $4);
    }
   | OP_MOVE_WIDE_16 REGISTER COMMA REGISTER {
       $$ = new Op_MOVE(OP_MOVE_WIDE_16, driver.stringPool(), $2, $4);
    }
   | OP_MOVE_OBJECT REGISTER COMMA REGISTER {
       $$ = new Op_MOVE(OP_MOVE_OBJECT, driver.stringPool(), $2, $4);
    }
   | OP_MOVE_OBJECT_FROM16 REGISTER COMMA REGISTER {
       $$ = new Op_MOVE(OP_MOVE_OBJECT_FROM16, driver.stringPool(), $2, $4);
    }
   | OP_MOVE_OBJECT_16 REGISTER COMMA REGISTER {
       $$ = new Op_MOVE(OP_MOVE_OBJECT_16, driver.stringPool(), $2, $4);
    }
   | OP_MOVE_RESULT REGISTER {
      $$ = new Op_MOVE_RESULT(OP_MOVE_RESULT, driver.stringPool(), $2);
    }
   | OP_MOVE_RESULT_WIDE REGISTER {
      $$ = new Op_MOVE_RESULT(OP_MOVE_RESULT_WIDE, driver.stringPool(), $2);
    }
   | OP_MOVE_RESULT_OBJECT REGISTER {
      $$ = new Op_MOVE_RESULT(OP_MOVE_RESULT_OBJECT, driver.stringPool(), $2);
    }
   | OP_MOVE_EXCEPTION REGISTER {
       $$ = new Op_MOVE_EXCEPTION(OP_MOVE_EXCEPTION, driver.stringPool(), $2);
    }
   | OP_RETURN_VOID {
        $$ = new Op_RETURN_VOID(OP_RETURN_VOID, driver.stringPool());
    }
   | OP_RETURN REGISTER {
      $$ = new Op_RETURN(OP_RETURN, driver.stringPool(), $2);
    }
   | OP_RETURN_WIDE REGISTER {
      $$ = new Op_RETURN(OP_RETURN_WIDE, driver.stringPool(), $2);
    }
   | OP_RETURN_OBJECT REGISTER {
      $$ = new Op_RETURN(OP_RETURN_OBJECT, driver.stringPool(), $2);
    }
   | OP_CONST_4 REGISTER COMMA integer{
        $$ = new Op_CONST(OP_CONST_4, driver.stringPool(), $2, $4);
    }
   | OP_CONST_16 REGISTER COMMA integer{
        $$ = new Op_CONST(OP_CONST_16, driver.stringPool(), $2, $4);
    }
   | OP_CONST REGISTER COMMA integer{
        $$ = new Op_CONST(OP_CONST, driver.stringPool(), $2, $4);
    }
   | OP_CONST_HIGH16 REGISTER COMMA INTEGER_LITERAL{
        auto number = $4.substr (0, $4.length () - 4);
        $$ = new Op_CONST(OP_CONST_HIGH16, driver.stringPool(), $2,
                         strtoll(number.c_str(), 0, 16));

    }
   | OP_CONST_WIDE_16 REGISTER COMMA integer{
        $$ = new Op_CONST(OP_CONST_WIDE_16, driver.stringPool(), $2, $4);
    }
   | OP_CONST_WIDE_32 REGISTER COMMA integer{
        $$ = new Op_CONST(OP_CONST_WIDE_32, driver.stringPool(), $2, $4);
    }
   | OP_CONST_WIDE REGISTER COMMA integer{
        $$ = new Op_CONST(OP_CONST_WIDE, driver.stringPool(), $2, $4);
    }
   | OP_CONST_WIDE_HIGH16 REGISTER COMMA LONG_LITERAL{
        auto number = $4.substr (0, $4.length () - 13);
        $$ = new Op_CONST(OP_CONST_WIDE_HIGH16, driver.stringPool(), $2,
                        strtoll(number.c_str(), 0, 16));
    }
   | OP_CONST_STRING REGISTER COMMA STRING_LITERAL {
       $$ = new Op_CONST_STRING(OP_CONST_STRING, driver.stringPool(), $2, $4);
    }
   | OP_CONST_STRING_JUMBO REGISTER COMMA STRING_LITERAL {
       $$ = new Op_CONST_STRING(OP_CONST_STRING_JUMBO, driver.stringPool(), $2, $4);
    }
   | OP_CONST_CLASS REGISTER COMMA classtypeOrArray {
       $$ = new Op_CONST_CLASS(OP_CONST_CLASS, driver.stringPool(), $2, $4);
    }
   | OP_MONITOR_ENTER REGISTER {
       $$ = new Op_MONITOR(OP_MONITOR_ENTER, driver.stringPool(), $2);
    }
   | OP_MONITOR_EXIT REGISTER {
       $$ = new Op_MONITOR(OP_MONITOR_EXIT, driver.stringPool(), $2);
    }
   | OP_CHECK_CAST REGISTER COMMA classtypeOrArray {
       $$ = new Op_CHECK_CAST(OP_CHECK_CAST, driver.stringPool(), $2, $4);
    }
   | OP_INSTANCE_OF REGISTER COMMA REGISTER COMMA classtypeOrArray {
       $$ = new Op_INSTANCE_OF(OP_INSTANCE_OF, driver.stringPool(), $2, $4, $6);
   }
   | OP_ARRAY_LENGTH REGISTER COMMA REGISTER {
       $$ = new Op_ARRAY_LENGTH(OP_ARRAY_LENGTH, driver.stringPool(), $2, $4);
    }
   | OP_NEW_INSTANCE REGISTER COMMA classtypeOrArray {
        $$ = new Op_NEW_INSTANCE(OP_NEW_INSTANCE, driver.stringPool(), $2, $4);
    }
   | OP_NEW_ARRAY REGISTER COMMA REGISTER COMMA classtypeOrArray {
       $$ = new Op_NEW_ARRAY(OP_NEW_ARRAY, driver.stringPool(), $2, $4, $6);
    }
   | OP_FILLED_NEW_ARRAY OPEN_BRACE regs CLOSE_BRACE COMMA classtypeOrArray {
       $$ = new Op_FILLED_NEW_ARRAY(OP_FILLED_NEW_ARRAY, driver.stringPool(), $3, $6);
    }
   | OP_FILLED_NEW_ARRAY_RANGE OPEN_BRACE REGISTER DOTDOT REGISTER CLOSE_BRACE COMMA classtypeOrArray {
       std::vector<int> regs;
       regs.push_back($3);
       regs.push_back($5);
       $$ = new Op_FILLED_NEW_ARRAY(OP_FILLED_NEW_ARRAY_RANGE, driver.stringPool(), regs, $8);
    }
   | OP_FILL_ARRAY_DATA REGISTER COMMA jmplabel {
       $$ = new Op_FILL_ARRAY_DATA(OP_FILL_ARRAY_DATA, driver.stringPool(), $2, $4);
    }
   | OP_THROW REGISTER {
       $$ = new Op_THROW(OP_THROW, driver.stringPool(), $2);
    }
   | OP_GOTO jmplabel {
       $$ = new Op_GOTO(OP_GOTO, driver.stringPool(), $2);
    }
   | OP_GOTO_16 jmplabel {
       $$ = new Op_GOTO(OP_GOTO_16, driver.stringPool(), $2);
    }
   | OP_GOTO_32 jmplabel {
       $$ = new Op_GOTO(OP_GOTO_32, driver.stringPool(), $2);
    }
   | OP_PACKED_SWITCH REGISTER COMMA jmplabel {
       $$ = new Op_X_SWITCH(OP_PACKED_SWITCH, driver.stringPool(), $2, $4);
    }
   | OP_SPARSE_SWITCH REGISTER COMMA jmplabel {
       $$ = new Op_X_SWITCH(OP_SPARSE_SWITCH, driver.stringPool(), $2, $4);
    }
   | OP_CMPL_FLOAT REGISTER COMMA REGISTER COMMA REGISTER {
       $$ = new Op_CMP(OP_CMPL_FLOAT, driver.stringPool(), $2, $4, $6);
    }
   | OP_CMPG_FLOAT REGISTER COMMA REGISTER COMMA REGISTER {
       $$ = new Op_CMP(OP_CMPG_FLOAT, driver.stringPool(), $2, $4, $6);
    }
   | OP_CMPL_DOUBLE REGISTER COMMA REGISTER COMMA REGISTER {
       $$ = new Op_CMP(OP_CMPL_DOUBLE, driver.stringPool(), $2, $4, $6);
    }
   | OP_CMPG_DOUBLE REGISTER COMMA REGISTER COMMA REGISTER {
       $$ = new Op_CMP(OP_CMPG_DOUBLE, driver.stringPool(), $2, $4, $6);
    }
   | OP_CMP_LONG REGISTER COMMA REGISTER COMMA REGISTER {
       $$ = new Op_CMP(OP_CMP_LONG, driver.stringPool(), $2, $4, $6);
    }
   | OP_IF_EQ REGISTER COMMA REGISTER COMMA jmplabel {
       $$ = new Op_IF_XX(OP_IF_EQ, driver.stringPool(), $2, $4, $6);
    }
   | OP_IF_NE REGISTER COMMA REGISTER COMMA jmplabel {
       $$ = new Op_IF_XX(OP_IF_NE, driver.stringPool(), $2, $4, $6);
    }
   | OP_IF_LT REGISTER COMMA REGISTER COMMA jmplabel {
       $$ = new Op_IF_XX(OP_IF_LT, driver.stringPool(), $2, $4, $6);
    }
   | OP_IF_GE REGISTER COMMA REGISTER COMMA jmplabel {
       $$ = new Op_IF_XX(OP_IF_GE, driver.stringPool(), $2, $4, $6);
    }
   | OP_IF_GT REGISTER COMMA REGISTER COMMA jmplabel {
       $$ = new Op_IF_XX(OP_IF_GT, driver.stringPool(), $2, $4, $6);
    }
   | OP_IF_LE REGISTER COMMA REGISTER COMMA jmplabel {
       $$ = new Op_IF_XX(OP_IF_LE, driver.stringPool(), $2, $4, $6);
    }
   | OP_IF_EQZ REGISTER COMMA jmplabel{
      $$ = new Op_IF_XXZ(OP_IF_EQZ, driver.stringPool(), $2, $4);
    }
   | OP_IF_NEZ REGISTER COMMA jmplabel{
      $$ = new Op_IF_XXZ(OP_IF_NEZ, driver.stringPool(), $2, $4);
    }
   | OP_IF_LTZ REGISTER COMMA jmplabel{
      $$ = new Op_IF_XXZ(OP_IF_LTZ, driver.stringPool(), $2, $4);
    }
   | OP_IF_GEZ REGISTER COMMA jmplabel{
      $$ = new Op_IF_XXZ(OP_IF_GEZ, driver.stringPool(), $2, $4);
    }
   | OP_IF_GTZ REGISTER COMMA jmplabel{
      $$ = new Op_IF_XXZ(OP_IF_GTZ, driver.stringPool(), $2, $4);
    }
   | OP_IF_LEZ REGISTER COMMA jmplabel{
      $$ = new Op_IF_XXZ(OP_IF_LEZ, driver.stringPool(), $2, $4);
    }
   | OP_UNUSED_3E
   | OP_UNUSED_3F
   | OP_UNUSED_40
   | OP_UNUSED_41
   | OP_UNUSED_42
   | OP_UNUSED_43
   | OP_AGET REGISTER COMMA REGISTER COMMA REGISTER {
       $$ = new Op_AGET(OP_AGET, driver.stringPool(), $2, $4, $6);
    }
   | OP_AGET_WIDE REGISTER COMMA REGISTER COMMA REGISTER {
       $$ = new Op_AGET(OP_AGET_WIDE, driver.stringPool(), $2, $4, $6);
    }
   | OP_AGET_OBJECT REGISTER COMMA REGISTER COMMA REGISTER {
       $$ = new Op_AGET(OP_AGET_OBJECT, driver.stringPool(), $2, $4, $6);
    }
   | OP_AGET_BOOLEAN REGISTER COMMA REGISTER COMMA REGISTER {
       $$ = new Op_AGET(OP_AGET_BOOLEAN, driver.stringPool(), $2, $4, $6);
    }
   | OP_AGET_BYTE REGISTER COMMA REGISTER COMMA REGISTER {
       $$ = new Op_AGET(OP_AGET_BYTE, driver.stringPool(), $2, $4, $6);
    }
   | OP_AGET_CHAR REGISTER COMMA REGISTER COMMA REGISTER {
       $$ = new Op_AGET(OP_AGET_CHAR, driver.stringPool(), $2, $4, $6);
    }
   | OP_AGET_SHORT REGISTER COMMA REGISTER COMMA REGISTER {
       $$ = new Op_AGET(OP_AGET_SHORT, driver.stringPool(), $2, $4, $6);
    }
   | OP_APUT REGISTER COMMA REGISTER COMMA REGISTER {
       $$ = new Op_APUT(OP_APUT, driver.stringPool(), $2, $4, $6);
    }
   | OP_APUT_WIDE REGISTER COMMA REGISTER COMMA REGISTER {
       $$ = new Op_APUT(OP_APUT_WIDE, driver.stringPool(), $2, $4, $6);
    }
   | OP_APUT_OBJECT REGISTER COMMA REGISTER COMMA REGISTER {
       $$ = new Op_APUT(OP_APUT_OBJECT, driver.stringPool(), $2, $4, $6);
    }
   | OP_APUT_BOOLEAN REGISTER COMMA REGISTER COMMA REGISTER {
       $$ = new Op_APUT(OP_APUT_BOOLEAN, driver.stringPool(), $2, $4, $6);
    }
   | OP_APUT_BYTE REGISTER COMMA REGISTER COMMA REGISTER {
       $$ = new Op_APUT(OP_APUT_BYTE, driver.stringPool(), $2, $4, $6);
    }
   | OP_APUT_CHAR REGISTER COMMA REGISTER COMMA REGISTER {
       $$ = new Op_APUT(OP_APUT_CHAR, driver.stringPool(), $2, $4, $6);
    }
   | OP_APUT_SHORT REGISTER COMMA REGISTER COMMA REGISTER {
       $$ = new Op_APUT(OP_APUT_SHORT, driver.stringPool(), $2, $4, $6);
    }
   | OP_IGET REGISTER COMMA REGISTER COMMA classtypeOrArray ARROW namestring COLON classtypeOrArray {
       $$ = new Op_IGET(OP_IGET, driver.stringPool(), $2, $4, $6, $8, $10);
    }
   | OP_IGET_WIDE REGISTER COMMA REGISTER COMMA classtypeOrArray ARROW namestring COLON classtypeOrArray {
       $$ = new Op_IGET(OP_IGET_WIDE, driver.stringPool(), $2, $4, $6, $8, $10);
    }
   | OP_IGET_OBJECT REGISTER COMMA REGISTER COMMA classtypeOrArray ARROW namestring COLON classtypeOrArray {
       $$ = new Op_IGET(OP_IGET_OBJECT, driver.stringPool(), $2, $4, $6, $8, $10);
    }
   | OP_IGET_BOOLEAN REGISTER COMMA REGISTER COMMA classtypeOrArray ARROW namestring COLON classtypeOrArray {
       $$ = new Op_IGET(OP_IGET_BOOLEAN, driver.stringPool(), $2, $4, $6, $8, $10);
    }
   | OP_IGET_BYTE REGISTER COMMA REGISTER COMMA classtypeOrArray ARROW namestring COLON classtypeOrArray {
       $$ = new Op_IGET(OP_IGET_BYTE, driver.stringPool(), $2, $4, $6, $8, $10);
    }
   | OP_IGET_CHAR REGISTER COMMA REGISTER COMMA classtypeOrArray ARROW namestring COLON classtypeOrArray {
       $$ = new Op_IGET(OP_IGET_CHAR, driver.stringPool(), $2, $4, $6, $8, $10);
    }
   | OP_IGET_SHORT REGISTER COMMA REGISTER COMMA classtypeOrArray ARROW namestring COLON classtypeOrArray {
       $$ = new Op_IGET(OP_IGET_SHORT, driver.stringPool(), $2, $4, $6, $8, $10);
    }
   | OP_IPUT REGISTER COMMA REGISTER COMMA classtypeOrArray ARROW namestring COLON classtypeOrArray {
       $$ = new Op_IPUT(OP_IPUT, driver.stringPool(), $2, $4, $6, $8, $10);
    }
   | OP_IPUT_WIDE REGISTER COMMA REGISTER COMMA classtypeOrArray ARROW namestring COLON classtypeOrArray {
       $$ = new Op_IPUT(OP_IPUT_WIDE, driver.stringPool(), $2, $4, $6, $8, $10);
    }
   | OP_IPUT_OBJECT REGISTER COMMA REGISTER COMMA classtypeOrArray ARROW namestring COLON classtypeOrArray {
       $$ = new Op_IPUT(OP_IPUT_OBJECT, driver.stringPool(), $2, $4, $6, $8, $10);
    }
   | OP_IPUT_BOOLEAN REGISTER COMMA REGISTER COMMA classtypeOrArray ARROW namestring COLON classtypeOrArray {
       $$ = new Op_IPUT(OP_IPUT_BOOLEAN, driver.stringPool(), $2, $4, $6, $8, $10);
    }
   | OP_IPUT_BYTE REGISTER COMMA REGISTER COMMA classtypeOrArray ARROW namestring COLON classtypeOrArray {
       $$ = new Op_IPUT(OP_IPUT_BYTE, driver.stringPool(), $2, $4, $6, $8, $10);
    }
   | OP_IPUT_CHAR REGISTER COMMA REGISTER COMMA classtypeOrArray ARROW namestring COLON classtypeOrArray {
       $$ = new Op_IPUT(OP_IPUT_CHAR, driver.stringPool(), $2, $4, $6, $8, $10);
    }
   | OP_IPUT_SHORT REGISTER COMMA REGISTER COMMA classtypeOrArray ARROW namestring COLON classtypeOrArray {
       $$ = new Op_IPUT(OP_IPUT_SHORT, driver.stringPool(), $2, $4, $6, $8, $10);
    }
   | OP_SGET REGISTER COMMA classtypeOrArray ARROW namestring COLON classtypeOrArray {
       $$ = new Op_SGET(OP_SGET, driver.stringPool(), $2, $4, $6, $8);
    }
   | OP_SGET_WIDE REGISTER COMMA classtypeOrArray ARROW namestring COLON classtypeOrArray {
       $$ = new Op_SGET(OP_SGET_WIDE, driver.stringPool(), $2, $4, $6, $8);
    }
   | OP_SGET_OBJECT REGISTER COMMA classtypeOrArray ARROW namestring COLON classtypeOrArray {
       $$ = new Op_SGET(OP_SGET_OBJECT, driver.stringPool(), $2, $4, $6, $8);
    }
   | OP_SGET_BOOLEAN REGISTER COMMA classtypeOrArray ARROW namestring COLON classtypeOrArray {
       $$ = new Op_SGET(OP_SGET_BOOLEAN, driver.stringPool(), $2, $4, $6, $8);
    }
   | OP_SGET_BYTE REGISTER COMMA classtypeOrArray ARROW namestring COLON classtypeOrArray {
       $$ = new Op_SGET(OP_SGET_BYTE, driver.stringPool(), $2, $4, $6, $8);
    }
   | OP_SGET_CHAR REGISTER COMMA classtypeOrArray ARROW namestring COLON classtypeOrArray {
       $$ = new Op_SGET(OP_SGET_CHAR, driver.stringPool(), $2, $4, $6, $8);
    }
   | OP_SGET_SHORT REGISTER COMMA classtypeOrArray ARROW namestring COLON classtypeOrArray {
       $$ = new Op_SGET(OP_SGET_SHORT, driver.stringPool(), $2, $4, $6, $8);
    }
   | OP_SPUT REGISTER COMMA classtypeOrArray ARROW namestring COLON classtypeOrArray {
       $$ = new Op_SPUT(OP_SPUT, driver.stringPool(), $2, $4, $6, $8);
    }
   | OP_SPUT_WIDE REGISTER COMMA classtypeOrArray ARROW namestring COLON classtypeOrArray {
       $$ = new Op_SPUT(OP_SPUT_WIDE, driver.stringPool(), $2, $4, $6, $8);
    }
   | OP_SPUT_OBJECT REGISTER COMMA classtypeOrArray ARROW namestring COLON classtypeOrArray {
       $$ = new Op_SPUT(OP_SPUT_OBJECT, driver.stringPool(), $2, $4, $6, $8);
    }
   | OP_SPUT_BOOLEAN REGISTER COMMA classtypeOrArray ARROW namestring COLON classtypeOrArray {
       $$ = new Op_SPUT(OP_SPUT_BOOLEAN, driver.stringPool(), $2, $4, $6, $8);
    }
   | OP_SPUT_BYTE REGISTER COMMA classtypeOrArray ARROW namestring COLON classtypeOrArray {
       $$ = new Op_SPUT(OP_SPUT_BYTE, driver.stringPool(), $2, $4, $6, $8);
    }
   | OP_SPUT_CHAR REGISTER COMMA classtypeOrArray ARROW namestring COLON classtypeOrArray {
       $$ = new Op_SPUT(OP_SPUT_CHAR, driver.stringPool(), $2, $4, $6, $8);
    }
   | OP_SPUT_SHORT REGISTER COMMA classtypeOrArray ARROW namestring COLON classtypeOrArray {
       $$ = new Op_SPUT(OP_SPUT_SHORT, driver.stringPool(), $2, $4, $6, $8);
    }
   | OP_INVOKE_VIRTUAL OPEN_BRACE regs CLOSE_BRACE COMMA classtypeOrArray ARROW namestring OPEN_PAREN args CLOSE_PAREN classtypeOrArray {
       $$ = new Op_INVOKE(OP_INVOKE_VIRTUAL, driver.stringPool(), $3, $6, $8, $10, $12);
    }
   | OP_INVOKE_SUPER OPEN_BRACE regs CLOSE_BRACE COMMA classtypeOrArray ARROW namestring OPEN_PAREN args CLOSE_PAREN classtypeOrArray {
       $$ = new Op_INVOKE(OP_INVOKE_SUPER, driver.stringPool(), $3, $6, $8, $10, $12);
    }
   | OP_INVOKE_DIRECT OPEN_BRACE regs CLOSE_BRACE COMMA classtypeOrArray ARROW namestring OPEN_PAREN args CLOSE_PAREN classtypeOrArray {
       $$ = new Op_INVOKE(OP_INVOKE_DIRECT, driver.stringPool(), $3, $6, $8, $10, $12);
    }
   | OP_INVOKE_STATIC OPEN_BRACE regs CLOSE_BRACE COMMA classtypeOrArray ARROW namestring OPEN_PAREN args CLOSE_PAREN classtypeOrArray {
       $$ = new Op_INVOKE(OP_INVOKE_STATIC, driver.stringPool(), $3, $6, $8, $10, $12);
    }
   | OP_INVOKE_INTERFACE OPEN_BRACE regs CLOSE_BRACE COMMA classtypeOrArray ARROW namestring OPEN_PAREN args CLOSE_PAREN classtypeOrArray {
       $$ = new Op_INVOKE(OP_INVOKE_INTERFACE, driver.stringPool(), $3, $6, $8, $10, $12);
    }
   | OP_UNUSED_73
   | OP_INVOKE_VIRTUAL_RANGE OPEN_BRACE REGISTER DOTDOT REGISTER CLOSE_BRACE COMMA classtypeOrArray ARROW namestring OPEN_PAREN args CLOSE_PAREN classtypeOrArray {
       $$ = new Op_INVOKE_X_RANGE(OP_INVOKE_VIRTUAL_RANGE, driver.stringPool(), $3, $5, $8, $10, $12, $14);
    }
   | OP_INVOKE_SUPER_RANGE OPEN_BRACE REGISTER DOTDOT REGISTER CLOSE_BRACE COMMA classtypeOrArray ARROW namestring OPEN_PAREN args CLOSE_PAREN classtypeOrArray {
       $$ = new Op_INVOKE_X_RANGE(OP_INVOKE_SUPER_RANGE, driver.stringPool(), $3, $5, $8, $10, $12, $14);
    }
   | OP_INVOKE_DIRECT_RANGE OPEN_BRACE REGISTER DOTDOT REGISTER CLOSE_BRACE COMMA classtypeOrArray ARROW namestring OPEN_PAREN args CLOSE_PAREN classtypeOrArray {
       $$ = new Op_INVOKE_X_RANGE(OP_INVOKE_DIRECT_RANGE, driver.stringPool(), $3, $5, $8, $10, $12, $14);
    }
   | OP_INVOKE_STATIC_RANGE OPEN_BRACE REGISTER DOTDOT REGISTER CLOSE_BRACE COMMA classtypeOrArray ARROW namestring OPEN_PAREN args CLOSE_PAREN classtypeOrArray {
       $$ = new Op_INVOKE_X_RANGE(OP_INVOKE_STATIC_RANGE, driver.stringPool(), $3, $5, $8, $10, $12, $14);
    }
   | OP_INVOKE_INTERFACE_RANGE OPEN_BRACE REGISTER DOTDOT REGISTER CLOSE_BRACE COMMA classtypeOrArray ARROW namestring OPEN_PAREN args CLOSE_PAREN classtypeOrArray {
       $$ = new Op_INVOKE_X_RANGE(OP_INVOKE_INTERFACE_RANGE, driver.stringPool(), $3, $5, $8, $10, $12, $14);
    }
   | OP_UNUSED_79
   | OP_UNUSED_7A
   | OP_NEG_INT REGISTER COMMA REGISTER {
       $$ = new Op_NEGNOT_X(OP_NEG_INT, driver.stringPool(), $2, $4);
    }
   | OP_NOT_INT REGISTER COMMA REGISTER {
       $$ = new Op_NEGNOT_X(OP_NOT_INT, driver.stringPool(), $2, $4);
    }
   | OP_NEG_LONG REGISTER COMMA REGISTER {
       $$ = new Op_NEGNOT_X(OP_NEG_LONG, driver.stringPool(), $2, $4);
    }
   | OP_NOT_LONG REGISTER COMMA REGISTER {
       $$ = new Op_NEGNOT_X(OP_NOT_LONG, driver.stringPool(), $2, $4);
    }
   | OP_NEG_FLOAT REGISTER COMMA REGISTER {
       $$ = new Op_NEGNOT_X(OP_NEG_FLOAT, driver.stringPool(), $2, $4);
    }
   | OP_NEG_DOUBLE REGISTER COMMA REGISTER {
       $$ = new Op_NEGNOT_X(OP_NEG_DOUBLE, driver.stringPool(), $2, $4);
    }
   | OP_INT_TO_LONG REGISTER COMMA REGISTER {
       $$ = new Op_X_TO_Y(OP_INT_TO_LONG, driver.stringPool(), $2, $4);
    }
   | OP_INT_TO_FLOAT REGISTER COMMA REGISTER {
       $$ = new Op_X_TO_Y(OP_INT_TO_FLOAT, driver.stringPool(), $2, $4);
    }
   | OP_INT_TO_DOUBLE REGISTER COMMA REGISTER {
       $$ = new Op_X_TO_Y(OP_INT_TO_DOUBLE, driver.stringPool(), $2, $4);
    }
   | OP_LONG_TO_INT REGISTER COMMA REGISTER {
       $$ = new Op_X_TO_Y(OP_LONG_TO_INT, driver.stringPool(), $2, $4);
    }
   | OP_LONG_TO_FLOAT REGISTER COMMA REGISTER {
       $$ = new Op_X_TO_Y(OP_LONG_TO_FLOAT, driver.stringPool(), $2, $4);
    }
   | OP_LONG_TO_DOUBLE REGISTER COMMA REGISTER {
       $$ = new Op_X_TO_Y(OP_LONG_TO_DOUBLE, driver.stringPool(), $2, $4);
    }
   | OP_FLOAT_TO_INT REGISTER COMMA REGISTER {
       $$ = new Op_X_TO_Y(OP_FLOAT_TO_INT, driver.stringPool(), $2, $4);
    }
   | OP_FLOAT_TO_LONG REGISTER COMMA REGISTER {
       $$ = new Op_X_TO_Y(OP_FLOAT_TO_LONG, driver.stringPool(), $2, $4);
    }
   | OP_FLOAT_TO_DOUBLE REGISTER COMMA REGISTER {
       $$ = new Op_X_TO_Y(OP_FLOAT_TO_DOUBLE, driver.stringPool(), $2, $4);
    }
   | OP_DOUBLE_TO_INT REGISTER COMMA REGISTER {
       $$ = new Op_X_TO_Y(OP_DOUBLE_TO_INT, driver.stringPool(), $2, $4);
    }
   | OP_DOUBLE_TO_LONG REGISTER COMMA REGISTER {
       $$ = new Op_X_TO_Y(OP_DOUBLE_TO_LONG, driver.stringPool(), $2, $4);
    }
   | OP_DOUBLE_TO_FLOAT REGISTER COMMA REGISTER {
       $$ = new Op_X_TO_Y(OP_DOUBLE_TO_FLOAT, driver.stringPool(), $2, $4);
    }
   | OP_INT_TO_BYTE REGISTER COMMA REGISTER {
       $$ = new Op_X_TO_Y(OP_INT_TO_BYTE, driver.stringPool(), $2, $4);
    }
   | OP_INT_TO_CHAR REGISTER COMMA REGISTER {
       $$ = new Op_X_TO_Y(OP_INT_TO_CHAR, driver.stringPool(), $2, $4);
    }
   | OP_INT_TO_SHORT REGISTER COMMA REGISTER {
       $$ = new Op_X_TO_Y(OP_INT_TO_SHORT, driver.stringPool(), $2, $4);
    }
   | OP_ADD_INT REGISTER COMMA REGISTER COMMA REGISTER {
       $$ = new Op_X_INT(OP_ADD_INT, driver.stringPool(), $2, $4, $6);
    }
   | OP_SUB_INT REGISTER COMMA REGISTER COMMA REGISTER {
       $$ = new Op_X_INT(OP_SUB_INT, driver.stringPool(), $2, $4, $6);
    }
   | OP_MUL_INT REGISTER COMMA REGISTER COMMA REGISTER {
       $$ = new Op_X_INT(OP_MUL_INT, driver.stringPool(), $2, $4, $6);
    }
   | OP_DIV_INT REGISTER COMMA REGISTER COMMA REGISTER {
       $$ = new Op_X_INT(OP_DIV_INT, driver.stringPool(), $2, $4, $6);
    }
   | OP_REM_INT REGISTER COMMA REGISTER COMMA REGISTER {
       $$ = new Op_X_INT(OP_REM_INT, driver.stringPool(), $2, $4, $6);
    }
   | OP_AND_INT REGISTER COMMA REGISTER COMMA REGISTER {
       $$ = new Op_X_INT(OP_AND_INT, driver.stringPool(), $2, $4, $6);
    }
   | OP_OR_INT REGISTER COMMA REGISTER COMMA REGISTER {
       $$ = new Op_X_INT(OP_OR_INT, driver.stringPool(), $2, $4, $6);
    }
   | OP_XOR_INT REGISTER COMMA REGISTER COMMA REGISTER {
       $$ = new Op_X_INT(OP_XOR_INT, driver.stringPool(), $2, $4, $6);
    }
   | OP_SHL_INT REGISTER COMMA REGISTER COMMA REGISTER {
       $$ = new Op_X_INT(OP_SHL_INT, driver.stringPool(), $2, $4, $6);
    }
   | OP_SHR_INT REGISTER COMMA REGISTER COMMA REGISTER {
       $$ = new Op_X_INT(OP_SHR_INT, driver.stringPool(), $2, $4, $6);
    }
   | OP_USHR_INT REGISTER COMMA REGISTER COMMA REGISTER {
       $$ = new Op_X_INT(OP_USHR_INT, driver.stringPool(), $2, $4, $6);
    }
   | OP_ADD_LONG REGISTER COMMA REGISTER COMMA REGISTER {
       $$ = new Op_X_LONG(OP_ADD_LONG, driver.stringPool(), $2, $4, $6);
    }
   | OP_SUB_LONG REGISTER COMMA REGISTER COMMA REGISTER {
       $$ = new Op_X_LONG(OP_SUB_LONG, driver.stringPool(), $2, $4, $6);
    }
   | OP_MUL_LONG REGISTER COMMA REGISTER COMMA REGISTER {
       $$ = new Op_X_LONG(OP_MUL_LONG, driver.stringPool(), $2, $4, $6);
    }
   | OP_DIV_LONG REGISTER COMMA REGISTER COMMA REGISTER {
       $$ = new Op_X_LONG(OP_DIV_LONG, driver.stringPool(), $2, $4, $6);
    }
   | OP_REM_LONG REGISTER COMMA REGISTER COMMA REGISTER {
       $$ = new Op_X_LONG(OP_REM_LONG, driver.stringPool(), $2, $4, $6);
    }
   | OP_AND_LONG REGISTER COMMA REGISTER COMMA REGISTER {
       $$ = new Op_X_LONG(OP_AND_LONG, driver.stringPool(), $2, $4, $6);
    }
   | OP_OR_LONG REGISTER COMMA REGISTER COMMA REGISTER {
       $$ = new Op_X_LONG(OP_OR_LONG, driver.stringPool(), $2, $4, $6);
    }
   | OP_XOR_LONG REGISTER COMMA REGISTER COMMA REGISTER {
       $$ = new Op_X_LONG(OP_XOR_LONG, driver.stringPool(), $2, $4, $6);
    }
   | OP_SHL_LONG REGISTER COMMA REGISTER COMMA REGISTER {
       $$ = new Op_X_LONG(OP_SHL_LONG, driver.stringPool(), $2, $4, $6);
    }
   | OP_SHR_LONG REGISTER COMMA REGISTER COMMA REGISTER {
       $$ = new Op_X_LONG(OP_SHR_LONG, driver.stringPool(), $2, $4, $6);
    }
   | OP_USHR_LONG REGISTER COMMA REGISTER COMMA REGISTER {
       $$ = new Op_X_LONG(OP_USHR_LONG, driver.stringPool(), $2, $4, $6);
    }
   | OP_ADD_FLOAT REGISTER COMMA REGISTER COMMA REGISTER {
       $$ = new Op_X_FLOAT(OP_ADD_FLOAT, driver.stringPool(), $2, $4, $6);
    }
   | OP_SUB_FLOAT REGISTER COMMA REGISTER COMMA REGISTER {
       $$ = new Op_X_FLOAT(OP_SUB_FLOAT, driver.stringPool(), $2, $4, $6);
    }
   | OP_MUL_FLOAT REGISTER COMMA REGISTER COMMA REGISTER {
       $$ = new Op_X_FLOAT(OP_MUL_FLOAT, driver.stringPool(), $2, $4, $6);
    }
   | OP_DIV_FLOAT REGISTER COMMA REGISTER COMMA REGISTER {
       $$ = new Op_X_FLOAT(OP_DIV_FLOAT, driver.stringPool(), $2, $4, $6);
    }
   | OP_REM_FLOAT REGISTER COMMA REGISTER COMMA REGISTER {
       $$ = new Op_X_FLOAT(OP_REM_FLOAT, driver.stringPool(), $2, $4, $6);
    }
   | OP_ADD_DOUBLE REGISTER COMMA REGISTER COMMA REGISTER {
       $$ = new Op_X_DOUBLE(OP_ADD_DOUBLE, driver.stringPool(), $2, $4, $6);
    }
   | OP_SUB_DOUBLE REGISTER COMMA REGISTER COMMA REGISTER {
       $$ = new Op_X_DOUBLE(OP_SUB_DOUBLE, driver.stringPool(), $2, $4, $6);
    }
   | OP_MUL_DOUBLE REGISTER COMMA REGISTER COMMA REGISTER {
       $$ = new Op_X_DOUBLE(OP_MUL_DOUBLE, driver.stringPool(), $2, $4, $6);
    }
   | OP_DIV_DOUBLE REGISTER COMMA REGISTER COMMA REGISTER {
       $$ = new Op_X_DOUBLE(OP_DIV_DOUBLE, driver.stringPool(), $2, $4, $6);
    }
   | OP_REM_DOUBLE REGISTER COMMA REGISTER COMMA REGISTER {
       $$ = new Op_X_DOUBLE(OP_REM_DOUBLE, driver.stringPool(), $2, $4, $6);
    }
   | OP_ADD_INT_2ADDR REGISTER COMMA REGISTER {
       $$ = new Op_X_INT_2ADDR(OP_ADD_INT_2ADDR, driver.stringPool(), $2, $4);
    }
   | OP_SUB_INT_2ADDR REGISTER COMMA REGISTER {
       $$ = new Op_X_INT_2ADDR(OP_SUB_INT_2ADDR, driver.stringPool(), $2, $4);
    }
   | OP_MUL_INT_2ADDR REGISTER COMMA REGISTER {
       $$ = new Op_X_INT_2ADDR(OP_MUL_INT_2ADDR, driver.stringPool(), $2, $4);
    }
   | OP_DIV_INT_2ADDR REGISTER COMMA REGISTER {
       $$ = new Op_X_INT_2ADDR(OP_DIV_INT_2ADDR, driver.stringPool(), $2, $4);
    }
   | OP_REM_INT_2ADDR REGISTER COMMA REGISTER {
       $$ = new Op_X_INT_2ADDR(OP_REM_INT_2ADDR, driver.stringPool(), $2, $4);
    }
   | OP_AND_INT_2ADDR REGISTER COMMA REGISTER {
       $$ = new Op_X_INT_2ADDR(OP_AND_INT_2ADDR, driver.stringPool(), $2, $4);
    }
   | OP_OR_INT_2ADDR REGISTER COMMA REGISTER {
       $$ = new Op_X_INT_2ADDR(OP_OR_INT_2ADDR, driver.stringPool(), $2, $4);
    }
   | OP_XOR_INT_2ADDR REGISTER COMMA REGISTER {
       $$ = new Op_X_INT_2ADDR(OP_XOR_INT_2ADDR, driver.stringPool(), $2, $4);
    }
   | OP_SHL_INT_2ADDR REGISTER COMMA REGISTER {
       $$ = new Op_X_INT_2ADDR(OP_SHL_INT_2ADDR, driver.stringPool(), $2, $4);
    }
   | OP_SHR_INT_2ADDR REGISTER COMMA REGISTER {
       $$ = new Op_X_INT_2ADDR(OP_SHR_INT_2ADDR, driver.stringPool(), $2, $4);
    }
   | OP_USHR_INT_2ADDR REGISTER COMMA REGISTER {
       $$ = new Op_X_INT_2ADDR(OP_USHR_INT_2ADDR, driver.stringPool(), $2, $4);
    }
   | OP_ADD_LONG_2ADDR REGISTER COMMA REGISTER {
       $$ = new Op_X_LONG_2ADDR(OP_ADD_LONG_2ADDR, driver.stringPool(), $2, $4);
    }
   | OP_SUB_LONG_2ADDR REGISTER COMMA REGISTER {
       $$ = new Op_X_LONG_2ADDR(OP_SUB_LONG_2ADDR, driver.stringPool(), $2, $4);
    }
   | OP_MUL_LONG_2ADDR REGISTER COMMA REGISTER {
       $$ = new Op_X_LONG_2ADDR(OP_MUL_LONG_2ADDR, driver.stringPool(), $2, $4);
    }
   | OP_DIV_LONG_2ADDR REGISTER COMMA REGISTER {
       $$ = new Op_X_LONG_2ADDR(OP_DIV_LONG_2ADDR, driver.stringPool(), $2, $4);
    }
   | OP_REM_LONG_2ADDR REGISTER COMMA REGISTER {
       $$ = new Op_X_LONG_2ADDR(OP_REM_LONG_2ADDR, driver.stringPool(), $2, $4);
    }
   | OP_AND_LONG_2ADDR REGISTER COMMA REGISTER {
       $$ = new Op_X_LONG_2ADDR(OP_AND_LONG_2ADDR, driver.stringPool(), $2, $4);
    }
   | OP_OR_LONG_2ADDR REGISTER COMMA REGISTER {
       $$ = new Op_X_LONG_2ADDR(OP_OR_LONG_2ADDR, driver.stringPool(), $2, $4);
    }
   | OP_XOR_LONG_2ADDR REGISTER COMMA REGISTER {
       $$ = new Op_X_LONG_2ADDR(OP_XOR_LONG_2ADDR, driver.stringPool(), $2, $4);
    }
   | OP_SHL_LONG_2ADDR REGISTER COMMA REGISTER {
       $$ = new Op_X_LONG_2ADDR(OP_SHL_LONG_2ADDR, driver.stringPool(), $2, $4);
    }
   | OP_SHR_LONG_2ADDR REGISTER COMMA REGISTER {
       $$ = new Op_X_LONG_2ADDR(OP_SHR_LONG_2ADDR, driver.stringPool(), $2, $4);
    }
   | OP_USHR_LONG_2ADDR REGISTER COMMA REGISTER {
       $$ = new Op_X_LONG_2ADDR(OP_USHR_LONG_2ADDR, driver.stringPool(), $2, $4);
    }
   | OP_ADD_FLOAT_2ADDR REGISTER COMMA REGISTER {
       $$ = new Op_X_FLOAT_2ADDR(OP_ADD_FLOAT_2ADDR, driver.stringPool(), $2, $4);
    }
   | OP_SUB_FLOAT_2ADDR REGISTER COMMA REGISTER {
       $$ = new Op_X_FLOAT_2ADDR(OP_SUB_FLOAT_2ADDR, driver.stringPool(), $2, $4);
    }
   | OP_MUL_FLOAT_2ADDR REGISTER COMMA REGISTER {
       $$ = new Op_X_FLOAT_2ADDR(OP_MUL_FLOAT_2ADDR, driver.stringPool(), $2, $4);
    }
   | OP_DIV_FLOAT_2ADDR REGISTER COMMA REGISTER {
       $$ = new Op_X_FLOAT_2ADDR(OP_DIV_FLOAT_2ADDR, driver.stringPool(), $2, $4);
    }
   | OP_REM_FLOAT_2ADDR REGISTER COMMA REGISTER {
       $$ = new Op_X_FLOAT_2ADDR(OP_REM_FLOAT_2ADDR, driver.stringPool(), $2, $4);
    }
   | OP_ADD_DOUBLE_2ADDR REGISTER COMMA REGISTER {
       $$ = new Op_X_DOUBLE_2ADDR(OP_ADD_DOUBLE_2ADDR, driver.stringPool(), $2, $4);
    }
   | OP_SUB_DOUBLE_2ADDR REGISTER COMMA REGISTER {
       $$ = new Op_X_DOUBLE_2ADDR(OP_SUB_DOUBLE_2ADDR, driver.stringPool(), $2, $4);
    }
   | OP_MUL_DOUBLE_2ADDR REGISTER COMMA REGISTER {
       $$ = new Op_X_DOUBLE_2ADDR(OP_MUL_DOUBLE_2ADDR, driver.stringPool(), $2, $4);
    }
   | OP_DIV_DOUBLE_2ADDR REGISTER COMMA REGISTER {
       $$ = new Op_X_DOUBLE_2ADDR(OP_DIV_DOUBLE_2ADDR, driver.stringPool(), $2, $4);
    }
   | OP_REM_DOUBLE_2ADDR REGISTER COMMA REGISTER {
       $$ = new Op_X_DOUBLE_2ADDR(OP_REM_DOUBLE_2ADDR, driver.stringPool(), $2, $4);
    }
   | OP_ADD_INT_LIT16 REGISTER COMMA REGISTER COMMA integer {
       $$ = new Op_X_INT_LIT(OP_ADD_INT_LIT16, driver.stringPool(), $2, $4, $6);
    }
   | OP_RSUB_INT REGISTER COMMA REGISTER COMMA integer {
       $$ = new Op_X_INT_LIT(OP_RSUB_INT, driver.stringPool(), $2, $4, $6);
    }
   | OP_MUL_INT_LIT16 REGISTER COMMA REGISTER COMMA integer {
       $$ = new Op_X_INT_LIT(OP_MUL_INT_LIT16, driver.stringPool(), $2, $4, $6);
    }
   | OP_DIV_INT_LIT16 REGISTER COMMA REGISTER COMMA integer {
       $$ = new Op_X_INT_LIT(OP_DIV_INT_LIT16, driver.stringPool(), $2, $4, $6);
    }
   | OP_REM_INT_LIT16 REGISTER COMMA REGISTER COMMA integer {
       $$ = new Op_X_INT_LIT(OP_REM_INT_LIT16, driver.stringPool(), $2, $4, $6);
    }
   | OP_AND_INT_LIT16 REGISTER COMMA REGISTER COMMA integer {
       $$ = new Op_X_INT_LIT(OP_AND_INT_LIT16, driver.stringPool(), $2, $4, $6);
    }
   | OP_OR_INT_LIT16 REGISTER COMMA REGISTER COMMA integer {
       $$ = new Op_X_INT_LIT(OP_OR_INT_LIT16, driver.stringPool(), $2, $4, $6);
    }
   | OP_XOR_INT_LIT16 REGISTER COMMA REGISTER COMMA integer {
       $$ = new Op_X_INT_LIT(OP_XOR_INT_LIT16, driver.stringPool(), $2, $4, $6);
    }
   | OP_ADD_INT_LIT8 REGISTER COMMA REGISTER COMMA integer {
       $$ = new Op_X_INT_LIT(OP_ADD_INT_LIT8, driver.stringPool(), $2, $4, $6);
    }
   | OP_RSUB_INT_LIT8 REGISTER COMMA REGISTER COMMA integer {
       $$ = new Op_X_INT_LIT(OP_RSUB_INT_LIT8, driver.stringPool(), $2, $4, $6);
    }
   | OP_MUL_INT_LIT8 REGISTER COMMA REGISTER COMMA integer {
       $$ = new Op_X_INT_LIT(OP_MUL_INT_LIT8, driver.stringPool(), $2, $4, $6);
    }
   | OP_DIV_INT_LIT8 REGISTER COMMA REGISTER COMMA integer {
       $$ = new Op_X_INT_LIT(OP_DIV_INT_LIT8, driver.stringPool(), $2, $4, $6);
    }
   | OP_REM_INT_LIT8 REGISTER COMMA REGISTER COMMA integer {
       $$ = new Op_X_INT_LIT(OP_REM_INT_LIT8, driver.stringPool(), $2, $4, $6);
    }
   | OP_AND_INT_LIT8 REGISTER COMMA REGISTER COMMA integer {
       $$ = new Op_X_INT_LIT(OP_AND_INT_LIT8, driver.stringPool(), $2, $4, $6);
    }
   | OP_OR_INT_LIT8 REGISTER COMMA REGISTER COMMA integer {
       $$ = new Op_X_INT_LIT(OP_OR_INT_LIT8, driver.stringPool(), $2, $4, $6);
    }
   | OP_XOR_INT_LIT8 REGISTER COMMA REGISTER COMMA integer {
       $$ = new Op_X_INT_LIT(OP_XOR_INT_LIT8, driver.stringPool(), $2, $4, $6);
    }
   | OP_SHL_INT_LIT8 REGISTER COMMA REGISTER COMMA integer {
       $$ = new Op_X_INT_LIT(OP_SHL_INT_LIT8, driver.stringPool(), $2, $4, $6);
    }
   | OP_SHR_INT_LIT8 REGISTER COMMA REGISTER COMMA integer {
       $$ = new Op_X_INT_LIT(OP_SHR_INT_LIT8, driver.stringPool(), $2, $4, $6);
    }
   | OP_USHR_INT_LIT8 REGISTER COMMA REGISTER COMMA integer {
       $$ = new Op_X_INT_LIT(OP_USHR_INT_LIT8, driver.stringPool(), $2, $4, $6);
    }
   | OP_IGET_VOLATILE
   | OP_IPUT_VOLATILE
   | OP_SGET_VOLATILE
   | OP_SPUT_VOLATILE
   | OP_IGET_OBJECT_VOLATILE
   | OP_IGET_WIDE_VOLATILE
   | OP_IPUT_WIDE_VOLATILE
   | OP_SGET_WIDE_VOLATILE
   | OP_SPUT_WIDE_VOLATILE
   | OP_BREAKPOINT
   | OP_THROW_VERIFICATION_ERROR
   | OP_EXECUTE_INLINE
   | OP_EXECUTE_INLINE_RANGE
   | OP_INVOKE_OBJECT_INIT_RANGE
   | OP_RETURN_VOID_BARRIER
   | OP_IGET_QUICK
   | OP_IGET_WIDE_QUICK
   | OP_IGET_OBJECT_QUICK
   | OP_IPUT_QUICK
   | OP_IPUT_WIDE_QUICK
   | OP_IPUT_OBJECT_QUICK
   | OP_INVOKE_VIRTUAL_QUICK
   | OP_INVOKE_VIRTUAL_QUICK_RANGE
   | OP_INVOKE_SUPER_QUICK
   | OP_INVOKE_SUPER_QUICK_RANGE
   | OP_IPUT_OBJECT_VOLATILE
   | OP_SGET_OBJECT_VOLATILE
   | OP_SPUT_OBJECT_VOLATILE
   | OP_UNUSED_FF
   | COLON namestring {
       $$ = new Op_JmpLabel(OP_JMPLABEL, driver.stringPool(), $2);
    }
   | CATCH_DIRECTIVE classtypeOrArray OPEN_BRACE jmplabel DOTDOT jmplabel CLOSE_BRACE jmplabel {
       $$ = new Op_CATCH(OP_CATCH, driver.stringPool(), $2, $4, $6, $8);
    }
   | CATCHALL_DIRECTIVE OPEN_BRACE jmplabel DOTDOT jmplabel CLOSE_BRACE jmplabel {
       std::string allclass = "";
       $$ = new Op_CATCH(OP_CATCHALL, driver.stringPool(), allclass, $3, $5, $7);
    }
   ;
%%

void Analysis::SmaliParser::error(const location &loc, const std::string &message) {
	cout << "Parse error: " << message << endl
	    << "Error location: " << loc << endl << driver.mLexer->text() << endl;
}
