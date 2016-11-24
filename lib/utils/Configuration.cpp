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
#include <QFile>
#include <QTextStream>
#include <QDebug>

Configuration::Configuration(QString cfgPath, QObject* mParent)
        : QObject(mParent)
{
    mSetFile = cfgPath;

    load ();
}

Configuration::~Configuration ()
{
    save ();
}

Configuration* Configuration::instance()
{
    static  Configuration* mPtr = nullptr;
    if(mPtr == nullptr) {
        mPtr = new Configuration("./Configs.xml");
    }
    return mPtr;
}

void Configuration::load ()
{
    QDomDocument domDocument;

    QFile file(mSetFile);
    if(!file.open(QFile::ReadOnly | QFile::Text)) {
        qDebug()<<"open file"<<mSetFile<<"failed, error:"<<file.errorString();
        return;
    }

    QString strError;
    int errLin = 0, errCol = 0;
    if(!domDocument.setContent(&file, false, &strError, &errLin, &errCol)) {
        qDebug()<<"parse file failed at line"<<errLin
                <<",column"<<errCol<<","<<strError;
        return;
    }

    if(domDocument.isNull()) {
        return;
    }
    QDomElement root = domDocument.documentElement();
    QDomElement catatype = root.firstChildElement();
    if( catatype.isNull())
        return;

    while(!catatype.isNull())
    {
        QString type = catatype.attributeNode("type").value();
        QString category = catatype.attributeNode ("category").value ();
        QString id = catatype.attributeNode ("id").value ();
        QString value = catatype.attributeNode ("value").value ();
        if(type == "uint") {
            Uints[category][id] = value.toUInt ();
        } else if (type == "bool") {
            Bools[category][id] = value.toInt ();
        } else if (type == "string") {
            Strings[category][id] = value;
        } else if (type == "color") {
            Colors[category][id] = colorFromString (value);
        } else if (type == "font") {
            Fonts[category][id] = fontFromString (value);
        } else if (type == "shortcut") {
            Shortcuts[category][id] = shortcutFromString (value);
        } else if (type == "byte") {
            Bytes[category][id] = byteFromString(value);
        }
        catatype = catatype.nextSiblingElement();
    }
}

void Configuration::save()
{
    QFile file(mSetFile);
    if(!file.open(QFile::WriteOnly | QFile::Text))
        return ;

    QDomDocument domDocument;
    QDomElement root = domDocument.createElement("configs");

    for(auto it = Colors.begin (), itEnd = Colors.end (); it != itEnd; it++) {
        for(auto itSub = it->begin (), itSubEnd = it->end ();
                itSub != itSubEnd; itSub++) {
            QString category = it.key ();
            QDomElement element =  domDocument.createElement("cfg");
            writeCfgElement (domDocument,element, "color",category,
                             itSub.key (), colorToString (itSub.value ()));
            root.appendChild (element);
        }
    }

    for(auto it = Bools.begin (), itEnd = Bools.end (); it != itEnd; it++) {
        for(auto itSub = it->begin (), itSubEnd = it->end ();
            itSub != itSubEnd; itSub++) {
            QString category = it.key ();
            QDomElement element =  domDocument.createElement("cfg");
            writeCfgElement (domDocument,element, "bool",category,
                             itSub.key (), QString::number (itSub.value ()));
            root.appendChild (element);
        }
    }

    for(auto it = Uints.begin (), itEnd = Uints.end (); it != itEnd; it++) {
        for(auto itSub = it->begin (), itSubEnd = it->end ();
            itSub != itSubEnd; itSub++) {
            QString category = it.key ();
            QDomElement element =  domDocument.createElement("cfg");
            writeCfgElement (domDocument,element, "uint", category,
                             itSub.key (), QString::number (itSub.value ()));
            root.appendChild (element);
        }
    }

    for(auto it = Fonts.begin (), itEnd = Fonts.end (); it != itEnd; it++) {
        for(auto itSub = it->begin (), itSubEnd = it->end ();
            itSub != itSubEnd; itSub++) {
            QString category = it.key ();
            QDomElement element =  domDocument.createElement("cfg");
            writeCfgElement (domDocument,element, "font",category,
                             itSub.key (), fontToString (itSub.value ()));
            root.appendChild (element);
        }
    }

    for(auto it = Shortcuts.begin (), itEnd = Shortcuts.end (); it != itEnd; it++) {
        for(auto itSub = it->begin (), itSubEnd = it->end ();
            itSub != itSubEnd; itSub++) {
            QString category = it.key ();
            QDomElement element =  domDocument.createElement("cfg");
            writeCfgElement (domDocument,element, "shortcut", category,
                             itSub.key (), shortcutToString (itSub.value ()));
            root.appendChild (element);
        }
    }

    for(auto it = Strings.begin (), itEnd = Strings.end (); it != itEnd; it++) {
        for(auto itSub = it->begin (), itSubEnd = it->end ();
            itSub != itSubEnd; itSub++) {
            QString category = it.key ();
            QDomElement element =  domDocument.createElement("string");
            writeCfgElement (domDocument,element, "string",category,
                             itSub.key (), itSub.value ());
            root.appendChild (element);
        }
    }

    for(auto it = Bytes.begin (), itEnd = Bytes.end (); it != itEnd; it++) {
        for(auto itSub = it->begin (), itSubEnd = it->end ();
            itSub != itSubEnd; itSub++) {
            QString category = it.key ();
            QDomElement element =  domDocument.createElement("byte");
            writeCfgElement (domDocument,element, "byte",category,
                             itSub.key (), byteToString(itSub.value ()));
            root.appendChild (element);
        }
    }

    domDocument.appendChild (root);

    QTextStream out(&file);
    domDocument.save(out,4);
}


