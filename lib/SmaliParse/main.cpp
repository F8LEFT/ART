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
#include "Lexer.h"
#include <sstream>
#include <fstream>
#include "Parser.hpp"
#include "Interpreter.h"

using namespace std;
using namespace Analysis;

int main() {
    auto l = strtoll ("-0x800000000L", 0, 16);
    ifstream ifile;
//    ifile.open ("/home/f8left/CodeSrc/ART/res/StubApplication.smali");


    // test Lexer
    if (ifile.is_open ()) {
        Lexer lexer;
        lexer.switch_streams (&ifile,nullptr);
        while(true) {
            auto token = lexer.get_next_token ();
            if(token.token () == 0)
                break;
            if(token.token () == Parser::token::TOKEN_EOL) {
                continue;
            }
            cout << " line :" << lexer.line ()
                 << " column :" << lexer.column ()
                 << " len :" << lexer.curTokenLen ()
                 << " token :" << lexer.curTokenText () << endl;
//                 << " text :" << lexer.text() << endl;
        }
    }
    ifile.close ();
    // test parser
    ifile.open ("/home/f8left/CodeSrc/ART/lib/gui/bin/Projects/app.greyshirts.sslcapture-1/Project/smali/org/spongycastle/crypto/digests/GOST3411Digest.smali");
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
    string a;
    a.substr (0, a.length () - 12);

    return 0;
}