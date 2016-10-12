//===- RegisterX.h - ART-LEX -----------------------------------*- c++ -*-===//
//
//                     ANDROID REVERSE TOOLKIT
//
// This file is distributed under the GNU GENERAL PUBLIC LICENSE
// V3 License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// RegisterX to save register number
//
//===----------------------------------------------------------------------===//


#ifndef SMALIPARSER_REGISTERX_H
#define SMALIPARSER_REGISTERX_H

#include <string>
#include <utils/formater.hpp>

// smali register vx px
namespace Analysis {
    struct RegisterX {
        short i;
        bool isP;

        RegisterX(int x) {
            if (x & 0x0100) {
                isP = true;
            } else isP = false;
            i = x & 0xff;
        }

        std::string toString() {
            std::string rel;
            if (isP) {
                rel = 'p';
            } else {
                rel = 'v';
            }
            rel += formater::int2decStr (i);
            return move(rel);
        }
    };
}

#endif //SMALIPARSER_REGISTERX_H
