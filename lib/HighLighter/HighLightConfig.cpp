//===- HighLightConfig.cpp - ART-GUI HighLighter----------------*- C++ -*-===//
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

#include "HighLighter/HighLightConfig.h"

HighLightConfig::HighLightConfig (QString cfgPath,QObject *mParent)
    : QObject(mParent)
{
    mSetFile = cfgPath;
    load ();
}

HighLightConfig::~HighLightConfig ()
{

}

HighLightConfig *HighLightConfig::instance (QString cfgPath,QObject *mParent)
{
    static  HighLightConfig* mPtr = nullptr;
    if(mPtr == nullptr) {
        mPtr = new HighLightConfig(cfgPath, mParent);
    }
    return mPtr;
}

void HighLightConfig::load ()
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
        QTextCharFormat format;
        QString font = catatype.attributeNode ("font").value ();
        QString fcolor = catatype.attributeNode ("foregroundcolor").value ();
        QString bcolor = catatype.attributeNode ("backgroundcolor").value ();
        QString ucolor = catatype.attributeNode ("underlinecolor").value ();
        int utype = catatype.attributeNode ("underlinetype").value ().toInt ();
        int antia = catatype.attributeNode ("antialias").value ().toInt ();
        FORMAT id = (FORMAT)catatype.attributeNode ("id").value ().toInt ();

        auto qfont = fontFromString (font);
        qfont.setStyleStrategy ((QFont::StyleStrategy)antia);
        format.setFont (qfont);
        format.setForeground (colorFromString (fcolor));
        format.setBackground (colorFromString (bcolor));
        format.setUnderlineColor (colorFromString (ucolor));
        format.setUnderlineStyle ((QTextCharFormat::UnderlineStyle)utype);
        mFormatMap[id] = format;

        catatype = catatype.nextSiblingElement();
    }
    onConfigUpdate ();
}

void HighLightConfig::save ()
{
    QFile file(mSetFile);
    if(!file.open(QFile::WriteOnly | QFile::Text))
        return ;

    QDomDocument domDocument;
    QDomElement root = domDocument.createElement("configs");


    for(auto it = mFormatMap.begin (), itEnd = mFormatMap.end ();
            it != itEnd; it++) {
        QDomElement element = domDocument.createElement ("QTextCharFormat");

        QDomAttr nameAttr = domDocument.createAttribute("name");
        element.setAttributeNode(nameAttr);
        element.setAttribute("name", getFormatName (it.key ()));

        QDomAttr idAttr = domDocument.createAttribute("id");
        element.setAttributeNode(idAttr);
        element.setAttribute("id",(int)it.key ());

        QDomAttr fColorAttr = domDocument.createAttribute("foregroundcolor");
        element.setAttributeNode(fColorAttr);
        element.setAttribute("foregroundcolor",colorToString (
                             it.value ().foreground ().color ()));

        QDomAttr bColorAttr = domDocument.createAttribute("backgroundcolor");
        element.setAttributeNode(bColorAttr);
        element.setAttribute("backgroundcolor",colorToString (
                             it.value ().background ().color ()));

        QDomAttr uColorAttr = domDocument.createAttribute("underlinecolor");
        element.setAttributeNode(uColorAttr);
        element.setAttribute("underlineColor", colorToString (
                             it.value ().underlineColor ()));

        QDomAttr uTypeAttr = domDocument.createAttribute("underlinetype");
        element.setAttributeNode(uTypeAttr);
        element.setAttribute("underlinetype",
                             (int)it.value ().underlineStyle ());

        QDomAttr fontAttr = domDocument.createAttribute("font");
        element.setAttributeNode(fontAttr);
        element.setAttribute("font", fontToString (it.value ().font ()));

        QDomAttr antiaAttr = domDocument.createAttribute ("antialias");
        element.setAttributeNode(antiaAttr);
        element.setAttribute("antialias", it.value ().font ().styleStrategy ());
        root.appendChild (element);
    }

    domDocument.appendChild (root);

    QTextStream out(&file);
    domDocument.save(out,4);
}



QColor HighLightConfig::colorFromString (const QString &value)
{
    QColor color (value);
    if(!color.isValid ()) {
        return Qt::transparent;
    }
    return color;
}

QString HighLightConfig::colorToString(const QColor &color)
{
    QString colorName = color.name().toUpper();
    if(!color.alpha())
        colorName = "#XXXXXX";
    return colorName;
}

QFont HighLightConfig::fontFromString (const QString &value)
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

QString HighLightConfig::fontToString(const QFont &font)
{
    return font.toString ();
}

QString HighLightConfig::getFormatName (HighLightConfig::FORMAT f)
{
    switch (f) {
        case FKeyword:
            return "Keyword";
        case FOp:
            return "OpCode";
        case FSymbol:
            return "Symbol";
        case FCString:
            return "String";
        case FNameString:
            return "Name";
        case FComment:
            return "Comment";
        case FClassType:
            return "ClassType";
        case FFlag:
            return "Flag";
        case FRegd:
            return "Register";
        case FNumber:
            return "Number";
        case FDefault:
            return "Default";
        default:
            return "Unknown";
    }
}

