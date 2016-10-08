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
//
//===----------------------------------------------------------------------===//
	#include <iostream>
	#include <cstdlib>
    #include "Lexer.h"
	#include "Parser.hpp"
	#include "location.hh"
    #include "AndroidDef.h"

	using namespace std;
	using namespace Analysis;

	#define yyterminate() Analysis::Parser::make_END(\
	    Analysis::location(YY_NULL,line(), column()));

	#define YY_USER_ACTION acceptToken(yytext, yyleng);
    #define LOCATION Analysis::location(YY_NULL, line(), column())
%}

%option nodefault
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

ASCSTR  [0-9a-zA-Z/\x3C\x3E_]
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

%s METHODDEF ARGSDEF

%%
{OWS}+
{EOL}       {return Parser::make_EOL(LOCATION); }
{COMMENT}   {return Analysis::Parser::make_COMMENT(yytext, LOCATION);}
{CLASSTYPE} {return Analysis::Parser::make_CLASSTYPE(yytext, LOCATION);}

   /*        declration        */
<INITIAL>".class"  {return Parser::make_CLASSBEG(LOCATION);}
<INITIAL>".super"  {return Parser::make_SUPERBEG(LOCATION);}
<INITIAL>".source"    {return Parser::make_SRCBEG(LOCATION);}
<INITIAL>".field"  {return Parser::make_FIELDBEG(LOCATION);}
<INITIAL>".method" {BEGIN(METHODDEF);
                    return Parser::make_METHODBEG(LOCATION);}
<METHODDEF>".end method" {BEGIN(INITIAL);
                    return Parser::make_METHODEND(LOCATION);}


    /*      method keyword  */
<METHODDEF>".registers"  {return Parser::make_REGISTERS(LOCATION);}
<METHODDEF>".prologue"    {return Parser::make_PROLOGUE(LOCATION);}
<METHODDEF>".line"       {return Parser::make_LINE(LOCATION);}

    /*      instruction keyword     */
<METHODDEF>"nop"        {return Parser::make_OP_NOP(LOCATION);}
<METHODDEF>"move"       {return Parser::make_OP_MOVE(LOCATION);}
<METHODDEF>"move/from16"        {return Parser::make_OP_MOVE_FROM16(LOCATION);}
<METHODDEF>"move/16"    {return Parser::make_OP_MOVE_16(LOCATION);}
<METHODDEF>"move-wide"  {return Parser::make_OP_MOVE_WIDE(LOCATION);}
<METHODDEF>"move-wide/from16"   {return Parser::make_OP_MOVE_WIDE_FROM16(LOCATION);}
<METHODDEF>"move-wide/16"       {return Parser::make_OP_MOVE_WIDE_16(LOCATION);}
<METHODDEF>"move-object"        {return Parser::make_OP_MOVE_OBJECT(LOCATION);}
<METHODDEF>"move-object/from16" {return Parser::make_OP_MOVE_OBJECT_FROM16(LOCATION);}
<METHODDEF>"move-object/16"     {return Parser::make_OP_MOVE_OBJECT_16(LOCATION);}
<METHODDEF>"move-result"        {return Parser::make_OP_MOVE_RESULT(LOCATION);}
<METHODDEF>"move-result-wide"   {return Parser::make_OP_MOVE_RESULT_WIDE(LOCATION);}
<METHODDEF>"move-result-object" {return Parser::make_OP_MOVE_RESULT_OBJECT(LOCATION);}
<METHODDEF>"move-exception"     {return Parser::make_OP_MOVE_EXCEPTION(LOCATION);}
<METHODDEF>"return-void"        {return Parser::make_OP_RETURN_VOID(LOCATION);}
<METHODDEF>"return"     {return Parser::make_OP_RETURN(LOCATION);}
<METHODDEF>"return-wide"        {return Parser::make_OP_RETURN_WIDE(LOCATION);}
<METHODDEF>"return-object"      {return Parser::make_OP_RETURN_OBJECT(LOCATION);}
<METHODDEF>"const/4"    {return Parser::make_OP_CONST_4(LOCATION);}
<METHODDEF>"const/16"   {return Parser::make_OP_CONST_16(LOCATION);}
<METHODDEF>"const"      {return Parser::make_OP_CONST(LOCATION);}
<METHODDEF>"const/high16"       {return Parser::make_OP_CONST_HIGH16(LOCATION);}
<METHODDEF>"const-wide/16"      {return Parser::make_OP_CONST_WIDE_16(LOCATION);}
<METHODDEF>"const-wide/32"      {return Parser::make_OP_CONST_WIDE_32(LOCATION);}
<METHODDEF>"const-wide" {return Parser::make_OP_CONST_WIDE(LOCATION);}
<METHODDEF>"const-wide/high16"  {return Parser::make_OP_CONST_WIDE_HIGH16(LOCATION);}
<METHODDEF>"const-string"       {return Parser::make_OP_CONST_STRING(LOCATION);}
<METHODDEF>"const-string/jumbo" {return Parser::make_OP_CONST_STRING_JUMBO(LOCATION);}
<METHODDEF>"const-class"        {return Parser::make_OP_CONST_CLASS(LOCATION);}
<METHODDEF>"monitor-enter"      {return Parser::make_OP_MONITOR_ENTER(LOCATION);}
<METHODDEF>"monitor-exit"       {return Parser::make_OP_MONITOR_EXIT(LOCATION);}
<METHODDEF>"check-cast" {return Parser::make_OP_CHECK_CAST(LOCATION);}
<METHODDEF>"instance-of"        {return Parser::make_OP_INSTANCE_OF(LOCATION);}
<METHODDEF>"array-length"       {return Parser::make_OP_ARRAY_LENGTH(LOCATION);}
<METHODDEF>"new-instance"       {return Parser::make_OP_NEW_INSTANCE(LOCATION);}
<METHODDEF>"new-array"  {return Parser::make_OP_NEW_ARRAY(LOCATION);}
<METHODDEF>"filled-new-array"   {return Parser::make_OP_FILLED_NEW_ARRAY(LOCATION);}
<METHODDEF>"filled-new-array/range" {
                    return Parser::make_OP_FILLED_NEW_ARRAY_RANGE(LOCATION);}
