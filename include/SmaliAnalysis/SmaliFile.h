//===- SmaliFile.h - ART-GUI Analysis engine --------------------*- cpp -*-===//
//
//                     ANDROID REVERSE TOOLKIT
//
// This file is distributed under the GNU GENERAL PUBLIC LICENSE
// V3 License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// SmaliFile use SmaliParser to parse .smali file to AST tree.
//
//===----------------------------------------------------------------------===//


#ifndef ANDROIDREVERSETOOLKIT_SMALIFILE_H
#define ANDROIDREVERSETOOLKIT_SMALIFILE_H

#include "SmaliLexer.h"
#include "SmaliParser.h"

#include "SmaliField.h"
#include "SmaliMethod.h"

#include <QVector>

class SmaliFileListener;

class SmaliFile {
public:
    SmaliFile(const QString& file);
    SmaliFile(const QString& file, const QString &input);
    ~SmaliFile();

//    void print();
    QString sourceFile() { return m_filepath; }

    // for smali class data
    QString buildAccessFlag();
    static QString buildAccessFlag(u4 flags);
    static u4 getAccessFlag(QString flags);

    bool isValid() { return m_isValid; }
    QString name() { return m_name; }
    int fieldCount() { return m_fields.size(); }
    SmaliField* field(int i) { return i < fieldCount() ? m_fields[i]: nullptr; }
    SmaliField* field(QString name);
    int methodCount() { return m_methods.size(); }
    SmaliMethod* method(int i) { return i < methodCount()? m_methods[i]: nullptr; }
    SmaliMethod* method(QString name, QString sig);
private:
    QString m_filepath;
    bool m_isValid = false;

    QString m_name;
    u4 m_accessflag;


    QVector<SmaliField*> m_fields;
    QVector<SmaliMethod*> m_methods;


    friend class SmaliFileListener;
};


#endif //ANDROIDREVERSETOOLKIT_SMALIFILE_H
