//===- Configuration.cpp - ART-GUI utilpart ---------------------*- C++ -*-===//
//
//                     ANDROID REVERSE TOOLKIT
//
// This file is distributed under the GNU GENERAL PUBLIC LICENSE
// V3 License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
#include "utils/Configuration.h"

#include "utils/StringUtil.h"

#include <QApplication>
#include <QFontInfo>
#include <QMessageBox>
#include <QIcon>
#include <QtGlobal>


Configuration::Configuration(QString cfgPath, QObject* mParent) : QObject(mParent)
{
    mSettings = new QSettings(cfgPath, QSettings::IniFormat, this);

    // hotkeys settings
//    Shortcuts.insert("FileOpen", Shortcut(tr("File -> Open"), "F3", true));

    load();
}

Configuration::~Configuration()
{
    save();
}

Configuration* Configuration::instance()
{
    static  Configuration* mPtr = nullptr;
    if(mPtr == nullptr) {
        mPtr = new Configuration("./Configs.ini");
    }
    return mPtr;
}

void Configuration::load()
{
    readColors();
    readBools();
    readUints();
    readFonts();
    readShortcuts();
    readStrings();
}

void Configuration::save()
{
    writeColors();
    writeBools();
    writeUints();
    writeFonts();
    writeShortcuts();
    writeStrings();
}

void Configuration::readColors()
{
    mSettings->beginGroup("Colors");
    QStringList keys = mSettings->allKeys();
    foreach(QString id, keys) {
        Colors[id] = colorFromConfig(id);
    }
    mSettings->endGroup();
}

void Configuration::writeColors()
{
    mSettings->beginGroup("Colors");
    for(int i = 0; i < Colors.size(); i++)
    {
        QString id = Colors.keys().at(i);
        colorToConfig(id, Colors[id]);
    }
    mSettings->endGroup();
    emit colorsUpdated();
}

void Configuration::readBools()
{
    QStringList allCategory = mSettings->childGroups();
    foreach(QString category, allCategory) {
        if (category.endsWith("_Bools")) {
            mSettings->beginGroup(category);
            category = category.left(category.length() - 6);

            QStringList keys = mSettings->childKeys();
            foreach(QString id, keys) {
                Bools[category][id] = boolFromConfig(id);
            }
            mSettings->endGroup();
        }
    }

}

void Configuration::writeBools()
{
    for(int i = 0; i < Bools.size(); i++)
    {
        QString category = Bools.keys().at(i);
        QMap<QString, bool>* currentBool = &Bools[category];
        mSettings->beginGroup(category + "_Bools");
        for(int j = 0; j < currentBool->size(); j++)
        {
            QString id = (*currentBool).keys().at(j);
            boolToConfig(id, (*currentBool)[id]);
        }
        mSettings->endGroup();
    }
}

void Configuration::readUints()
{
    QStringList allCategory = mSettings->childGroups();
    foreach(QString category, allCategory) {
        if (category.endsWith("Uints")) {
            mSettings->beginGroup(category);
            category = category.left(category.length() - 6);

            QStringList keys = mSettings->childKeys();
            foreach(QString id, keys) {
                Uints[category][id] = uintFromConfig(id);
            }
            mSettings->endGroup();
        }

    }
}

void Configuration::writeUints()
{
    for(int i = 0; i < Uints.size(); i++)
    {
        QString category = Uints.keys().at(i);
        QMap<QString, unsigned>* currentUint = &Uints[category];

        mSettings->beginGroup(category + "_Uints");
        for(int j = 0; j < currentUint->size(); j++)
        {
            QString id = (*currentUint).keys().at(j);
            uintToConfig(id, (*currentUint)[id]);
        }
        mSettings->endGroup();
    }

}

void Configuration::readFonts()
{
    mSettings->beginGroup("Fonts");
    QStringList keys = mSettings->allKeys();

    foreach(QString id, keys) {
        QFont font = fontFromConfig(id);
        QFontInfo fontInfo(font);
        if(fontInfo.fixedPitch())
            Fonts[id] = font;
    }
    mSettings->endGroup();
}

void Configuration::writeFonts()
{
    mSettings->beginGroup("Fonts");
    for(int i = 0; i < Fonts.size(); i++)
    {
        QString id = Fonts.keys().at(i);
        fontToConfig(id, Fonts[id]);
    }
    mSettings->endGroup();
    emit fontsUpdated();
}

void Configuration::readShortcuts()
{
    mSettings->beginGroup("Shortcuts");
    QStringList keys = mSettings->allKeys();

    foreach(QString id, keys) {
        QString key = shortcutFromConfig(id);
        if(key != "")
        {
            if(key == "NOT_SET")
                Shortcuts[id].Hotkey = QKeySequence();
            else
            {
                QKeySequence KeySequence(key);
                Shortcuts[id].Hotkey = KeySequence;
            }
        }
    }
    mSettings->endGroup();
    emit shortcutsUpdated();
}

void Configuration::writeShortcuts()
{
    mSettings->beginGroup("Shortcuts");
    for(auto it = Shortcuts.begin(), iEnd = Shortcuts.end();
            it != iEnd; it++) {
        shortcutToConfig(it.key(), it.value().Hotkey);
    }
    mSettings->endGroup();
    emit shortcutsUpdated();
}

