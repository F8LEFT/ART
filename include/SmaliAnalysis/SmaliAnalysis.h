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


#include "SmaliFile.h"

#include <QMap>
#include <QObject>
#include <QDir>
#include <QSharedPointer>
#include <QStringList>
#include <QThread>
#include <QAbstractItemModel>
#include <QStandardItemModel>
#include <QFileSystemWatcher>

class SmaliTreeItem;

class SmaliAnalysis : public QStandardItemModel
{
    Q_OBJECT
public:
    enum ItemRole {
        Source = Qt::UserRole,
        Line,
    };
public:
    static SmaliAnalysis* instance();
    QStringList sources() { return m_sourceDir; }

    void addSourcePath(QString source);
    void startFileParseThread(QString path);
    void clear();
    // interface for ItemModel

private:
    void addSmaliFileinToTree(QString filepath);
    void removeSmaliFromTree(QString filepath);
    void removeAllSmaliTree();

signals:
    void fileAnalysisFinished(const QString &filePath);

private slots:
    void onFileAnalysisFinished(SmaliFile* file);

public:
    // get SmaliFile data with full path
    QSharedPointer<SmaliFile> getSmaliFile(QString filepath);
    // get SmaliFile data with signature like Ljava/lang/Object;
    // or java.lang.Object
    QSharedPointer<SmaliFile> getSmaliFileBySig(QString sig);

    QStandardItem * findChildByFullPath(QString filepath, bool gen = false);
    QStandardItem * findChild(QStandardItem *parent, QString name, bool gen = false);
private:
    SmaliAnalysis();
    ~SmaliAnalysis ();

    void addSmaliFileinToMap(SmaliFile* smaliFile);
    bool removeSmaliFileFromMap(QString fileName);
    void removeAllSmaliFile();

    typedef QMap<QString, QSharedPointer<SmaliFile>> FileNameDatasMap;
    typedef QMap<QString, FileNameDatasMap *> DirectoryFileDatasMap;

    DirectoryFileDatasMap m_filenamesMap;
    QMap<QString, QSharedPointer<SmaliFile>> m_classnamesMap;

    QStringList m_sourceDir;

    QIcon m_dirIcon;
    QIcon m_classIcon;
    QIcon m_fieldIcon;
    QIcon m_methodIcon;

    QFileSystemWatcher m_fileWatcher;
};

class SmaliAnalysisThread: public QThread
{
Q_OBJECT
public:
    SmaliAnalysisThread(QString path, QObject *parent = Q_NULLPTR);

signals:
    void fileAnalysisFinished(SmaliFile* file);
protected:
    void run();
    void parseFile(QString path);
    void parseDirectory(QString path);
private:
    QString m_src;
};

#endif //PROJECT_SMALIANALYSIS_H
