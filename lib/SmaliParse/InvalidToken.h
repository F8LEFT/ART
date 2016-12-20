//===- InvalidToken.h - ART-LEX ---------------------------------*- cpp -*-===//
//
//                     ANDROID REVERSE TOOLKIT
//
// This file is distributed under the GNU GENERAL PUBLIC LICENSE
// V3 License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file define InvalidToken to output invalid message
//
//===----------------------------------------------------------------------===//


#ifndef ANDROIDREVERSETOOLKIT_INVALIDTOKEN_H
#define ANDROIDREVERSETOOLKIT_INVALIDTOKEN_H

#include "antlr4-runtime.h"


class InvalidToken: public antlr4::CommonToken {

public:
    InvalidToken(std::string message);

    InvalidToken(std::string message, std::string text);

    std::string getMessage();

private:
    std::string message;
};

#endif //ANDROIDREVERSETOOLKIT_INVALIDTOKEN_H
