//===- Configuration.h - ART-GUI utilpart -----------------------*- C++ -*-===//
//
//                     ANDROID REVERSE TOOLKIT
//
// This file is distributed under the GNU GENERAL PUBLIC LICENSE
// V3 License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file use QDomXml to save user setting.
//
//===----------------------------------------------------------------------===//
#ifndef CONFIGURATION_H
#define CONFIGURATION_H
#include <QSettings>
#include <QObject>
#include <QKeySequence>
#include <QMap>
#include <QColor>
#include <QFont>
#include <QDomDocument>

class Configuration;

#define Config() (Configuration::instance())
#define ConfigColor(x,y) (Config()->getColor(x,y))
#define ConfigBool(x,y) (Config()->getBool(x,y))
#define ConfigUint(x,y) (Config()->getUint(x,y))
#define ConfigFont(x,y) (Config()->getFont(x,y))
#define ConfigShortcut(x,y) (Config()->getShortcut(x,y))
#define ConfigString(x,y) (Config()->getString(x,y))
#define ConfigHScrollBarStyle() "QScrollBar:horizontal{border:1px solid grey;background:#f1f1f1;height:10px}QScrollBar::handle:horizontal{background:#aaa;min-width:20px;margin:1px}QScrollBar::add-line:horizontal,QScrollBar::sub-line:horizontal{width:0;height:0}"
#define ConfigVScrollBarStyle() "QScrollBar:vertical{border:1px solid grey;background:#f1f1f1;width:10px}QScrollBar::handle:vertical{background:#aaa;min-height:20px;margin:1px}QScrollBar::add-line:vertical,QScrollBar::sub-line:vertical{width:0;height:0}"

class Configuration : public QObject
{
    Q_OBJECT

public:
    explicit Configuration(QString cfgPath, QObject* mParent = nullptr);
    ~Configuration();
    static Configuration* instance();
    void load();
    void save();

    const QColor getColor (const QString &category,const QString &id);
    void setColor (const QString &category,const QString &id,const QColor &c);
    const bool getBool (const QString &category,const QString &id);
    void setBool (const QString &category,const QString &id,const bool b);
    const unsigned getUint (const QString &category,const QString &id);
    void setUint (const QString &category,const QString &id,const unsigned i);
    const QFont getFont (const QString &category,const QString &id);
    void setFont (const QString &category,const QString &id,const QFont &f);
    const QKeySequence getShortcut (const QString &category,const QString &id);
    void setShortcut (const QString &category,const QString &id,
                      const QKeySequence &sequence);
    const QString getString (const QString &category,const QString &id);
    void setString (const QString &category,const QString &id,const QString &s);


public:
    QMap<QString, QMap<QString, QColor>> Colors;        //[Colors]
    QMap<QString, QMap<QString, bool>> Bools;           //[Bools]
    QMap<QString, QMap<QString, unsigned>> Uints;       //[Uints]
    QMap<QString, QMap<QString, QFont>> Fonts;          //[Fonts]
    QMap<QString, QMap<QString, QKeySequence>> Shortcuts;   //[Shortcuts]
    QMap<QString, QMap<QString, QString>> Strings;      //[Strings]


signals:
    void colorsUpdated();
    void fontsUpdated();
    void shortcutsUpdated();
    void tokenizerConfigUpdated();

private:
    QString mSetFile;

private:
    QColor colorFromString (const QString &value);
    QString colorToString(const QColor& color);
    QFont fontFromString (const QString &value);
    QString fontToString(const QFont& font);
    QKeySequence shortcutFromString (const QString &value);
    QString shortcutToString (const QKeySequence &sequence);

    bool writeCfgElement (QDomDocument &doc,QDomElement &element,
                          const QString &type,const QString &category,
                          const QString &id,const QString &value);
};

#endif // CONFIGURATION_H
