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
//    SmaliLexer lexer;
//    auto str = text.toStdString ();
//    std::istringstream is(str);
//    lexer.switch_streams (&is,nullptr);
//    while(true)
//    {
//        auto token = lexer.get_next_token ();
//        auto type = token.token ();
//        if (type == SmaliParser::token::TOKEN_END)
//            break;
//        if (type == SmaliParser::token::TOKEN_EOL)
//        {
//            continue;
//        }
//        HighLightConfig::FORMAT format;
//        if(type > SmaliParser::token::TOKEN_KEYWORD_BEGIN
//           && type < SmaliParser::token::TOKEN_KEYWORD_END) {
//            format = HighLightConfig::FKeyword;
//        } else
//        if (type > SmaliParser::token::TOKEN_OP_BEGIN
//            && type < SmaliParser::token::TOKEN_OP_END) {
//            format = HighLightConfig::FOp;
//        } else
//        if (type > SmaliParser::token::TOKEN_SYMBOL_BEGIN
//            && type < SmaliParser::token::TOKEN_SYMBOL_END) {
//            format = HighLightConfig::FSymbol;
//        } else {
//            switch (type) {
//                case SmaliParser::token::TOKEN_STRING_LITERAL:
//                case SmaliParser::token::TOKEN_CHAR_LITERAL:
//                    format = HighLightConfig::FCString;
//                    break;
//                case SmaliParser::token::TOKEN_SIMPLE_NAME:
//                case SmaliParser::token::TOKEN_MEMBER_NAME:
//                    format = HighLightConfig::FNameString;
//                    break;
//                case SmaliParser::token::TOKEN_LINE_COMMENT:
//                    format = HighLightConfig::FComment;
//                    break;
//                case SmaliParser::token::TOKEN_CLASS_DESCRIPTOR:
//                case SmaliParser::token::TOKEN_PRIMITIVE_TYPE:
//                case SmaliParser::token::TOKEN_ARRAY_TYPE_PREFIX:
//                case SmaliParser::token::TOKEN_VOID_TYPE:
//                case SmaliParser::token::TOKEN_PARAM_LIST_OR_ID_PRIMITIVE_TYPE:
//                    format = HighLightConfig::FClassType;
//                    break;
//                case SmaliParser::token::TOKEN_FLAG:
//                    format = HighLightConfig::FFlag;
//                    break;
//                case SmaliParser::token::TOKEN_REGISTER:
//                    format = HighLightConfig::FRegd;
//                    break;
//                case SmaliParser::token::TOKEN_NEGATIVE_INTEGER_LITERAL:
//                case SmaliParser::token::TOKEN_POSITIVE_INTEGER_LITERAL:
//                case SmaliParser::token::TOKEN_LONG_LITERAL:
//                case SmaliParser::token::TOKEN_SHORT_LITERAL:
//                case SmaliParser::token::TOKEN_BYTE_LITERAL:
//                case SmaliParser::token::TOKEN_FLOAT_LITERAL_OR_ID:
//                case SmaliParser::token::TOKEN_DOUBLE_LITERAL_OR_ID:
//                case SmaliParser::token::TOKEN_FLOAT_LITERAL:
//                case SmaliParser::token::TOKEN_DOUBLE_LITERAL:
//                    format = HighLightConfig::FNumber;
//                    break;
//                default:
//                    format = HighLightConfig::FDefault;
//                    break;
//            }
//        }
//        setFormat (lexer.column () - 1, lexer.curTokenLen (), mFormatMap[format]);
//    }
}

void SmaliHighlight::setTheme(const KSyntaxHighlighting::Theme &theme)
{
    m_theme = theme;
}


