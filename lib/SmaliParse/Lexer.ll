%{
//===- Lexer.ll - ART-LEX -------------------------------------*- flex -*-===//
//
//                     ANDROID REVERSE TOOLKIT
//
// This file is distributed under the GNU GENERAL PUBLIC LICENSE
// V3 License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// The file defines a lexer for smali language. Please use
// flex -o Lexer.cpp Lexer.ll
// to generate lex source file
// or
// flex -s -o Lexer.cpp Lexer.ll
// to debug
//
//===----------------------------------------------------------------------===//
	#include <iostream>
	#include <cstdlib>
    #include "Lexer.h"
	#include "Parser.hpp"
	#include "location.hh"
    #include "utils/Defs.h"

	using namespace std;
	using namespace Analysis;

	#define yyterminate() Analysis::Parser::make_END(\
	    Analysis::location(YY_NULL,line(), column()));

	#define YY_USER_ACTION acceptToken(yytext, yyleng);
    #define LOCATION Analysis::location(YY_NULL, line(), column())
%}

%option noyywrap
%option c++
%option yyclass="Lexer"
%option prefix="Analysis_"


/*  unicode support*/
ASC     [\x00-\x7f]
ASCN    [\x00-\t\v-\x7f]
U       [\x80-\xbf]
U2      [\xc2-\xdf]
U3      [\xe0-\xef]
U4      [\xf0-\xf4]

UONLY   {U2}{U}|{U3}{U}{U}|{U4}{U}{U}{U}
UANY    {ASC}|{UONLY}
UANYN   {ASCN}|{UONLY}

ASCSTR  [0-9a-zA-Z/<>$_]
UASTR   {ASCSTR}|{UONLY}

/* Define constants */
OWS             [ \t\r]
EOL             \n

CLASSNAME       L{UASTR}+;

DNUMBER         [0-9]+
HNUMBER         [0-9A-Fa-f]+

CLASSTYPE       "["*({CLASSNAME}|V|Z|C|B|S|I|F|J|D)

CSTRING          "\""{UANYN}*"\""
NAMESTRING      {UASTR}+
COMMENT         #{UANYN}*

%x ARGSDEF

%%
{OWS}+
{EOL}       {return Parser::make_EOL(LOCATION); }
{COMMENT}   {return Analysis::Parser::make_COMMENT(yytext, LOCATION);}
<INITIAL,ARGSDEF>{CLASSTYPE} {
        return Analysis::Parser::make_CLASSTYPE(yytext, LOCATION);}

   /*        declration        */
".class"  {return Parser::make_CLASSBEG(LOCATION);}
".super"  {return Parser::make_SUPERBEG(LOCATION);}
".source"    {return Parser::make_SRCBEG(LOCATION);}
".field"  {return Parser::make_FIELDBEG(LOCATION);}
".method" { return Parser::make_METHODBEG(LOCATION);}
".end method" { return Parser::make_METHODEND(LOCATION);}


    /*      method keyword  */
".registers"  {return Parser::make_REGISTERS(LOCATION);}

    /*      instruction keyword     */
