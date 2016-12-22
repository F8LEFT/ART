//===- SmaliLexer.g4 - ART-LEX -------------------------------*- ANTLR4 -*-===//
//
//                     ANDROID REVERSE TOOLKIT
//
// This file is distributed under the GNU GENERAL PUBLIC LICENSE
// V3 License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file define Smali Lexer with ANTLR4.
//
//===----------------------------------------------------------------------===//

lexer grammar SmaliLexer;

// These are all supported lexer sections:

// Lexer file header. Appears at the top of h + cpp files. Use e.g. for copyrights.
@lexer::header {/* lexer header section */
}

// Appears before any #include in h + cpp files.
@lexer::preinclude {/* lexer precinclude section */
}

// Follows directly after the standard #includes in h + cpp files.
@lexer::postinclude {/* lexer postinclude section */
    #include <string>
    #include "InvalidToken.h"
    #include <QString>
}

// Directly preceds the lexer class declaration in the h file (e.g. for additional types etc.).
@lexer::context {/* lexer context section */}

// Appears in the public part of the lexer in the h file.
@lexer::members {/* public lexer declarations section */
    void resumeInput(size_t size) {
        auto inputs = getInputStream();
        inputs->seek(inputs->index() - size);
    }

    antlr4::CommonToken invalidToken(std::string message) {
        return invalidToken(message, getText());
    }

    antlr4::CommonToken* invalidToken(std::string message, std::string text) {
        InvalidToken* token = new InvalidToken(message, text);

        token->setStartIndex(getCharIndex());
        token->setStopIndex(*(text.end()-1));
        token->setLine(getLine());
        token->setCharPositionInLine(getCharPositionInLine());

        return token;
    }

    void beginStringOrChar() {
        sb.clear();
        stringStartLine = getLine();
        stringStartCol = getCharPositionInLine();
        stringStartChar = getCharIndex();
        m_stringOrcharError.clear();
    }

    std::unique_ptr<antlr4::Token> endStringOrChar(size_t type) {
        if(!m_stringOrcharError.empty()) {
            return invalidStringOrChar(m_stringOrcharError);
        }
        auto text = getText();
        std::unique_ptr<antlr4::Token> token(new antlr4::CommonToken(type, sb.toStdString()));
        auto ptr = (antlr4::CommonToken*)token.get();
        ptr->setStartIndex(stringStartChar);
        ptr->setStopIndex(*(text.end()-1));
        ptr->setLine(stringStartLine);
        ptr->setCharPositionInLine(stringStartCol);
        return token;
    }

    void setStringOrCharError(std::string message) {
        if(m_stringOrcharError.empty()) {
            m_stringOrcharError = message;
        }
    }

    std::unique_ptr<antlr4::Token> invalidStringOrChar(std::string message) {
        auto text = getText();
        std::unique_ptr<antlr4::Token> token(new InvalidToken(message, sb.toStdString()));

        auto ptr = (InvalidToken*)token.get();
        ptr->setStartIndex(stringStartChar);
        ptr->setStopIndex(*(text.end()-1));
        ptr->setLine(stringStartLine);
        ptr->setCharPositionInLine(stringStartCol);
        return token;
    }

    QString decodeUtf16(QString utf) {
        if(utf.length() != 6) {
            return "";
        }
        QString u = utf.mid(2, 4);
        ushort data = u.toUShort(nullptr, 16);
        return QString().setUtf16(&data, 1);
    }

    QString decodeUtf16(std::string utf) {
        return decodeUtf16(QString::fromStdString(utf));
    }

    std::unique_ptr<antlr4::Token> nextToken() override {
        std::unique_ptr<antlr4::Token> token;
        token = Lexer::nextToken();
        switch (mode) {
            case STRING:
                while(mode == STRING) {
                    if(hitEOF) {
                        setStringOrCharError("Unterminated string literal");
                        popMode();
                        break;
                    }
                    token = Lexer::nextToken();
                    //auto ptr = token.get();
                    //std::cout << ptr->getType() << "," << ptr->getCharPositionInLine() << std::endl;
                }
                token = endStringOrChar(STRING_LITERAL);
                break;
            case CHAR:
                while(mode == CHAR) {
                    if(hitEOF) {
                        setStringOrCharError("Unterminated character literal");
                        popMode();
                        break;
                    }
                    token = Lexer::nextToken();
                }
                token = endStringOrChar(CHAR_LITERAL);
                break;
            case TYPE_LIST_MODE:
                if(hitEOF) {
                    popMode();
                }
                break;
            default:
                break;
        }
        return token;
    }
}

