//===- SmaliHighlight.cpp - ART-GUI HighLighter------------------*- C++ -*-===//
//
//                     ANDROID REVERSE TOOLKIT
//
// This file is distributed under the GNU GENERAL PUBLIC LICENSE
// V3 License. See LICENSE.TXT for details.
//
//===---------------------------------------------------------------------===//
#include "SmaliLexer.h"


#include "SmaliHighlight.h"

#include <sstream>
#include <QTextDocument>
#include <QDebug>
#include <Config/Config.h>
#include <utils/StringUtil.h>
#include <utils/Configuration.h>


SmaliHighlight::SmaliHighlight (QTextDocument *parent)
        : QSyntaxHighlighter(parent)
{
}

SmaliHighlight::~SmaliHighlight()
{

}


void SmaliHighlight::highlightBlock (const QString &text)
{
    antlr4::ANTLRInputStream input(text.toStdString());
    SmaliLexer lexer(&input);
    antlr4::CommonTokenStream tokens(&lexer);

    tokens.fill();
    for (auto token : tokens.getTokens()) {
        KSyntaxHighlighting::Theme::TextStyle  style;
        switch(token->getType()) {
            case SmaliLexer::CLASS_DIRECTIVE :
            case SmaliLexer::SUPER_DIRECTIVE :
            case SmaliLexer::IMPLEMENTS_DIRECTIVE :
            case SmaliLexer::SOURCE_DIRECTIVE :
            case SmaliLexer::FIELD_DIRECTIVE :
            case SmaliLexer::END_FIELD_DIRECTIVE :
            case SmaliLexer::SUBANNOTATION_DIRECTIVE :
            case SmaliLexer::END_SUBANNOTATION_DIRECTIVE :
            case SmaliLexer::ANNOTATION_DIRECTIVE :
            case SmaliLexer::END_ANNOTATION_DIRECTIVE :
            case SmaliLexer::ENUM_DIRECTIVE :
            case SmaliLexer::METHOD_DIRECTIVE :
            case SmaliLexer::END_METHOD_DIRECTIVE :
            case SmaliLexer::REGISTERS_DIRECTIVE :
            case SmaliLexer::LOCALS_DIRECTIVE :
            case SmaliLexer::ARRAY_DATA_DIRECTIVE :
            case SmaliLexer::END_ARRAY_DATA_DIRECTIVE :
            case SmaliLexer::PACKED_SWITCH_DIRECTIVE :
            case SmaliLexer::END_PACKED_SWITCH_DIRECTIVE :
            case SmaliLexer::SPARSE_SWITCH_DIRECTIVE :
            case SmaliLexer::END_SPARSE_SWITCH_DIRECTIVE :
            case SmaliLexer::CATCH_DIRECTIVE :
            case SmaliLexer::CATCHALL_DIRECTIVE :
            case SmaliLexer::LINE_DIRECTIVE :
            case SmaliLexer::PARAMETER_DIRECTIVE :
            case SmaliLexer::END_PARAMETER_DIRECTIVE :
            case SmaliLexer::LOCAL_DIRECTIVE :
            case SmaliLexer::END_LOCAL_DIRECTIVE :
            case SmaliLexer::RESTART_LOCAL_DIRECTIVE :
            case SmaliLexer::PROLOGUE_DIRECTIVE :
            case SmaliLexer::EPILOGUE_DIRECTIVE :
                style = KSyntaxHighlighting::Theme::Keyword;
                break;
            case SmaliLexer::POSITIVE_INTEGER_LITERAL :
            case SmaliLexer::NEGATIVE_INTEGER_LITERAL :
            case SmaliLexer::LONG_LITERAL :
            case SmaliLexer::SHORT_LITERAL :
            case SmaliLexer::BYTE_LITERAL :
                style = KSyntaxHighlighting::Theme::BaseN;
                break;
            case SmaliLexer::FLOAT_LITERAL_OR_ID :
            case SmaliLexer::DOUBLE_LITERAL_OR_ID :
            case SmaliLexer::FLOAT_LITERAL :
            case SmaliLexer::DOUBLE_LITERAL :
                style = KSyntaxHighlighting::Theme::Float;
                break;
            case SmaliLexer::BOOL_LITERAL :
            case SmaliLexer::NULL_LITERAL :
                style = KSyntaxHighlighting::Theme::DecVal;
                break;
            case SmaliLexer::REGISTER :
                style = KSyntaxHighlighting::Theme::Variable;
                break;
            case SmaliLexer::ANNOTATION_VISIBILITY :
                style = KSyntaxHighlighting::Theme::Annotation;
                break;
            case SmaliLexer::ACCESS_SPEC :
            case SmaliLexer::INLINE_INDEX :
            case SmaliLexer::VTABLE_INDEX :
            case SmaliLexer::FIELD_INDEX :
                style = KSyntaxHighlighting::Theme::Variable;
                break;
            case SmaliLexer::LINE_COMMENT :
                style = KSyntaxHighlighting::Theme::Comment;
                break;
            case SmaliLexer::INSTRUCTION_FORMAT10t :
            case SmaliLexer::INSTRUCTION_FORMAT10x :
            case SmaliLexer::INSTRUCTION_FORMAT10x_ODEX :
            case SmaliLexer::INSTRUCTION_FORMAT11n :
            case SmaliLexer::INSTRUCTION_FORMAT11x :
            case SmaliLexer::INSTRUCTION_FORMAT12x_OR_ID :
            case SmaliLexer::INSTRUCTION_FORMAT12x :
            case SmaliLexer::INSTRUCTION_FORMAT20bc :
            case SmaliLexer::INSTRUCTION_FORMAT20t :
            case SmaliLexer::INSTRUCTION_FORMAT21c_FIELD :
            case SmaliLexer::INSTRUCTION_FORMAT21c_FIELD_ODEX :
            case SmaliLexer::INSTRUCTION_FORMAT21c_STRING :
            case SmaliLexer::INSTRUCTION_FORMAT21c_TYPE :
            case SmaliLexer::INSTRUCTION_FORMAT21ih :
            case SmaliLexer::INSTRUCTION_FORMAT21lh :
            case SmaliLexer::INSTRUCTION_FORMAT21s :
            case SmaliLexer::INSTRUCTION_FORMAT21t :
            case SmaliLexer::INSTRUCTION_FORMAT22b :
            case SmaliLexer::INSTRUCTION_FORMAT22c_FIELD :
            case SmaliLexer::INSTRUCTION_FORMAT22c_FIELD_ODEX :
            case SmaliLexer::INSTRUCTION_FORMAT22c_TYPE :
            case SmaliLexer::INSTRUCTION_FORMAT22cs_FIELD :
            case SmaliLexer::INSTRUCTION_FORMAT22s_OR_ID :
            case SmaliLexer::INSTRUCTION_FORMAT22s :
            case SmaliLexer::INSTRUCTION_FORMAT22t :
            case SmaliLexer::INSTRUCTION_FORMAT22x :
            case SmaliLexer::INSTRUCTION_FORMAT23x :
            case SmaliLexer::INSTRUCTION_FORMAT30t :
            case SmaliLexer::INSTRUCTION_FORMAT31c :
            case SmaliLexer::INSTRUCTION_FORMAT31i_OR_ID :
            case SmaliLexer::INSTRUCTION_FORMAT31i :
            case SmaliLexer::INSTRUCTION_FORMAT31t :
            case SmaliLexer::INSTRUCTION_FORMAT32x :
            case SmaliLexer::INSTRUCTION_FORMAT35c_METHOD :
            case SmaliLexer::INSTRUCTION_FORMAT35c_METHOD_ODEX :
            case SmaliLexer::INSTRUCTION_FORMAT35c_TYPE :
            case SmaliLexer::INSTRUCTION_FORMAT35mi_METHOD :
            case SmaliLexer::INSTRUCTION_FORMAT35ms_METHOD :
            case SmaliLexer::INSTRUCTION_FORMAT3rc_METHOD :
            case SmaliLexer::INSTRUCTION_FORMAT3rc_METHOD_ODEX :
            case SmaliLexer::INSTRUCTION_FORMAT3rc_TYPE :
            case SmaliLexer::INSTRUCTION_FORMAT3rmi_METHOD :
            case SmaliLexer::INSTRUCTION_FORMAT3rms_METHOD :
            case SmaliLexer::INSTRUCTION_FORMAT45cc_METHOD :
            case SmaliLexer::INSTRUCTION_FORMAT4rcc_METHOD :
            case SmaliLexer::INSTRUCTION_FORMAT51l :
                style = KSyntaxHighlighting::Theme::BuiltIn;
                break;
            case SmaliLexer::SIMPLE_NAME :
            case SmaliLexer::MEMBER_NAME :
                style = KSyntaxHighlighting::Theme::Function;
                break;
            case SmaliLexer::DOTDOT :
            case SmaliLexer::ARROW :
            case SmaliLexer::EQUAL :
            case SmaliLexer::COLON :
            case SmaliLexer::COMMA :
            case SmaliLexer::OPEN_BRACE :
            case SmaliLexer::CLOSE_BRACE :
            case SmaliLexer::OPEN_PAREN :
            case SmaliLexer::CLOSE_PAREN :
                style = KSyntaxHighlighting::Theme::Operator;
                break;
            case SmaliLexer::STRING_LITERAL :
            case SmaliLexer::STRING_ESCAPE :
            case SmaliLexer::STRING_ESCAPEERROR :
            case SmaliLexer::STRING_UTFERROR :
            case SmaliLexer::STRING_END :
            case SmaliLexer::STRING_FILEEND :
                style = KSyntaxHighlighting::Theme::String;
                break;
            case SmaliLexer::CHAR_LITERAL :
            case SmaliLexer::CHAR_ESCAPE :
            case SmaliLexer::CHAR_ESCAPEERROR :
            case SmaliLexer::CHAR_UTFERROR :
            case SmaliLexer::CHAR_END :
            case SmaliLexer::CHAR_FILEEND :
                style = KSyntaxHighlighting::Theme::Char;
                break;
            case SmaliLexer::PRIMITIVE_TYPE :
            case SmaliLexer::VOID_TYPE :
                style = KSyntaxHighlighting::Theme::Constant;
                break;
            case SmaliLexer::CLASS_DESCRIPTOR :
                style = KSyntaxHighlighting::Theme::DataType;
                break;
            case SmaliLexer::ARRAY_TYPE_PREFIX :
                style = KSyntaxHighlighting::Theme::SpecialString;
                break;
            case SmaliLexer::TYPE_LIST_EOF :
            case SmaliLexer::INVALID_TOKEN :
            case SmaliLexer::VERIFICATION_ERROR_TYPE :
            default:
                style = KSyntaxHighlighting::Theme::Error;
                break;

        }
        setFormat (token->getStartIndex(), token->getStopIndex() - token->getStartIndex() + 1, mFormatMap[style]);
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


