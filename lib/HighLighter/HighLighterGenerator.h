//===- HighLighterGenerator.h - ART-GUI HighLighter-------------*- C++ -*-===//
//
//                     ANDROID REVERSE TOOLKIT
//
// This file is distributed under the GNU GENERAL PUBLIC LICENSE
// V3 License. See LICENSE.TXT for details.
//
//===---------------------------------------------------------------------===//
//
// HighLighterGenerator will read xml files and parse Highlight
// defination.
//
//===----------------------------------------------------------------------===//


#ifndef PROJECT_HIGHLIGHTERGENERATOR_H
#define PROJECT_HIGHLIGHTERGENERATOR_H

#include "HighLighterXmlReader.h"
#include <qlist.h>

class HighLighterGenerator {
public:
    static HighLighterGenerator* getInstance();
    // read all .xml files
    bool addXmlsPath(QString xmlsPath);
    QSharedPointer<HighlightDefinition> getHighLightReader(QString fileType);

    struct HighLitherFile{
        QRegExp pattern;
        QSharedPointer<HighLighterXmlReader> reader;
    };
    QList<HighLitherFile> xmlfiles;
};

#endif //PROJECT_HIGHLIGHTERGENERATOR_H