// Appears in the private part of the lexer in the h file.
@lexer::declarations {/* private lexer declarations/members section */
    QString sb;
    std::string m_stringOrcharError;
    size_t stringStartLine;
    size_t stringStartCol;
    size_t stringStartChar;
}

// Appears in line with the other class member definitions in the cpp file.
@lexer::definitions {/* lexer definitions section */}

tokens {
    INVALID_TOKEN
}

fragment HexPrefix: '0' [xX];

fragment HexDigit: [0-9a-fA-F];
fragment HexDigits: HexDigit HexDigit HexDigit HexDigit;
fragment FewerHexDigits:
    | HexDigit
    | HexDigit HexDigit
    | HexDigit HexDigit HexDigit;

fragment Integer1: '0';
fragment Integer2: [1-9] [0-9]*;
fragment Integer3: '0' [0-7]+;
fragment Integer4: HexPrefix HexDigit+;
fragment Integer: Integer1 | Integer2 | Integer3 | Integer4;

fragment DecimalExponent: [eE] '-'? [0-9]+;

fragment BinaryExponent: [pP] '-'? [0-9]+;

/*This can either be a floating point number or an identifier*/
fragment FloatOrID1: '-'? [0-9]+ DecimalExponent;
fragment FloatOrID2: '-'? HexPrefix HexDigit+ BinaryExponent;
fragment FloatOrID3: '-'? [iI][nN][fF][iI][nN][iI][tT][yY];
fragment FloatOrID4: [nN][aA][nN];
fragment FloatOrID: FloatOrID1 |FloatOrID2 | FloatOrID3 | FloatOrID4;


/*This can only be a float and not an identifier, due to the decimal point*/
fragment Float1: '-'? [0-9]+ '.' [0-9]* DecimalExponent?;
fragment Float2: '-'? '.' [0-9]+ DecimalExponent?;
fragment Float3: '-'? HexPrefix HexDigit+ '.' HexDigit* BinaryExponent;
fragment Float4: '-'? HexPrefix '.' HexDigit+ BinaryExponent;
fragment Float:  Float1 | Float2 | Float3 | Float4;

fragment HighSurrogate: [\ud800-\udbff];

fragment LowSurrogate: [\udc00-\udfff];

fragment SimpleNameCharacter: (HighSurrogate LowSurrogate) | [$A-Za-z0-9\u00a1-\u1fff\u2010-\u2027\u2030-\ud7ff\ue000-\uffef_-];

fragment SimpleName: SimpleNameCharacter+;

fragment PrimitiveType: [ZBSCIJFD];

fragment ClassDescriptor: 'L' (SimpleName '/')* SimpleName ';' ;

fragment ArrayPrefix: '['+;

fragment Type: PrimitiveType | ClassDescriptor | ArrayPrefix (ClassDescriptor | PrimitiveType);


// ----------------------- define default mode action ---------------
/*Directives*/
CLASS_DIRECTIVE: '.class';
SUPER_DIRECTIVE: '.super';
IMPLEMENTS_DIRECTIVE: '.implements';
SOURCE_DIRECTIVE: '.source';
FIELD_DIRECTIVE: '.field';
END_FIELD_DIRECTIVE: '.end field';
SUBANNOTATION_DIRECTIVE: '.subannotation';
END_SUBANNOTATION_DIRECTIVE: '.end subannotation';
ANNOTATION_DIRECTIVE: '.annotation';
END_ANNOTATION_DIRECTIVE: '.end annotation';
ENUM_DIRECTIVE: '.enum';
METHOD_DIRECTIVE: '.method';
END_METHOD_DIRECTIVE: '.end method';
REGISTERS_DIRECTIVE: '.registers';
LOCALS_DIRECTIVE: '.locals';
ARRAY_DATA_DIRECTIVE: '.array-data';
END_ARRAY_DATA_DIRECTIVE: '.end array-data';
PACKED_SWITCH_DIRECTIVE: '.packed-switch';
END_PACKED_SWITCH_DIRECTIVE: '.end packed-switch';
SPARSE_SWITCH_DIRECTIVE: '.sparse-switch';
END_SPARSE_SWITCH_DIRECTIVE: '.end sparse-switch';
CATCH_DIRECTIVE: '.catch';
CATCHALL_DIRECTIVE: '.catchall';
LINE_DIRECTIVE: '.line';
PARAMETER_DIRECTIVE: '.param';
END_PARAMETER_DIRECTIVE: '.end param';
LOCAL_DIRECTIVE: '.local';
END_LOCAL_DIRECTIVE: '.end local';
RESTART_LOCAL_DIRECTIVE: '.restart local';
PROLOGUE_DIRECTIVE: '.prologue';
EPILOGUE_DIRECTIVE: '.epilogue';