"nop"        {return Parser::make_OP_NOP(LOCATION);}
"move"       {return Parser::make_OP_MOVE(LOCATION);}
"move/from16"        {return Parser::make_OP_MOVE_FROM16(LOCATION);}
"move/16"    {return Parser::make_OP_MOVE_16(LOCATION);}
"move-wide"  {return Parser::make_OP_MOVE_WIDE(LOCATION);}
"move-wide/from16"   {return Parser::make_OP_MOVE_WIDE_FROM16(LOCATION);}
"move-wide/16"       {return Parser::make_OP_MOVE_WIDE_16(LOCATION);}
"move-object"        {return Parser::make_OP_MOVE_OBJECT(LOCATION);}
"move-object/from16" {return Parser::make_OP_MOVE_OBJECT_FROM16(LOCATION);}
"move-object/16"     {return Parser::make_OP_MOVE_OBJECT_16(LOCATION);}
"move-result"        {return Parser::make_OP_MOVE_RESULT(LOCATION);}
"move-result-wide"   {return Parser::make_OP_MOVE_RESULT_WIDE(LOCATION);}
"move-result-object" {return Parser::make_OP_MOVE_RESULT_OBJECT(LOCATION);}
"move-exception"     {return Parser::make_OP_MOVE_EXCEPTION(LOCATION);}
"return-void"        {return Parser::make_OP_RETURN_VOID(LOCATION);}
"return"     {return Parser::make_OP_RETURN(LOCATION);}
"return-wide"        {return Parser::make_OP_RETURN_WIDE(LOCATION);}
"return-object"      {return Parser::make_OP_RETURN_OBJECT(LOCATION);}
"const/4"    {return Parser::make_OP_CONST_4(LOCATION);}
"const/16"   {return Parser::make_OP_CONST_16(LOCATION);}
"const"      {return Parser::make_OP_CONST(LOCATION);}
"const/high16"       {return Parser::make_OP_CONST_HIGH16(LOCATION);}
"const-wide/16"      {return Parser::make_OP_CONST_WIDE_16(LOCATION);}
"const-wide/32"      {return Parser::make_OP_CONST_WIDE_32(LOCATION);}
"const-wide" {return Parser::make_OP_CONST_WIDE(LOCATION);}
"const-wide/high16"  {return Parser::make_OP_CONST_WIDE_HIGH16(LOCATION);}
"const-string"       {return Parser::make_OP_CONST_STRING(LOCATION);}
"const-string/jumbo" {return Parser::make_OP_CONST_STRING_JUMBO(LOCATION);}
"const-class"        {return Parser::make_OP_CONST_CLASS(LOCATION);}
"monitor-enter"      {return Parser::make_OP_MONITOR_ENTER(LOCATION);}
"monitor-exit"       {return Parser::make_OP_MONITOR_EXIT(LOCATION);}
"check-cast" {return Parser::make_OP_CHECK_CAST(LOCATION);}
"instance-of"        {return Parser::make_OP_INSTANCE_OF(LOCATION);}
"array-length"       {return Parser::make_OP_ARRAY_LENGTH(LOCATION);}
"new-instance"       {return Parser::make_OP_NEW_INSTANCE(LOCATION);}
"new-array"  {return Parser::make_OP_NEW_ARRAY(LOCATION);}
"filled-new-array"   {return Parser::make_OP_FILLED_NEW_ARRAY(LOCATION);}
"filled-new-array/range" {
                    return Parser::make_OP_FILLED_NEW_ARRAY_RANGE(LOCATION);}
