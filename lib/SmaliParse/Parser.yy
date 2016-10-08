%skeleton "lalr1.cc" /* -*- C++ -*- */
%require "3.0"
%defines
%define parser_class_name { Parser }

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
// bison -v -o Parser.cpp Parser.yy
// to generate parser source file
//
//===----------------------------------------------------------------------===//
    #include <iostream>
    #include <string>
    #include <vector>
    #include <stdint.h>
    #include "Lexer.h"
    namespace Analysis {
        class Lexer;
    }
    using namespace std;
}

%code top
{
    #include <iostream>
    #include "Lexer.h"
    #include "Parser.hpp"
    #include "location.hh"

    static Analysis::Parser::symbol_type yylex(Analysis::Lexer &lexer) {
        return lexer.get_next_token();
    }

    using namespace Analysis;
}

%lex-param { Analysis::Lexer &lexer }
%parse-param { Analysis::Lexer &lexer }
%locations
%define parse.trace
%define parse.error verbose

%define api.token.prefix {TOKEN_}

%token END 0 "end of file";
%token EOL "end of line";

%start program

%%
program :   {
                ;
            }
        | program EOL
        | program error EOL
        ;
%%

void Analysis::Parser::error(const location &loc , const std::string &message) {
	cout << "Parse error: " << message << endl
	    << "Error location: " << loc << endl << endl;
}
