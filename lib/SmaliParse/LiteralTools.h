//===- LiteralTools.h - ART-LEX ---------------------------------*- cpp -*-===//
//
//                     ANDROID REVERSE TOOLKIT
//
// This file is distributed under the GNU GENERAL PUBLIC LICENSE
// V3 License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file define convert string and int
//
//===----------------------------------------------------------------------===//


#ifndef ANDROIDREVERSETOOLKIT_LITERALTOOLS_H
#define ANDROIDREVERSETOOLKIT_LITERALTOOLS_H

#include "string"

class LiteralTools {
public:
    static int parseInt(std::string intLiteral);
};


#endif //ANDROIDREVERSETOOLKIT_LITERALTOOLS_H
