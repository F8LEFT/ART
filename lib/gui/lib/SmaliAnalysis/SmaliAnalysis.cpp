//===- SmaliAnalysis.cpp - ART-GUI Analysis engine -------------*- C++ -*-===//
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

#include "SmaliAnalysis/SmaliAnalysis.h"

#include "Interpreter.h"

#include <fstream>
#include <QtCore/QObject>
#include <QDebug>
#include <QDirIterator>

using namespace std;
using namespace Analysis;

SmaliAnalysis* SmaliAnalysis::mPtr = nullptr;

SmaliAnalysis::SmaliAnalysis (QObject *parent)
        : QObject (parent)
{
    Q_ASSERT (mPtr == nullptr && "SmaliAnalysis has been initialize");
    mPtr = this;
}

SmaliAnalysis::~SmaliAnalysis ()
{
    Q_ASSERT (mPtr != nullptr && "SmaliAnalysis must be alloc first");
    mPtr = nullptr;
            foreach(Analysis::SmaliClass* sClass, mAllClass.values ()) {
            delete sClass;
        }

}

SmaliAnalysis *SmaliAnalysis::instance ()
{
    Q_ASSERT (mPtr != nullptr && "SmaliAnalysis must be alloc first");
    return mPtr;
}

bool SmaliAnalysis::addSmaliFolder (QStringList dirs)
{
    return true;
    foreach(QString dir, dirs) {
            addDirectory (dir);
        }
    return true;
}

bool SmaliAnalysis::addDirectory (QString dir)
{
    QDirIterator it(dir, QDirIterator::Subdirectories);
    while (it.hasNext()) {
        auto filePath = it.next();
        auto info = QFileInfo(filePath);
        if(info.isFile () && info.fileName ().endsWith (".smali")) {
            parseFile (info.absoluteFilePath ());
        }
    }
    return true;
}


QString SmaliAnalysis::parseFile (QString filePath)
{
    ifstream ifile;
    ifile.open (filePath.toStdString ());
    string classname;
    if(ifile.is_open ()) {
        Interpreter interpreter;
        SmaliClass sClass;
        StringPool strpool;
        sClass.setStringPool (&strpool);
        interpreter.switchInputStream (&ifile,&sClass);
        interpreter.parse ();
        interpreter.analysis ();
        classname = sClass.classType ();
    }
    ifile.close ();
    return QString::fromStdString (classname);
}