<METHODDEF>"fill-array-data"    {return Parser::make_OP_FILL_ARRAY_DATA(LOCATION);}
<METHODDEF>"throw"      {return Parser::make_OP_THROW(LOCATION);}
<METHODDEF>"goto"       {return Parser::make_OP_GOTO(LOCATION);}
<METHODDEF>"goto/16"    {return Parser::make_OP_GOTO_16(LOCATION);}
<METHODDEF>"goto/32"    {return Parser::make_OP_GOTO_32(LOCATION);}
<METHODDEF>"packed-switch"      {return Parser::make_OP_PACKED_SWITCH(LOCATION);}
<METHODDEF>"sparse-switch"      {return Parser::make_OP_SPARSE_SWITCH(LOCATION);}
<METHODDEF>"cmpl-float" {return Parser::make_OP_CMPL_FLOAT(LOCATION);}
<METHODDEF>"cmpg-float" {return Parser::make_OP_CMPG_FLOAT(LOCATION);}
<METHODDEF>"cmpl-double"        {return Parser::make_OP_CMPL_DOUBLE(LOCATION);}
<METHODDEF>"cmpg-double"        {return Parser::make_OP_CMPG_DOUBLE(LOCATION);}
<METHODDEF>"cmp-long"   {return Parser::make_OP_CMP_LONG(LOCATION);}
<METHODDEF>"if-eq"      {return Parser::make_OP_IF_EQ(LOCATION);}
<METHODDEF>"if-ne"      {return Parser::make_OP_IF_NE(LOCATION);}
<METHODDEF>"if-lt"      {return Parser::make_OP_IF_LT(LOCATION);}
<METHODDEF>"if-ge"      {return Parser::make_OP_IF_GE(LOCATION);}
<METHODDEF>"if-gt"      {return Parser::make_OP_IF_GT(LOCATION);}
<METHODDEF>"if-le"      {return Parser::make_OP_IF_LE(LOCATION);}
<METHODDEF>"if-eqz"     {return Parser::make_OP_IF_EQZ(LOCATION);}
<METHODDEF>"if-nez"     {return Parser::make_OP_IF_NEZ(LOCATION);}
<METHODDEF>"if-ltz"     {return Parser::make_OP_IF_LTZ(LOCATION);}
<METHODDEF>"if-gez"     {return Parser::make_OP_IF_GEZ(LOCATION);}
<METHODDEF>"if-gtz"     {return Parser::make_OP_IF_GTZ(LOCATION);}
<METHODDEF>"if-lez"     {return Parser::make_OP_IF_LEZ(LOCATION);}
<METHODDEF>"unused-3e"  {return Parser::make_OP_UNUSED_3E(LOCATION);}
<METHODDEF>"unused-3f"  {return Parser::make_OP_UNUSED_3F(LOCATION);}
<METHODDEF>"unused-40"  {return Parser::make_OP_UNUSED_40(LOCATION);}
<METHODDEF>"unused-41"  {return Parser::make_OP_UNUSED_41(LOCATION);}
<METHODDEF>"unused-42"  {return Parser::make_OP_UNUSED_42(LOCATION);}
<METHODDEF>"unused-43"  {return Parser::make_OP_UNUSED_43(LOCATION);}
<METHODDEF>"aget"       {return Parser::make_OP_AGET(LOCATION);}
<METHODDEF>"aget-wide"  {return Parser::make_OP_AGET_WIDE(LOCATION);}
<METHODDEF>"aget-object"        {return Parser::make_OP_AGET_OBJECT(LOCATION);}
<METHODDEF>"aget-boolean"       {return Parser::make_OP_AGET_BOOLEAN(LOCATION);}
<METHODDEF>"aget-byte"  {return Parser::make_OP_AGET_BYTE(LOCATION);}
<METHODDEF>"aget-char"  {return Parser::make_OP_AGET_CHAR(LOCATION);}
<METHODDEF>"aget-short" {return Parser::make_OP_AGET_SHORT(LOCATION);}
<METHODDEF>"aput"       {return Parser::make_OP_APUT(LOCATION);}
<METHODDEF>"aput-wide"  {return Parser::make_OP_APUT_WIDE(LOCATION);}
<METHODDEF>"aput-object"        {return Parser::make_OP_APUT_OBJECT(LOCATION);}
<METHODDEF>"aput-boolean"       {return Parser::make_OP_APUT_BOOLEAN(LOCATION);}
<METHODDEF>"aput-byte"  {return Parser::make_OP_APUT_BYTE(LOCATION);}
<METHODDEF>"aput-char"  {return Parser::make_OP_APUT_CHAR(LOCATION);}
<METHODDEF>"aput-short" {return Parser::make_OP_APUT_SHORT(LOCATION);}
<METHODDEF>"iget"       {return Parser::make_OP_IGET(LOCATION);}
<METHODDEF>"iget-wide"  {return Parser::make_OP_IGET_WIDE(LOCATION);}
<METHODDEF>"iget-object"        {return Parser::make_OP_IGET_OBJECT(LOCATION);}
<METHODDEF>"iget-boolean"       {return Parser::make_OP_IGET_BOOLEAN(LOCATION);}
<METHODDEF>"iget-byte"  {return Parser::make_OP_IGET_BYTE(LOCATION);}
<METHODDEF>"iget-char"  {return Parser::make_OP_IGET_CHAR(LOCATION);}
<METHODDEF>"iget-short" {return Parser::make_OP_IGET_SHORT(LOCATION);}
<METHODDEF>"iput"       {return Parser::make_OP_IPUT(LOCATION);}
<METHODDEF>"iput-wide"  {return Parser::make_OP_IPUT_WIDE(LOCATION);}
<METHODDEF>"iput-object"        {return Parser::make_OP_IPUT_OBJECT(LOCATION);}
<METHODDEF>"iput-boolean"       {return Parser::make_OP_IPUT_BOOLEAN(LOCATION);}
<METHODDEF>"iput-byte"  {return Parser::make_OP_IPUT_BYTE(LOCATION);}
<METHODDEF>"iput-char"  {return Parser::make_OP_IPUT_CHAR(LOCATION);}
<METHODDEF>"iput-short" {return Parser::make_OP_IPUT_SHORT(LOCATION);}
<METHODDEF>"sget"       {return Parser::make_OP_SGET(LOCATION);}
<METHODDEF>"sget-wide"  {return Parser::make_OP_SGET_WIDE(LOCATION);}
<METHODDEF>"sget-object"        {return Parser::make_OP_SGET_OBJECT(LOCATION);}
<METHODDEF>"sget-boolean"       {return Parser::make_OP_SGET_BOOLEAN(LOCATION);}
<METHODDEF>"sget-byte"  {return Parser::make_OP_SGET_BYTE(LOCATION);}
<METHODDEF>"sget-char"  {return Parser::make_OP_SGET_CHAR(LOCATION);}
<METHODDEF>"sget-short" {return Parser::make_OP_SGET_SHORT(LOCATION);}
<METHODDEF>"sput"       {return Parser::make_OP_SPUT(LOCATION);}
<METHODDEF>"sput-wide"  {return Parser::make_OP_SPUT_WIDE(LOCATION);}
<METHODDEF>"sput-object"        {return Parser::make_OP_SPUT_OBJECT(LOCATION);}
<METHODDEF>"sput-boolean"       {return Parser::make_OP_SPUT_BOOLEAN(LOCATION);}
<METHODDEF>"sput-byte"  {return Parser::make_OP_SPUT_BYTE(LOCATION);}
<METHODDEF>"sput-char"  {return Parser::make_OP_SPUT_CHAR(LOCATION);}
<METHODDEF>"sput-short" {return Parser::make_OP_SPUT_SHORT(LOCATION);}
<METHODDEF>"invoke-virtual"     {return Parser::make_OP_INVOKE_VIRTUAL(LOCATION);}
<METHODDEF>"invoke-super"       {return Parser::make_OP_INVOKE_SUPER(LOCATION);}
<METHODDEF>"invoke-direct"      {return Parser::make_OP_INVOKE_DIRECT(LOCATION);}
<METHODDEF>"invoke-static"      {return Parser::make_OP_INVOKE_STATIC(LOCATION);}
<METHODDEF>"invoke-interface"   {return Parser::make_OP_INVOKE_INTERFACE(LOCATION);}
<METHODDEF>"unused-73"  {return Parser::make_OP_UNUSED_73(LOCATION);}
<METHODDEF>"invoke-virtual/range" {
                        return Parser::make_OP_INVOKE_VIRTUAL_RANGE(LOCATION);}