"fill-array-data"    {return Parser::make_OP_FILL_ARRAY_DATA(LOCATION);}
"throw"      {return Parser::make_OP_THROW(LOCATION);}
"goto"       {return Parser::make_OP_GOTO(LOCATION);}
"goto/16"    {return Parser::make_OP_GOTO_16(LOCATION);}
"goto/32"    {return Parser::make_OP_GOTO_32(LOCATION);}
"packed-switch"      {return Parser::make_OP_PACKED_SWITCH(LOCATION);}
".packed-switch"     {return Parser::make_OP_PACKED_SWITCHDATABEG(LOCATION);}
".end packed-switch" {return Parser::make_OP_PACKED_SWITCHDATAEND(LOCATION);}
"sparse-switch"      {return Parser::make_OP_SPARSE_SWITCH(LOCATION);}
"cmpl-float" {return Parser::make_OP_CMPL_FLOAT(LOCATION);}
"cmpg-float" {return Parser::make_OP_CMPG_FLOAT(LOCATION);}
"cmpl-double"        {return Parser::make_OP_CMPL_DOUBLE(LOCATION);}
"cmpg-double"        {return Parser::make_OP_CMPG_DOUBLE(LOCATION);}
"cmp-long"   {return Parser::make_OP_CMP_LONG(LOCATION);}
"if-eq"      {return Parser::make_OP_IF_EQ(LOCATION);}
"if-ne"      {return Parser::make_OP_IF_NE(LOCATION);}
"if-lt"      {return Parser::make_OP_IF_LT(LOCATION);}
"if-ge"      {return Parser::make_OP_IF_GE(LOCATION);}
"if-gt"      {return Parser::make_OP_IF_GT(LOCATION);}
"if-le"      {return Parser::make_OP_IF_LE(LOCATION);}
"if-eqz"     {return Parser::make_OP_IF_EQZ(LOCATION);}
"if-nez"     {return Parser::make_OP_IF_NEZ(LOCATION);}
"if-ltz"     {return Parser::make_OP_IF_LTZ(LOCATION);}
"if-gez"     {return Parser::make_OP_IF_GEZ(LOCATION);}
"if-gtz"     {return Parser::make_OP_IF_GTZ(LOCATION);}
"if-lez"     {return Parser::make_OP_IF_LEZ(LOCATION);}
"unused-3e"  {return Parser::make_OP_UNUSED_3E(LOCATION);}
"unused-3f"  {return Parser::make_OP_UNUSED_3F(LOCATION);}
"unused-40"  {return Parser::make_OP_UNUSED_40(LOCATION);}
"unused-41"  {return Parser::make_OP_UNUSED_41(LOCATION);}
"unused-42"  {return Parser::make_OP_UNUSED_42(LOCATION);}
"unused-43"  {return Parser::make_OP_UNUSED_43(LOCATION);}
"aget"       {return Parser::make_OP_AGET(LOCATION);}
"aget-wide"  {return Parser::make_OP_AGET_WIDE(LOCATION);}
"aget-object"        {return Parser::make_OP_AGET_OBJECT(LOCATION);}
"aget-boolean"       {return Parser::make_OP_AGET_BOOLEAN(LOCATION);}
"aget-byte"  {return Parser::make_OP_AGET_BYTE(LOCATION);}
"aget-char"  {return Parser::make_OP_AGET_CHAR(LOCATION);}
"aget-short" {return Parser::make_OP_AGET_SHORT(LOCATION);}
"aput"       {return Parser::make_OP_APUT(LOCATION);}
"aput-wide"  {return Parser::make_OP_APUT_WIDE(LOCATION);}
"aput-object"        {return Parser::make_OP_APUT_OBJECT(LOCATION);}
"aput-boolean"       {return Parser::make_OP_APUT_BOOLEAN(LOCATION);}
"aput-byte"  {return Parser::make_OP_APUT_BYTE(LOCATION);}
"aput-char"  {return Parser::make_OP_APUT_CHAR(LOCATION);}
"aput-short" {return Parser::make_OP_APUT_SHORT(LOCATION);}
"iget"       {return Parser::make_OP_IGET(LOCATION);}
"iget-wide"  {return Parser::make_OP_IGET_WIDE(LOCATION);}
"iget-object"        {return Parser::make_OP_IGET_OBJECT(LOCATION);}
"iget-boolean"       {return Parser::make_OP_IGET_BOOLEAN(LOCATION);}
"iget-byte"  {return Parser::make_OP_IGET_BYTE(LOCATION);}
"iget-char"  {return Parser::make_OP_IGET_CHAR(LOCATION);}
"iget-short" {return Parser::make_OP_IGET_SHORT(LOCATION);}
"iput"       {return Parser::make_OP_IPUT(LOCATION);}
"iput-wide"  {return Parser::make_OP_IPUT_WIDE(LOCATION);}
"iput-object"        {return Parser::make_OP_IPUT_OBJECT(LOCATION);}
"iput-boolean"       {return Parser::make_OP_IPUT_BOOLEAN(LOCATION);}
"iput-byte"  {return Parser::make_OP_IPUT_BYTE(LOCATION);}
"iput-char"  {return Parser::make_OP_IPUT_CHAR(LOCATION);}
"iput-short" {return Parser::make_OP_IPUT_SHORT(LOCATION);}
"sget"       {return Parser::make_OP_SGET(LOCATION);}
"sget-wide"  {return Parser::make_OP_SGET_WIDE(LOCATION);}
"sget-object"        {return Parser::make_OP_SGET_OBJECT(LOCATION);}
"sget-boolean"       {return Parser::make_OP_SGET_BOOLEAN(LOCATION);}
"sget-byte"  {return Parser::make_OP_SGET_BYTE(LOCATION);}
"sget-char"  {return Parser::make_OP_SGET_CHAR(LOCATION);}
"sget-short" {return Parser::make_OP_SGET_SHORT(LOCATION);}
"sput"       {return Parser::make_OP_SPUT(LOCATION);}
"sput-wide"  {return Parser::make_OP_SPUT_WIDE(LOCATION);}
"sput-object"        {return Parser::make_OP_SPUT_OBJECT(LOCATION);}
"sput-boolean"       {return Parser::make_OP_SPUT_BOOLEAN(LOCATION);}
"sput-byte"  {return Parser::make_OP_SPUT_BYTE(LOCATION);}
"sput-char"  {return Parser::make_OP_SPUT_CHAR(LOCATION);}
"sput-short" {return Parser::make_OP_SPUT_SHORT(LOCATION);}
"invoke-virtual"     {return Parser::make_OP_INVOKE_VIRTUAL(LOCATION);}
"invoke-super"       {return Parser::make_OP_INVOKE_SUPER(LOCATION);}
"invoke-direct"      {return Parser::make_OP_INVOKE_DIRECT(LOCATION);}
"invoke-static"      {return Parser::make_OP_INVOKE_STATIC(LOCATION);}
"invoke-interface"   {return Parser::make_OP_INVOKE_INTERFACE(LOCATION);}
"unused-73"  {return Parser::make_OP_UNUSED_73(LOCATION);}
"invoke-virtual/range" {
                        return Parser::make_OP_INVOKE_VIRTUAL_RANGE(LOCATION);}
