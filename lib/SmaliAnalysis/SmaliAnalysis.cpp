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
    mAllClass.clear ();
}

SmaliAnalysis *SmaliAnalysis::instance ()
{
    Q_ASSERT (mPtr != nullptr && "SmaliAnalysis must be alloc first");
    return mPtr;
}

bool SmaliAnalysis::addSmaliFolder (QStringList dirs)
{
    return true;
    SmaliAnalysisThread* analysisThread = new SmaliAnalysisThread;

    analysisThread->setSearchDir (dirs);
    analysisThread->setStringPool(&mStringPool);

    connect(analysisThread, SIGNAL(fileAnalysisFinished(QString,Analysis::SmaliClass*)),
            this, SLOT(onFileAnalysisFinished(QString,Analysis::SmaliClass*)));
    connect(analysisThread, SIGNAL(finished()), this, SLOT(onAllAnalysisFinished()));

    analysisThread->start ();
    return true;
}

void SmaliAnalysis::onFileAnalysisFinished (QString filePath,Analysis::SmaliClass *cla)
{
    bool exist = false;
    auto it = mAllClass.find (filePath);
    if(it != mAllClass.end ()) {
        exist = true;
    }
    auto p = QSharedPointer<Analysis::SmaliClass>(cla);
    mAllClass[filePath] = p;
    if(exist && mInit) {
        emit analysisUpdated (filePath, p);
    }
}

void SmaliAnalysis::onAllAnalysisFinished ()
{
    mInit = true;
    qDebug() << "SmaliAnalysis Finished";
    emit analysisFinished();
}

QString parseFile (QString filePath,StringPool *sp,
                   Analysis::SmaliClass *sc)
{
    ifstream ifile;
    ifile.open (filePath.toStdString ());
    string classname;
    if(ifile.is_open ()) {
        Interpreter interpreter;
        sc->setStringPool (sp);
        sc->setFileName (filePath.toStdString ());
        interpreter.switchInputStream (&ifile,sc);
        interpreter.parse ();
        interpreter.analysis ();
        classname = sc->classType ();
    }
    ifile.close ();
    return QString::fromStdString (classname);
}

SmaliAnalysisThread::SmaliAnalysisThread (QObject *parent)
        : QThread (parent)
{
    connect(this, SIGNAL(finished()), this, SLOT(deleteLater()));
}

void SmaliAnalysisThread::setSearchDir (QStringList d)
{
    mDirs = d;
}

void SmaliAnalysisThread::addSearchDir (QString d)
{
    mDirs << d;
}

void SmaliAnalysisThread::setStringPool (StringPool *sp)
{
    mStringPool = sp;
}


void SmaliAnalysisThread::run ()
{
    Q_FOREACH (QString dir, mDirs) {
            QDirIterator it(dir, QDirIterator::Subdirectories);
            while (it.hasNext()) {
                auto filePath = it.next();
                auto info = QFileInfo(filePath);
                if(info.isFile () && info.fileName ().endsWith (".smali")) {
                    SmaliClass* sc = new SmaliClass;
                    auto fp = parseFile (info.absoluteFilePath (),mStringPool,sc);
                    if(!fp.isEmpty ()) {
                        emit fileAnalysisFinished (fp, sc);
                    }
                }
            }
        }
    emit allAnalysisFinished ();
}