const QColor Configuration::getColor (const QString &category,const QString &id)
{
    if(Colors.contains(category))
    {
        if (Colors[category].contains (id))
        {
            return Colors[category][id].value ();
        }
    }
    return Qt::black;
}

void Configuration::setColor (const QString &category,const QString &id,
                              const QColor &c)
{
    Colors[id][category] = c;
    return;
}

const bool Configuration::getBool (const QString &category,const QString &id)
{
    if(Bools.contains(category))
    {
        if(Bools[category].contains(id))
            return Bools[category][id];
    }
    return false;
}

void Configuration::setBool (const QString &category,const QString &id,const bool b)
{
    Bools[category][id] = b;
    return;
}

const unsigned Configuration::getUint (const QString &category,const QString &id)
{
    if(Uints.contains(category))
    {
        if(Uints[category].contains(id))
            return Uints[category][id];
    }
    return 0;
}

void Configuration::setUint (const QString &category,const QString &id,
                             const unsigned i)
{
    Uints[category][id] = i;
    return;
}

const QFont Configuration::getFont (const QString &category,const QString &id)
{
    if(Fonts.contains(category))
    {
        if(Fonts[category].contains(id))
            return Fonts[category][id];
    }
    QFont ret("Lucida Console", 8, QFont::Normal, false);
    ret.setFixedPitch(true);
    ret.setStyleHint(QFont::Monospace);
    return ret;
}

void Configuration::setFont (const QString &category,const QString &id,const QFont &f)
{
    Fonts[id][category] = f;
}

const QKeySequence Configuration::getShortcut (const QString &category,
                                               const QString &id)
{
    if(Shortcuts.contains(category))
    {
        if(Shortcuts[category].contains(id))
            return Shortcuts[category][id];
    }
    return QKeySequence();
}

void Configuration::setShortcut (const QString &category,const QString &id,
                                 const QKeySequence &sequence)
{
    Shortcuts[id][category] = sequence;
    return;
}

const QString Configuration::getString (const QString &category,const QString &id)
{
    if(Strings.contains(category))
    {
        if(Strings[category].contains(id))
            return Strings[category][id];
    }
    return "";
}

void Configuration::setString(const QString &category,const QString &id,
                              const QString &s)
{
    Strings[category][id] = s;
    return;
}

const QByteArray Configuration::getByte(const QString &category, const QString &id)
{
    if(Bytes.contains(category)) {
        if(Bytes[category].contains(id))
            return Bytes[category][id];
    }
    return QByteArray();
}
void Configuration::setByte(const QString &category, const QString &id, const QByteArray &s)
{
    Bytes[category][id] = s;
}

QColor Configuration::colorFromString (const QString &value)
{
    QColor color (value);
    if(!color.isValid ()) {
        return Qt::black;;
    }
    return color;
}

QString Configuration::colorToString(const QColor &color)
{
    QString colorName = color.name().toUpper();
    if(!color.alpha())
        colorName = "#XXXXXX";
    return colorName;
}

QFont Configuration::fontFromString (const QString &value)
{
    QFont font;
    if(!font.fromString (value)) {
        QFont defont("Lucida Console", 8, QFont::Normal, false);
        defont.setFixedPitch(true);
        defont.setStyleHint(QFont::Monospace);
        return defont;
    }
    return font;
}

QString Configuration::fontToString(const QFont &font)
{
    return font.toString ();
}

QKeySequence Configuration::shortcutFromString (const QString &value)
{
    if(value == "NOT_SET") {
        return QKeySequence();
    }
    return QKeySequence (value);
}

QString Configuration::shortcutToString(const QKeySequence &sequence)
{
    if(sequence.isEmpty ()) {
        return "NOT_SET";
    }
    return sequence.toString ();
}

bool Configuration::writeCfgElement (QDomDocument &doc,QDomElement &element,
                                     const QString &type,const QString &category,
                                     const QString &id,const QString &value)
{

    QDomAttr typeAttr = doc.createAttribute("type");
    element.setAttributeNode(typeAttr);
    element.setAttribute("type",type);

    QDomAttr categoryAttr = doc.createAttribute("category");
    element.setAttributeNode(categoryAttr);
    element.setAttribute("category",category);

    QDomAttr idAttr = doc.createAttribute("id");
    element.setAttributeNode(idAttr);
    element.setAttribute("id",id);

    QDomAttr valueAttr = doc.createAttribute("value");
    element.setAttributeNode(valueAttr);
    element.setAttribute("value",value);
    return true;
}
QByteArray Configuration::byteFromString(const QString &value)
{
    return QByteArray::fromHex(value.toLatin1());
}
QString Configuration::byteToString(const QByteArray &byte)
{
    return byte.toHex();
}
