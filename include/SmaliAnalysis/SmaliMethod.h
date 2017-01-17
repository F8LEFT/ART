//===- SmaliMethod.h - ART-GUI Analysis engine ------------------*- cpp -*-===//
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


#ifndef ANDROIDREVERSETOOLKIT_SMALIMETHOD_H
#define ANDROIDREVERSETOOLKIT_SMALIMETHOD_H

#include "utils/Defs.h"
#include <QString>
#include <QStringList>
#include <QMap>
#include <QVector>
#include <QList>

struct SmaliInstruction {
    int m_codeidx;
    int m_line;
};

struct SmaliMethod {
    QString m_name;
    u4 m_accessflag = 0;
    QVector<QString> m_params;
    QString m_ret;

    int m_localRegisterCount = 0;
    int m_paramRegisterCount = 0;

    int m_startline = -1;         // defination in source file
    int m_endline = -1;

    QList<SmaliInstruction> m_instructions;

    QString buildProto();
    QString buildAccessFlag();
    static QString buildAccessFlag(u4 flags);
    static u4 getAccessFlag(QString flags);

    bool equal(QString name, QVector<QString> params);
};


#endif //ANDROIDREVERSETOOLKIT_SMALIMETHOD_H