"invoke-super/range" {return Parser::make_OP_INVOKE_SUPER_RANGE(LOCATION);}
"invoke-direct/range" {
                        return Parser::make_OP_INVOKE_DIRECT_RANGE(LOCATION);}
"invoke-static/range" {
                        return Parser::make_OP_INVOKE_STATIC_RANGE(LOCATION);}
"invoke-interface/range" {
                        return Parser::make_OP_INVOKE_INTERFACE_RANGE(LOCATION);}
"unused-79"  {return Parser::make_OP_UNUSED_79(LOCATION);}
"unused-7a"  {return Parser::make_OP_UNUSED_7A(LOCATION);}
"neg-int"    {return Parser::make_OP_NEG_INT(LOCATION);}
"not-int"    {return Parser::make_OP_NOT_INT(LOCATION);}
"neg-long"   {return Parser::make_OP_NEG_LONG(LOCATION);}
"not-long"   {return Parser::make_OP_NOT_LONG(LOCATION);}
"neg-float"  {return Parser::make_OP_NEG_FLOAT(LOCATION);}
"neg-double" {return Parser::make_OP_NEG_DOUBLE(LOCATION);}
"int-to-long"        {return Parser::make_OP_INT_TO_LONG(LOCATION);}
"int-to-float"       {return Parser::make_OP_INT_TO_FLOAT(LOCATION);}
"int-to-double"      {return Parser::make_OP_INT_TO_DOUBLE(LOCATION);}
"long-to-int"        {return Parser::make_OP_LONG_TO_INT(LOCATION);}
"long-to-float"      {return Parser::make_OP_LONG_TO_FLOAT(LOCATION);}
"long-to-double"     {return Parser::make_OP_LONG_TO_DOUBLE(LOCATION);}
"float-to-int"       {return Parser::make_OP_FLOAT_TO_INT(LOCATION);}
"float-to-long"      {return Parser::make_OP_FLOAT_TO_LONG(LOCATION);}
"float-to-double"    {return Parser::make_OP_FLOAT_TO_DOUBLE(LOCATION);}
"double-to-int"      {return Parser::make_OP_DOUBLE_TO_INT(LOCATION);}
"double-to-long"     {return Parser::make_OP_DOUBLE_TO_LONG(LOCATION);}
"double-to-float"    {return Parser::make_OP_DOUBLE_TO_FLOAT(LOCATION);}
"int-to-byte"        {return Parser::make_OP_INT_TO_BYTE(LOCATION);}
"int-to-char"        {return Parser::make_OP_INT_TO_CHAR(LOCATION);}
"int-to-short"       {return Parser::make_OP_INT_TO_SHORT(LOCATION);}
"add-int"    {return Parser::make_OP_ADD_INT(LOCATION);}
"sub-int"    {return Parser::make_OP_SUB_INT(LOCATION);}
"mul-int"    {return Parser::make_OP_MUL_INT(LOCATION);}
"div-int"    {return Parser::make_OP_DIV_INT(LOCATION);}
"rem-int"    {return Parser::make_OP_REM_INT(LOCATION);}
"and-int"    {return Parser::make_OP_AND_INT(LOCATION);}
"or-int"     {return Parser::make_OP_OR_INT(LOCATION);}
"xor-int"    {return Parser::make_OP_XOR_INT(LOCATION);}
"shl-int"    {return Parser::make_OP_SHL_INT(LOCATION);}
"shr-int"    {return Parser::make_OP_SHR_INT(LOCATION);}
"ushr-int"   {return Parser::make_OP_USHR_INT(LOCATION);}
"add-long"   {return Parser::make_OP_ADD_LONG(LOCATION);}
"sub-long"   {return Parser::make_OP_SUB_LONG(LOCATION);}
"mul-long"   {return Parser::make_OP_MUL_LONG(LOCATION);}
"div-long"   {return Parser::make_OP_DIV_LONG(LOCATION);}
"rem-long"   {return Parser::make_OP_REM_LONG(LOCATION);}
"and-long"   {return Parser::make_OP_AND_LONG(LOCATION);}
"or-long"    {return Parser::make_OP_OR_LONG(LOCATION);}
"xor-long"   {return Parser::make_OP_XOR_LONG(LOCATION);}
"shl-long"   {return Parser::make_OP_SHL_LONG(LOCATION);}
"shr-long"   {return Parser::make_OP_SHR_LONG(LOCATION);}
"ushr-long"  {return Parser::make_OP_USHR_LONG(LOCATION);}
"add-float"  {return Parser::make_OP_ADD_FLOAT(LOCATION);}
"sub-float"  {return Parser::make_OP_SUB_FLOAT(LOCATION);}
"mul-float"  {return Parser::make_OP_MUL_FLOAT(LOCATION);}
"div-float"  {return Parser::make_OP_DIV_FLOAT(LOCATION);}
"rem-float"  {return Parser::make_OP_REM_FLOAT(LOCATION);}
"add-double" {return Parser::make_OP_ADD_DOUBLE(LOCATION);}
"sub-double" {return Parser::make_OP_SUB_DOUBLE(LOCATION);}
"mul-double" {return Parser::make_OP_MUL_DOUBLE(LOCATION);}
"div-double" {return Parser::make_OP_DIV_DOUBLE(LOCATION);}
"rem-double" {return Parser::make_OP_REM_DOUBLE(LOCATION);}
"add-int/2addr"      {return Parser::make_OP_ADD_INT_2ADDR(LOCATION);}
"sub-int/2addr"      {return Parser::make_OP_SUB_INT_2ADDR(LOCATION);}
"mul-int/2addr"      {return Parser::make_OP_MUL_INT_2ADDR(LOCATION);}
"div-int/2addr"      {return Parser::make_OP_DIV_INT_2ADDR(LOCATION);}
"rem-int/2addr"      {return Parser::make_OP_REM_INT_2ADDR(LOCATION);}
"and-int/2addr"      {return Parser::make_OP_AND_INT_2ADDR(LOCATION);}
"or-int/2addr"       {return Parser::make_OP_OR_INT_2ADDR(LOCATION);}
"xor-int/2addr"      {return Parser::make_OP_XOR_INT_2ADDR(LOCATION);}
"shl-int/2addr"      {return Parser::make_OP_SHL_INT_2ADDR(LOCATION);}
"shr-int/2addr"      {return Parser::make_OP_SHR_INT_2ADDR(LOCATION);}
"ushr-int/2addr"     {return Parser::make_OP_USHR_INT_2ADDR(LOCATION);}
"add-long/2addr"     {return Parser::make_OP_ADD_LONG_2ADDR(LOCATION);}
"sub-long/2addr"     {return Parser::make_OP_SUB_LONG_2ADDR(LOCATION);}
"mul-long/2addr"     {return Parser::make_OP_MUL_LONG_2ADDR(LOCATION);}
"div-long/2addr"     {return Parser::make_OP_DIV_LONG_2ADDR(LOCATION);}
"rem-long/2addr"     {return Parser::make_OP_REM_LONG_2ADDR(LOCATION);}
"and-long/2addr"     {return Parser::make_OP_AND_LONG_2ADDR(LOCATION);}
"or-long/2addr"      {return Parser::make_OP_OR_LONG_2ADDR(LOCATION);}
"xor-long/2addr"     {return Parser::make_OP_XOR_LONG_2ADDR(LOCATION);}
"shl-long/2addr"     {return Parser::make_OP_SHL_LONG_2ADDR(LOCATION);}
"shr-long/2addr"     {return Parser::make_OP_SHR_LONG_2ADDR(LOCATION);}
"ushr-long/2addr"    {return Parser::make_OP_USHR_LONG_2ADDR(LOCATION);}
"add-float/2addr"    {return Parser::make_OP_ADD_FLOAT_2ADDR(LOCATION);}
"sub-float/2addr"    {return Parser::make_OP_SUB_FLOAT_2ADDR(LOCATION);}
"mul-float/2addr"    {return Parser::make_OP_MUL_FLOAT_2ADDR(LOCATION);}
"div-float/2addr"    {return Parser::make_OP_DIV_FLOAT_2ADDR(LOCATION);}
"rem-float/2addr"    {return Parser::make_OP_REM_FLOAT_2ADDR(LOCATION);}
"add-double/2addr"   {return Parser::make_OP_ADD_DOUBLE_2ADDR(LOCATION);}
"sub-double/2addr"   {return Parser::make_OP_SUB_DOUBLE_2ADDR(LOCATION);}
"mul-double/2addr"   {return Parser::make_OP_MUL_DOUBLE_2ADDR(LOCATION);}
"div-double/2addr"   {return Parser::make_OP_DIV_DOUBLE_2ADDR(LOCATION);}
"rem-double/2addr"   {return Parser::make_OP_REM_DOUBLE_2ADDR(LOCATION);}
"add-int/lit16"      {return Parser::make_OP_ADD_INT_LIT16(LOCATION);}
"rsub-int"   {return Parser::make_OP_RSUB_INT(LOCATION);}
"mul-int/lit16"      {return Parser::make_OP_MUL_INT_LIT16(LOCATION);}
"div-int/lit16"      {return Parser::make_OP_DIV_INT_LIT16(LOCATION);}
"rem-int/lit16"      {return Parser::make_OP_REM_INT_LIT16(LOCATION);}
"and-int/lit16"      {return Parser::make_OP_AND_INT_LIT16(LOCATION);}
"or-int/lit16"       {return Parser::make_OP_OR_INT_LIT16(LOCATION);}
"xor-int/lit16"      {return Parser::make_OP_XOR_INT_LIT16(LOCATION);}
"add-int/lit8"       {return Parser::make_OP_ADD_INT_LIT8(LOCATION);}
"rsub-int/lit8"      {return Parser::make_OP_RSUB_INT_LIT8(LOCATION);}
"mul-int/lit8"       {return Parser::make_OP_MUL_INT_LIT8(LOCATION);}
"div-int/lit8"       {return Parser::make_OP_DIV_INT_LIT8(LOCATION);}
"rem-int/lit8"       {return Parser::make_OP_REM_INT_LIT8(LOCATION);}
"and-int/lit8"       {return Parser::make_OP_AND_INT_LIT8(LOCATION);}
"or-int/lit8"        {return Parser::make_OP_OR_INT_LIT8(LOCATION);}
"xor-int/lit8"       {return Parser::make_OP_XOR_INT_LIT8(LOCATION);}
"shl-int/lit8"       {return Parser::make_OP_SHL_INT_LIT8(LOCATION);}
"shr-int/lit8"       {return Parser::make_OP_SHR_INT_LIT8(LOCATION);}
"ushr-int/lit8"      {return Parser::make_OP_USHR_INT_LIT8(LOCATION);}
"+iget-volatile"     {return Parser::make_OP_IGET_VOLATILE(LOCATION);}
"+iput-volatile"     {return Parser::make_OP_IPUT_VOLATILE(LOCATION);}
"+sget-volatile"     {return Parser::make_OP_SGET_VOLATILE(LOCATION);}
"+sput-volatile"     {return Parser::make_OP_SPUT_VOLATILE(LOCATION);}
"+iget-object-volatile" {
                        return Parser::make_OP_IGET_OBJECT_VOLATILE(LOCATION);}