<METHODDEF>"invoke-super/range" {return Parser::make_OP_INVOKE_SUPER_RANGE(LOCATION);}
<METHODDEF>"invoke-direct/range" {
                        return Parser::make_OP_INVOKE_DIRECT_RANGE(LOCATION);}
<METHODDEF>"invoke-static/range" {
                        return Parser::make_OP_INVOKE_STATIC_RANGE(LOCATION);}
<METHODDEF>"invoke-interface/range" {
                        return Parser::make_OP_INVOKE_INTERFACE_RANGE(LOCATION);}
<METHODDEF>"unused-79"  {return Parser::make_OP_UNUSED_79(LOCATION);}
<METHODDEF>"unused-7a"  {return Parser::make_OP_UNUSED_7A(LOCATION);}
<METHODDEF>"neg-int"    {return Parser::make_OP_NEG_INT(LOCATION);}
<METHODDEF>"not-int"    {return Parser::make_OP_NOT_INT(LOCATION);}
<METHODDEF>"neg-long"   {return Parser::make_OP_NEG_LONG(LOCATION);}
<METHODDEF>"not-long"   {return Parser::make_OP_NOT_LONG(LOCATION);}
<METHODDEF>"neg-float"  {return Parser::make_OP_NEG_FLOAT(LOCATION);}
<METHODDEF>"neg-double" {return Parser::make_OP_NEG_DOUBLE(LOCATION);}
<METHODDEF>"int-to-long"        {return Parser::make_OP_INT_TO_LONG(LOCATION);}
<METHODDEF>"int-to-float"       {return Parser::make_OP_INT_TO_FLOAT(LOCATION);}
<METHODDEF>"int-to-double"      {return Parser::make_OP_INT_TO_DOUBLE(LOCATION);}
<METHODDEF>"long-to-int"        {return Parser::make_OP_LONG_TO_INT(LOCATION);}
<METHODDEF>"long-to-float"      {return Parser::make_OP_LONG_TO_FLOAT(LOCATION);}
<METHODDEF>"long-to-double"     {return Parser::make_OP_LONG_TO_DOUBLE(LOCATION);}
<METHODDEF>"float-to-int"       {return Parser::make_OP_FLOAT_TO_INT(LOCATION);}
<METHODDEF>"float-to-long"      {return Parser::make_OP_FLOAT_TO_LONG(LOCATION);}
<METHODDEF>"float-to-double"    {return Parser::make_OP_FLOAT_TO_DOUBLE(LOCATION);}
<METHODDEF>"double-to-int"      {return Parser::make_OP_DOUBLE_TO_INT(LOCATION);}
<METHODDEF>"double-to-long"     {return Parser::make_OP_DOUBLE_TO_LONG(LOCATION);}
<METHODDEF>"double-to-float"    {return Parser::make_OP_DOUBLE_TO_FLOAT(LOCATION);}
<METHODDEF>"int-to-byte"        {return Parser::make_OP_INT_TO_BYTE(LOCATION);}
<METHODDEF>"int-to-char"        {return Parser::make_OP_INT_TO_CHAR(LOCATION);}
<METHODDEF>"int-to-short"       {return Parser::make_OP_INT_TO_SHORT(LOCATION);}
<METHODDEF>"add-int"    {return Parser::make_OP_ADD_INT(LOCATION);}
<METHODDEF>"sub-int"    {return Parser::make_OP_SUB_INT(LOCATION);}
<METHODDEF>"mul-int"    {return Parser::make_OP_MUL_INT(LOCATION);}
<METHODDEF>"div-int"    {return Parser::make_OP_DIV_INT(LOCATION);}
<METHODDEF>"rem-int"    {return Parser::make_OP_REM_INT(LOCATION);}
<METHODDEF>"and-int"    {return Parser::make_OP_AND_INT(LOCATION);}
<METHODDEF>"or-int"     {return Parser::make_OP_OR_INT(LOCATION);}
<METHODDEF>"xor-int"    {return Parser::make_OP_XOR_INT(LOCATION);}
<METHODDEF>"shl-int"    {return Parser::make_OP_SHL_INT(LOCATION);}
<METHODDEF>"shr-int"    {return Parser::make_OP_SHR_INT(LOCATION);}
<METHODDEF>"ushr-int"   {return Parser::make_OP_USHR_INT(LOCATION);}
<METHODDEF>"add-long"   {return Parser::make_OP_ADD_LONG(LOCATION);}
<METHODDEF>"sub-long"   {return Parser::make_OP_SUB_LONG(LOCATION);}
<METHODDEF>"mul-long"   {return Parser::make_OP_MUL_LONG(LOCATION);}
<METHODDEF>"div-long"   {return Parser::make_OP_DIV_LONG(LOCATION);}
<METHODDEF>"rem-long"   {return Parser::make_OP_REM_LONG(LOCATION);}
<METHODDEF>"and-long"   {return Parser::make_OP_AND_LONG(LOCATION);}
<METHODDEF>"or-long"    {return Parser::make_OP_OR_LONG(LOCATION);}
<METHODDEF>"xor-long"   {return Parser::make_OP_XOR_LONG(LOCATION);}
<METHODDEF>"shl-long"   {return Parser::make_OP_SHL_LONG(LOCATION);}
<METHODDEF>"shr-long"   {return Parser::make_OP_SHR_LONG(LOCATION);}
<METHODDEF>"ushr-long"  {return Parser::make_OP_USHR_LONG(LOCATION);}
<METHODDEF>"add-float"  {return Parser::make_OP_ADD_FLOAT(LOCATION);}
<METHODDEF>"sub-float"  {return Parser::make_OP_SUB_FLOAT(LOCATION);}
<METHODDEF>"mul-float"  {return Parser::make_OP_MUL_FLOAT(LOCATION);}
<METHODDEF>"div-float"  {return Parser::make_OP_DIV_FLOAT(LOCATION);}
<METHODDEF>"rem-float"  {return Parser::make_OP_REM_FLOAT(LOCATION);}
<METHODDEF>"add-double" {return Parser::make_OP_ADD_DOUBLE(LOCATION);}
<METHODDEF>"sub-double" {return Parser::make_OP_SUB_DOUBLE(LOCATION);}
<METHODDEF>"mul-double" {return Parser::make_OP_MUL_DOUBLE(LOCATION);}
<METHODDEF>"div-double" {return Parser::make_OP_DIV_DOUBLE(LOCATION);}
<METHODDEF>"rem-double" {return Parser::make_OP_REM_DOUBLE(LOCATION);}
<METHODDEF>"add-int/2addr"      {return Parser::make_OP_ADD_INT_2ADDR(LOCATION);}
<METHODDEF>"sub-int/2addr"      {return Parser::make_OP_SUB_INT_2ADDR(LOCATION);}
<METHODDEF>"mul-int/2addr"      {return Parser::make_OP_MUL_INT_2ADDR(LOCATION);}
<METHODDEF>"div-int/2addr"      {return Parser::make_OP_DIV_INT_2ADDR(LOCATION);}
<METHODDEF>"rem-int/2addr"      {return Parser::make_OP_REM_INT_2ADDR(LOCATION);}
<METHODDEF>"and-int/2addr"      {return Parser::make_OP_AND_INT_2ADDR(LOCATION);}
<METHODDEF>"or-int/2addr"       {return Parser::make_OP_OR_INT_2ADDR(LOCATION);}
<METHODDEF>"xor-int/2addr"      {return Parser::make_OP_XOR_INT_2ADDR(LOCATION);}
<METHODDEF>"shl-int/2addr"      {return Parser::make_OP_SHL_INT_2ADDR(LOCATION);}
<METHODDEF>"shr-int/2addr"      {return Parser::make_OP_SHR_INT_2ADDR(LOCATION);}
<METHODDEF>"ushr-int/2addr"     {return Parser::make_OP_USHR_INT_2ADDR(LOCATION);}
<METHODDEF>"add-long/2addr"     {return Parser::make_OP_ADD_LONG_2ADDR(LOCATION);}
<METHODDEF>"sub-long/2addr"     {return Parser::make_OP_SUB_LONG_2ADDR(LOCATION);}
<METHODDEF>"mul-long/2addr"     {return Parser::make_OP_MUL_LONG_2ADDR(LOCATION);}
<METHODDEF>"div-long/2addr"     {return Parser::make_OP_DIV_LONG_2ADDR(LOCATION);}
<METHODDEF>"rem-long/2addr"     {return Parser::make_OP_REM_LONG_2ADDR(LOCATION);}
<METHODDEF>"and-long/2addr"     {return Parser::make_OP_AND_LONG_2ADDR(LOCATION);}
<METHODDEF>"or-long/2addr"      {return Parser::make_OP_OR_LONG_2ADDR(LOCATION);}
<METHODDEF>"xor-long/2addr"     {return Parser::make_OP_XOR_LONG_2ADDR(LOCATION);}
<METHODDEF>"shl-long/2addr"     {return Parser::make_OP_SHL_LONG_2ADDR(LOCATION);}
<METHODDEF>"shr-long/2addr"     {return Parser::make_OP_SHR_LONG_2ADDR(LOCATION);}
<METHODDEF>"ushr-long/2addr"    {return Parser::make_OP_USHR_LONG_2ADDR(LOCATION);}
<METHODDEF>"add-float/2addr"    {return Parser::make_OP_ADD_FLOAT_2ADDR(LOCATION);}
<METHODDEF>"sub-float/2addr"    {return Parser::make_OP_SUB_FLOAT_2ADDR(LOCATION);}
<METHODDEF>"mul-float/2addr"    {return Parser::make_OP_MUL_FLOAT_2ADDR(LOCATION);}
<METHODDEF>"div-float/2addr"    {return Parser::make_OP_DIV_FLOAT_2ADDR(LOCATION);}
<METHODDEF>"rem-float/2addr"    {return Parser::make_OP_REM_FLOAT_2ADDR(LOCATION);}
<METHODDEF>"add-double/2addr"   {return Parser::make_OP_ADD_DOUBLE_2ADDR(LOCATION);}
<METHODDEF>"sub-double/2addr"   {return Parser::make_OP_SUB_DOUBLE_2ADDR(LOCATION);}
<METHODDEF>"mul-double/2addr"   {return Parser::make_OP_MUL_DOUBLE_2ADDR(LOCATION);}
<METHODDEF>"div-double/2addr"   {return Parser::make_OP_DIV_DOUBLE_2ADDR(LOCATION);}
<METHODDEF>"rem-double/2addr"   {return Parser::make_OP_REM_DOUBLE_2ADDR(LOCATION);}
<METHODDEF>"add-int/lit16"      {return Parser::make_OP_ADD_INT_LIT16(LOCATION);}
<METHODDEF>"rsub-int"   {return Parser::make_OP_RSUB_INT(LOCATION);}
<METHODDEF>"mul-int/lit16"      {return Parser::make_OP_MUL_INT_LIT16(LOCATION);}
<METHODDEF>"div-int/lit16"      {return Parser::make_OP_DIV_INT_LIT16(LOCATION);}
<METHODDEF>"rem-int/lit16"      {return Parser::make_OP_REM_INT_LIT16(LOCATION);}
<METHODDEF>"and-int/lit16"      {return Parser::make_OP_AND_INT_LIT16(LOCATION);}
<METHODDEF>"or-int/lit16"       {return Parser::make_OP_OR_INT_LIT16(LOCATION);}
<METHODDEF>"xor-int/lit16"      {return Parser::make_OP_XOR_INT_LIT16(LOCATION);}
<METHODDEF>"add-int/lit8"       {return Parser::make_OP_ADD_INT_LIT8(LOCATION);}
<METHODDEF>"rsub-int/lit8"      {return Parser::make_OP_RSUB_INT_LIT8(LOCATION);}
<METHODDEF>"mul-int/lit8"       {return Parser::make_OP_MUL_INT_LIT8(LOCATION);}
<METHODDEF>"div-int/lit8"       {return Parser::make_OP_DIV_INT_LIT8(LOCATION);}
<METHODDEF>"rem-int/lit8"       {return Parser::make_OP_REM_INT_LIT8(LOCATION);}
<METHODDEF>"and-int/lit8"       {return Parser::make_OP_AND_INT_LIT8(LOCATION);}
<METHODDEF>"or-int/lit8"        {return Parser::make_OP_OR_INT_LIT8(LOCATION);}
<METHODDEF>"xor-int/lit8"       {return Parser::make_OP_XOR_INT_LIT8(LOCATION);}
<METHODDEF>"shl-int/lit8"       {return Parser::make_OP_SHL_INT_LIT8(LOCATION);}
<METHODDEF>"shr-int/lit8"       {return Parser::make_OP_SHR_INT_LIT8(LOCATION);}
<METHODDEF>"ushr-int/lit8"      {return Parser::make_OP_USHR_INT_LIT8(LOCATION);}
<METHODDEF>"+iget-volatile"     {return Parser::make_OP_IGET_VOLATILE(LOCATION);}
<METHODDEF>"+iput-volatile"     {return Parser::make_OP_IPUT_VOLATILE(LOCATION);}
<METHODDEF>"+sget-volatile"     {return Parser::make_OP_SGET_VOLATILE(LOCATION);}
<METHODDEF>"+sput-volatile"     {return Parser::make_OP_SPUT_VOLATILE(LOCATION);}
<METHODDEF>"+iget-object-volatile" {
                        return Parser::make_OP_IGET_OBJECT_VOLATILE(LOCATION);}
