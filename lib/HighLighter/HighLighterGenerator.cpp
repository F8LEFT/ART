//===- HighLighterGenerator.cpp - ART-GUI HighLighter-----------*- C++ -*-===//
//
//                     ANDROID REVERSE TOOLKIT
//
// This file is distributed under the GNU GENERAL PUBLIC LICENSE
// V3 License. See LICENSE.TXT for details.
//
//===---------------------------------------------------------------------===//


#include "HighLighterGenerator.h"
#include "utils/StringUtil.h"

#include <QDir>


bool HighLighterGenerator::addXmlsPath(QString xmlsPath) {
    QDir dir(xmlsPath);
    if (!dir.exists()) {
        return false;
    }
    dir.setFilter(QDir::Files | QDir::NoSymLinks);
    QFileInfoList list = dir.entryInfoList();

    int fCount = list.count();
    if (fCount <= 0) {
        return false;
    }

    QStringList strList;
    for (int i = 0; i < fCount; i++) {
        QFileInfo fInfo = list.at(i);
        QString suffix = fInfo.suffix();

        if (suffix.compare("xml", Qt::CaseInsensitive) == 0) {
            QString filePath = fInfo.absoluteFilePath();
            QFile file(filePath);
            if (!file.open(QFile::ReadOnly | QFile::Text)) {
                continue;
            }
            QXmlStreamReader reader;
            reader.setDevice(&file);
            bool isFind = false;
            while (!isFind && !reader.atEnd()) {
                auto token = reader.readNext();
                switch (token) {
                    case QXmlStreamReader::StartElement:
                        if (reader.name() == "language") {
                            auto pattern = reader.attributes().value("extensions");
                            if (pattern.contains("*.")) {
                                QSharedPointer<HighlightDefinition> define(new HighlightDefinition());
                                HighLitherFile f;

                                f.pattern = QRegExp(pattern.toString().replace("*.", "."));
                                f.reader = QSharedPointer<HighLighterXmlReader>(
                                        new HighLighterXmlReader(define, filePath));
                                xmlfiles.push_back(f);
                            }
                            isFind = true;
                        }
                        break;
                    default:
                        break;
                }
            }
        }
    }
    return true;
}

QSharedPointer<HighlightDefinition> HighLighterGenerator::getHighLightReader(QString fileType) {
        foreach(auto &xmlfile, xmlfiles) {
        QRegExp expression(xmlfile.pattern);
        int index = expression.indexIn(fileType);
        if (index >= 0) {
            xmlfile.reader->loadXmlFile();
            return xmlfile.reader->getHighLighterDefine();
        }
    }
    return QSharedPointer<HighlightDefinition>(new HighlightDefinition);
}

HighLighterGenerator *HighLighterGenerator::getInstance() {
    static HighLighterGenerator* mInstance = nullptr;
    if(mInstance == nullptr) {
        mInstance = new HighLighterGenerator;
        mInstance->addXmlsPath (GetCfgsPath("highlight"));
    }
    return mInstance;
}

