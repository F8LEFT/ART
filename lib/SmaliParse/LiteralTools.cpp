//===- LiteralTools.cpp - ART-LEX -------------------------------*- cpp -*-===//
//
//                     ANDROID REVERSE TOOLKIT
//
// This file is distributed under the GNU GENERAL PUBLIC LICENSE
// V3 License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

#include "LiteralTools.h"
#include <QString>

int LiteralTools::parseInt(std::string intLiteral) {
    QString literal = QString::fromStdString(intLiteral);
    if(literal.isEmpty()) {
        return 0;
    }
    QByteArray intChars = literal.toLatin1();
    int position = 0;
    int radix = 10;
//    bool negative = false;
    if (intChars[position] == '-') {
        position++;
//        negative = true;
    }

    if (intChars[position] == '0') {
        position++;
        if (position == intChars.length()) {
            return 0;
        } else if (intChars[position] == 'x' || intChars[position] == 'X') {
            radix = 16;
            position++;
        } else  {
            radix = 8;
        }
    }
    int result = intChars.toInt(nullptr, radix);
    return result;
}