<METHODDEF>"+iget-wide-volatile" {
                        return Parser::make_OP_IGET_WIDE_VOLATILE(LOCATION);}
<METHODDEF>"+iput-wide-volatile" {
                        return Parser::make_OP_IPUT_WIDE_VOLATILE(LOCATION);}
<METHODDEF>"+sget-wide-volatile" {
                        return Parser::make_OP_SGET_WIDE_VOLATILE(LOCATION);}
<METHODDEF>"+sput-wide-volatile" {
                        return Parser::make_OP_SPUT_WIDE_VOLATILE(LOCATION);}
<METHODDEF>"^breakpoint"        {return Parser::make_OP_BREAKPOINT(LOCATION);}
<METHODDEF>"^throw-verification-error" {
                        return Parser::make_OP_THROW_VERIFICATION_ERROR(LOCATION);}
<METHODDEF>"+execute-inline"    {return Parser::make_OP_EXECUTE_INLINE(LOCATION);}
<METHODDEF>"+execute-inline/range" {
                        return Parser::make_OP_EXECUTE_INLINE_RANGE(LOCATION);}
<METHODDEF>"+invoke-object-init/range" {
                        return Parser::make_OP_INVOKE_OBJECT_INIT_RANGE(LOCATION);}
<METHODDEF>"+return-void-barrier" {
                        return Parser::make_OP_RETURN_VOID_BARRIER(LOCATION);}
