//===- InvalidToken.cpp - ART-LEX ----------------------------*- ANTLR4 -*-===//
//
//                     ANDROID REVERSE TOOLKIT
//
// This file is distributed under the GNU GENERAL PUBLIC LICENSE
// V3 License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
#include "SmaliLexer.h"
#include "InvalidToken.h"

InvalidToken::InvalidToken(std::string message)
        : CommonToken((size_t)SmaliLexer::INVALID_TOKEN){
    message = message;
//    channel = SmaliLexer::ERROR_CHANNEL;
}

InvalidToken::InvalidToken(std::string message, std::string text)
        : CommonToken(SmaliLexer::INVALID_TOKEN, text) {
    message = message;
//    channel = smaliParser.ERROR_CHANNEL;
}

std::string InvalidToken::getMessage() {
    return message;
}
