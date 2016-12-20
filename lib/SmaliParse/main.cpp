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
#include <sstream>
#include <fstream>

#include "SmaliLexer.h"
#include <QString>

using namespace std;

void testANRLR() {
    std::string file = "/home/f8left/CodeSrc/ART/res/Loader$ForceLoadContentObserver.smali";


    antlr4::ANTLRFileStream input(file);
    SmaliLexer lexer(&input);
    antlr4::CommonTokenStream tokens(&lexer);

    auto names = lexer.getTokenNames();

    tokens.fill();
    for (auto token : tokens.getTokens()) {
        if(token->getType() >= names.size()) {
            break;
        }
        std::cout << (int)token->getLine() << "," << (int)token->getCharPositionInLine() << ":" <<
                  token->getText() << "," << names[token->getType()] << std::endl;
    }

    for (auto token : tokens.getTokens()) {
        std::cout << token->toString() << std::endl;
    }

//    antlr4::CommonToken tok;
//    QString sb;
//    sb.length();
//
//    std::string s;
//    lexer.getCharPositionInLine()


//    TParser parser(&tokens);
//    tree::ParseTree* tree = parser.main();

//    std::cout << tree->toStringTree(&parser) << std::endl << std::endl;
}

int main() {
    testANRLR();
    return 0;
}