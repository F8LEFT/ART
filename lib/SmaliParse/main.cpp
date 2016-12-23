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
#include "SmaliParser.h"
#include "SmaliFile.h"
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

    SmaliParser parser(&tokens);

    antlr4::tree::ParseTree* tree = parser.smali_file();

    std::cout << tree->toStringTree(&parser) << std::endl << std::endl;
}

int main() {
//    testANRLR();
//    SmaliFile file("/home/f8left/CodeSrc/ART/res/Loader$ForceLoadContentObserver.smali");
//    file.print();
    auto m_smalidata = new SmaliFile("/home/f8left/CodeSrc/ART/cmake-build-debug/bin/Projects/crackme/Project/smali/com/bradzhao/crackme/MainActivity.smali");

    auto tokens = m_smalidata->m_tokens;
    for(auto& token : tokens->getTokens()) {
        cout << token->getLine() << ", " << token->getText() << endl;
    }

    auto root = m_smalidata->m_smali;

    // for foldable
    auto annotations = root->annotation();
    for(auto &annotation: annotations) {
        auto startLine = annotation->ANNOTATION_DIRECTIVE()->getSymbol()->getLine();
        auto endLine = annotation->END_ANNOTATION_DIRECTIVE()->getSymbol()->getLine();
        cout << startLine << "--" << endLine << endl;
//        setFoldableArea(startLine, endLine, SmaliParser::ANNOTATION_DIRECTIVE);
    }
    auto methods = root->method();
    for(auto& method: methods) {
        auto startLine = method->METHOD_DIRECTIVE()->getSymbol()->getLine();
        auto endLine = method->END_METHOD_DIRECTIVE()->getSymbol()->getLine();
        cout << startLine << "--" << endLine << endl;
//        setFoldableArea(startLine, endLine, SmaliParser::METHOD_DIRECTIVE);
    }
    return 0;
}