"+iget-wide-volatile" {
                        return Parser::make_OP_IGET_WIDE_VOLATILE(LOCATION);}
"+iput-wide-volatile" {
                        return Parser::make_OP_IPUT_WIDE_VOLATILE(LOCATION);}
"+sget-wide-volatile" {
                        return Parser::make_OP_SGET_WIDE_VOLATILE(LOCATION);}
"+sput-wide-volatile" {
                        return Parser::make_OP_SPUT_WIDE_VOLATILE(LOCATION);}
"^breakpoint"        {return Parser::make_OP_BREAKPOINT(LOCATION);}
"^throw-verification-error" {
                        return Parser::make_OP_THROW_VERIFICATION_ERROR(LOCATION);}
"+execute-inline"    {return Parser::make_OP_EXECUTE_INLINE(LOCATION);}
"+execute-inline/range" {
                        return Parser::make_OP_EXECUTE_INLINE_RANGE(LOCATION);}
"+invoke-object-init/range" {
                        return Parser::make_OP_INVOKE_OBJECT_INIT_RANGE(LOCATION);}
"+return-void-barrier" {
                        return Parser::make_OP_RETURN_VOID_BARRIER(LOCATION);}
"+iget-quick"        {return Parser::make_OP_IGET_QUICK(LOCATION);}
"+iget-wide-quick"   {return Parser::make_OP_IGET_WIDE_QUICK(LOCATION);}
"+iget-object-quick" {return Parser::make_OP_IGET_OBJECT_QUICK(LOCATION);}
"+iput-quick"        {return Parser::make_OP_IPUT_QUICK(LOCATION);}
"+iput-wide-quick"   {return Parser::make_OP_IPUT_WIDE_QUICK(LOCATION);}
"+iput-object-quick" {return Parser::make_OP_IPUT_OBJECT_QUICK(LOCATION);}
"+invoke-virtual-quick" {
                        return Parser::make_OP_INVOKE_VIRTUAL_QUICK(LOCATION);}
