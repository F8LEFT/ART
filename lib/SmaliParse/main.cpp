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
using namespace std;
using namespace Analysis;

int main() {

    ifstream ifile;
    ifile.open ("/home/f8left/CodeSrc/FDA/SmaliParser/res/StubApplication.smali");
    // test Lexer
    if (ifile.is_open ()) {
        Lexer lexer;
        lexer.switch_streams (&ifile,nullptr);
        while(true) {
            auto token = lexer.get_next_token ();
            if(token.token () == 0)
                break;
            cout << lexer.text() << endl;
        }
    }
    return 0;
}