/*Literals*/
POSITIVE_INTEGER_LITERAL: Integer;
NEGATIVE_INTEGER_LITERAL: '-' Integer;
LONG_LITERAL: '-'? Integer [lL];
SHORT_LITERAL: '-'? Integer [sS];
BYTE_LITERAL: '-'? Integer [tT];

FLOAT_LITERAL_OR_ID: FloatOrID [fF] | '-'? [0-9]+ [fF];
DOUBLE_LITERAL_OR_ID: FloatOrID [dD]? | '-'? [0-9]+ [dD];
FLOAT_LITERAL: Float [fF];
DOUBLE_LITERAL: Float [dD]?;

BOOL_LITERAL: 'true'|'false';
NULL_LITERAL: 'null';

DOUBLE_QUOT: '"' { beginStringOrChar(); sb.append('\"'); } -> more, pushMode(STRING);
SINGLE_QUOT: '\'' { beginStringOrChar(); sb.append('\''); } -> more, pushMode(CHAR);

/*Misc*/
REGISTER: [vp] [0-9]+;

ANNOTATION_VISIBILITY: 'build' | 'runtime' | 'system';

ACCESS_SPEC:
    'public' | 'private' | 'protected' | 'static' | 'final' | 'synchronized' | 'bridge' | 'varargs' | 'native' |
    'abstract' | 'strictfp' | 'synthetic' | 'constructor' | 'declared-synchronized' | 'interface' | 'enum' |
    'annotation' | 'volatile' | 'transient';

VERIFICATION_ERROR_TYPE:
    'no-error' | 'generic-error' | 'no-such-class' | 'no-such-field' | 'no-such-method' | 'illegal-class-access' |
    'illegal-field-access' | 'illegal-method-access' | 'class-change-error' | 'instantiation-error';

INLINE_INDEX: 'inline@0x' HexDigit+ ;
VTABLE_INDEX: 'vtable@0x' HexDigit+ ;
FIELD_OFFSET: 'field@0x' HexDigit+;

LINE_COMMENT: '#' ~[\r\n]*;

/*Instructions*/
INSTRUCTION_FORMAT10t: 'goto';

INSTRUCTION_FORMAT10x: 'return-void' | 'nop' ;

INSTRUCTION_FORMAT10x_ODEX: 'return-void-barrier' | 'return-void-no-barrier';

INSTRUCTION_FORMAT11n: 'const/4';

INSTRUCTION_FORMAT11x:
    'move-result' | 'move-result-wide' | 'move-result-object' | 'move-exception' | 'return' | 'return-wide' |
    'return-object' | 'monitor-enter' | 'monitor-exit' | 'throw' ;

INSTRUCTION_FORMAT12x_OR_ID:
    'move' | 'move-wide' | 'move-object' | 'array-length' | 'neg-int' | 'not-int' | 'neg-long' | 'not-long' |
    'neg-float' | 'neg-double' | 'int-to-long' | 'int-to-float' | 'int-to-double' | 'long-to-int' | 'long-to-float' |
    'long-to-double' | 'float-to-int' | 'float-to-long' | 'float-to-double' | 'double-to-int' | 'double-to-long' |
    'double-to-float' | 'int-to-byte' | 'int-to-char' | 'int-to-short';

INSTRUCTION_FORMAT12x:
    'add-int/2addr' | 'sub-int/2addr' | 'mul-int/2addr' | 'div-int/2addr' | 'rem-int/2addr' | 'and-int/2addr' |
    'or-int/2addr' | 'xor-int/2addr' | 'shl-int/2addr' | 'shr-int/2addr' | 'ushr-int/2addr' | 'add-long/2addr' |
    'sub-long/2addr' | 'mul-long/2addr' | 'div-long/2addr' | 'rem-long/2addr' | 'and-long/2addr' | 'or-long/2addr' |
    'xor-long/2addr' | 'shl-long/2addr' | 'shr-long/2addr' | 'ushr-long/2addr' | 'add-float/2addr' |
    'sub-float/2addr' | 'mul-float/2addr' | 'div-float/2addr' | 'rem-float/2addr' | 'add-double/2addr' |
    'sub-double/2addr' | 'mul-double/2addr' | 'div-double/2addr' | 'rem-double/2addr';

