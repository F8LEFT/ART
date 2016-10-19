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
// flex -o SmaliLexer.cpp SmaliLexer.ll
// to generate lex source file
// or
// flex -s -o SmaliLexer.cpp SmaliLexer.ll
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


	#define MATCHT acceptToken(yytext, yyleng)
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

".." { MATCHT; return makeToken(DOTDOT); }
"->" { MATCHT; return makeToken(ARROW); }
"=" { MATCHT; return makeToken(EQUAL); }
":" { MATCHT; return makeToken(COLON); }
"," { MATCHT; return makeToken(COMMA); }
"{" { MATCHT; return makeToken(OPEN_BRACE); }
"}" { MATCHT; return makeToken(CLOSE_BRACE); }
"(" { MATCHT; return makeToken(OPEN_PAREN); }
")" { MATCHT; return makeToken(CLOSE_PAREN); }

    /*Directives*/

".class" { MATCHT; return makeToken(CLASS_DIRECTIVE); }
".super" { MATCHT; return makeToken(SUPER_DIRECTIVE); }
".implements" { MATCHT; return makeToken(IMPLEMENTS_DIRECTIVE); }
".source" { MATCHT; return makeToken(SOURCE_DIRECTIVE); }
".field" { MATCHT; return makeToken(FIELD_DIRECTIVE); }
".end field" { MATCHT; return makeToken(END_FIELD_DIRECTIVE); }
".subannotation" { MATCHT; return makeToken(SUBANNOTATION_DIRECTIVE); }
".end subannotation" { MATCHT; return makeToken(END_SUBANNOTATION_DIRECTIVE); }
".annotation" { MATCHT; return makeToken(ANNOTATION_DIRECTIVE); }
".end annotation" { MATCHT; return makeToken(END_ANNOTATION_DIRECTIVE); }
".enum" { MATCHT; return makeToken(ENUM_DIRECTIVE); }
".method" { MATCHT; return makeToken(METHOD_DIRECTIVE); }
".end method" { MATCHT; return makeToken(END_METHOD_DIRECTIVE); }
".registers" { MATCHT; return makeToken(REGISTERS_DIRECTIVE); }
".locals" { MATCHT; return makeToken(LOCALS_DIRECTIVE); }
".array-data" { MATCHT; return makeToken(ARRAY_DATA_DIRECTIVE); }
".end array-data" { MATCHT; return makeToken(END_ARRAY_DATA_DIRECTIVE); }
".packed-switch" { MATCHT; return makeToken(PACKED_SWITCH_DIRECTIVE); }
".end packed-switch" { MATCHT; return makeToken(END_PACKED_SWITCH_DIRECTIVE); }
".sparse-switch" { MATCHT; return makeToken(SPARSE_SWITCH_DIRECTIVE); }
".end sparse-switch" { MATCHT; return makeToken(END_SPARSE_SWITCH_DIRECTIVE); }
".catch" { MATCHT; return makeToken(CATCH_DIRECTIVE); }
".catchall" { MATCHT; return makeToken(CATCHALL_DIRECTIVE); }
".line" { MATCHT; return makeToken(LINE_DIRECTIVE); }
".param" { MATCHT; return makeToken(PARAMETER_DIRECTIVE); }
".end param" { MATCHT; return makeToken(END_PARAMETER_DIRECTIVE); }
".local" { MATCHT; return makeToken(LOCAL_DIRECTIVE); }
".end local" { MATCHT; return makeToken(END_LOCAL_DIRECTIVE); }
".restart local" { MATCHT; return makeToken(RESTART_LOCAL_DIRECTIVE); }
".prologue" { MATCHT; return makeToken(PROLOGUE_DIRECTIVE); }
".epilogue" { MATCHT; return makeToken(EPILOGUE_DIRECTIVE); }

    /*Literals*/
{Integer} { MATCHT; return makeTokenStr(POSITIVE_INTEGER_LITERAL); }
-{Integer} { MATCHT; return makeTokenStr(NEGATIVE_INTEGER_LITERAL); }
-?{Integer}[lL] { MATCHT; return makeTokenStr(LONG_LITERAL); }
-?{Integer}[sS] { MATCHT; return makeTokenStr(SHORT_LITERAL); }
-?{Integer}[tT] { MATCHT; return makeTokenStr(BYTE_LITERAL); }

{FloatOrID}[fF]|-?[0-9]+[fF] { MATCHT; return makeTokenStr(FLOAT_LITERAL_OR_ID); }
{FloatOrID}[dD]?|-?[0-9]+[dD] { MATCHT; return makeTokenStr(DOUBLE_LITERAL_OR_ID); }
{Float}[fF] { MATCHT; return makeTokenStr(FLOAT_LITERAL); }
{Float}[dD]? { MATCHT; return makeTokenStr(DOUBLE_LITERAL); }