<METHODDEF>"+iget-quick"        {return Parser::make_OP_IGET_QUICK(LOCATION);}
<METHODDEF>"+iget-wide-quick"   {return Parser::make_OP_IGET_WIDE_QUICK(LOCATION);}
<METHODDEF>"+iget-object-quick" {return Parser::make_OP_IGET_OBJECT_QUICK(LOCATION);}
<METHODDEF>"+iput-quick"        {return Parser::make_OP_IPUT_QUICK(LOCATION);}
<METHODDEF>"+iput-wide-quick"   {return Parser::make_OP_IPUT_WIDE_QUICK(LOCATION);}
<METHODDEF>"+iput-object-quick" {return Parser::make_OP_IPUT_OBJECT_QUICK(LOCATION);}
<METHODDEF>"+invoke-virtual-quick" {
                        return Parser::make_OP_INVOKE_VIRTUAL_QUICK(LOCATION);}
<METHODDEF>"+invoke-virtual-quick/range" {
                        return Parser::make_OP_INVOKE_VIRTUAL_QUICK_RANGE(LOCATION);}
<METHODDEF>"+invoke-super-quick" {
                        return Parser::make_OP_INVOKE_SUPER_QUICK(LOCATION);}
<METHODDEF>"+invoke-super-quick/range" {
                        return Parser::make_OP_INVOKE_SUPER_QUICK_RANGE(LOCATION);}