void Configuration::readStrings()
{
    QStringList allCategory = mSettings->childGroups();
    foreach(QString category, allCategory) {
        if (category.endsWith("Strings")) {
            mSettings->beginGroup(category);
            category = category.left(category.length() - 8);

            QStringList keys = mSettings->childKeys();
            foreach(QString id, keys) {
                Strings[category][id] = stringFromConfig(id);
            }
            mSettings->endGroup();
        }
    }
}

void Configuration::writeStrings()
{
    for(int i = 0; i < Strings.size(); i++)
    {
        QString category = Strings.keys().at(i);
        QMap<QString, QString>* currentString = &Strings[category];

        mSettings->beginGroup(category + "_Strings");
        for(int j = 0; j < currentString->size(); j++)
        {
            QString id = (*currentString).keys().at(j);
            stringToConfig(id, (*currentString)[id]);
        }
        mSettings->endGroup();
    }
}

const QColor Configuration::getColor(const QString id) const
{
    if(Colors.contains(id))
        return Colors.constFind(id).value();

    return Qt::black;
}

void Configuration::setColor(const QString id, QColor c)
{
    Colors[id] = c;
    return;
}

const bool Configuration::getBool(const QString category, const QString id) const
{
    if(Bools.contains(category))
    {
        if(Bools[category].contains(id))
            return Bools[category][id];
    }
    return false;
}

void Configuration::setBool(const QString category, const QString id, const bool b)
{
    Bools[category][id] = b;
    return;
}

const unsigned Configuration::getUint(const QString category, const QString id) const
{
    if(Uints.contains(category))
    {
        if(Uints[category].contains(id))
            return Uints[category][id];
    }
    return 0;
}

void Configuration::setUint(const QString category, const QString id, const unsigned i)
{
    Uints[category][id] = i;
    return;
}

const QFont Configuration::getFont(const QString id) const
{
    if(Fonts.contains(id))
        return Fonts.constFind(id).value();
    QFont ret("Lucida Console", 8, QFont::Normal, false);
    ret.setFixedPitch(true);
    ret.setStyleHint(QFont::Monospace);
    return ret;
}

void Configuration::setFont(const QString id, QFont f)
{
    Fonts[id] = f;
}

const Configuration::Shortcut Configuration::getShortcut(const QString key_id) const
{
    if(Shortcuts.contains(key_id))
        return Shortcuts.constFind(key_id).value();
    return Shortcut();
}

void Configuration::setShortcut(const QString key_id, const QKeySequence key_sequence)
{
    Shortcuts[key_id].Hotkey = key_sequence;
    return;
}

const QString Configuration::getString(const QString category, const QString id) const
{
    if(Strings.contains(category))
    {
        if(Strings[category].contains(id))
            return Strings[category][id];
    }
    return "";
}

void Configuration::setString(const QString category, const QString id, const QString s)
{
    Strings[category][id] = s;
    return;
}

QColor Configuration::colorFromConfig(const QString id)
{
    QString setting = mSettings->value(id, QVariant("#FFFFFF")).toString();
    QColor color(setting);
    if (!color.isValid())
    {
        return Qt::black;
    }
    return color;
}

bool Configuration::colorToConfig(const QString id, const QColor color)
{
    QString colorName = color.name().toUpper();
    if(!color.alpha())
        colorName = "#XXXXXX";
    mSettings->setValue(id, colorName);
    return true;
}

bool Configuration::boolFromConfig(const QString id)
{
    return mSettings->value(id, false).toBool();
}

bool Configuration::boolToConfig(const QString id, bool bBool)
{
    mSettings->setValue(id, bBool);
    return true;
}

unsigned Configuration::uintFromConfig(const QString id)
{
    return mSettings->value(id, 0).toUInt();
}

bool Configuration::uintToConfig(const QString id, unsigned i)
{
    mSettings->setValue(id, i);
    return true;
}

QFont Configuration::fontFromConfig(const QString id)
{
    QString setting = mSettings->value(id, "Lucida Console").toString();
    QFont font;
    if (!font.fromString(setting))
    {
        QFont ret("Lucida Console", 8, QFont::Normal, false);
        ret.setFixedPitch(true);
        ret.setStyleHint(QFont::Monospace);
        return ret;
    }
    return font;
}

bool Configuration::fontToConfig(const QString id, const QFont font)
{
    mSettings->setValue(id, font.toString());
    return true;
}

QString Configuration::shortcutFromConfig(const QString id)
{
    QString _id = QString("%1").arg(id);
    return mSettings->value(_id, "").toString();
}

bool Configuration::shortcutToConfig(const QString id, const QKeySequence shortcut)
{
    QString _id = QString("%1").arg(id);
    QString _key = "";
    if(!shortcut.isEmpty())
        _key = shortcut.toString(QKeySequence::NativeText);
    else
        _key = "NOT_SET";
    mSettings->setValue(_id, _key);
    return true;
}

QString Configuration::stringFromConfig(const QString id)
{
    return mSettings->value(id, "").toString();
}

bool Configuration::stringToConfig(const QString id, const QString s)
{
    mSettings->setValue(id, s);
    return true;
}

