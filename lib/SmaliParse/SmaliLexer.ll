%{
//===- SmaliLexer.ll - ART-LEX --------------------------------*- flex -*-===//
//
//                     ANDROID REVERSE TOOLKIT
//
// This file is distributed under the GNU GENERAL PUBLIC LICENSE
// V3 License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// The file defines a lexer for smali language. Please use
// flex++ -o SmaliLexer.cpp SmaliLexer.ll
// to generate lex source file
// or
// flex++ -s -o SmaliLexer.cpp SmaliLexer.ll
// to debug
// some defination is copied from Apktool
// see https://github.com/iBotPeaches/Apktool
//
//===----------------------------------------------------------------------===//
	#include <iostream>
	#include <cstdlib>
    #include "SmaliLexer.h"
	#include "SmaliParser.hpp"
	#include "location.hh"
    #include "utils/Defs.h"

	using namespace std;
	using namespace Analysis;


	#define YY_USER_ACTION acceptToken(yytext, yyleng);
    #define LOCATION Analysis::location(YY_NULL, line(), column())
    #define yyterminate() SmaliParser::make_END(LOCATION);
    #define makeToken(x) SmaliParser::make_##x(LOCATION)
    #define makeTokenStr(x) SmaliParser::make_##x(std::string(yytext, yyleng), LOCATION)
    #define makeTokenI(x, y) SmaliParser::make_##x(y, LOCATION)
%}

%option noyywrap
%option c++
%option yyclass="SmaliLexer"
%option prefix="Analysis_"

HexPrefix           0[xX]

HexDigit            [0-9a-fA-F]
HexDigits           [0-9a-fA-F]{4}
FewerHexDigits      [0-9a-fA-F]{0,3}

Integer1            0
Integer2            [1-9][0-9]*
Integer3            0[0-7]+
Integer4            {HexPrefix}{HexDigit}+
Integer             {Integer1}|{Integer2}|{Integer3}|{Integer4}

DecimalExponent     [eE]-?[0-9]+

BinaryExponent      [pP]-?[0-9]+

/*This can either be a floating point number or an identifier*/
FloatOrID1          -?[0-9]+{DecimalExponent}
FloatOrID2          -?{HexPrefix}{HexDigit}+{BinaryExponent}
FloatOrID3          -?[iI][nN][fF][iI][nN][iI][tT][yY]
FloatOrID4          [nN][aA][nN]
FloatOrID           {FloatOrID1}|{FloatOrID2}|{FloatOrID3}|{FloatOrID4}


/*This can only be a float and not an identifier, due to the decimal point*/
Float1              -?[0-9]+"."[0-9]*{DecimalExponent}?
Float2              -?"."[0-9]+{DecimalExponent}?
Float3              -?{HexPrefix}{HexDigit}+"."{HexDigit}*{BinaryExponent}
Float4              -?{HexPrefix}"."{HexDigit}+{BinaryExponent}
Float               {Float1}|{Float2}|{Float3}|{Float4}

ASC     [\x00-\x7f]
ASCN    [\x00-\t\v-\x7f]
U       [\x80-\xbf]
U2      [\xc2-\xdf]
U3      [\xe0-\xef]
U4      [\xf0-\xf4]

UONLY   {U2}{U}|{U3}{U}{U}|{U4}{U}{U}{U}
UANY    {ASC}|{UONLY}
UANYN   {ASCN}|{UONLY}

ASCSTR  [0-9a-zA-Z/$_]
UASTR   {ASCSTR}|{UONLY}

SimpleNameCharacter {UASTR}
SimpleName          {SimpleNameCharacter}+

PrimitiveType       [ZBSCIJFD]

ClassDescriptor     L({SimpleName}"/")*{SimpleName};

ArrayPrefix         "["+

Type                {PrimitiveType}|{ClassDescriptor}|{ArrayPrefix}({ClassDescriptor}|{PrimitiveType})

%x PARAM_LIST_OR_ID PARAM_LIST ARRAY_DESCRIPTOR STRING CHAR

%%
    /*Symbols/Whitespace/EOF*/

".." { return makeToken(DOTDOT); }
"->" { return makeToken(ARROW); }
"=" { return makeToken(EQUAL); }
":" { return makeToken(COLON); }
"," { return makeToken(COMMA); }
"{" { return makeToken(OPEN_BRACE); }
"}" { return makeToken(CLOSE_BRACE); }
"(" { return makeToken(OPEN_PAREN); }
")" { return makeToken(CLOSE_PAREN); }

    /*Directives*/