<METHODDEF>"+iput-object-volatile" {
                        return Parser::make_OP_IPUT_OBJECT_VOLATILE(LOCATION);}
<METHODDEF>"+sget-object-volatile" {
                        return Parser::make_OP_SGET_OBJECT_VOLATILE(LOCATION);}
<METHODDEF>"+sput-object-volatile" {
                        return Parser::make_OP_SPUT_OBJECT_VOLATILE(LOCATION);}
<METHODDEF>"unused-ff"  {return Parser::make_OP_UNUSED_FF(LOCATION);}
<METHODDEF>".catch"     {return Parser::make_OP_CATCH(LOCATION);}

<METHODDEF>[vp][0-9]+ {
                    int number = strtoull(yytext + 1, 0, 10);
                    if (yytext[0] == 'p' || yytext[0] == 'P') {
                        number |= 0x100;
                    }
                    return Parser::make_REGD(number, LOCATION);
                }


    /*          flags          */
<INITIAL,METHODDEF>"public" {
        return Parser::make_FLAG(ACC_FLAGS::ACC_PUBLIC, LOCATION);}
<INITIAL,METHODDEF>"private" {
        return Parser::make_FLAG(ACC_FLAGS::ACC_PRIVATE, LOCATION);}
<INITIAL,METHODDEF>"protected" {
        return Parser::make_FLAG(ACC_FLAGS::ACC_PROTECTED, LOCATION);}