"+invoke-virtual-quick/range" {
                        return Parser::make_OP_INVOKE_VIRTUAL_QUICK_RANGE(LOCATION);}
"+invoke-super-quick" {
                        return Parser::make_OP_INVOKE_SUPER_QUICK(LOCATION);}
"+invoke-super-quick/range" {
                        return Parser::make_OP_INVOKE_SUPER_QUICK_RANGE(LOCATION);}
"+iput-object-volatile" {
                        return Parser::make_OP_IPUT_OBJECT_VOLATILE(LOCATION);}
"+sget-object-volatile" {
                        return Parser::make_OP_SGET_OBJECT_VOLATILE(LOCATION);}
"+sput-object-volatile" {
                        return Parser::make_OP_SPUT_OBJECT_VOLATILE(LOCATION);}
"unused-ff"  {return Parser::make_OP_UNUSED_FF(LOCATION);}
".catch"     {return Parser::make_OP_CATCH(LOCATION);}

[vp][0-9]+ {
                    int number = strtoull(yytext + 1, 0, 10);
                    if (yytext[0] == 'p' || yytext[0] == 'P') {
                        number |= 0x100;
                    }
                    return Parser::make_REGD(number, LOCATION);
                }


    /*          flags          */
"public" {
        return Parser::make_FLAG(ACC_FLAGS::ACC_PUBLIC, LOCATION);}
