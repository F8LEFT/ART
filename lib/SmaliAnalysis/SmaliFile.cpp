//===- SmaliFile.cpp - ART-GUI Analysis engine -----------------*- cpp -*-===//
//
//                     ANDROID REVERSE TOOLKIT
//
// This file is distributed under the GNU GENERAL PUBLIC LICENSE
// V3 License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

#include "SmaliAnalysis/SmaliFile.h"

#include "SmaliFileListener.h"

#define NUM_FLAGS   18

SmaliFile::SmaliFile(const QString& file)
{
    m_filepath = file;

    antlr4::ANTLRFileStream input(file.toStdString());
    SmaliLexer lexer(&input);
    antlr4::CommonTokenStream tokens(&lexer);
    tokens.fill();

    SmaliParser parser(&tokens);
    SmaliFileListener listener(this);

    auto* tree = parser.smali_file();
    antlr4::tree::ParseTreeWalker::DEFAULT.walk(&listener, tree);
}

SmaliFile::SmaliFile(const QString& file, const QString &inputs) {
    m_filepath = file;

    antlr4::ANTLRInputStream input(inputs.toStdString());
    SmaliLexer lexer(&input);
    antlr4::CommonTokenStream tokens(&lexer);
    tokens.fill();

    SmaliParser parser(&tokens);
    SmaliFileListener listener(this);

    auto* tree = parser.smali_file();
    antlr4::tree::ParseTreeWalker::DEFAULT.walk(&listener, tree);
}


SmaliFile::~SmaliFile() {
    qDeleteAll(m_fields);
    qDeleteAll(m_methods);
}

QString SmaliFile::buildAccessFlag() {
    return buildAccessFlag(m_accessflag);
}

QString SmaliFile::buildAccessFlag(u4 flags) {
    static QString kAccessStrings[] = {
        "PUBLIC",           /* 0x0001 */
        "PRIVATE",          /* 0x0002 */
        "PROTECTED",        /* 0x0004 */
        "STATIC",           /* 0x0008 */
        "FINAL",            /* 0x0010 */
        "?",                /* 0x0020 */
        "?",                /* 0x0040 */
        "?",                /* 0x0080 */
        "?",                /* 0x0100 */
        "INTERFACE",        /* 0x0200 */
        "ABSTRACT",         /* 0x0400 */
        "?",                /* 0x0800 */
        "SYNTHETIC",        /* 0x1000 */
        "ANNOTATION",       /* 0x2000 */
        "ENUM",             /* 0x4000 */
        "?",                /* 0x8000 */
        "VERIFIED",         /* 0x10000 */
        "OPTIMIZED",        /* 0x20000 */
    };
    QString rel;
    for (auto i = 0; i < NUM_FLAGS; i++) {
        if (flags & 0x01) {
            rel += kAccessStrings[i];
            rel.push_back(' ');
        }
        flags >>= 1;
    }
    return rel;
}

u4 SmaliFile::getAccessFlag(QString flags) {
    static QMap<QString, u4> kAccessMap = {
            {"PUBLIC",          ACC_PUBLIC},
            {"PRIVATE",         ACC_PRIVATE},
            {"PROTECTED",       ACC_PROTECTED},
            {"STATIC",          ACC_STATIC},
            {"FINAL",           ACC_FINAL},
            {"INTERFACE",       ACC_INTERFACE},
            {"ABSTRACT",        ACC_ABSTRACT},
            {"SYNTHETIC",       ACC_SYNTHETIC},
            {"ANNOTATION",      ACC_ANNOTATION},
            {"ENUM",            ACC_ENUM},
            {"VERIFIED",        ACC_CONSTRUCTOR},
            {"OPTIMIZED",       ACC_DECLARED_SYNCHRONIZED}
    };

    u4 rel = 0;
    auto flagList = flags.split(' ', QString::SkipEmptyParts);
    for(auto &flag: flagList) {
        auto it = kAccessMap.constFind(flag.toUpper());
        if(it != kAccessMap.constEnd()) {
            rel |= it.value();
        }
    }

    return rel;
}

//void SmaliFile::print() {
//    if(!m_smali->isValid)
//        cout << "smali file is not valid!!!" << endl;
//    if(m_smali->hasClassSpec) {
//        cout << ".class ";
//        auto class_spec = m_smali->class_spec(0);
//        auto access_spec = class_spec->access_list()->ACCESS_SPEC();
//        for(auto* access: access_spec) {
//            cout << access->getText() << " ";
//        }
//
//        cout << class_spec->className << endl;
//    }
//    if(m_smali->hasSuperSpec) {
//        auto super_spec = m_smali->super_spec(0);
//        cout << ".super " << super_spec->CLASS_DESCRIPTOR()->getText() << endl;
//    }
//    if(m_smali->hasSourceSpec) {
//        auto sourc_spec = m_smali->source_spec(0);
//        cout << ".source " << sourc_spec->STRING_LITERAL()->getText() << endl;
//    }
//}