<INITIAL,METHODDEF>"static" {
        return Parser::make_FLAG(ACC_FLAGS::ACC_STATIC, LOCATION);}
<INITIAL,METHODDEF>"final" {
        return Parser::make_FLAG(ACC_FLAGS::ACC_FINAL, LOCATION);}
<INITIAL,METHODDEF>"synchronized" {
        return Parser::make_FLAG(ACC_FLAGS::ACC_SYNCHRONIZED, LOCATION);}
<INITIAL,METHODDEF>"super" {
        return Parser::make_FLAG(ACC_FLAGS::ACC_SUPER, LOCATION);}
<INITIAL,METHODDEF>"volatile" {
        return Parser::make_FLAG(ACC_FLAGS::ACC_VOLATILE, LOCATION);}
<INITIAL,METHODDEF>"bridge" {
        return Parser::make_FLAG(ACC_FLAGS::ACC_BRIDGE, LOCATION);}
<INITIAL,METHODDEF>"transient" {
        return Parser::make_FLAG(ACC_FLAGS::ACC_TRANSIENT, LOCATION);}
<INITIAL,METHODDEF>"varargs" {
        return Parser::make_FLAG(ACC_FLAGS::ACC_VARARGS, LOCATION);}
<INITIAL,METHODDEF>"native" {
        return Parser::make_FLAG(ACC_FLAGS::ACC_NATIVE, LOCATION);}
