//===- HighLightConfig.h - ART-GUI HighLighter------------------*- C++ -*-===//
//
//                     ANDROID REVERSE TOOLKIT
//
// This file is distributed under the GNU GENERAL PUBLIC LICENSE
// V3 License. See LICENSE.TXT for details.
//
//===---------------------------------------------------------------------===//
//
// Query highlightConfig from xml file.
//
//===----------------------------------------------------------------------===//

#ifndef PROJECT_HIGHLIGHTCONFIG_H
#define PROJECT_HIGHLIGHTCONFIG_H

#include <QtXml>
#include <QTextCharFormat>

class HighLightConfig: public QObject
{
    Q_OBJECT
public:
    explicit HighLightConfig(QString cfgPath, QObject* mParent = nullptr);
    ~HighLightConfig ();

    static HighLightConfig* instance(QString cfgPath = "", QObject* mParent = nullptr);
    void load();
    void save();
signals:
    void onConfigUpdate();

public:
    enum FORMAT{
        FKeyword,
        FOp,
        FSymbol,
        FCString,
        FNameString,
        FComment,
        FClassType,
        FFlag,
        FRegd,
        FNumber,
        FDefault
    };
public:
    QMap<FORMAT, QTextCharFormat> mFormatMap;
    QString mSetFile;

    static QString getFormatName(FORMAT f);
private:
    QColor colorFromString(const QString &value);
    QString colorToString(const QColor &color);
    QFont fontFromString(const QString &value);
    QString fontToString(const QFont &font);

};


#endif //PROJECT_HIGHLIGHTCONFIG_H
