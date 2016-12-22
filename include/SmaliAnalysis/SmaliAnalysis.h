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

#include <QMap>
#include <QObject>
#include <QDir>
#include <QSharedPointer>
#include <QThread>

class SmaliAnalysis : public QObject
{
    Q_OBJECT
//signals:
//    void analysisFinished();
//    void analysisUpdated(const QString &filePath,
//                         const QSharedPointer<Analysis::SmaliClass>&);

public:
    SmaliAnalysis(QObject* parent = 0);
    ~SmaliAnalysis ();

    static SmaliAnalysis* mPtr;
    static SmaliAnalysis* instance();

    bool addSmaliFolder(QStringList dirs);

//private slots:
//    void onFileAnalysisFinished(QString filePath, Analysis::SmaliClass* cla);
//    void onAllAnalysisFinished();
//
//public:
//    StringPool mStringPool;
//    QMap<QString, QSharedPointer<Analysis::SmaliClass>> mAllClass;
//
//    bool mInit = false;
};

//class SmaliAnalysisThread: public QThread
//{
//Q_OBJECT
//public:
//    SmaliAnalysisThread(QObject *parent = Q_NULLPTR);
//
//    void setSearchDir(QStringList d);
//    void addSearchDir(QString d);
//    void setStringPool(StringPool* sp);
//signals:
//    void fileAnalysisFinished(QString filePath, Analysis::SmaliClass* cla);
//    void allAnalysisFinished();
//protected:
//    void run();
//
//private:
//    QStringList mDirs;
//    StringPool* mStringPool;
//};

// return ClassName
//QString parseFile(QString filePath, StringPool* sp, Analysis::SmaliClass* sc);

#endif //PROJECT_SMALIANALYSIS_H