"true"|"false" {
     MATCHT;
     if (yytext[0] == 'y')
         return makeTokenI(BOOL_LITERAL, 1);
     else
         return makeTokenI(BOOL_LITERAL, 0); }

"null" { MATCHT; return makeToken(NULL_LITERAL); }

"\"" { beginStringOrChar(STRING); sb.push_back('"'); }

' { beginStringOrChar(CHAR); sb.push_back('\''); }


<PARAM_LIST_OR_ID>{PrimitiveType} { MATCHT; return makeTokenStr(PARAM_LIST_OR_ID_PRIMITIVE_TYPE); }
<PARAM_LIST_OR_ID>[^\n] { yyless(0); BEGIN(INITIAL); }
<PARAM_LIST_OR_ID><<EOF>> { BEGIN(INITIAL); }

<PARAM_LIST>{PrimitiveType} { MATCHT; return makeTokenStr(PRIMITIVE_TYPE); }
<PARAM_LIST>{ClassDescriptor} { MATCHT; return makeTokenStr(CLASS_DESCRIPTOR); }
<PARAM_LIST>{ArrayPrefix} { MATCHT; return makeTokenStr(ARRAY_TYPE_PREFIX); }
<PARAM_LIST>[^\n] { yyless(0); BEGIN(INITIAL);}
<PARAM_LIST><<EOF>> { BEGIN(INITIAL);}


