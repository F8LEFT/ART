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
            config = HighLightConfig::instance (
                    HighLightConfig::SMALI,
                    GetCfgsPath ("smaliTheme/" +
                                  ConfigString("Highlight", "SmaliHighlight")));
        }
        return new SmaliHighlight(parent, fileName, config);
    } else {
        auto hl = GeneralHighlight::getAvaliableHl (fileName);
        if(hl == nullptr)
            return nullptr;
        if(config == nullptr) {
            config = HighLightConfig::instance (
                    HighLightConfig::GENERAL,
                    GetCfgsPath ("genHlTheme/" +
                                 ConfigString("Highlight", "GenHighlight")));
        }
        return new GeneralHighlight(parent, hl, config);
    }
}
