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
#include <QDebug>
#include <Config/Config.h>
#include <utils/StringUtil.h>
#include <utils/Configuration.h>

using namespace Analysis;

SmaliHighlight::SmaliHighlight (QTextDocument *parent)
        : QSyntaxHighlighter(parent)
{
}

SmaliHighlight::~SmaliHighlight()
{

}


void SmaliHighlight::highlightBlock (const QString &text)
{
    SmaliLexer lexer;
    auto str = text.toStdString ();
    std::istringstream is(str);
    lexer.switch_streams (&is,nullptr);
    while(true)
    {
        KSyntaxHighlighting::Theme::TextStyle  style;

        auto token = lexer.get_next_token ();
        auto type = token.token ();
        if (type == SmaliParser::token::TOKEN_END)
            break;
        if (type == SmaliParser::token::TOKEN_EOL)
        {
            continue;
        }
        if(type > SmaliParser::token::TOKEN_KEYWORD_BEGIN
           && type < SmaliParser::token::TOKEN_KEYWORD_END) {
            style = KSyntaxHighlighting::Theme::Keyword;
        } else
        if (type > SmaliParser::token::TOKEN_OP_BEGIN
            && type < SmaliParser::token::TOKEN_OP_END) {
            style = KSyntaxHighlighting::Theme::BuiltIn;
        } else
        if (type > SmaliParser::token::TOKEN_SYMBOL_BEGIN
            && type < SmaliParser::token::TOKEN_SYMBOL_END) {
            style = KSyntaxHighlighting::Theme::Operator;
        } else {
            switch (type) {
                case SmaliParser::token::TOKEN_STRING_LITERAL:
                    style = KSyntaxHighlighting::Theme::String;
                    break;
                case SmaliParser::token::TOKEN_CHAR_LITERAL:
                    style = KSyntaxHighlighting::Theme::Char;
                    break;
                case SmaliParser::token::TOKEN_SIMPLE_NAME:
                    style = KSyntaxHighlighting::Theme::VerbatimString;
                    break;
                case SmaliParser::token::TOKEN_MEMBER_NAME:
                    style = KSyntaxHighlighting::Theme::Variable;
                    break;
                case SmaliParser::token::TOKEN_LINE_COMMENT:
                    style = KSyntaxHighlighting::Theme::Comment;
                    break;
                case SmaliParser::token::TOKEN_CLASS_DESCRIPTOR:
                case SmaliParser::token::TOKEN_PRIMITIVE_TYPE:
                case SmaliParser::token::TOKEN_ARRAY_TYPE_PREFIX:
                case SmaliParser::token::TOKEN_VOID_TYPE:
                case SmaliParser::token::TOKEN_PARAM_LIST_OR_ID_PRIMITIVE_TYPE:
                    style = KSyntaxHighlighting::Theme::Import;
                    break;
                case SmaliParser::token::TOKEN_FLAG:
                    style = KSyntaxHighlighting::Theme::RegionMarker;
                    break;
                case SmaliParser::token::TOKEN_REGISTER:
                    style = KSyntaxHighlighting::Theme::SpecialChar;
                    break;
                case SmaliParser::token::TOKEN_NEGATIVE_INTEGER_LITERAL:
                case SmaliParser::token::TOKEN_POSITIVE_INTEGER_LITERAL:
                case SmaliParser::token::TOKEN_LONG_LITERAL:
                case SmaliParser::token::TOKEN_SHORT_LITERAL:
                case SmaliParser::token::TOKEN_BYTE_LITERAL:
                    style = KSyntaxHighlighting::Theme::DecVal;
                    break;
                case SmaliParser::token::TOKEN_FLOAT_LITERAL_OR_ID:
                case SmaliParser::token::TOKEN_DOUBLE_LITERAL_OR_ID:
                case SmaliParser::token::TOKEN_FLOAT_LITERAL:
                case SmaliParser::token::TOKEN_DOUBLE_LITERAL:
                    style = KSyntaxHighlighting::Theme::Float;
                    break;
                default:
                    style = KSyntaxHighlighting::Theme::Error;
                    break;
            }
        }
        setFormat (lexer.column () - 1, lexer.curTokenLen (), mFormatMap[style]);
    }
}

void SmaliHighlight::setTheme(const KSyntaxHighlighting::Theme &theme)
{
    m_theme = theme;

    // TODO generate and store map in Theme?
    mFormatMap.clear();
    for(int i = KSyntaxHighlighting::Theme::Normal;
            i < KSyntaxHighlighting::Theme::Others; i ++) {
        auto style = (KSyntaxHighlighting::Theme::TextStyle) i;

        QTextCharFormat format;
        auto foreground = m_theme.textColor(style);
        if(foreground != 0) {
            format.setForeground(QBrush(foreground));
        }
        auto background = m_theme.backgroundColor(style);
        if(background != 0) {
            format.setBackground(QBrush(background));
        }

        QFont font;
        font.setBold(m_theme.isBold(style));
        font.setItalic(m_theme.isItalic(style));
        font.setUnderline(m_theme.isUnderline(style));
        font.setStrikeOut(m_theme.isStrikeThrough(style));
        format.setFont(font);

        mFormatMap[style] = format;
    }
}


