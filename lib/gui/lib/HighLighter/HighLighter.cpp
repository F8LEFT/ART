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
#include <utils/StringUtil.h>
#include <utils/Configuration.h>
QSyntaxHighlighter *setHighLighter (QTextDocument *parent,QString fileName,
                                    HighLightConfig* config)
{
    if(fileName.endsWith (".smali")) {
        if(config == nullptr) {
            config = HighLightConfig::instance (GetCfgsPath ("smaliTheme/" +
                                  ConfigString("FileEdit", "SmaliHighlight")));
        }
        return new SmaliHighlight(parent, fileName, config);
    } else {
        return new GeneralHighlight(parent, fileName);
    }
}
