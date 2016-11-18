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

#include <KateHighlight/katesyntaxmanager.h>
#include "HighLighter/HighLightConfig.h"

HighLightConfig::HighLightConfig (QString cfgPath, CfgType type,QObject *mParent)
    : QObject(mParent)
{
    mSetFile = cfgPath;
    mCfgType = type;
    load ();
}

HighLightConfig::~HighLightConfig ()
{

}

HighLightConfig *HighLightConfig::instance (CfgType cfgType, QString cfgPath,QObject *mParent)
{
    static QMap<CfgType, HighLightConfig *> mMap;
    HighLightConfig* mPtr = nullptr;
    auto it = mMap.find (cfgType);
    if(it == mMap.end ()) {
        mPtr = new HighLightConfig(cfgPath, cfgType, mParent);
        mMap[cfgType] = mPtr;
    } else {
        mPtr = it.value ();
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

QString HighLightConfig::getFormatName (int n, CfgType cfgType, bool translateNames)
{
    if(cfgType == SMALI) {
        static QStringList names;
        static QStringList translatedNames;

        if (names.isEmpty()) {
            names << QStringLiteral("Keyword");
            names << QStringLiteral("OpCode");
            names << QStringLiteral("Symbol");
            names << QStringLiteral("String");
            names << QStringLiteral("Name");
            names << QStringLiteral("Comment");
            names << QStringLiteral("ClassType");
            names << QStringLiteral("Flag");
            names << QStringLiteral("Register");
            names << QStringLiteral("Number");
            names << QStringLiteral("Default");
            names << QStringLiteral("Error");

            translatedNames << tr("Keyword");
            translatedNames << tr("OpCode");
            translatedNames << tr("Symbol");
            translatedNames << tr("String");
            translatedNames << tr("Name");
            translatedNames << tr("Comment");
            translatedNames << tr("ClassType");
            translatedNames << tr("Flag");
            translatedNames << tr("Register");
            translatedNames << tr("Number");
            translatedNames << tr("Default");
            translatedNames << tr("Error");
        }

        // sanity checks
        Q_ASSERT(n >= 0);
        Q_ASSERT(n < names.size());

        return translateNames ? translatedNames[n] : names[n];
    } else {
        static QStringList names;
        static QStringList translatedNames;

        if (names.isEmpty()) {
            names << QStringLiteral("Normal");
            names << QStringLiteral("Keyword");
            names << QStringLiteral("Function");
            names << QStringLiteral("Variable");
            names << QStringLiteral("Control Flow");
            names << QStringLiteral("Operator");
            names << QStringLiteral("Built-in");
            names << QStringLiteral("Extension");
            names << QStringLiteral("Preprocessor");
            names << QStringLiteral("Attribute");

            names << QStringLiteral("Character");
            names << QStringLiteral("Special Character");
            names << QStringLiteral("String");
            names << QStringLiteral("Verbatim String");
            names << QStringLiteral("Special String");
            names << QStringLiteral("Import");

            names << QStringLiteral("Data Type");
            names << QStringLiteral("Decimal/Value");
            names << QStringLiteral("Base-N Integer");
            names << QStringLiteral("Floating Point");
            names << QStringLiteral("Constant");

            names << QStringLiteral("Comment");
            names << QStringLiteral("Documentation");
            names << QStringLiteral("Annotation");
            names << QStringLiteral("Comment Variable");
            // this next one is for denoting the beginning/end of a user defined folding region
            names << QStringLiteral("Region Marker");
            names << QStringLiteral("Information");
            names << QStringLiteral("Warning");
            names << QStringLiteral("Alert");

            names << QStringLiteral("Others");
            // this one is for marking invalid input
            names << QStringLiteral("Error");

            translatedNames << tr("Normal");
            translatedNames << tr("Keyword");
            translatedNames << tr("Function");
            translatedNames << tr("Variable");
            translatedNames << tr("Control Flow");
            translatedNames << tr("Operator");
            translatedNames << tr("Built-in");
            translatedNames << tr("Extension");
            translatedNames << tr("Preprocessor");
            translatedNames << tr("Attribute");

            translatedNames << tr("Character");
            translatedNames << tr("Special Character");
            translatedNames << tr("String");
            translatedNames << tr("Verbatim String");
            translatedNames << tr("Special String");
            translatedNames << tr("Imports, Modules, Includes");

            translatedNames << tr("Data Type");
            translatedNames << tr("Decimal/Value");
            translatedNames << tr("Base-N Integer");
            translatedNames << tr("Floating Point");
            translatedNames << tr("Constant");

            translatedNames << tr("Comment");
            translatedNames << tr("Documentation");
            translatedNames << tr("Annotation");
            translatedNames << tr("Comment Variable");
            // this next one is for denoting the beginning/end of a user defined folding region
            translatedNames << tr("Region Marker");
            translatedNames << tr("Information");
            translatedNames << tr("Warning");
            translatedNames << tr("Alert");

            translatedNames << tr("Others");
            // this one is for marking invalid input
            translatedNames << tr("Error");
        }

        // sanity checks
        Q_ASSERT(n >= 0);
        Q_ASSERT(n < names.size());

        return translateNames ? translatedNames[n] : names[n];
    }

}

QTextCharFormat &HighLightConfig::getFormat (int i)
{
    return mFormatMap[(FORMAT)i];
}

QString HighLightConfig::getFormatName (int n,bool t)
{
    return getFormatName (n, mCfgType, t);
}

int HighLightConfig::getFormatSize ()
{
    return getFormatSize (mCfgType);
}

int HighLightConfig::getFormatSize (HighLightConfig::CfgType cfgType)
{
    if(cfgType == SMALI) {
        return (int)FError + 1;
    } else {
        return KateHlManager::defaultStyleCount () + 1;
    }
}
