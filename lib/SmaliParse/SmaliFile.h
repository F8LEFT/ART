//===- SmaliFile.h - ART-LEX ------------------------------------*- cpp -*-===//
//
//                     ANDROID REVERSE TOOLKIT
//
// This file is distributed under the GNU GENERAL PUBLIC LICENSE
// V3 License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// SmaliFile use SmaliParser to parse .smali file to AST tree.
//
//===----------------------------------------------------------------------===//


#ifndef ANDROIDREVERSETOOLKIT_SMALIFILE_H
#define ANDROIDREVERSETOOLKIT_SMALIFILE_H

#include "SmaliLexer.h"
#include "SmaliParser.h"
#include <QSharedPointer>

class SmaliFile {
public:
    SmaliFile(const std::string& file);
    SmaliFile(const std::string& file, const std::string &input);
    ~SmaliFile();

    void print();
public:
    std::string m_filepath;

    antlr4::CharStream *m_input;
    SmaliLexer* m_lexer;
    SmaliParser* m_parser;
    antlr4::CommonTokenStream* m_tokens;
    SmaliParser::Smali_fileContext* m_smali;
};


#endif //ANDROIDREVERSETOOLKIT_SMALIFILE_H