INSTRUCTION_FORMAT20bc: 'throw-verification-error' ;

INSTRUCTION_FORMAT20t: 'goto/16';

INSTRUCTION_FORMAT21c_FIELD:
    'sget' | 'sget-wide' | 'sget-object' | 'sget-boolean' | 'sget-byte' | 'sget-char' | 'sget-short' | 'sput' |
    'sput-wide' | 'sput-object' | 'sput-boolean' | 'sput-byte' | 'sput-char' | 'sput-short';

INSTRUCTION_FORMAT21c_FIELD_ODEX:
    'sget-volatile' | 'sget-wide-volatile' | 'sget-object-volatile' | 'sput-volatile' | 'sput-wide-volatile' |
    'sput-object-volatile';

INSTRUCTION_FORMAT21c_STRING: 'const-string';

INSTRUCTION_FORMAT21c_TYPE:
    'check-cast' | 'new-instance' | 'const-class';

INSTRUCTION_FORMAT21ih: 'const/high16';

INSTRUCTION_FORMAT21lh: 'const-wide/high16';

INSTRUCTION_FORMAT21s: 'const/16' | 'const-wide/16' ;

INSTRUCTION_FORMAT21t:
    'if-eqz' | 'if-nez' | 'if-ltz' | 'if-gez' | 'if-gtz' | 'if-lez';

INSTRUCTION_FORMAT22b:
    'add-int/lit8' | 'rsub-int/lit8' | 'mul-int/lit8' | 'div-int/lit8' | 'rem-int/lit8' | 'and-int/lit8' |
    'or-int/lit8' | 'xor-int/lit8' | 'shl-int/lit8' | 'shr-int/lit8' | 'ushr-int/lit8';

INSTRUCTION_FORMAT22c_FIELD:
    'iget' | 'iget-wide' | 'iget-object' | 'iget-boolean' | 'iget-byte' | 'iget-char' | 'iget-short' | 'iput' |
    'iput-wide' | 'iput-object' | 'iput-boolean' | 'iput-byte' | 'iput-char' | 'iput-short';

INSTRUCTION_FORMAT22c_FIELD_ODEX:
    'iget-volatile' | 'iget-wide-volatile' | 'iget-object-volatile' | 'iput-volatile' | 'iput-wide-volatile' |
    'iput-object-volatile';

INSTRUCTION_FORMAT22c_TYPE: 'instance-of' | 'new-array' ;

INSTRUCTION_FORMAT22cs_FIELD:
    'iget-quick' | 'iget-wide-quick' | 'iget-object-quick' | 'iput-quick' | 'iput-wide-quick' | 'iput-object-quick' |
    'iput-boolean-quick' | 'iput-byte-quick' | 'iput-char-quick' | 'iput-short-quick';

INSTRUCTION_FORMAT22s_OR_ID: 'rsub-int';

INSTRUCTION_FORMAT22s:
    'add-int/lit16' | 'mul-int/lit16' | 'div-int/lit16' | 'rem-int/lit16' | 'and-int/lit16' | 'or-int/lit16' |
    'xor-int/lit16' ;

INSTRUCTION_FORMAT22t:
    'if-eq' | 'if-ne' | 'if-lt' | 'if-ge' | 'if-gt' | 'if-le';

INSTRUCTION_FORMAT22x:
    'move/from16' | 'move-wide/from16' | 'move-object/from16';

INSTRUCTION_FORMAT23x:
    'cmpl-float' | 'cmpg-float' | 'cmpl-double' | 'cmpg-double' | 'cmp-long' | 'aget' | 'aget-wide' | 'aget-object' |
    'aget-boolean' | 'aget-byte' | 'aget-char' | 'aget-short' | 'aput' | 'aput-wide' | 'aput-object' | 'aput-boolean' |
    'aput-byte' | 'aput-char' | 'aput-short' | 'add-int' | 'sub-int' | 'mul-int' | 'div-int' | 'rem-int' | 'and-int' |
    'or-int' | 'xor-int' | 'shl-int' | 'shr-int' | 'ushr-int' | 'add-long' | 'sub-long' | 'mul-long' | 'div-long' |
    'rem-long' | 'and-long' | 'or-long' | 'xor-long' | 'shl-long' | 'shr-long' | 'ushr-long' | 'add-float' |
    'sub-float' | 'mul-float' | 'div-float' | 'rem-float' | 'add-double' | 'sub-double' | 'mul-double' | 'div-double' |
    'rem-double';

