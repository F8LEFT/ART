//===- SmaliHighlight.cpp - ART-GUI HighLighter------------------*- C++ -*-===//
//
//                     ANDROID REVERSE TOOLKIT
//
// This file is distributed under the GNU GENERAL PUBLIC LICENSE
// V3 License. See LICENSE.TXT for details.
//
//===---------------------------------------------------------------------===//


#include "SmaliHighlight.h"
#include "SmaliLexer.h"

#include <sstream>
#include <QTextDocument>

using namespace Analysis;

SmaliHighlight::SmaliHighlight (QTextDocument *parent,QString fileName)
        : QSyntaxHighlighter(parent)
{
    mKeywordFormat.setForeground(QBrush(QColor(175,215,231)));
    mOpFormat.setForeground(QBrush(QColor(128,0,128)));
    mSymbolFormat.setForeground(QBrush(QColor(0,0,128)));
    mCStringFormat.setForeground(QBrush(QColor(0,128,0)));
    mNameStringFormat.setForeground(QBrush(QColor(102,163,52)));
    mCommentFormat.setForeground(QBrush(QColor(0,128,0)));
    mClassTypeFormat.setForeground(QBrush(QColor(0,0,0)));
    mFlagFormat.setForeground(QBrush(QColor(128,0,128)));
    mREGDFormat.setForeground(QBrush(QColor(0,0,255)));
    mNumberFormat.setForeground(QBrush(QColor(0,0,128)));

    auto font = parent->defaultFont ();
    mKeywordFormat.setFont (font);
    mOpFormat.setFont (font);
    mSymbolFormat.setFont (font);
    mCStringFormat.setFont (font);
    mNameStringFormat.setFont (font);
    mCommentFormat.setFont (font);
    mClassTypeFormat.setFont (font);
    mFlagFormat.setFont (font);
    mREGDFormat.setFont (font);
    mNumberFormat.setFont (font);
}

void SmaliHighlight::highlightBlock (const QString &text)
{
    SmaliLexer lexer;
    auto str = text.toStdString ();
    std::istringstream is(str);
    lexer.switch_streams (&is,nullptr);
    while(true)
    {
        auto token = lexer.get_next_token ();
        auto type = token.token ();
        if (type == SmaliParser::token::TOKEN_END)
            break;
        if (type == SmaliParser::token::TOKEN_EOL)
        {
            continue;
        }
        QTextCharFormat* format;
        if(type > SmaliParser::token::TOKEN_KEYWORD_BEGIN
           && type < SmaliParser::token::TOKEN_KEYWORD_END) {
            format = &mKeywordFormat;
        } else
        if (type > SmaliParser::token::TOKEN_OP_BEGIN
            && type < SmaliParser::token::TOKEN_OP_END) {
            format = &mOpFormat;
        } else
        if (type > SmaliParser::token::TOKEN_SYMBOL_BEGIN
              && type < SmaliParser::token::TOKEN_SYMBOL_END) {
            format = &mSymbolFormat;
        } else {
            switch (type) {
                case SmaliParser::token::TOKEN_STRING_LITERAL:
                case SmaliParser::token::TOKEN_CHAR_LITERAL:
                    format = &mCStringFormat;
                    break;
                case SmaliParser::token::TOKEN_SIMPLE_NAME:
                case SmaliParser::token::TOKEN_MEMBER_NAME:
                    format = &mNameStringFormat;
                    break;
                case SmaliParser::token::TOKEN_LINE_COMMENT:
                    format = &mCommentFormat;
                    break;
                case SmaliParser::token::TOKEN_CLASS_DESCRIPTOR:
                case SmaliParser::token::TOKEN_PRIMITIVE_TYPE:
                case SmaliParser::token::TOKEN_ARRAY_TYPE_PREFIX:
                case SmaliParser::token::TOKEN_VOID_TYPE:
                    format = &mClassTypeFormat;
                    break;
                case SmaliParser::token::TOKEN_FLAG:
                    format = &mFlagFormat;
                    break;
                case SmaliParser::token::TOKEN_REGISTER:
                    format = &mREGDFormat;
                    break;
                case SmaliParser::token::TOKEN_NEGATIVE_INTEGER_LITERAL:
                case SmaliParser::token::TOKEN_POSITIVE_INTEGER_LITERAL:
                case SmaliParser::token::TOKEN_LONG_LITERAL:
                case SmaliParser::token::TOKEN_SHORT_LITERAL:
                case SmaliParser::token::TOKEN_BYTE_LITERAL:
                case SmaliParser::token::TOKEN_FLOAT_LITERAL_OR_ID:
                case SmaliParser::token::TOKEN_DOUBLE_LITERAL_OR_ID:
                case SmaliParser::token::TOKEN_FLOAT_LITERAL:
                case SmaliParser::token::TOKEN_DOUBLE_LITERAL:
                    format = &mNumberFormat;
                    break;
                default:
                    Q_ASSERT (false && "unknown token!!");
                    break;
            }
        }
        setFormat(lexer.column () - 1, lexer.curTokenLen (), *format);
    }
}