"private" {
        return Parser::make_FLAG(ACC_FLAGS::ACC_PRIVATE, LOCATION);}
"protected" {
        return Parser::make_FLAG(ACC_FLAGS::ACC_PROTECTED, LOCATION);}
"static" {
        return Parser::make_FLAG(ACC_FLAGS::ACC_STATIC, LOCATION);}
"final" {
        return Parser::make_FLAG(ACC_FLAGS::ACC_FINAL, LOCATION);}
"synchronized" {
        return Parser::make_FLAG(ACC_FLAGS::ACC_SYNCHRONIZED, LOCATION);}
"super" {
        return Parser::make_FLAG(ACC_FLAGS::ACC_SUPER, LOCATION);}
"volatile" {
        return Parser::make_FLAG(ACC_FLAGS::ACC_VOLATILE, LOCATION);}
"bridge" {
        return Parser::make_FLAG(ACC_FLAGS::ACC_BRIDGE, LOCATION);}
"transient" {
        return Parser::make_FLAG(ACC_FLAGS::ACC_TRANSIENT, LOCATION);}
"varargs" {
        return Parser::make_FLAG(ACC_FLAGS::ACC_VARARGS, LOCATION);}
"native" {
        return Parser::make_FLAG(ACC_FLAGS::ACC_NATIVE, LOCATION);}