INSTRUCTION_FORMAT30t: 'goto/32';

INSTRUCTION_FORMAT31c: 'const-string/jumbo';

INSTRUCTION_FORMAT31i_OR_ID: 'const';

INSTRUCTION_FORMAT31i: 'const-wide/32';

INSTRUCTION_FORMAT31t: 'fill-array-data' | 'packed-switch' | 'sparse-switch';

INSTRUCTION_FORMAT32x: 'move/16' | 'move-wide/16' | 'move-object/16';

INSTRUCTION_FORMAT35c_METHOD:
    'invoke-virtual' | 'invoke-super' | 'invoke-direct' | 'invoke-static' | 'invoke-interface' ;

INSTRUCTION_FORMAT35c_METHOD_ODEX: 'invoke-direct-empty';

INSTRUCTION_FORMAT35c_TYPE: 'filled-new-array';

INSTRUCTION_FORMAT35mi_METHOD: 'execute-inline';

INSTRUCTION_FORMAT35ms_METHOD: 'invoke-virtual-quick' | 'invoke-super-quick';

INSTRUCTION_FORMAT3rc_METHOD:
    'invoke-virtual/range' | 'invoke-super/range' | 'invoke-direct/range' | 'invoke-static/range' |
    'invoke-interface/range';

INSTRUCTION_FORMAT3rc_METHOD_ODEX: 'invoke-object-init/range';

INSTRUCTION_FORMAT3rc_TYPE: 'filled-new-array/range';

INSTRUCTION_FORMAT3rmi_METHOD: 'execute-inline/range';

INSTRUCTION_FORMAT3rms_METHOD:
    'invoke-virtual-quick/range' | 'invoke-super-quick/range';

INSTRUCTION_FORMAT45cc_METHOD: 'invoke-polymorphic';

INSTRUCTION_FORMAT4rcc_METHOD: 'invoke-polymorphic/range';

INSTRUCTION_FORMAT51l: 'const-wide';

/*Types*/
VOID_TYPE: 'V';
//    {PrimitiveType} { return newToken(PRIMITIVE_TYPE); }
//    {ClassDescriptor} { return newToken(CLASS_DESCRIPTOR); }

// we have to drop into a separate state so that we don't parse something like
// "[I->" as "[" followed by "I-" as a SIMPLE_NAME
//    {ArrayPrefix} {
//      yybegin(ARRAY_DESCRIPTOR);
//      return newToken(ARRAY_TYPE_PREFIX);
//    }

//    {PrimitiveType} {PrimitiveType}+ {
//        // go back and re-lex it as a PARAM_LIST_OR_ID
//        yypushback(yylength());
//        yybegin(PARAM_LIST_OR_ID);
//    }

TYPE_LIST: Type+ {
        resumeInput(getText().length());
    } -> more, pushMode(TYPE_LIST_MODE);

SIMPLE_NAME: SimpleName;
MEMBER_NAME: '<' SimpleName '>';

/*Symbols/Whitespace/EOF*/
DOTDOT: '..';
ARROW: '->';
EQUAL: '=';
COLON: ':';
COMMA: ',';
OPEN_BRACE: '{';
CLOSE_BRACE: '}';
OPEN_PAREN: '(';
CLOSE_PAREN: ')';
WHITE_SPACE: [\r\n\t ]+ -> skip;
//    <<EOF>> { return newToken(EOF); }

/*catch all*/
INVALID_TOKEN: '.end'
    | '.end ' [a-zA-Z0-9_-]+
    | '.restart'
    | '.restart ' [a-zA-Z0-9_-]+
    | '.'
    | '.' [a-zA-Z_-]
    | '.' [a-zA-Z_-] [a-zA-Z0-9_-]*
    | .;

//<PARAM_LIST_OR_ID> {
//    {PrimitiveType} { return newToken(PARAM_LIST_OR_ID_PRIMITIVE_TYPE); }
//    [^] { yypushback(1); yybegin(YYINITIAL); }
//    <<EOF>> { yybegin(YYINITIAL); }
//}

//<PARAM_LIST> {
//    {PrimitiveType} { return newToken(PRIMITIVE_TYPE); }
//    {ClassDescriptor} { return newToken(CLASS_DESCRIPTOR); }
//    {ArrayPrefix} { return newToken(ARRAY_TYPE_PREFIX); }
//    [^] { yypushback(1); yybegin(YYINITIAL);}
//    <<EOF>> { yybegin(YYINITIAL);}
//}