".class" { return makeToken(CLASS_DIRECTIVE); }
".super" { return makeToken(SUPER_DIRECTIVE); }
".implements" { return makeToken(IMPLEMENTS_DIRECTIVE); }
".source" { return makeToken(SOURCE_DIRECTIVE); }
".field" { return makeToken(FIELD_DIRECTIVE); }
".end field" { return makeToken(END_FIELD_DIRECTIVE); }
".subannotation" { return makeToken(SUBANNOTATION_DIRECTIVE); }
".end subannotation" { return makeToken(END_SUBANNOTATION_DIRECTIVE); }
".annotation" { return makeToken(ANNOTATION_DIRECTIVE); }
".end annotation" { return makeToken(END_ANNOTATION_DIRECTIVE); }
".enum" { return makeToken(ENUM_DIRECTIVE); }
".method" { return makeToken(METHOD_DIRECTIVE); }
".end method" { return makeToken(END_METHOD_DIRECTIVE); }
".registers" { return makeToken(REGISTERS_DIRECTIVE); }
".locals" { return makeToken(LOCALS_DIRECTIVE); }
".array-data" { return makeToken(ARRAY_DATA_DIRECTIVE); }
".end array-data" { return makeToken(END_ARRAY_DATA_DIRECTIVE); }
".packed-switch" { return makeToken(PACKED_SWITCH_DIRECTIVE); }
".end packed-switch" { return makeToken(END_PACKED_SWITCH_DIRECTIVE); }
".sparse-switch" { return makeToken(SPARSE_SWITCH_DIRECTIVE); }
".end sparse-switch" { return makeToken(END_SPARSE_SWITCH_DIRECTIVE); }
".catch" { return makeToken(CATCH_DIRECTIVE); }
".catchall" { return makeToken(CATCHALL_DIRECTIVE); }
".line" { return makeToken(LINE_DIRECTIVE); }
".param" { return makeToken(PARAMETER_DIRECTIVE); }
".end param" { return makeToken(END_PARAMETER_DIRECTIVE); }
".local" { return makeToken(LOCAL_DIRECTIVE); }
".end local" { return makeToken(END_LOCAL_DIRECTIVE); }
".restart local" { return makeToken(RESTART_LOCAL_DIRECTIVE); }
".prologue" { return makeToken(PROLOGUE_DIRECTIVE); }
".epilogue" { return makeToken(EPILOGUE_DIRECTIVE); }

    /*Literals*/
{Integer} { return makeTokenStr(POSITIVE_INTEGER_LITERAL); }
-{Integer} { return makeTokenStr(NEGATIVE_INTEGER_LITERAL); }
-?{Integer}[lL] { return makeTokenStr(LONG_LITERAL); }
-?{Integer}[sS] { return makeTokenStr(SHORT_LITERAL); }
-?{Integer}[tT] { return makeTokenStr(BYTE_LITERAL); }

{FloatOrID}[fF]|-?[0-9]+[fF] { return makeTokenStr(FLOAT_LITERAL_OR_ID); }
{FloatOrID}[dD]?|-?[0-9]+[dD] { return makeTokenStr(DOUBLE_LITERAL_OR_ID); }
{Float}[fF] { return makeTokenStr(FLOAT_LITERAL); }
{Float}[dD]? { return makeTokenStr(DOUBLE_LITERAL); }

"true"|"false" {
     if (yytext[0] == 'y')
         return makeTokenI(BOOL_LITERAL, 1);
     else
         return makeTokenI(BOOL_LITERAL, 0); }

"null" { return makeToken(NULL_LITERAL); }

"\"" { beginStringOrChar(STRING); sb.push_back('"'); }

' { beginStringOrChar(CHAR); sb.push_back('\''); }


<PARAM_LIST_OR_ID>{PrimitiveType} { return makeTokenStr(PARAM_LIST_OR_ID_PRIMITIVE_TYPE); }
<PARAM_LIST_OR_ID>[^\n] { mColumn -= yyleng; yyless(0); BEGIN(INITIAL); }
<PARAM_LIST_OR_ID><<EOF>> { BEGIN(INITIAL); }

<PARAM_LIST>{PrimitiveType} { return makeTokenStr(PRIMITIVE_TYPE); }
<PARAM_LIST>{ClassDescriptor} { return makeTokenStr(CLASS_DESCRIPTOR); }
<PARAM_LIST>{ArrayPrefix} { return makeTokenStr(ARRAY_TYPE_PREFIX); }
<PARAM_LIST>[^\n] { mColumn -= yyleng; yyless(0); BEGIN(INITIAL);}
<PARAM_LIST><<EOF>> { BEGIN(INITIAL);}


<STRING>"\""  {
        sb.push_back('"');
        return endStringOrChar(SmaliParser::token::TOKEN_STRING_LITERAL); }

<STRING>[^\r\n\"\\]+ { sb.append(yytext, yyleng); }
<STRING>"\\b" { sb.push_back('\b'); }
<STRING>"\\t" { sb.push_back('\t'); }
<STRING>"\\n" { sb.push_back('\n'); }
<STRING>"\\f" { sb.push_back('\f'); }
<STRING>"\\r" { sb.push_back('\r'); }
<STRING>"\\'" { sb.push_back('\''); }
<STRING>"\\\"" { sb.push_back('"'); }
<STRING>"\\\\" { sb.push_back('\\'); }
<STRING>"\\u"{HexDigits} {
        auto i = strtol(yytext+2, 0, 16);
        sb.append((char*)&i, 2);
    }

<STRING>"\\u"{FewerHexDigits} {
        sb.append(yytext, yyleng);
    }

<STRING>"\\"[^btnfr'\"\\u] {
        sb.append(yytext, yyleng);
    }

<STRING>[\r\n] { return makeTokenStr(ERROR); }
<STRING><<EOF>> { return makeTokenStr(ERROR); }



<CHAR>' {
        sb.push_back('\'');
        if (sb.length() != 3 ) {
            return makeTokenStr(ERROR);
        }

        return endStringOrChar(SmaliParser::token::TOKEN_CHAR_LITERAL);
    }

