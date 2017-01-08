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

#include <utils/ProjectInfo.h>

#include <fstream>
#include <QtCore/QObject>
#include <QDebug>
#include <QDirIterator>
#include <QDir>

using namespace std;

SmaliAnalysis *SmaliAnalysis::instance ()
{
    static SmaliAnalysis* mPtr = nullptr;
    if(mPtr == nullptr) {
        mPtr = new SmaliAnalysis;
    }
    return mPtr;
}

SmaliAnalysis::SmaliAnalysis()
    : m_dirIcon(":/images/treeOpen.png"),
      m_classIcon(":/images/class.png"),
      m_fieldIcon(":/images/field.png"),
      m_methodIcon(":/images/method.png")
{
    invisibleRootItem()->setColumnCount(2);

    connect(&m_fileWatcher, &QFileSystemWatcher::fileChanged, [this](QString path) {
        startFileParseThread(path);
    });
}

SmaliAnalysis::~SmaliAnalysis() {
}

void SmaliAnalysis::addSourcePath(QString source) {
    m_sourceDir << source;

    startFileParseThread(source);
}

void SmaliAnalysis::startFileParseThread(QString path) {
    SmaliAnalysisThread* thread = new SmaliAnalysisThread(path, this);
    connect(thread, &SmaliAnalysisThread::fileAnalysisFinished, this, &SmaliAnalysis::onFileAnalysisFinished);
    thread->start();
}

void SmaliAnalysis::clear() {
    removeAllSmaliFile();
    removeAllSmaliTree();
    m_sourceDir.clear();
}

void SmaliAnalysis::onFileAnalysisFinished (SmaliFile* file)
{
    qDebug() << "file analysis finished: " << file->sourceFile();
    addSmaliFileinToMap(file);
    addSmaliFileinToTree(file->sourceFile());
    fileAnalysisFinished(file->sourceFile());
}

void SmaliAnalysis::addSmaliFileinToMap(SmaliFile *smaliFile) {
    const QFileInfo fi(smaliFile->sourceFile());
    const QString &path = fi.path();
    if (!m_filenamesMap.contains(path))
        m_filenamesMap.insert(path, new FileNameDatasMap());
    m_filenamesMap.value(path)->insert(fi.fileName(), QSharedPointer<SmaliFile>(smaliFile));

    m_fileWatcher.addPath(smaliFile->sourceFile());

}

bool SmaliAnalysis::removeSmaliFileFromMap(QString fileName) {
    m_fileWatcher.removePath(fileName);

    bool found = false;
    const QFileInfo fi(fileName);
    if (auto files = m_filenamesMap.value(fi.path())) {
        files->remove(fi.fileName());
        if (files->count() <= 0) {
            m_filenamesMap.remove(fi.path());
            delete files;
        }
    }
    return found;
}

void SmaliAnalysis::removeAllSmaliFile() {
    m_fileWatcher.removePaths(m_fileWatcher.files());

    auto end = m_filenamesMap.constEnd();
    for (auto it = m_filenamesMap.constBegin(); it != end; ++it) {
        FileNameDatasMap *files = it.value();
        delete files;
    }
    m_filenamesMap.clear();
}

void SmaliAnalysis::addSmaliFileinToTree(QString filepath) {
    QFileInfo fi(filepath);
    auto filedata = getSmaliFile(fi.absoluteFilePath());
    if(filedata.isNull()) {
        return;
    }

    auto parent = findChildByFullPath(fi.absolutePath(), true);
    auto child = findChild(parent, fi.baseName(), true);
    child->setIcon(m_classIcon);
    child->setData(filedata->sourceFile(), ItemRole::Source);
    child->removeRows(0, child->rowCount());

    for(auto i = 0, count = filedata->fieldCount(); i < count; i++) {
        auto field = filedata->field(i);
        auto item = new QStandardItem(m_fieldIcon, field->m_name);
        item->setEditable(false);
        item->setData(field->m_line, ItemRole::Line);
        auto type = new QStandardItem(field->m_class);
        type->setEditable(false);
        child->appendRow(QList<QStandardItem*>() << item << type);
    }

    for(auto i = 0, count = filedata->methodCount(); i < count; i++) {
        auto method = filedata->method(i);
        auto item = new QStandardItem(m_methodIcon, method->m_name);
        item->setEditable(false);
        item->setData(method->m_startline, ItemRole::Line);
        auto type = new QStandardItem(method->buildProto());
        type->setEditable(false);
        child->appendRow(QList<QStandardItem*>() << item << type);
    }
}

QSharedPointer<SmaliFile> SmaliAnalysis::getSmaliFile(QString filepath) {
    const QFileInfo fi(filepath);
    if (auto files = m_filenamesMap.value(fi.path())) {
        return files->value(fi.fileName());
    }
    return QSharedPointer<SmaliFile>();
}

QStandardItem *SmaliAnalysis::findChildByFullPath(QString filepath, bool gen) {
    QString projectroot = QFileInfo(ProjectInfo::current()->getSourcePath()).absoluteFilePath();
    QDir dir(filepath);
    QStringList midpaths;
    while(dir.absolutePath() != projectroot) {
        midpaths << dir.dirName();
        dir.cdUp();
    }
    if(dir.absolutePath() != projectroot) {
        return nullptr;
    }
    auto parent = invisibleRootItem();
    for(auto it = midpaths.rbegin(), itEnd = midpaths.rend(); it != itEnd; it ++) {
        auto child = findChild(parent, *it, gen);
        if(child == nullptr) {
            return child;
        }
        parent = child;
    }
    return parent;
}

QStandardItem *SmaliAnalysis::findChild(QStandardItem *parent, QString name, bool gen) {
    for(auto i = 0, count = parent->rowCount(); i < count; i++) {
        auto child = parent->child(i, 0);
        if(child->text() == name) {
            return child;
        }
    }
    // chld not found
    if(!gen) {
        return nullptr;
    }
    auto child = new QStandardItem(m_dirIcon, name);
    child->setEditable(false);
    parent->appendRow(child);
    return child;
}


void SmaliAnalysis::removeSmaliFromTree(QString filepath) {
    QFileInfo fi(filepath);
    auto parent = findChildByFullPath(fi.absolutePath(), false);
    if(parent == nullptr) {
        return;
    }
    auto child = findChild(parent, fi.baseName(), false);
    if(child == nullptr) {
        return;
    }
    parent->removeRow(child->row());
}

void SmaliAnalysis::removeAllSmaliTree() {
    auto root = invisibleRootItem();
    root->removeRows(0, root->rowCount());
}



SmaliAnalysisThread::SmaliAnalysisThread (QString path, QObject *parent)
        : QThread (parent)
{
    m_src = path;
    connect(this, SIGNAL(finished()), this, SLOT(deleteLater()));
}

void SmaliAnalysisThread::run ()
{
    QFileInfo fi(m_src);
    if(fi.isDir()) {
        parseDirectory(m_src);
    } else {
        parseFile(m_src);
    }
}

void SmaliAnalysisThread::parseFile(QString path) {
    auto* filedata = new SmaliFile(path);
    if(!filedata->isValid()) {
        delete filedata;
        return;
    }
    fileAnalysisFinished(filedata);
}

void SmaliAnalysisThread::parseDirectory(QString path) {
    QDirIterator it(path, QDirIterator::Subdirectories);
    while (it.hasNext()) {
        auto filePath = it.next();
        auto info = QFileInfo(filePath);
        if(info.isFile () && info.fileName ().endsWith (".smali")) {
            parseFile(info.absoluteFilePath());
        }
    }
}