// ----------------- About how to parse a string --------------------
mode STRING;
STRING_LITERAL: '"' { sb.append('\"'); } -> popMode;    // end STRING mode and return token
STRING_DATA: ~[\r\n"\\]+ { sb.append(QString::fromStdString(getText())); } -> more;
STRING_ESCAPE
    :  '\\b' { sb.append('\b'); }
    |  '\\t' { sb.append('\t'); }
    |  '\\n' { sb.append('\n'); }
    |  '\\f' { sb.append('\f'); }
    |  '\\r' { sb.append('\r'); }
    |  '\\\'' { sb.append('\''); }
    |  '\\"' { sb.append('\"'); }
    |  '\\\\' { sb.append('\\'); };
STRING_ESCAPEERROR: '\\' ~[btnfr\'"\\u] {        // no match ESCAPE
        sb.append(QString::fromStdString(getText()));
        setStringOrCharError(std::string("Invalid escape sequence ") + getText());
    } -> popMode;
STRING_UTFENCODE
    : '\\u' HexDigits { sb.append(decodeUtf16(getText())); } -> more;
STRING_UTFERROR: '\\u' FewerHexDigits {
        sb.append(QString::fromStdString(getText()));
        setStringOrCharError("Invalid \\u sequence. \\u must be followed by 4 hex digits");
    } -> popMode;
STRING_END: [\r\n] { setStringOrCharError("Unterminated string literal"); } -> popMode;
STRING_FILEEND: EOF { setStringOrCharError("Unterminated string literal"); } -> popMode;

// ----------------- About how to parse a Char --------------------
mode CHAR;
CHAR_LITERAL: '\'' { sb.append('\'');
       if(sb.length() == 2) {
           setStringOrCharError("Empty character literal");
       } else if(sb.length() > 3) {
           setStringOrCharError("Character literal with multiple chars");
       }
   } -> popMode;
CHAR_DATA: ~[\r\n'\\]+ { sb.append(QString::fromStdString(getText())); } -> more;
CHAR_ESCAPE
    :  '\\b' { sb.append('\b'); }
    |  '\\t' { sb.append('\t'); }
    |  '\\n' { sb.append('\n'); }
    |  '\\f' { sb.append('\f'); }
    |  '\\r' { sb.append('\r'); }
    |  '\\\'' { sb.append('\''); }
    |  '\\"' { sb.append('\"'); }
    |  '\\\\' { sb.append('\\'); };
CHAR_ESCAPEERROR: '\\' ~[btnfr\'"\\u] {       // no match ESCAPE
        sb.append(QString::fromStdString(getText()));
        setStringOrCharError(std::string("Invalid escape sequence ") + getText());
    } -> popMode;
CHAR_UTFENCODE: '\\u' HexDigits { sb.append(decodeUtf16(getText())); } -> more;
CHAR_UTFERROR: '\\u' FewerHexDigits {
        sb.append(QString::fromStdString(getText()));
        setStringOrCharError("Invalid \\u sequence. \\u must be followed by 4 hex digits");
    } -> popMode;
CHAR_END: [\r\n] { setStringOrCharError("Unterminated character literal"); } -> popMode;
CHAR_FILEEND: EOF { setStringOrCharError("Unterminated character literal"); } -> popMode;

// ----------------- About how to parse ARRAY --------------------
// TODO How to parse array? PRIMITIVE_TYPE is defined before
//mode ARRAY_DESCRIPTOR;
//PRIMITIVE_TYPE: PrimitiveType -> popMode;
//CLASS_DESCRIPTOR: ClassDescriptor -> popMode;
//ARRAY_DESCRIPTOR_END: . {auto inputs = getInputStream();
//    inputs->seek(inputs->index()-1); }-> popMode;
//ARRAY_DESCRIPTOR_FILEEND: EOF -> popMode;
// ---------------- About how to parse TYPE ---------------------
mode TYPE_LIST_MODE;
PRIMITIVE_TYPE: PrimitiveType;
CLASS_DESCRIPTOR: ClassDescriptor;
ARRAY_TYPE_PREFIX: ArrayPrefix;
TYPE_LIST_END: . {
        resumeInput(1);
    }-> more, popMode;
TYPE_LIST_EOF: EOF -> popMode;
