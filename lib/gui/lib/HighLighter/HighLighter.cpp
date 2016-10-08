//===- HighLighter.cpp - ART-GUI HighLighter--------------------*- C++ -*-===//
//
//                     ANDROID REVERSE TOOLKIT
//
// This file is distributed under the GNU GENERAL PUBLIC LICENSE
// V3 License. See LICENSE.TXT for details.
//
//===---------------------------------------------------------------------===//

#include "HighLighter/HighLighter.h"
#include "SmaliHighlight.h"
#include "GeneralHighlight.h"
QSyntaxHighlighter *setHighLighter (QTextDocument *parent,QString fileName)
{
    if(fileName.endsWith (".smali")) {
        return new SmaliHighlight(parent, fileName);
    } else {
        return new GeneralHighlight(parent, fileName);
    }
}