<INITIAL,METHODDEF>"interface" {
        return Parser::make_FLAG(ACC_FLAGS::ACC_INTERFACE, LOCATION);}
<INITIAL,METHODDEF>"abstract" {
        return Parser::make_FLAG(ACC_FLAGS::ACC_ABSTRACT, LOCATION);}
<INITIAL,METHODDEF>"strict" {
        return Parser::make_FLAG(ACC_FLAGS::ACC_STRICT, LOCATION);}
<INITIAL,METHODDEF>"synthetic" {
        return Parser::make_FLAG(ACC_FLAGS::ACC_SYNTHETIC, LOCATION);}
<INITIAL,METHODDEF>"annotation" {
        return Parser::make_FLAG(ACC_FLAGS::ACC_ANNOTATION, LOCATION);}
<INITIAL,METHODDEF>"enum" {
        return Parser::make_FLAG(ACC_FLAGS::ACC_ENUM, LOCATION);}
<INITIAL,METHODDEF>"constructor" {
        return Parser::make_FLAG(ACC_FLAGS::ACC_CONSTRUCTOR, LOCATION);}
<INITIAL,METHODDEF>"declared_synchronized" {
        return Parser::make_FLAG(ACC_FLAGS::ACC_DECLARED_SYNCHRONIZED, LOCATION);}

":"         {return Parser::make_COLON(LOCATION);}
<METHODDEF>"("         {BEGIN(ARGSDEF); return Parser::make_LEFTPAR(LOCATION);}
<ARGSDEF>")"         {BEGIN(METHODDEF); return Parser::make_RIGHTPAR(LOCATION);}
<METHODDEF>"," {return Parser::make_COMMA(LOCATION);}
<METHODDEF>"->" {return Parser::make_POINT(LOCATION);}
<METHODDEF>"{" {return Parser::make_INIBRACE(LOCATION);}
<METHODDEF>"}"  {return Parser::make_CLOBRACE(LOCATION);}
<METHODDEF>".."  {return Parser::make_ELLIPSIS(LOCATION);}


<INITIAL,METHODDEF>{DNUMBER}   {
                uint64_t number = strtoull(yytext, 0, 10);
                return Parser::make_NUMBER(number, LOCATION);
            }
<INITIAL,METHODDEF>"0x"{HNUMBER} {
                uint64_t number = strtoull(yytext, 0, 16);
                return Parser::make_NUMBER(number, LOCATION);
            }

<INITIAL,METHODDEF>{CSTRING} {
        return Parser::make_CSTRING(std::string(yytext+1, yyleng - 2), LOCATION);}
<INITIAL,METHODDEF>{NAMESTRING} {return Parser::make_NAMESTRING(yytext, LOCATION);}


.           {;}
<<EOF>>     {return yyterminate(); }

%%

void Analysis::Lexer::beginInitial() {
    BEGIN(INITIAL);
}

void Analysis::Lexer::beginMethodDef() {
    BEGIN(METHODDEF);
}

void Analysis::Lexer::beginArgsDef() {
    BEGIN(ARGSDEF);
}