"interface" {
        return Parser::make_FLAG(ACC_FLAGS::ACC_INTERFACE, LOCATION);}
"abstract" {
        return Parser::make_FLAG(ACC_FLAGS::ACC_ABSTRACT, LOCATION);}
"strict" {
        return Parser::make_FLAG(ACC_FLAGS::ACC_STRICT, LOCATION);}
"synthetic" {
        return Parser::make_FLAG(ACC_FLAGS::ACC_SYNTHETIC, LOCATION);}
"annotation" {
        return Parser::make_FLAG(ACC_FLAGS::ACC_ANNOTATION, LOCATION);}
"enum" {
        return Parser::make_FLAG(ACC_FLAGS::ACC_ENUM, LOCATION);}
"constructor" {
        return Parser::make_FLAG(ACC_FLAGS::ACC_CONSTRUCTOR, LOCATION);}
"declared-synchronized" {
        return Parser::make_FLAG(ACC_FLAGS::ACC_DECLARED_SYNCHRONIZED, LOCATION);}

":"         {return Parser::make_COLON(LOCATION);}
"("         {BEGIN(ARGSDEF); return Parser::make_LEFTPAR(LOCATION);}
<ARGSDEF>")"         {BEGIN(INITIAL); return Parser::make_RIGHTPAR(LOCATION);}
"," {return Parser::make_COMMA(LOCATION);}
"->" {return Parser::make_POINT(LOCATION);}
"{" {return Parser::make_INIBRACE(LOCATION);}
"}"  {return Parser::make_CLOBRACE(LOCATION);}
".."  {return Parser::make_ELLIPSIS(LOCATION);}


[-]?{DNUMBER}   {
                int64_t number = strtoll(yytext, 0, 10);
                return Parser::make_NUMBER(number, LOCATION);
            }
[-]?"0x"{HNUMBER} {
                int64_t number = strtoll(yytext, 0, 16);
                return Parser::make_NUMBER(number, LOCATION);
            }

{CSTRING} {
        return Parser::make_CSTRING(std::string(yytext+1, yyleng - 2), LOCATION);}
{NAMESTRING} {return Parser::make_NAMESTRING(yytext, LOCATION);}


.           {;}
<<EOF>>     {return yyterminate(); }

%%

void Analysis::Lexer::beginInitial() {
    BEGIN(INITIAL);
}

void Analysis::Lexer::beginArgsDef() {
    BEGIN(ARGSDEF);
}