<STRING>"\""  {
        sb.push_back('"');
        acceptToken(sb.c_str(), sb.length());
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

<STRING>[\r\n] {
                BEGIN(INITIAL);
                acceptToken(sb.c_str(), sb.length());
                return SmaliParser::make_ERROR(sb, LOCATION); }
<STRING><<EOF>> {
             BEGIN(INITIAL);
             acceptToken(sb.c_str(), sb.length());
             return SmaliParser::make_ERROR(sb, LOCATION); }



<CHAR>' {
        sb.push_back('\'');
        if (sb.length() != 3 ) {
            acceptToken(sb.c_str(), sb.length());
            return SmaliParser::make_ERROR(sb, LOCATION);
        }
        acceptToken(sb.c_str(), sb.length());
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

<CHAR>[\r\n] { BEGIN(INITIAL);
            acceptToken(sb.c_str(), sb.length());
            return SmaliParser::make_ERROR(sb, LOCATION); }
<CHAR><<EOF>> { BEGIN(INITIAL);
            acceptToken(sb.c_str(), sb.length());
            return SmaliParser::make_ERROR(sb, LOCATION); }


    /*Misc*/
[vp][0-9]+ {
        int number = strtoull(yytext + 1, 0, 10);
        if (yytext[0] == 'p' || yytext[0] == 'P') {
            number |= 0x100;
        }
        MATCHT; return makeTokenI(REGISTER, number);
    }

"build"|"runtime"|"system" {
        MATCHT; return makeTokenStr(ANNOTATION_VISIBILITY);
    }

"public" {
        MATCHT; return makeTokenI(FLAG, ACC_FLAGS::ACC_PUBLIC);}
"private" {
        MATCHT; return makeTokenI(FLAG, ACC_FLAGS::ACC_PRIVATE);}
"protected" {
        MATCHT; return makeTokenI(FLAG, ACC_FLAGS::ACC_PROTECTED);}
"static" {
        MATCHT; return makeTokenI(FLAG, ACC_FLAGS::ACC_STATIC);}
"final" {
        MATCHT; return makeTokenI(FLAG, ACC_FLAGS::ACC_FINAL);}
"synchronized" {
        MATCHT; return makeTokenI(FLAG, ACC_FLAGS::ACC_SYNCHRONIZED);}
"super" {
        MATCHT; return makeTokenI(FLAG, ACC_FLAGS::ACC_SUPER);}
"volatile" {
        MATCHT; return makeTokenI(FLAG, ACC_FLAGS::ACC_VOLATILE);}
"bridge" {
        MATCHT; return makeTokenI(FLAG, ACC_FLAGS::ACC_BRIDGE);}
"transient" {
        MATCHT; return makeTokenI(FLAG, ACC_FLAGS::ACC_TRANSIENT);}
"varargs" {
        MATCHT; return makeTokenI(FLAG, ACC_FLAGS::ACC_VARARGS);}
"native" {
        MATCHT; return makeTokenI(FLAG, ACC_FLAGS::ACC_NATIVE);}
"interface" {
        MATCHT; return makeTokenI(FLAG, ACC_FLAGS::ACC_INTERFACE);}
"abstract" {
        MATCHT; return makeTokenI(FLAG, ACC_FLAGS::ACC_ABSTRACT);}
"strict" {
        MATCHT; return makeTokenI(FLAG, ACC_FLAGS::ACC_STRICT);}
"synthetic" {
        MATCHT; return makeTokenI(FLAG, ACC_FLAGS::ACC_SYNTHETIC);}
"annotation" {
        MATCHT; return makeTokenI(FLAG, ACC_FLAGS::ACC_ANNOTATION);}
"enum" {
        MATCHT; return makeTokenI(FLAG, ACC_FLAGS::ACC_ENUM);}
"constructor" {
        MATCHT; return makeTokenI(FLAG, ACC_FLAGS::ACC_CONSTRUCTOR);}
"declared-synchronized" {
        MATCHT; return makeTokenI(FLAG, ACC_FLAGS::ACC_DECLARED_SYNCHRONIZED);}

"no-error"|"generic-error"|"no-such-class"|"no-such-field"|"no-such-method"|"illegal-class-access"|"illegal-field-access"|"illegal-method-access"|"class-change-error"|"instantiation-error" {
    MATCHT; return makeTokenStr(VERIFICATION_ERROR_TYPE);
    }

"inline@0x"{HexDigit}+ { MATCHT; return makeTokenStr(INLINE_INDEX); }
"vtable@0x"{HexDigit}+ { MATCHT; return makeTokenStr(VTABLE_INDEX); }
"field@0x"{HexDigit}+ { MATCHT; return makeTokenStr(FIELD_OFFSET); }

#[^\r\n]* { MATCHT; return makeTokenStr(LINE_COMMENT); }

    /*      instruction keyword     */
"nop"        {MATCHT; return makeToken(OP_NOP);}
"move"       {MATCHT; return makeToken(OP_MOVE);}
"move/from16"        {MATCHT; return makeToken(OP_MOVE_FROM16);}
"move/16"    {MATCHT; return makeToken(OP_MOVE_16);}
"move-wide"  {MATCHT; return makeToken(OP_MOVE_WIDE);}
"move-wide/from16"   {MATCHT; return makeToken(OP_MOVE_WIDE_FROM16);}
"move-wide/16"       {MATCHT; return makeToken(OP_MOVE_WIDE_16);}
"move-object"        {MATCHT; return makeToken(OP_MOVE_OBJECT);}
"move-object/from16" {MATCHT; return makeToken(OP_MOVE_OBJECT_FROM16);}
"move-object/16"     {MATCHT; return makeToken(OP_MOVE_OBJECT_16);}
"move-result"        {MATCHT; return makeToken(OP_MOVE_RESULT);}
"move-result-wide"   {MATCHT; return makeToken(OP_MOVE_RESULT_WIDE);}
"move-result-object" {MATCHT; return makeToken(OP_MOVE_RESULT_OBJECT);}
"move-exception"     {MATCHT; return makeToken(OP_MOVE_EXCEPTION);}
"return-void"        {MATCHT; return makeToken(OP_RETURN_VOID);}
"return"     {MATCHT; return makeToken(OP_RETURN);}
"return-wide"        {MATCHT; return makeToken(OP_RETURN_WIDE);}
"return-object"      {MATCHT; return makeToken(OP_RETURN_OBJECT);}
"const/4"    {MATCHT; return makeToken(OP_CONST_4);}
"const/16"   {MATCHT; return makeToken(OP_CONST_16);}
"const"      {MATCHT; return makeToken(OP_CONST);}
"const/high16"       {MATCHT; return makeToken(OP_CONST_HIGH16);}
"const-wide/16"      {MATCHT; return makeToken(OP_CONST_WIDE_16);}
"const-wide/32"      {MATCHT; return makeToken(OP_CONST_WIDE_32);}
"const-wide" {MATCHT; return makeToken(OP_CONST_WIDE);}
"const-wide/high16"  {MATCHT; return makeToken(OP_CONST_WIDE_HIGH16);}
"const-string"       {MATCHT; return makeToken(OP_CONST_STRING);}
"const-string/jumbo" {MATCHT; return makeToken(OP_CONST_STRING_JUMBO);}
"const-class"        {MATCHT; return makeToken(OP_CONST_CLASS);}
"monitor-enter"      {MATCHT; return makeToken(OP_MONITOR_ENTER);}
"monitor-exit"       {MATCHT; return makeToken(OP_MONITOR_EXIT);}
"check-cast" {MATCHT; return makeToken(OP_CHECK_CAST);}
"instance-of"        {MATCHT; return makeToken(OP_INSTANCE_OF);}
"array-length"       {MATCHT; return makeToken(OP_ARRAY_LENGTH);}
"new-instance"       {MATCHT; return makeToken(OP_NEW_INSTANCE);}
"new-array"  {MATCHT; return makeToken(OP_NEW_ARRAY);}
"filled-new-array"   {MATCHT; return makeToken(OP_FILLED_NEW_ARRAY);}
"filled-new-array/range" {
                    MATCHT; return makeToken(OP_FILLED_NEW_ARRAY_RANGE);}
"fill-array-data"    {MATCHT; return makeToken(OP_FILL_ARRAY_DATA);}
"throw"      {MATCHT; return makeToken(OP_THROW);}
"goto"       {MATCHT; return makeToken(OP_GOTO);}
"goto/16"    {MATCHT; return makeToken(OP_GOTO_16);}
"goto/32"    {MATCHT; return makeToken(OP_GOTO_32);}
"packed-switch"      {MATCHT; return makeToken(OP_PACKED_SWITCH);}
"sparse-switch"      {MATCHT; return makeToken(OP_SPARSE_SWITCH);}
"cmpl-float" {MATCHT; return makeToken(OP_CMPL_FLOAT);}
"cmpg-float" {MATCHT; return makeToken(OP_CMPG_FLOAT);}
"cmpl-double"        {MATCHT; return makeToken(OP_CMPL_DOUBLE);}
"cmpg-double"        {MATCHT; return makeToken(OP_CMPG_DOUBLE);}
"cmp-long"   {MATCHT; return makeToken(OP_CMP_LONG);}
"if-eq"      {MATCHT; return makeToken(OP_IF_EQ);}
"if-ne"      {MATCHT; return makeToken(OP_IF_NE);}
"if-lt"      {MATCHT; return makeToken(OP_IF_LT);}
"if-ge"      {MATCHT; return makeToken(OP_IF_GE);}
"if-gt"      {MATCHT; return makeToken(OP_IF_GT);}
"if-le"      {MATCHT; return makeToken(OP_IF_LE);}
"if-eqz"     {MATCHT; return makeToken(OP_IF_EQZ);}
"if-nez"     {MATCHT; return makeToken(OP_IF_NEZ);}
"if-ltz"     {MATCHT; return makeToken(OP_IF_LTZ);}
"if-gez"     {MATCHT; return makeToken(OP_IF_GEZ);}
"if-gtz"     {MATCHT; return makeToken(OP_IF_GTZ);}
"if-lez"     {MATCHT; return makeToken(OP_IF_LEZ);}
"unused-3e"  {MATCHT; return makeToken(OP_UNUSED_3E);}
"unused-3f"  {MATCHT; return makeToken(OP_UNUSED_3F);}
"unused-40"  {MATCHT; return makeToken(OP_UNUSED_40);}
"unused-41"  {MATCHT; return makeToken(OP_UNUSED_41);}
"unused-42"  {MATCHT; return makeToken(OP_UNUSED_42);}
"unused-43"  {MATCHT; return makeToken(OP_UNUSED_43);}
"aget"       {MATCHT; return makeToken(OP_AGET);}
"aget-wide"  {MATCHT; return makeToken(OP_AGET_WIDE);}
"aget-object"        {MATCHT; return makeToken(OP_AGET_OBJECT);}
"aget-boolean"       {MATCHT; return makeToken(OP_AGET_BOOLEAN);}
"aget-byte"  {MATCHT; return makeToken(OP_AGET_BYTE);}
"aget-char"  {MATCHT; return makeToken(OP_AGET_CHAR);}
"aget-short" {MATCHT; return makeToken(OP_AGET_SHORT);}
"aput"       {MATCHT; return makeToken(OP_APUT);}
"aput-wide"  {MATCHT; return makeToken(OP_APUT_WIDE);}
"aput-object"        {MATCHT; return makeToken(OP_APUT_OBJECT);}
"aput-boolean"       {MATCHT; return makeToken(OP_APUT_BOOLEAN);}
"aput-byte"  {MATCHT; return makeToken(OP_APUT_BYTE);}
"aput-char"  {MATCHT; return makeToken(OP_APUT_CHAR);}
"aput-short" {MATCHT; return makeToken(OP_APUT_SHORT);}
"iget"       {MATCHT; return makeToken(OP_IGET);}
"iget-wide"  {MATCHT; return makeToken(OP_IGET_WIDE);}
"iget-object"        {MATCHT; return makeToken(OP_IGET_OBJECT);}
"iget-boolean"       {MATCHT; return makeToken(OP_IGET_BOOLEAN);}
"iget-byte"  {MATCHT; return makeToken(OP_IGET_BYTE);}
"iget-char"  {MATCHT; return makeToken(OP_IGET_CHAR);}
"iget-short" {MATCHT; return makeToken(OP_IGET_SHORT);}
"iput"       {MATCHT; return makeToken(OP_IPUT);}
"iput-wide"  {MATCHT; return makeToken(OP_IPUT_WIDE);}
"iput-object"        {MATCHT; return makeToken(OP_IPUT_OBJECT);}
"iput-boolean"       {MATCHT; return makeToken(OP_IPUT_BOOLEAN);}
"iput-byte"  {MATCHT; return makeToken(OP_IPUT_BYTE);}
"iput-char"  {MATCHT; return makeToken(OP_IPUT_CHAR);}
"iput-short" {MATCHT; return makeToken(OP_IPUT_SHORT);}
"sget"       {MATCHT; return makeToken(OP_SGET);}
"sget-wide"  {MATCHT; return makeToken(OP_SGET_WIDE);}
"sget-object"        {MATCHT; return makeToken(OP_SGET_OBJECT);}
"sget-boolean"       {MATCHT; return makeToken(OP_SGET_BOOLEAN);}
"sget-byte"  {MATCHT; return makeToken(OP_SGET_BYTE);}
"sget-char"  {MATCHT; return makeToken(OP_SGET_CHAR);}
"sget-short" {MATCHT; return makeToken(OP_SGET_SHORT);}
"sput"       {MATCHT; return makeToken(OP_SPUT);}
"sput-wide"  {MATCHT; return makeToken(OP_SPUT_WIDE);}
"sput-object"        {MATCHT; return makeToken(OP_SPUT_OBJECT);}
"sput-boolean"       {MATCHT; return makeToken(OP_SPUT_BOOLEAN);}
"sput-byte"  {MATCHT; return makeToken(OP_SPUT_BYTE);}
"sput-char"  {MATCHT; return makeToken(OP_SPUT_CHAR);}
"sput-short" {MATCHT; return makeToken(OP_SPUT_SHORT);}
"invoke-virtual"     {MATCHT; return makeToken(OP_INVOKE_VIRTUAL);}
"invoke-super"       {MATCHT; return makeToken(OP_INVOKE_SUPER);}
"invoke-direct"      {MATCHT; return makeToken(OP_INVOKE_DIRECT);}
"invoke-static"      {MATCHT; return makeToken(OP_INVOKE_STATIC);}
"invoke-interface"   {MATCHT; return makeToken(OP_INVOKE_INTERFACE);}
"unused-73"  {MATCHT; return makeToken(OP_UNUSED_73);}
"invoke-virtual/range" {
                        MATCHT; return makeToken(OP_INVOKE_VIRTUAL_RANGE);}
"invoke-super/range" {MATCHT; return makeToken(OP_INVOKE_SUPER_RANGE);}
"invoke-direct/range" {
                        MATCHT; return makeToken(OP_INVOKE_DIRECT_RANGE);}
"invoke-static/range" {
                        MATCHT; return makeToken(OP_INVOKE_STATIC_RANGE);}
"invoke-interface/range" {
                        MATCHT; return makeToken(OP_INVOKE_INTERFACE_RANGE);}
"unused-79"  {MATCHT; return makeToken(OP_UNUSED_79);}
"unused-7a"  {MATCHT; return makeToken(OP_UNUSED_7A);}
"neg-int"    {MATCHT; return makeToken(OP_NEG_INT);}
"not-int"    {MATCHT; return makeToken(OP_NOT_INT);}
"neg-long"   {MATCHT; return makeToken(OP_NEG_LONG);}
"not-long"   {MATCHT; return makeToken(OP_NOT_LONG);}
"neg-float"  {MATCHT; return makeToken(OP_NEG_FLOAT);}
"neg-double" {MATCHT; return makeToken(OP_NEG_DOUBLE);}
"int-to-long"        {MATCHT; return makeToken(OP_INT_TO_LONG);}
"int-to-float"       {MATCHT; return makeToken(OP_INT_TO_FLOAT);}
"int-to-double"      {MATCHT; return makeToken(OP_INT_TO_DOUBLE);}
"long-to-int"        {MATCHT; return makeToken(OP_LONG_TO_INT);}
"long-to-float"      {MATCHT; return makeToken(OP_LONG_TO_FLOAT);}
"long-to-double"     {MATCHT; return makeToken(OP_LONG_TO_DOUBLE);}
"float-to-int"       {MATCHT; return makeToken(OP_FLOAT_TO_INT);}
"float-to-long"      {MATCHT; return makeToken(OP_FLOAT_TO_LONG);}
"float-to-double"    {MATCHT; return makeToken(OP_FLOAT_TO_DOUBLE);}
"double-to-int"      {MATCHT; return makeToken(OP_DOUBLE_TO_INT);}
"double-to-long"     {MATCHT; return makeToken(OP_DOUBLE_TO_LONG);}
"double-to-float"    {MATCHT; return makeToken(OP_DOUBLE_TO_FLOAT);}
"int-to-byte"        {MATCHT; return makeToken(OP_INT_TO_BYTE);}
"int-to-char"        {MATCHT; return makeToken(OP_INT_TO_CHAR);}
"int-to-short"       {MATCHT; return makeToken(OP_INT_TO_SHORT);}
"add-int"    {MATCHT; return makeToken(OP_ADD_INT);}
"sub-int"    {MATCHT; return makeToken(OP_SUB_INT);}
"mul-int"    {MATCHT; return makeToken(OP_MUL_INT);}
"div-int"    {MATCHT; return makeToken(OP_DIV_INT);}
"rem-int"    {MATCHT; return makeToken(OP_REM_INT);}
"and-int"    {MATCHT; return makeToken(OP_AND_INT);}
"or-int"     {MATCHT; return makeToken(OP_OR_INT);}
"xor-int"    {MATCHT; return makeToken(OP_XOR_INT);}
"shl-int"    {MATCHT; return makeToken(OP_SHL_INT);}
"shr-int"    {MATCHT; return makeToken(OP_SHR_INT);}
"ushr-int"   {MATCHT; return makeToken(OP_USHR_INT);}
"add-long"   {MATCHT; return makeToken(OP_ADD_LONG);}
"sub-long"   {MATCHT; return makeToken(OP_SUB_LONG);}
"mul-long"   {MATCHT; return makeToken(OP_MUL_LONG);}
"div-long"   {MATCHT; return makeToken(OP_DIV_LONG);}
"rem-long"   {MATCHT; return makeToken(OP_REM_LONG);}
"and-long"   {MATCHT; return makeToken(OP_AND_LONG);}
"or-long"    {MATCHT; return makeToken(OP_OR_LONG);}
"xor-long"   {MATCHT; return makeToken(OP_XOR_LONG);}
"shl-long"   {MATCHT; return makeToken(OP_SHL_LONG);}
"shr-long"   {MATCHT; return makeToken(OP_SHR_LONG);}
"ushr-long"  {MATCHT; return makeToken(OP_USHR_LONG);}
"add-float"  {MATCHT; return makeToken(OP_ADD_FLOAT);}
"sub-float"  {MATCHT; return makeToken(OP_SUB_FLOAT);}
"mul-float"  {MATCHT; return makeToken(OP_MUL_FLOAT);}
"div-float"  {MATCHT; return makeToken(OP_DIV_FLOAT);}
"rem-float"  {MATCHT; return makeToken(OP_REM_FLOAT);}
"add-double" {MATCHT; return makeToken(OP_ADD_DOUBLE);}
"sub-double" {MATCHT; return makeToken(OP_SUB_DOUBLE);}
"mul-double" {MATCHT; return makeToken(OP_MUL_DOUBLE);}
"div-double" {MATCHT; return makeToken(OP_DIV_DOUBLE);}
"rem-double" {MATCHT; return makeToken(OP_REM_DOUBLE);}
"add-int/2addr"      {MATCHT; return makeToken(OP_ADD_INT_2ADDR);}
"sub-int/2addr"      {MATCHT; return makeToken(OP_SUB_INT_2ADDR);}
"mul-int/2addr"      {MATCHT; return makeToken(OP_MUL_INT_2ADDR);}
"div-int/2addr"      {MATCHT; return makeToken(OP_DIV_INT_2ADDR);}
"rem-int/2addr"      {MATCHT; return makeToken(OP_REM_INT_2ADDR);}
"and-int/2addr"      {MATCHT; return makeToken(OP_AND_INT_2ADDR);}
"or-int/2addr"       {MATCHT; return makeToken(OP_OR_INT_2ADDR);}
"xor-int/2addr"      {MATCHT; return makeToken(OP_XOR_INT_2ADDR);}
"shl-int/2addr"      {MATCHT; return makeToken(OP_SHL_INT_2ADDR);}
"shr-int/2addr"      {MATCHT; return makeToken(OP_SHR_INT_2ADDR);}
"ushr-int/2addr"     {MATCHT; return makeToken(OP_USHR_INT_2ADDR);}
"add-long/2addr"     {MATCHT; return makeToken(OP_ADD_LONG_2ADDR);}
"sub-long/2addr"     {MATCHT; return makeToken(OP_SUB_LONG_2ADDR);}
"mul-long/2addr"     {MATCHT; return makeToken(OP_MUL_LONG_2ADDR);}
"div-long/2addr"     {MATCHT; return makeToken(OP_DIV_LONG_2ADDR);}
"rem-long/2addr"     {MATCHT; return makeToken(OP_REM_LONG_2ADDR);}
"and-long/2addr"     {MATCHT; return makeToken(OP_AND_LONG_2ADDR);}
"or-long/2addr"      {MATCHT; return makeToken(OP_OR_LONG_2ADDR);}
"xor-long/2addr"     {MATCHT; return makeToken(OP_XOR_LONG_2ADDR);}
"shl-long/2addr"     {MATCHT; return makeToken(OP_SHL_LONG_2ADDR);}
"shr-long/2addr"     {MATCHT; return makeToken(OP_SHR_LONG_2ADDR);}
"ushr-long/2addr"    {MATCHT; return makeToken(OP_USHR_LONG_2ADDR);}
"add-float/2addr"    {MATCHT; return makeToken(OP_ADD_FLOAT_2ADDR);}
"sub-float/2addr"    {MATCHT; return makeToken(OP_SUB_FLOAT_2ADDR);}
"mul-float/2addr"    {MATCHT; return makeToken(OP_MUL_FLOAT_2ADDR);}
"div-float/2addr"    {MATCHT; return makeToken(OP_DIV_FLOAT_2ADDR);}
"rem-float/2addr"    {MATCHT; return makeToken(OP_REM_FLOAT_2ADDR);}
"add-double/2addr"   {MATCHT; return makeToken(OP_ADD_DOUBLE_2ADDR);}
"sub-double/2addr"   {MATCHT; return makeToken(OP_SUB_DOUBLE_2ADDR);}
"mul-double/2addr"   {MATCHT; return makeToken(OP_MUL_DOUBLE_2ADDR);}
"div-double/2addr"   {MATCHT; return makeToken(OP_DIV_DOUBLE_2ADDR);}
"rem-double/2addr"   {MATCHT; return makeToken(OP_REM_DOUBLE_2ADDR);}
"add-int/lit16"      {MATCHT; return makeToken(OP_ADD_INT_LIT16);}
"rsub-int"   {MATCHT; return makeToken(OP_RSUB_INT);}
"mul-int/lit16"      {MATCHT; return makeToken(OP_MUL_INT_LIT16);}
"div-int/lit16"      {MATCHT; return makeToken(OP_DIV_INT_LIT16);}
"rem-int/lit16"      {MATCHT; return makeToken(OP_REM_INT_LIT16);}
"and-int/lit16"      {MATCHT; return makeToken(OP_AND_INT_LIT16);}
"or-int/lit16"       {MATCHT; return makeToken(OP_OR_INT_LIT16);}
"xor-int/lit16"      {MATCHT; return makeToken(OP_XOR_INT_LIT16);}
"add-int/lit8"       {MATCHT; return makeToken(OP_ADD_INT_LIT8);}
"rsub-int/lit8"      {MATCHT; return makeToken(OP_RSUB_INT_LIT8);}
"mul-int/lit8"       {MATCHT; return makeToken(OP_MUL_INT_LIT8);}
"div-int/lit8"       {MATCHT; return makeToken(OP_DIV_INT_LIT8);}
"rem-int/lit8"       {MATCHT; return makeToken(OP_REM_INT_LIT8);}
"and-int/lit8"       {MATCHT; return makeToken(OP_AND_INT_LIT8);}
"or-int/lit8"        {MATCHT; return makeToken(OP_OR_INT_LIT8);}
"xor-int/lit8"       {MATCHT; return makeToken(OP_XOR_INT_LIT8);}
"shl-int/lit8"       {MATCHT; return makeToken(OP_SHL_INT_LIT8);}
"shr-int/lit8"       {MATCHT; return makeToken(OP_SHR_INT_LIT8);}
"ushr-int/lit8"      {MATCHT; return makeToken(OP_USHR_INT_LIT8);}
"+iget-volatile"     {MATCHT; return makeToken(OP_IGET_VOLATILE);}
"+iput-volatile"     {MATCHT; return makeToken(OP_IPUT_VOLATILE);}
"+sget-volatile"     {MATCHT; return makeToken(OP_SGET_VOLATILE);}
"+sput-volatile"     {MATCHT; return makeToken(OP_SPUT_VOLATILE);}
"+iget-object-volatile" {
                        MATCHT; return makeToken(OP_IGET_OBJECT_VOLATILE);}
"+iget-wide-volatile" {
                        MATCHT; return makeToken(OP_IGET_WIDE_VOLATILE);}
"+iput-wide-volatile" {
                        MATCHT; return makeToken(OP_IPUT_WIDE_VOLATILE);}
"+sget-wide-volatile" {
                        MATCHT; return makeToken(OP_SGET_WIDE_VOLATILE);}
"+sput-wide-volatile" {
                        MATCHT; return makeToken(OP_SPUT_WIDE_VOLATILE);}
"^breakpoint"        {MATCHT; return makeToken(OP_BREAKPOINT);}
"^throw-verification-error" {
                        MATCHT; return makeToken(OP_THROW_VERIFICATION_ERROR);}
"+execute-inline"    {MATCHT; return makeToken(OP_EXECUTE_INLINE);}
"+execute-inline/range" {
                        MATCHT; return makeToken(OP_EXECUTE_INLINE_RANGE);}
"+invoke-object-init/range" {
                        MATCHT; return makeToken(OP_INVOKE_OBJECT_INIT_RANGE);}
"+return-void-barrier" {
                        MATCHT; return makeToken(OP_RETURN_VOID_BARRIER);}
"+iget-quick"        {MATCHT; return makeToken(OP_IGET_QUICK);}
"+iget-wide-quick"   {MATCHT; return makeToken(OP_IGET_WIDE_QUICK);}
"+iget-object-quick" {MATCHT; return makeToken(OP_IGET_OBJECT_QUICK);}
"+iput-quick"        {MATCHT; return makeToken(OP_IPUT_QUICK);}
"+iput-wide-quick"   {MATCHT; return makeToken(OP_IPUT_WIDE_QUICK);}
"+iput-object-quick" {MATCHT; return makeToken(OP_IPUT_OBJECT_QUICK);}
"+invoke-virtual-quick" {
                        MATCHT; return makeToken(OP_INVOKE_VIRTUAL_QUICK);}
"+invoke-virtual-quick/range" {
                        MATCHT; return makeToken(OP_INVOKE_VIRTUAL_QUICK_RANGE);}
"+invoke-super-quick" {
                        MATCHT; return makeToken(OP_INVOKE_SUPER_QUICK);}
"+invoke-super-quick/range" {
                        MATCHT; return makeToken(OP_INVOKE_SUPER_QUICK_RANGE);}
"+iput-object-volatile" {
                        MATCHT; return makeToken(OP_IPUT_OBJECT_VOLATILE);}
"+sget-object-volatile" {
                        MATCHT; return makeToken(OP_SGET_OBJECT_VOLATILE);}
"+sput-object-volatile" {
                        MATCHT; return makeToken(OP_SPUT_OBJECT_VOLATILE);}
"unused-ff"  {MATCHT; return makeToken(OP_UNUSED_FF);}


<ARRAY_DESCRIPTOR>{PrimitiveType} { BEGIN(INITIAL); MATCHT; return makeTokenStr(PRIMITIVE_TYPE); }
<ARRAY_DESCRIPTOR>{ClassDescriptor} { BEGIN(INITIAL); MATCHT; return makeTokenStr(CLASS_DESCRIPTOR); }
<ARRAY_DESCRIPTOR>[^\n] { yyless(0); BEGIN(INITIAL); }
<ARRAY_DESCRIPTOR><<EOF>> { BEGIN(INITIAL); }


    /*Types*/
{PrimitiveType} { MATCHT; return makeTokenStr(PRIMITIVE_TYPE); }
V { MATCHT; return makeToken(VOID_TYPE); }
{ClassDescriptor} { MATCHT; return makeTokenStr(CLASS_DESCRIPTOR); }

    /* we have to drop into a separate state so that we don't parse something like */
    /* "[I->" as "[" followed by "I-" as a SIMPLE_NAME */
{ArrayPrefix} {
      BEGIN(ARRAY_DESCRIPTOR);
      MATCHT; return makeTokenStr(ARRAY_TYPE_PREFIX);
    }

{PrimitiveType}{PrimitiveType}+ {
        // go back and re-lex it as a PARAM_LIST_OR_ID
        yyless(0);
        BEGIN(PARAM_LIST_OR_ID);
    }

{Type}{Type}+ {
        // go back and re-lex it as a PARAM_LIST
        yyless(0);
        BEGIN(PARAM_LIST);
    }

{SimpleName} { MATCHT; return makeTokenStr(SIMPLE_NAME); }
"<"{SimpleName}">" { MATCHT; return makeTokenStr(MEMBER_NAME); }


[\t\r]      { MATCHT; }
[\n]        { MATCHT; return makeToken(EOL); }
.           { MATCHT; }
<<EOF>>     { return yyterminate(); }

%%

void Analysis::SmaliLexer::yyBegin(int type) {
    BEGIN(type);
}

