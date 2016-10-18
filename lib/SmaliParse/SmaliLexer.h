//===- SmaliLexer.h - ART-LEX ----------------------------------*- c++ -*-===//
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


#ifndef PROJECT_SMALILEXER_H
#define PROJECT_SMALILEXER_H

#if ! defined(yyFlexLexerOnce)
#undef yyFlexLexer
#define yyFlexLexer Analysis_FlexLexer
#include <FlexLexer.h>
#endif

#undef YY_DECL
#define YY_DECL Analysis::SmaliParser::symbol_type Analysis::SmaliLexer::get_next_token()

#include "SmaliParser.hpp"

namespace Analysis {

    class SmaliLexer : public yyFlexLexer {
    public:
        SmaliLexer():mColumn(1), mLine(1) {}
        virtual ~SmaliLexer() {}
        virtual Analysis::SmaliParser::symbol_type get_next_token();
    public:
        const std::string& text() {return mText;}
        const std::string& curTokenText() {return mCurTokenText;}
        int curTokenLen() {return mCurTokenText.length ();}
        int column() {return mColumn;}
        int line() {return mLine;}

    public:
        void yyBegin(int type);

    private:
        void acceptToken(const char* text, int len) {
            if (text[0] == '\n') {
                mColumn = 1;
                mLine++;
                mText.clear ();
                mCurTokenText.clear ();
                return;
            }
            mColumn += mCurTokenText.length ();
            mCurTokenText = std::string(text, len);
            mText += mCurTokenText;
        }

    private:
        std::string mText;          // current line
        std::string mCurTokenText;  // current token
        int mColumn;
        int mLine;

    public:
        void switch_streams( FLEX_STD istream* new_in,
                             FLEX_STD ostream* new_out ) {
            mColumn = 1; mLine = 1;
            mText.clear (); mCurTokenText.clear ();
            yyFlexLexer::switch_streams (new_in,new_out);
        }
        void switch_streams( FLEX_STD istream& new_in,
                             FLEX_STD ostream& new_out ) {
            mColumn = 1; mLine = 1;
            mText.clear (); mCurTokenText.clear ();
            yyFlexLexer::switch_streams (new_in,new_out);
        }

    private:
        void beginStringOrChar(int state) {
            yyBegin (state);
            sb.clear();
        }
        Analysis::SmaliParser::symbol_type endStringOrChar(int type) {
            yyBegin(0);
            mCurTokenText = sb;
            mColumn -= sb.length () - 1;
            switch(type) {
                case SmaliParser::token::TOKEN_STRING_LITERAL:
                    return SmaliParser::make_STRING_LITERAL (sb, Analysis::location(nullptr, line(), column()));
                    break;
                case SmaliParser::token::TOKEN_CHAR_LITERAL:
                    return SmaliParser::make_CHAR_LITERAL (sb, Analysis::location(nullptr, line(), column()));
                    break;
                default:
                    break;
            }
            return SmaliParser::make_ERROR (sb, Analysis::location(nullptr, line(), column()));
        }

        std::string sb;
    };
}
#endif //PROJECT_SMALILEXER_H
