//===- main.cpp - ART-LEX --------------------------------------*- C++ -*-===//
//
//                     ANDROID REVERSE TOOLKIT
//
// This file is distributed under the GNU GENERAL PUBLIC LICENSE
// V3 License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// The file defines a test to SmaliParse.
//
//===----------------------------------------------------------------------===//

#include <iostream>
#include "SmaliLexer.h"
#include <sstream>
#include <fstream>
#include "SmaliParser.hpp"
#include "Interpreter.h"

using namespace std;
using namespace Analysis;

int main() {
    string st;
    ifstream ifile;
    ifile.open ("/home/f8left/CodeSrc/ART/res/LruCache.smali");

    // test Lexer
    if (ifile.is_open ()) {
        SmaliLexer lexer;
        lexer.switch_streams (&ifile,nullptr);
        while(true) {
            auto token = lexer.get_next_token ();
            if(token.token () == 0)
                break;
            if(token.token () == SmaliParser::token::TOKEN_EOL) {
                continue;
            }
            cout << "type " << token.token ()
                 << " line :" << lexer.line ()
                 << " column :" << lexer.column ()
                 << " len :" << lexer.curTokenLen ()
                 << " token :" << lexer.curTokenText () << endl;
//                 << " text :" << lexer.text() << endl;
        }
    }
    ifile.close ();
    // test parser
    ifile.open ("/home/f8left/CodeSrc/ART/res/LruCache.smali");
    if(ifile.is_open ()) {
        Interpreter interpreter;
        SmaliClass sClass;
        StringPool sp;
        sClass.setStringPool (&sp);
        interpreter.switchInputStream (&ifile,&sClass);
        interpreter.parse ();
        interpreter.analysis ();
        cout << "print file tree" << endl;
        interpreter.print ();
    }
    ifile.close ();
    return 0;
}