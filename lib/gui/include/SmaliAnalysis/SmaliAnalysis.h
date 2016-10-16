//===- SmaliAnalysis.h - ART-GUI Analysis engine ---------------*- C++ -*-===//
//
//                     ANDROID REVERSE TOOLKIT
//
// This file is distributed under the GNU GENERAL PUBLIC LICENSE
// V3 License. See LICENSE.TXT for details.
//
//===---------------------------------------------------------------------===//
//
// This file defines project tab in workspace tab bar. It helps user to
// choose project to open or change project setting.
//
//===----------------------------------------------------------------------===//


#ifndef PROJECT_SMALIANALYSIS_H
#define PROJECT_SMALIANALYSIS_H

#include "utils/StringPool.hpp"
#include "SmaliAst/SmaliClass.h"
#include <QMap>
#include <QObject>
#include <QDir>
class SmaliAnalysis : public QObject
{
    Q_OBJECT
public:
    SmaliAnalysis(QObject* parent = 0);
    ~SmaliAnalysis ();

    static SmaliAnalysis* mPtr;
    static SmaliAnalysis* instance();

    bool addDirectory(QDir dir);
    QString parseFile(QString filePath);

public:
    StringPool mStringPool;
    QMap<int, Analysis::SmaliClass*> mAllClass;
};


#endif //PROJECT_SMALIANALYSIS_H
