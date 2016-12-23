//===- SmaliFile.cpp - ART-LEX ----------------------------------*- cpp -*-===//
//
//                     ANDROID REVERSE TOOLKIT
//
// This file is distributed under the GNU GENERAL PUBLIC LICENSE
// V3 License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

#include "SmaliFile.h"

#include <SmaliLexer.h>
#include <iostream>

using namespace std;


SmaliFile::SmaliFile(const std::string& file)
{
    m_filepath = file;
    m_input = new antlr4::ANTLRFileStream(file);

    m_lexer = new SmaliLexer(m_input);

    m_tokens = new antlr4::CommonTokenStream(m_lexer);
    m_tokens->fill();
    m_parser = new SmaliParser(m_tokens);
    m_smali = m_parser->smali_file();

}

SmaliFile::SmaliFile(const std::string& file, const std::string &input) {
    m_filepath = file;
    m_input = new antlr4::ANTLRInputStream(input);

    m_lexer = new SmaliLexer(m_input);

    m_tokens = new antlr4::CommonTokenStream(m_lexer);
    m_tokens->fill();
    m_parser = new SmaliParser(m_tokens);
    m_smali = m_parser->smali_file();

}


SmaliFile::~SmaliFile() {
    delete m_input;
    delete m_lexer;
    delete m_parser;
    delete m_tokens;
}

void SmaliFile::print() {
    if(!m_smali->isValid)
        cout << "smali file is not valid!!!" << endl;
    if(m_smali->hasClassSpec) {
        cout << ".class ";
        auto class_spec = m_smali->class_spec(0);
        auto access_spec = class_spec->access_list()->ACCESS_SPEC();
        for(auto* access: access_spec) {
            cout << access->getText() << " ";
        }

        cout << class_spec->className << endl;
    }
    if(m_smali->hasSuperSpec) {
        auto super_spec = m_smali->super_spec(0);
        cout << ".super " << super_spec->CLASS_DESCRIPTOR()->getText() << endl;
    }
    if(m_smali->hasSourceSpec) {
        auto sourc_spec = m_smali->source_spec(0);
        cout << ".source " << sourc_spec->STRING_LITERAL()->getText() << endl;
    }
}


