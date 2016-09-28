//===- Configuration.h - ART-GUI utilpart -----------------------*- C++ -*-===//
//
//                     ANDROID REVERSE TOOLKIT
//
// This file is distributed under the GNU GENERAL PUBLIC LICENSE
// V3 License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file use QSetting to save user setting.
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

class Configuration;

#define Config() (Configuration::instance())
#define ConfigColor(x) (Config()->getColor(x))
#define ConfigBool(x,y) (Config()->getBool(x,y))
#define ConfigUint(x,y) (Config()->getUint(x,y))
#define ConfigFont(x) (Config()->getFont(x))
#define ConfigShortcut(x) (Config()->getShortcut(x).Hotkey)
#define ConfigHScrollBarStyle() "QScrollBar:horizontal{border:1px solid grey;background:#f1f1f1;height:10px}QScrollBar::handle:horizontal{background:#aaa;min-width:20px;margin:1px}QScrollBar::add-line:horizontal,QScrollBar::sub-line:horizontal{width:0;height:0}"
#define ConfigVScrollBarStyle() "QScrollBar:vertical{border:1px solid grey;background:#f1f1f1;width:10px}QScrollBar::handle:vertical{background:#aaa;min-height:20px;margin:1px}QScrollBar::add-line:vertical,QScrollBar::sub-line:vertical{width:0;height:0}"

class Configuration : public QObject
{
    Q_OBJECT
public:
    //Structures
    struct Shortcut
    {
        QString Name;
        QKeySequence Hotkey;
        bool GlobalShortcut;

        Shortcut(QString n = QString(), QString h = QString(), bool g = false)
        {
            Name = n;
            Hotkey = QKeySequence(h);
            GlobalShortcut = g;
        }
    };

    //Functions
public:
    explicit Configuration(QString cfgPath, QObject* mParent = nullptr);
    ~Configuration();

    static Configuration* instance();
    void load();
    void save();
    void readColors();
    void writeColors();
    void emitColorsUpdated();
    void emitTokenizerConfigUpdated();
    void readBools();
    void writeBools();
    void readUints();
    void writeUints();
    void readFonts();
    void writeFonts();
    void emitFontsUpdated();
    void readShortcuts();
    void writeShortcuts();

    const QColor getColor(const QString id) const;
    void setColor(const QString id, QColor c);
    const bool getBool(const QString category, const QString id) const;
    void setBool(const QString category, const QString id, const bool b);
    const unsigned getUint(const QString category, const QString id) const;
    void setUint(const QString category, const QString id, const unsigned i);
    const QFont getFont(const QString id) const;
    void setFont(const QString id, QFont f);
    const Shortcut getShortcut(const QString key_id) const;
    void setShortcut(const QString key_id, const QKeySequence key_sequence);

    //public variables
    QMap<QString, QColor> Colors;                   //[Colors]
    QMap<QString, QMap<QString, bool>> Bools;       //[Bools]
    QMap<QString, QMap<QString, unsigned>> Uints;   //[Uints]
    QMap<QString, QFont> Fonts;                     //[Fonts]
    QMap<QString, Shortcut> Shortcuts;              //[Shortcuts]

signals:
    void colorsUpdated();
    void fontsUpdated();
    void shortcutsUpdated();
    void tokenizerConfigUpdated();

private:
    QColor colorFromConfig(const QString id);
    bool colorToConfig(const QString id, const QColor color);
    bool boolFromConfig(const QString id);
    bool boolToConfig(const QString id, bool bBool);
    unsigned uintFromConfig(const QString id);
    bool uintToConfig(const QString id, unsigned i);
    QFont fontFromConfig(const QString id);
    bool fontToConfig(const QString id, const QFont font);
    QString shortcutFromConfig(const QString id);
    bool shortcutToConfig(const QString id, const QKeySequence shortcut);

    QSettings* mSettings;
};
#endif // CONFIGURATION_H
