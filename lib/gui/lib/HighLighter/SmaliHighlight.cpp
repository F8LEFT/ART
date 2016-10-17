//===- SmaliHighlight.cpp - ART-GUI HighLighter------------------*- C++ -*-===//
//
//                     ANDROID REVERSE TOOLKIT
//
// This file is distributed under the GNU GENERAL PUBLIC LICENSE
// V3 License. See LICENSE.TXT for details.
//
//===---------------------------------------------------------------------===//


#include "SmaliHighlight.h"
#include "Lexer.h"

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
    Lexer lexer;
    auto str = text.toStdString ();
    std::istringstream is(str);
    lexer.switch_streams (&is,nullptr);
    while(true)
    {
        auto token = lexer.get_next_token ();
        auto type = token.token ();
        if (type == Parser::token::TOKEN_END)
            break;
        if (type == Parser::token::TOKEN_EOL)
        {
            continue;
        }
        QTextCharFormat* format;
        if(type > Parser::token::TOKEN_KEYWORD_BEGIN
           && type < Parser::token::TOKEN_KEYWORD_END) {
            format = &mKeywordFormat;
        } else
        if (type > Parser::token::TOKEN_OP_BEGIN
            && type < Parser::token::TOKEN_OP_END) {
            format = &mOpFormat;
        } else
        if (type > Parser::token::TOKEN_SYMBOL_BEGIN
              && type < Parser::token::TOKEN_SYMBOL_END) {
            format = &mSymbolFormat;
        } else {
            switch (type) {
                case Parser::token::TOKEN_CSTRING:
                    format = &mCStringFormat;
                    break;
                case Parser::token::TOKEN_NAMESTRING:
                    format = &mNameStringFormat;
                    break;
                case Parser::token::TOKEN_COMMENT:
                    format = &mCommentFormat;
                    break;
                case Parser::token::TOKEN_CLASSNAME:
                case Parser::token::TOKEN_CLASSTYPE:
                    format = &mClassTypeFormat;
                    break;
                case Parser::token::TOKEN_FLAG:
                    format = &mFlagFormat;
                    break;
                case Parser::token::TOKEN_REGD:
                    format = &mREGDFormat;
                    break;
                case Parser::token::TOKEN_NUMBERSTRING:
                case Parser::token::TOKEN_HEXNUMBERSTRING:
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
