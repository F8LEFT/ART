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
    enum FORMAT{
        FKeyword = 0,
        FOp,
        FSymbol,
        FCString,
        FNameString,
        FComment,
        FClassType,
        FFlag,
        FRegd,
        FNumber,
        FDefault,
        FError
    };

    enum CfgType {
        SMALI,
        GENERAL
    };
public:
    explicit HighLightConfig(QString cfgPath, CfgType type, QObject* mParent = nullptr);
    ~HighLightConfig ();

    static HighLightConfig* instance(CfgType cfgType, QString cfgPath = "",
                                     QObject* mParent = nullptr);
    void load();
    void save();
signals:
    void onConfigUpdate();

public:
    QMap<int, QTextCharFormat> mFormatMap;
    QString mSetFile;
    CfgType mCfgType;


    static QString getFormatName(int n, CfgType cfgType,
                                 bool translateNames = false);
    QString getFormatName(int n, bool translateNames = false);
    static int getFormatSize(CfgType cfgType);
    int getFormatSize();
    QTextCharFormat& getFormat(int n);
private:
    QColor colorFromString(const QString &value);
    QString colorToString(const QColor &color);
    QFont fontFromString(const QString &value);
    QString fontToString(const QFont &font);
};


#endif //PROJECT_HIGHLIGHTCONFIG_H
