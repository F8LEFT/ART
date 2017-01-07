//===- SmaliFileListener.h - ART-GUI Analysis engine ------------*- cpp -*-===//
//
//                     ANDROID REVERSE TOOLKIT
//
// This file is distributed under the GNU GENERAL PUBLIC LICENSE
// V3 License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// SmaliFilelistener will walk smali ast context and output file information.
//
//===----------------------------------------------------------------------===//

#ifndef ANDROIDREVERSETOOLKIT_SMALIFILELISTENER_H
#define ANDROIDREVERSETOOLKIT_SMALIFILELISTENER_H

#include "SmaliParserBaseListener.h"

class SmaliFile;

class SmaliFileListener: public SmaliParserBaseListener {

public:
    SmaliFileListener(SmaliFile* filedata);

    void enterSmali_file(SmaliParser::Smali_fileContext * ctx) override;
    void exitSmali_file(SmaliParser::Smali_fileContext * ctx) override;


    void enterMethod(SmaliParser::MethodContext * ctx) override;
    void exitMethod(SmaliParser::MethodContext * ctx) override;

    void enterField(SmaliParser::FieldContext * ctx) override;
    void exitField(SmaliParser::FieldContext * ctx) override;

    SmaliFile* m_smali;
};


#endif //ANDROIDREVERSETOOLKIT_SMALIFILELISTENER_H