<CHAR>[^\r\n'\\]+ { sb.append(yytext, yyleng); }
<CHAR>"\\b" { sb.push_back('\b'); }
<CHAR>"\\t" { sb.push_back('\t'); }
<CHAR>"\\n" { sb.push_back('\n'); }
<CHAR>"\\f" { sb.push_back('\f'); }
<CHAR>"\\r" { sb.push_back('\r'); }
<CHAR>"\\'" { sb.push_back('\''); }
<CHAR>"\\\"" { sb.push_back('"'); }
<CHAR>"\\\\" { sb.push_back('\\'); }
<CHAR>"\\u"{HexDigits} {
        auto i = strtol(yytext+2, 0, 16);
        sb.append((char*)&i, 2);
    }

<CHAR>"\\u"{HexDigit}* {
        sb.append(yytext, yyleng);
    }

<CHAR>"\\"[^btnfr'\"\\u] {
        sb.append(yytext, yyleng);
    }

<CHAR>[\r\n] { return makeTokenStr(ERROR); }
<CHAR><<EOF>> { return makeTokenStr(ERROR); }


    /*Misc*/
[vp][0-9]+ {
        int number = strtoull(yytext + 1, 0, 10);
        if (yytext[0] == 'p' || yytext[0] == 'P') {
            number |= 0x100;
        }
        return makeTokenI(REGISTER, number);
    }

"build"|"runtime"|"system" {
        return makeTokenStr(ANNOTATION_VISIBILITY);
    }

"public" {
        return makeTokenI(FLAG, ACC_FLAGS::ACC_PUBLIC);}
"private" {
        return makeTokenI(FLAG, ACC_FLAGS::ACC_PRIVATE);}
"protected" {
        return makeTokenI(FLAG, ACC_FLAGS::ACC_PROTECTED);}
"static" {
        return makeTokenI(FLAG, ACC_FLAGS::ACC_STATIC);}
"final" {
        return makeTokenI(FLAG, ACC_FLAGS::ACC_FINAL);}
"synchronized" {
        return makeTokenI(FLAG, ACC_FLAGS::ACC_SYNCHRONIZED);}
"super" {
        return makeTokenI(FLAG, ACC_FLAGS::ACC_SUPER);}
"volatile" {
        return makeTokenI(FLAG, ACC_FLAGS::ACC_VOLATILE);}
"bridge" {
        return makeTokenI(FLAG, ACC_FLAGS::ACC_BRIDGE);}
"transient" {
        return makeTokenI(FLAG, ACC_FLAGS::ACC_TRANSIENT);}
"varargs" {
        return makeTokenI(FLAG, ACC_FLAGS::ACC_VARARGS);}
"native" {
        return makeTokenI(FLAG, ACC_FLAGS::ACC_NATIVE);}
"interface" {
        return makeTokenI(FLAG, ACC_FLAGS::ACC_INTERFACE);}
"abstract" {
        return makeTokenI(FLAG, ACC_FLAGS::ACC_ABSTRACT);}
"strict" {
        return makeTokenI(FLAG, ACC_FLAGS::ACC_STRICT);}
"synthetic" {
        return makeTokenI(FLAG, ACC_FLAGS::ACC_SYNTHETIC);}
"annotation" {
        return makeTokenI(FLAG, ACC_FLAGS::ACC_ANNOTATION);}
"enum" {
        return makeTokenI(FLAG, ACC_FLAGS::ACC_ENUM);}
"constructor" {
        return makeTokenI(FLAG, ACC_FLAGS::ACC_CONSTRUCTOR);}
"declared-synchronized" {
        return makeTokenI(FLAG, ACC_FLAGS::ACC_DECLARED_SYNCHRONIZED);}

"no-error"|"generic-error"|"no-such-class"|"no-such-field"|"no-such-method"|"illegal-class-access"|"illegal-field-access"|"illegal-method-access"|"class-change-error"|"instantiation-error" {
    return makeTokenStr(VERIFICATION_ERROR_TYPE);
    }

"inline@0x"{HexDigit}+ { return makeTokenStr(INLINE_INDEX); }
"vtable@0x"{HexDigit}+ { return makeTokenStr(VTABLE_INDEX); }
"field@0x"{HexDigit}+ { return makeTokenStr(FIELD_OFFSET); }

#[^\r\n]* { return makeTokenStr(LINE_COMMENT); }

    /*      instruction keyword     */
"nop"        {return SmaliParser::make_OP_NOP(LOCATION);}
"move"       {return SmaliParser::make_OP_MOVE(LOCATION);}
"move/from16"        {return SmaliParser::make_OP_MOVE_FROM16(LOCATION);}
"move/16"    {return SmaliParser::make_OP_MOVE_16(LOCATION);}
"move-wide"  {return SmaliParser::make_OP_MOVE_WIDE(LOCATION);}
"move-wide/from16"   {return SmaliParser::make_OP_MOVE_WIDE_FROM16(LOCATION);}
"move-wide/16"       {return SmaliParser::make_OP_MOVE_WIDE_16(LOCATION);}
"move-object"        {return SmaliParser::make_OP_MOVE_OBJECT(LOCATION);}
"move-object/from16" {return SmaliParser::make_OP_MOVE_OBJECT_FROM16(LOCATION);}
"move-object/16"     {return SmaliParser::make_OP_MOVE_OBJECT_16(LOCATION);}
"move-result"        {return SmaliParser::make_OP_MOVE_RESULT(LOCATION);}
"move-result-wide"   {return SmaliParser::make_OP_MOVE_RESULT_WIDE(LOCATION);}
"move-result-object" {return SmaliParser::make_OP_MOVE_RESULT_OBJECT(LOCATION);}
"move-exception"     {return SmaliParser::make_OP_MOVE_EXCEPTION(LOCATION);}
"return-void"        {return SmaliParser::make_OP_RETURN_VOID(LOCATION);}
"return"     {return SmaliParser::make_OP_RETURN(LOCATION);}
"return-wide"        {return SmaliParser::make_OP_RETURN_WIDE(LOCATION);}
"return-object"      {return SmaliParser::make_OP_RETURN_OBJECT(LOCATION);}
"const/4"    {return SmaliParser::make_OP_CONST_4(LOCATION);}
"const/16"   {return SmaliParser::make_OP_CONST_16(LOCATION);}
"const"      {return SmaliParser::make_OP_CONST(LOCATION);}
"const/high16"       {return SmaliParser::make_OP_CONST_HIGH16(LOCATION);}
"const-wide/16"      {return SmaliParser::make_OP_CONST_WIDE_16(LOCATION);}
"const-wide/32"      {return SmaliParser::make_OP_CONST_WIDE_32(LOCATION);}
"const-wide" {return SmaliParser::make_OP_CONST_WIDE(LOCATION);}
"const-wide/high16"  {return SmaliParser::make_OP_CONST_WIDE_HIGH16(LOCATION);}
"const-string"       {return SmaliParser::make_OP_CONST_STRING(LOCATION);}
"const-string/jumbo" {return SmaliParser::make_OP_CONST_STRING_JUMBO(LOCATION);}
"const-class"        {return SmaliParser::make_OP_CONST_CLASS(LOCATION);}
"monitor-enter"      {return SmaliParser::make_OP_MONITOR_ENTER(LOCATION);}
"monitor-exit"       {return SmaliParser::make_OP_MONITOR_EXIT(LOCATION);}
"check-cast" {return SmaliParser::make_OP_CHECK_CAST(LOCATION);}
"instance-of"        {return SmaliParser::make_OP_INSTANCE_OF(LOCATION);}
"array-length"       {return SmaliParser::make_OP_ARRAY_LENGTH(LOCATION);}
"new-instance"       {return SmaliParser::make_OP_NEW_INSTANCE(LOCATION);}
"new-array"  {return SmaliParser::make_OP_NEW_ARRAY(LOCATION);}
"filled-new-array"   {return SmaliParser::make_OP_FILLED_NEW_ARRAY(LOCATION);}
"filled-new-array/range" {
                    return SmaliParser::make_OP_FILLED_NEW_ARRAY_RANGE(LOCATION);}
"fill-array-data"    {return SmaliParser::make_OP_FILL_ARRAY_DATA(LOCATION);}
"throw"      {return SmaliParser::make_OP_THROW(LOCATION);}
"goto"       {return SmaliParser::make_OP_GOTO(LOCATION);}
"goto/16"    {return SmaliParser::make_OP_GOTO_16(LOCATION);}
"goto/32"    {return SmaliParser::make_OP_GOTO_32(LOCATION);}
"packed-switch"      {return SmaliParser::make_OP_PACKED_SWITCH(LOCATION);}
"sparse-switch"      {return SmaliParser::make_OP_SPARSE_SWITCH(LOCATION);}
"cmpl-float" {return SmaliParser::make_OP_CMPL_FLOAT(LOCATION);}
"cmpg-float" {return SmaliParser::make_OP_CMPG_FLOAT(LOCATION);}
"cmpl-double"        {return SmaliParser::make_OP_CMPL_DOUBLE(LOCATION);}
"cmpg-double"        {return SmaliParser::make_OP_CMPG_DOUBLE(LOCATION);}
"cmp-long"   {return SmaliParser::make_OP_CMP_LONG(LOCATION);}
"if-eq"      {return SmaliParser::make_OP_IF_EQ(LOCATION);}
"if-ne"      {return SmaliParser::make_OP_IF_NE(LOCATION);}
"if-lt"      {return SmaliParser::make_OP_IF_LT(LOCATION);}
"if-ge"      {return SmaliParser::make_OP_IF_GE(LOCATION);}
"if-gt"      {return SmaliParser::make_OP_IF_GT(LOCATION);}
"if-le"      {return SmaliParser::make_OP_IF_LE(LOCATION);}
"if-eqz"     {return SmaliParser::make_OP_IF_EQZ(LOCATION);}
"if-nez"     {return SmaliParser::make_OP_IF_NEZ(LOCATION);}
"if-ltz"     {return SmaliParser::make_OP_IF_LTZ(LOCATION);}
"if-gez"     {return SmaliParser::make_OP_IF_GEZ(LOCATION);}
"if-gtz"     {return SmaliParser::make_OP_IF_GTZ(LOCATION);}
"if-lez"     {return SmaliParser::make_OP_IF_LEZ(LOCATION);}
"unused-3e"  {return SmaliParser::make_OP_UNUSED_3E(LOCATION);}
"unused-3f"  {return SmaliParser::make_OP_UNUSED_3F(LOCATION);}
"unused-40"  {return SmaliParser::make_OP_UNUSED_40(LOCATION);}
"unused-41"  {return SmaliParser::make_OP_UNUSED_41(LOCATION);}
"unused-42"  {return SmaliParser::make_OP_UNUSED_42(LOCATION);}
"unused-43"  {return SmaliParser::make_OP_UNUSED_43(LOCATION);}
"aget"       {return SmaliParser::make_OP_AGET(LOCATION);}
"aget-wide"  {return SmaliParser::make_OP_AGET_WIDE(LOCATION);}
"aget-object"        {return SmaliParser::make_OP_AGET_OBJECT(LOCATION);}
"aget-boolean"       {return SmaliParser::make_OP_AGET_BOOLEAN(LOCATION);}
"aget-byte"  {return SmaliParser::make_OP_AGET_BYTE(LOCATION);}
"aget-char"  {return SmaliParser::make_OP_AGET_CHAR(LOCATION);}
"aget-short" {return SmaliParser::make_OP_AGET_SHORT(LOCATION);}
"aput"       {return SmaliParser::make_OP_APUT(LOCATION);}
"aput-wide"  {return SmaliParser::make_OP_APUT_WIDE(LOCATION);}
"aput-object"        {return SmaliParser::make_OP_APUT_OBJECT(LOCATION);}
"aput-boolean"       {return SmaliParser::make_OP_APUT_BOOLEAN(LOCATION);}
"aput-byte"  {return SmaliParser::make_OP_APUT_BYTE(LOCATION);}
"aput-char"  {return SmaliParser::make_OP_APUT_CHAR(LOCATION);}
"aput-short" {return SmaliParser::make_OP_APUT_SHORT(LOCATION);}
"iget"       {return SmaliParser::make_OP_IGET(LOCATION);}
"iget-wide"  {return SmaliParser::make_OP_IGET_WIDE(LOCATION);}
"iget-object"        {return SmaliParser::make_OP_IGET_OBJECT(LOCATION);}
"iget-boolean"       {return SmaliParser::make_OP_IGET_BOOLEAN(LOCATION);}
"iget-byte"  {return SmaliParser::make_OP_IGET_BYTE(LOCATION);}
"iget-char"  {return SmaliParser::make_OP_IGET_CHAR(LOCATION);}
"iget-short" {return SmaliParser::make_OP_IGET_SHORT(LOCATION);}
"iput"       {return SmaliParser::make_OP_IPUT(LOCATION);}
"iput-wide"  {return SmaliParser::make_OP_IPUT_WIDE(LOCATION);}
"iput-object"        {return SmaliParser::make_OP_IPUT_OBJECT(LOCATION);}
"iput-boolean"       {return SmaliParser::make_OP_IPUT_BOOLEAN(LOCATION);}
"iput-byte"  {return SmaliParser::make_OP_IPUT_BYTE(LOCATION);}
"iput-char"  {return SmaliParser::make_OP_IPUT_CHAR(LOCATION);}
"iput-short" {return SmaliParser::make_OP_IPUT_SHORT(LOCATION);}
"sget"       {return SmaliParser::make_OP_SGET(LOCATION);}
"sget-wide"  {return SmaliParser::make_OP_SGET_WIDE(LOCATION);}
"sget-object"        {return SmaliParser::make_OP_SGET_OBJECT(LOCATION);}
"sget-boolean"       {return SmaliParser::make_OP_SGET_BOOLEAN(LOCATION);}
"sget-byte"  {return SmaliParser::make_OP_SGET_BYTE(LOCATION);}
"sget-char"  {return SmaliParser::make_OP_SGET_CHAR(LOCATION);}
"sget-short" {return SmaliParser::make_OP_SGET_SHORT(LOCATION);}
"sput"       {return SmaliParser::make_OP_SPUT(LOCATION);}
"sput-wide"  {return SmaliParser::make_OP_SPUT_WIDE(LOCATION);}
"sput-object"        {return SmaliParser::make_OP_SPUT_OBJECT(LOCATION);}
"sput-boolean"       {return SmaliParser::make_OP_SPUT_BOOLEAN(LOCATION);}
"sput-byte"  {return SmaliParser::make_OP_SPUT_BYTE(LOCATION);}
"sput-char"  {return SmaliParser::make_OP_SPUT_CHAR(LOCATION);}
"sput-short" {return SmaliParser::make_OP_SPUT_SHORT(LOCATION);}
"invoke-virtual"     {return SmaliParser::make_OP_INVOKE_VIRTUAL(LOCATION);}
"invoke-super"       {return SmaliParser::make_OP_INVOKE_SUPER(LOCATION);}
"invoke-direct"      {return SmaliParser::make_OP_INVOKE_DIRECT(LOCATION);}
"invoke-static"      {return SmaliParser::make_OP_INVOKE_STATIC(LOCATION);}
"invoke-interface"   {return SmaliParser::make_OP_INVOKE_INTERFACE(LOCATION);}
"unused-73"  {return SmaliParser::make_OP_UNUSED_73(LOCATION);}
"invoke-virtual/range" {
                        return SmaliParser::make_OP_INVOKE_VIRTUAL_RANGE(LOCATION);}
"invoke-super/range" {return SmaliParser::make_OP_INVOKE_SUPER_RANGE(LOCATION);}
"invoke-direct/range" {
                        return SmaliParser::make_OP_INVOKE_DIRECT_RANGE(LOCATION);}
"invoke-static/range" {
                        return SmaliParser::make_OP_INVOKE_STATIC_RANGE(LOCATION);}
"invoke-interface/range" {
                        return SmaliParser::make_OP_INVOKE_INTERFACE_RANGE(LOCATION);}
"unused-79"  {return SmaliParser::make_OP_UNUSED_79(LOCATION);}
"unused-7a"  {return SmaliParser::make_OP_UNUSED_7A(LOCATION);}
"neg-int"    {return SmaliParser::make_OP_NEG_INT(LOCATION);}
"not-int"    {return SmaliParser::make_OP_NOT_INT(LOCATION);}
"neg-long"   {return SmaliParser::make_OP_NEG_LONG(LOCATION);}
"not-long"   {return SmaliParser::make_OP_NOT_LONG(LOCATION);}
"neg-float"  {return SmaliParser::make_OP_NEG_FLOAT(LOCATION);}
"neg-double" {return SmaliParser::make_OP_NEG_DOUBLE(LOCATION);}
"int-to-long"        {return SmaliParser::make_OP_INT_TO_LONG(LOCATION);}
"int-to-float"       {return SmaliParser::make_OP_INT_TO_FLOAT(LOCATION);}
"int-to-double"      {return SmaliParser::make_OP_INT_TO_DOUBLE(LOCATION);}
"long-to-int"        {return SmaliParser::make_OP_LONG_TO_INT(LOCATION);}
"long-to-float"      {return SmaliParser::make_OP_LONG_TO_FLOAT(LOCATION);}
"long-to-double"     {return SmaliParser::make_OP_LONG_TO_DOUBLE(LOCATION);}
"float-to-int"       {return SmaliParser::make_OP_FLOAT_TO_INT(LOCATION);}
"float-to-long"      {return SmaliParser::make_OP_FLOAT_TO_LONG(LOCATION);}
"float-to-double"    {return SmaliParser::make_OP_FLOAT_TO_DOUBLE(LOCATION);}
"double-to-int"      {return SmaliParser::make_OP_DOUBLE_TO_INT(LOCATION);}
"double-to-long"     {return SmaliParser::make_OP_DOUBLE_TO_LONG(LOCATION);}
"double-to-float"    {return SmaliParser::make_OP_DOUBLE_TO_FLOAT(LOCATION);}
"int-to-byte"        {return SmaliParser::make_OP_INT_TO_BYTE(LOCATION);}
"int-to-char"        {return SmaliParser::make_OP_INT_TO_CHAR(LOCATION);}
"int-to-short"       {return SmaliParser::make_OP_INT_TO_SHORT(LOCATION);}
"add-int"    {return SmaliParser::make_OP_ADD_INT(LOCATION);}
"sub-int"    {return SmaliParser::make_OP_SUB_INT(LOCATION);}
"mul-int"    {return SmaliParser::make_OP_MUL_INT(LOCATION);}
"div-int"    {return SmaliParser::make_OP_DIV_INT(LOCATION);}
"rem-int"    {return SmaliParser::make_OP_REM_INT(LOCATION);}
"and-int"    {return SmaliParser::make_OP_AND_INT(LOCATION);}
"or-int"     {return SmaliParser::make_OP_OR_INT(LOCATION);}
"xor-int"    {return SmaliParser::make_OP_XOR_INT(LOCATION);}
"shl-int"    {return SmaliParser::make_OP_SHL_INT(LOCATION);}
"shr-int"    {return SmaliParser::make_OP_SHR_INT(LOCATION);}
"ushr-int"   {return SmaliParser::make_OP_USHR_INT(LOCATION);}
"add-long"   {return SmaliParser::make_OP_ADD_LONG(LOCATION);}
"sub-long"   {return SmaliParser::make_OP_SUB_LONG(LOCATION);}
"mul-long"   {return SmaliParser::make_OP_MUL_LONG(LOCATION);}
"div-long"   {return SmaliParser::make_OP_DIV_LONG(LOCATION);}
"rem-long"   {return SmaliParser::make_OP_REM_LONG(LOCATION);}
"and-long"   {return SmaliParser::make_OP_AND_LONG(LOCATION);}
"or-long"    {return SmaliParser::make_OP_OR_LONG(LOCATION);}
"xor-long"   {return SmaliParser::make_OP_XOR_LONG(LOCATION);}
"shl-long"   {return SmaliParser::make_OP_SHL_LONG(LOCATION);}
"shr-long"   {return SmaliParser::make_OP_SHR_LONG(LOCATION);}
"ushr-long"  {return SmaliParser::make_OP_USHR_LONG(LOCATION);}
"add-float"  {return SmaliParser::make_OP_ADD_FLOAT(LOCATION);}
"sub-float"  {return SmaliParser::make_OP_SUB_FLOAT(LOCATION);}
"mul-float"  {return SmaliParser::make_OP_MUL_FLOAT(LOCATION);}
"div-float"  {return SmaliParser::make_OP_DIV_FLOAT(LOCATION);}
"rem-float"  {return SmaliParser::make_OP_REM_FLOAT(LOCATION);}
"add-double" {return SmaliParser::make_OP_ADD_DOUBLE(LOCATION);}
"sub-double" {return SmaliParser::make_OP_SUB_DOUBLE(LOCATION);}
"mul-double" {return SmaliParser::make_OP_MUL_DOUBLE(LOCATION);}
"div-double" {return SmaliParser::make_OP_DIV_DOUBLE(LOCATION);}
"rem-double" {return SmaliParser::make_OP_REM_DOUBLE(LOCATION);}
"add-int/2addr"      {return SmaliParser::make_OP_ADD_INT_2ADDR(LOCATION);}
"sub-int/2addr"      {return SmaliParser::make_OP_SUB_INT_2ADDR(LOCATION);}
"mul-int/2addr"      {return SmaliParser::make_OP_MUL_INT_2ADDR(LOCATION);}
"div-int/2addr"      {return SmaliParser::make_OP_DIV_INT_2ADDR(LOCATION);}
"rem-int/2addr"      {return SmaliParser::make_OP_REM_INT_2ADDR(LOCATION);}
"and-int/2addr"      {return SmaliParser::make_OP_AND_INT_2ADDR(LOCATION);}
"or-int/2addr"       {return SmaliParser::make_OP_OR_INT_2ADDR(LOCATION);}
"xor-int/2addr"      {return SmaliParser::make_OP_XOR_INT_2ADDR(LOCATION);}
"shl-int/2addr"      {return SmaliParser::make_OP_SHL_INT_2ADDR(LOCATION);}
"shr-int/2addr"      {return SmaliParser::make_OP_SHR_INT_2ADDR(LOCATION);}
"ushr-int/2addr"     {return SmaliParser::make_OP_USHR_INT_2ADDR(LOCATION);}
"add-long/2addr"     {return SmaliParser::make_OP_ADD_LONG_2ADDR(LOCATION);}
"sub-long/2addr"     {return SmaliParser::make_OP_SUB_LONG_2ADDR(LOCATION);}
"mul-long/2addr"     {return SmaliParser::make_OP_MUL_LONG_2ADDR(LOCATION);}
"div-long/2addr"     {return SmaliParser::make_OP_DIV_LONG_2ADDR(LOCATION);}
"rem-long/2addr"     {return SmaliParser::make_OP_REM_LONG_2ADDR(LOCATION);}
"and-long/2addr"     {return SmaliParser::make_OP_AND_LONG_2ADDR(LOCATION);}
"or-long/2addr"      {return SmaliParser::make_OP_OR_LONG_2ADDR(LOCATION);}
"xor-long/2addr"     {return SmaliParser::make_OP_XOR_LONG_2ADDR(LOCATION);}
"shl-long/2addr"     {return SmaliParser::make_OP_SHL_LONG_2ADDR(LOCATION);}
"shr-long/2addr"     {return SmaliParser::make_OP_SHR_LONG_2ADDR(LOCATION);}
"ushr-long/2addr"    {return SmaliParser::make_OP_USHR_LONG_2ADDR(LOCATION);}
"add-float/2addr"    {return SmaliParser::make_OP_ADD_FLOAT_2ADDR(LOCATION);}
"sub-float/2addr"    {return SmaliParser::make_OP_SUB_FLOAT_2ADDR(LOCATION);}
"mul-float/2addr"    {return SmaliParser::make_OP_MUL_FLOAT_2ADDR(LOCATION);}
"div-float/2addr"    {return SmaliParser::make_OP_DIV_FLOAT_2ADDR(LOCATION);}
"rem-float/2addr"    {return SmaliParser::make_OP_REM_FLOAT_2ADDR(LOCATION);}
"add-double/2addr"   {return SmaliParser::make_OP_ADD_DOUBLE_2ADDR(LOCATION);}
"sub-double/2addr"   {return SmaliParser::make_OP_SUB_DOUBLE_2ADDR(LOCATION);}
"mul-double/2addr"   {return SmaliParser::make_OP_MUL_DOUBLE_2ADDR(LOCATION);}
"div-double/2addr"   {return SmaliParser::make_OP_DIV_DOUBLE_2ADDR(LOCATION);}
"rem-double/2addr"   {return SmaliParser::make_OP_REM_DOUBLE_2ADDR(LOCATION);}
"add-int/lit16"      {return SmaliParser::make_OP_ADD_INT_LIT16(LOCATION);}
"rsub-int"   {return SmaliParser::make_OP_RSUB_INT(LOCATION);}
"mul-int/lit16"      {return SmaliParser::make_OP_MUL_INT_LIT16(LOCATION);}
"div-int/lit16"      {return SmaliParser::make_OP_DIV_INT_LIT16(LOCATION);}
"rem-int/lit16"      {return SmaliParser::make_OP_REM_INT_LIT16(LOCATION);}
"and-int/lit16"      {return SmaliParser::make_OP_AND_INT_LIT16(LOCATION);}
"or-int/lit16"       {return SmaliParser::make_OP_OR_INT_LIT16(LOCATION);}
"xor-int/lit16"      {return SmaliParser::make_OP_XOR_INT_LIT16(LOCATION);}
"add-int/lit8"       {return SmaliParser::make_OP_ADD_INT_LIT8(LOCATION);}
"rsub-int/lit8"      {return SmaliParser::make_OP_RSUB_INT_LIT8(LOCATION);}
"mul-int/lit8"       {return SmaliParser::make_OP_MUL_INT_LIT8(LOCATION);}
"div-int/lit8"       {return SmaliParser::make_OP_DIV_INT_LIT8(LOCATION);}
"rem-int/lit8"       {return SmaliParser::make_OP_REM_INT_LIT8(LOCATION);}
"and-int/lit8"       {return SmaliParser::make_OP_AND_INT_LIT8(LOCATION);}
"or-int/lit8"        {return SmaliParser::make_OP_OR_INT_LIT8(LOCATION);}
"xor-int/lit8"       {return SmaliParser::make_OP_XOR_INT_LIT8(LOCATION);}
"shl-int/lit8"       {return SmaliParser::make_OP_SHL_INT_LIT8(LOCATION);}
"shr-int/lit8"       {return SmaliParser::make_OP_SHR_INT_LIT8(LOCATION);}
"ushr-int/lit8"      {return SmaliParser::make_OP_USHR_INT_LIT8(LOCATION);}
"+iget-volatile"     {return SmaliParser::make_OP_IGET_VOLATILE(LOCATION);}
"+iput-volatile"     {return SmaliParser::make_OP_IPUT_VOLATILE(LOCATION);}
"+sget-volatile"     {return SmaliParser::make_OP_SGET_VOLATILE(LOCATION);}
"+sput-volatile"     {return SmaliParser::make_OP_SPUT_VOLATILE(LOCATION);}
"+iget-object-volatile" {
                        return SmaliParser::make_OP_IGET_OBJECT_VOLATILE(LOCATION);}
"+iget-wide-volatile" {
                        return SmaliParser::make_OP_IGET_WIDE_VOLATILE(LOCATION);}
"+iput-wide-volatile" {
                        return SmaliParser::make_OP_IPUT_WIDE_VOLATILE(LOCATION);}
"+sget-wide-volatile" {
                        return SmaliParser::make_OP_SGET_WIDE_VOLATILE(LOCATION);}
"+sput-wide-volatile" {
                        return SmaliParser::make_OP_SPUT_WIDE_VOLATILE(LOCATION);}
"^breakpoint"        {return SmaliParser::make_OP_BREAKPOINT(LOCATION);}
"^throw-verification-error" {
                        return SmaliParser::make_OP_THROW_VERIFICATION_ERROR(LOCATION);}
"+execute-inline"    {return SmaliParser::make_OP_EXECUTE_INLINE(LOCATION);}
"+execute-inline/range" {
                        return SmaliParser::make_OP_EXECUTE_INLINE_RANGE(LOCATION);}
"+invoke-object-init/range" {
                        return SmaliParser::make_OP_INVOKE_OBJECT_INIT_RANGE(LOCATION);}
"+return-void-barrier" {
                        return SmaliParser::make_OP_RETURN_VOID_BARRIER(LOCATION);}
"+iget-quick"        {return SmaliParser::make_OP_IGET_QUICK(LOCATION);}
"+iget-wide-quick"   {return SmaliParser::make_OP_IGET_WIDE_QUICK(LOCATION);}
"+iget-object-quick" {return SmaliParser::make_OP_IGET_OBJECT_QUICK(LOCATION);}
"+iput-quick"        {return SmaliParser::make_OP_IPUT_QUICK(LOCATION);}
"+iput-wide-quick"   {return SmaliParser::make_OP_IPUT_WIDE_QUICK(LOCATION);}
"+iput-object-quick" {return SmaliParser::make_OP_IPUT_OBJECT_QUICK(LOCATION);}
"+invoke-virtual-quick" {
                        return SmaliParser::make_OP_INVOKE_VIRTUAL_QUICK(LOCATION);}
"+invoke-virtual-quick/range" {
                        return SmaliParser::make_OP_INVOKE_VIRTUAL_QUICK_RANGE(LOCATION);}
"+invoke-super-quick" {
                        return SmaliParser::make_OP_INVOKE_SUPER_QUICK(LOCATION);}
"+invoke-super-quick/range" {
                        return SmaliParser::make_OP_INVOKE_SUPER_QUICK_RANGE(LOCATION);}
"+iput-object-volatile" {
                        return SmaliParser::make_OP_IPUT_OBJECT_VOLATILE(LOCATION);}
"+sget-object-volatile" {
                        return SmaliParser::make_OP_SGET_OBJECT_VOLATILE(LOCATION);}
"+sput-object-volatile" {
                        return SmaliParser::make_OP_SPUT_OBJECT_VOLATILE(LOCATION);}
"unused-ff"  {return SmaliParser::make_OP_UNUSED_FF(LOCATION);}


<ARRAY_DESCRIPTOR>{PrimitiveType} { BEGIN(INITIAL); return makeTokenStr(PRIMITIVE_TYPE); }
<ARRAY_DESCRIPTOR>{ClassDescriptor} { BEGIN(INITIAL); return makeTokenStr(CLASS_DESCRIPTOR); }
<ARRAY_DESCRIPTOR>[^\n] { mColumn -= yyleng; yyless(0); BEGIN(INITIAL); }
<ARRAY_DESCRIPTOR><<EOF>> { BEGIN(INITIAL); }


    /*Types*/
{PrimitiveType} { return makeTokenStr(PRIMITIVE_TYPE); }
V { return makeToken(VOID_TYPE); }
{ClassDescriptor} { return makeTokenStr(CLASS_DESCRIPTOR); }

    /* we have to drop into a separate state so that we don't parse something like */
    /* "[I->" as "[" followed by "I-" as a SIMPLE_NAME */
{ArrayPrefix} {
      BEGIN(ARRAY_DESCRIPTOR);
      return makeTokenStr(ARRAY_TYPE_PREFIX);
    }

{PrimitiveType}{PrimitiveType}+ {
        // go back and re-lex it as a PARAM_LIST_OR_ID
        mColumn -= yyleng; yyless(0);
        BEGIN(PARAM_LIST_OR_ID);
    }

{Type}{Type}+ {
        // go back and re-lex it as a PARAM_LIST
        mColumn -= yyleng; yyless(0);
        BEGIN(PARAM_LIST);
    }

{SimpleName} { return makeTokenStr(SIMPLE_NAME); }
"<"{SimpleName}">" { return makeTokenStr(MEMBER_NAME); }


[\t\r]
[\n]        { return makeToken(EOL); }
.           { ;}
<<EOF>>     { return yyterminate(); }

%%

void Analysis::SmaliLexer::yyBegin(int type) {
    BEGIN(type);
}

