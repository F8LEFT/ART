//===- SmaliField.h - ART-GUI Analysis engine -------------------*- cpp -*-===//
//
//                     ANDROID REVERSE TOOLKIT
//
// This file is distributed under the GNU GENERAL PUBLIC LICENSE
// V3 License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// SmaliField is used to record smaliData
//
//===----------------------------------------------------------------------===//



#ifndef ANDROIDREVERSETOOLKIT_SMALIFIELD_H
#define ANDROIDREVERSETOOLKIT_SMALIFIELD_H

#include <QString>
#include <utils/Defs.h>
#include <QStringList>
#include <QMap>

struct SmaliField {
    QString m_name;
    u4 m_accessflag;
    QString m_class;


    int m_line;         // defination in source file

    QString buildAccessFlag();
    static QString buildAccessFlag(u4 flags);
    static u4 getAccessFlag(QString flags);
};


#endif //ANDROIDREVERSETOOLKIT_SMALIFIELD_H
