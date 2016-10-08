//===- Lexer.h - ART-LEX ---------------------------------------*- c++ -*-===//
//
//                     ANDROID REVERSE TOOLKIT
//
// This file is distributed under the GNU GENERAL PUBLIC LICENSE
// V3 License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// The file defines a header for lexer.ll.
//
//===----------------------------------------------------------------------===//

#ifndef PROJECT_LEXER_H
#define PROJECT_LEXER_H

#if ! defined(yyFlexLexerOnce)
#undef yyFlexLexer
#define yyFlexLexer Analysis_FlexLexer
#include <FlexLexer.h>
#endif

#undef YY_DECL
#define YY_DECL Analysis::Parser::symbol_type Analysis::Lexer::get_next_token()

#include "Parser.hpp"

namespace Analysis {
    class Lexer : public yyFlexLexer {
    public:
        Lexer() {}
        virtual ~Lexer() {}
        virtual Analysis::Parser::symbol_type get_next_token();

    public:
        const std::string& text() {return mText;}
        const std::string& curTokenText() {return mCurTokenText;}
        int column() {return mColumn;}
        int line() {return mLine;}

    private:
        void acceptToken(const char* text, int len) {
            mCurTokenText = std::string(text, len);
            if (text[0] == '\n') {
                mColumn = 1;
                mLine++;
                mText.clear ();
                return;
            }
            mText += mCurTokenText;
            mColumn += len;
        }

    private:
        std::string mText;          // current line
        std::string mCurTokenText;  // current token
        int mColumn;
        int mLine;
    };
}

#endif //PROJECT_LEXER_H
