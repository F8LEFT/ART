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

	using namespace std;

	#define yyterminate() Analysis::Parser::make_END(\
	    Analysis::location(YY_NULL,line(), column()));

	#define YY_USER_ACTION acceptToken(yytext, yyleng);

%}

%option nodefault
%option noyywrap
%option c++
%option yyclass="Lexer"
%option prefix="Analysis_"

%%

.           {;}
<<EOF>>     {return yyterminate(); }

%%
