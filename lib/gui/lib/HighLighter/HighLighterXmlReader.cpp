//===- HighLighterXmlReader.cpp - ART-GUI HighLighter------------*- C++ -*-===//
//
//                     ANDROID REVERSE TOOLKIT
//
// This file is distributed under the GNU GENERAL PUBLIC LICENSE
// V3 License. See LICENSE.TXT for details.
//
//===---------------------------------------------------------------------===//

#include "HighLighterXmlReader.h"
#include <qdebug.h>

// for xml reader
static const QLatin1String fName("name");
static const QLatin1String fList("list");
static const QLatin1String fItem("item");
static const QLatin1String fContext("context");
static const QLatin1String fAttribute("attribute");
static const QLatin1String fDynamic("dynamic");
static const QLatin1String fFallthrough("fallthrough");
static const QLatin1String fLineEndContext("lineEndContext");
static const QLatin1String fLineBeginContext("lineBeginContext");
static const QLatin1String fFallthroughContext("fallthroughContext");
static const QLatin1String fBeginRegion("region");
static const QLatin1String fEndRegion("endRegion");
static const QLatin1String fLookAhead("lookAhead");
static const QLatin1String fFirstNonSpace("firstNonSpace");
static const QLatin1String fColumn("column");
static const QLatin1String fItemData("itemData");
static const QLatin1String fDefStyleNum("defStyleNum");
static const QLatin1String fColor("color");
static const QLatin1String fSelColor("selColor");
static const QLatin1String fItalic("italic");
static const QLatin1String fBold("bold");
static const QLatin1String fUnderline("underline");
static const QLatin1String fStrikeout("strikeout");
static const QLatin1String fChar("char");
static const QLatin1String fChar1("char1");
static const QLatin1String fString("String");
static const QLatin1String fInsensitive("insensitive");
static const QLatin1String fMinimal("minimal");
static const QLatin1String fKeywords("keywords");
static const QLatin1String fCaseSensitive("casesensitive");
static const QLatin1String fWeakDeliminator("weakDeliminator");
static const QLatin1String fAdditionalDeliminator("additionalDeliminator");
static const QLatin1String fComment("comment");
static const QLatin1String fPosition("position");
static const QLatin1String fSingleLine("singleline");
static const QLatin1String fMultiLine("multiline");
static const QLatin1String fStart("start");
static const QLatin1String fEnd("end");
static const QLatin1String fRegion("region");
static const QLatin1String fDetectChar("DetectChar");
static const QLatin1String fDetect2Chars("Detect2Chars");
static const QLatin1String fAnyChar("AnyChar");
static const QLatin1String fStringDetect("StringDetect");
static const QLatin1String fRegExpr("RegExpr");
static const QLatin1String fKeyword("keyword");
static const QLatin1String fInt("Int");
static const QLatin1String fFloat("Float");
static const QLatin1String fHlCOct("HlCOct");
static const QLatin1String fHlCHex("HlCHex");
static const QLatin1String fHlCStringChar("HlCStringChar");
static const QLatin1String fHlCChar("HlCChar");
static const QLatin1String fRangeDetect("RangeDetect");
static const QLatin1String fLineContinue("LineContinue");
static const QLatin1String fIncludeRules("IncludeRules");
static const QLatin1String fDetectSpaces("DetectSpaces");
static const QLatin1String fDetectIdentifier("DetectIdentifier");
static const QLatin1String fIncludeAttrib("includeAttrib");
static const QLatin1String fFolding("folding");
static const QLatin1String fIndentationSensitive("indentationsensitive");
static const QLatin1String fHash("#");
static const QLatin1String fDoubleHash("##");

bool HighLighterXmlReader::loadXmlFile() {
    if (isLoaded)
        return true;

    QFile file(xmlfile);
    if (!file.open(QFile::ReadOnly | QFile::Text)) {
        return false;
    }

    QXmlStreamReader reader;
    reader.setDevice(&file);
    while (!reader.atEnd()) {
        auto token = reader.readNext();
        switch (token) {
            case QXmlStreamReader::Invalid:
                qDebug() << "error has occured when reading xml";
                return false;
            case QXmlStreamReader::StartDocument:
                startDocument();
                break;
            case QXmlStreamReader::EndDocument:
                endDocument();
                break;
            case QXmlStreamReader::StartElement:
                startElement(reader.namespaceUri(), reader.name(), reader.attributes());
                break;
            case QXmlStreamReader::EndElement:
                endElement(reader.namespaceUri(), reader.name());
                break;
            case QXmlStreamReader::Characters:
                characters(reader.text());
                break;
            default:
                break;
        }
    }
    file.close();
    isLoaded = true;
    return true;
}

bool HighLighterXmlReader::startDocument() {
    return true;
}

bool HighLighterXmlReader::endDocument() {
    return true;
}

bool HighLighterXmlReader::startElement(const QStringRef &, const QStringRef &qName, const QXmlStreamAttributes &atts) {
    if (qName == fList)
        listElementStarted(atts);
    else if (qName == fItem)
        itemElementStarted(atts);
    else if (qName == fKeyword)
        keywordElementStarted(atts);
    else if (qName == fRegExpr)
        regExprElementStarted(atts);
    else if (qName == fItemData)
        itemDataElementStarted(atts);
    else if (qName == fComment)
        commentElementStarted(atts);
    else if (qName == fKeywords)
        keywordsElementStarted(atts);
//    else if (qName == fFolding)
//        foldingElementStarted(atts);
    return false;
}

bool HighLighterXmlReader::endElement(const QStringRef &, const QStringRef &qName) {

//    if (qName == fList)
//        listElementEnded();
//    else if (qName == fItem)
//        itemElementEnded();
//    else if (qName == fKeyword)
//        keywordElementEnded();
//    else if(qName == fRegExpr)
//        regExprElementEnded();
//    else if (qName == fItemData)
//        itemDataElementEnded();
//    else if (qName == fComment)
//        commentElementEnded();
//    else if (qName == fKeywords)
//        keywordsElementEnded();
    return true;
}

bool HighLighterXmlReader::characters(const QStringRef &ch) {

    return false;
}

void HighLighterXmlReader::listElementStarted(const QXmlStreamAttributes &atts) {
    m_currentList = m_definition->createKeywordList(atts.value(fName).toString());
}

void HighLighterXmlReader::itemElementStarted(const QXmlStreamAttributes &atts) {
    m_currentList->addKeyword(atts.value(fName).toString());
}

void HighLighterXmlReader::itemDataElementStarted(const QXmlStreamAttributes &atts) {
    QSharedPointer<ItemData> itemData = m_definition->createItemData(atts.value(fName).toString());
    itemData->setStyle(atts.value(fDefStyleNum).toString());
    itemData->setColor(atts.value(fColor).toString());
    itemData->setSelectionColor(atts.value(fSelColor).toString());
    itemData->setItalic(atts.value(fItalic).toString());
    itemData->setBold(atts.value(fBold).toString());
    itemData->setUnderlined(atts.value(fUnderline).toString());
    itemData->setStrikeOut(atts.value(fStrikeout).toString());
    itemData->makeFormat();
}

void HighLighterXmlReader::commentElementStarted(const QXmlStreamAttributes &atts) {
    const QString &commentType = atts.value(fName).toString();
    if (commentType.compare(fSingleLine, Qt::CaseInsensitive) == 0) {
        m_definition->setSingleLineComment(atts.value(fStart).toString());
        m_definition->setCommentAfterWhitespaces(atts.value(fPosition).toString());
    } else if (commentType.compare(fMultiLine, Qt::CaseInsensitive) == 0) {
        m_definition->setMultiLineCommentStart(atts.value(fStart).toString());
        m_definition->setMultiLineCommentEnd(atts.value(fEnd).toString());
        m_definition->setMultiLineCommentRegion(atts.value(fRegion).toString());
    }
}

void HighLighterXmlReader::keywordsElementStarted(const QXmlStreamAttributes &atts) {
    m_definition->setKeywordsSensitive(atts.value(fCaseSensitive).toString());
    m_definition->removeDelimiters(atts.value(fWeakDeliminator).toString());
    m_definition->addDelimiters(atts.value(fAdditionalDeliminator).toString());
}

//void HighLighterXmlReader::foldingElementStarted(const QXmlStreamAttributes &atts) {
//    m_definition->setIndentationBasedFolding(atts.value(fIndentationSensitive).toString());
//}

void HighLighterXmlReader::keywordElementStarted(const QXmlStreamAttributes &atts) {
    QSharedPointer<Context> context = m_definition->createContext(atts.value("string").toString());
    context->setType(Context::CtxType::Keyword);
    contextElementStarted(context, atts);
}

void HighLighterXmlReader::regExprElementStarted(const QXmlStreamAttributes &atts) {
    QSharedPointer<Context> context = m_definition->createContext(atts.value("string").toString());
    context->setType(Context::CtxType::RegExpr);
    contextElementStarted(context, atts);
}

void HighLighterXmlReader::contextElementStarted(QSharedPointer<Context> ctx, const QXmlStreamAttributes &atts) {
    ctx->setName(atts.value("string").toString());
    ctx->setRegion(atts.value("region").toString());
    ctx->setAttribute(atts.value("attribute").toString());
}

HighLighterXmlReader::HighLighterXmlReader(const QSharedPointer<HighlightDefinition> &definition, QString filepath) :
        m_definition(definition), xmlfile(filepath) {

}

QSharedPointer<HighlightDefinition> HighLighterXmlReader::getHighLighterDefine() {
    return m_definition;
}


struct FFormatMap {
    FFormatMap();

    QHash<QString, HighLighterXmlReader::TextFormatId> m_ids;
};

FFormatMap::FFormatMap() {
    m_ids.insert(QLatin1String("dsNormal"), HighLighterXmlReader::Normal);
    m_ids.insert(QLatin1String("dsKeyword"), HighLighterXmlReader::Keyword);
    m_ids.insert(QLatin1String("dsDataType"), HighLighterXmlReader::DataType);
    m_ids.insert(QLatin1String("dsComment"), HighLighterXmlReader::Comment);
    m_ids.insert(QLatin1String("dsDecVal"), HighLighterXmlReader::Decimal);
    m_ids.insert(QLatin1String("dsBaseN"), HighLighterXmlReader::BaseN);
    m_ids.insert(QLatin1String("dsFloat"), HighLighterXmlReader::Float);
    m_ids.insert(QLatin1String("dsChar"), HighLighterXmlReader::Char);
    m_ids.insert(QLatin1String("dsSpecialChar"), HighLighterXmlReader::SpecialChar);
    m_ids.insert(QLatin1String("dsString"), HighLighterXmlReader::String);
    m_ids.insert(QLatin1String("dsAlert"), HighLighterXmlReader::Alert);
    m_ids.insert(QLatin1String("dsInformation"), HighLighterXmlReader::Information);
    m_ids.insert(QLatin1String("dsWarning"), HighLighterXmlReader::Warning);
    m_ids.insert(QLatin1String("dsError"), HighLighterXmlReader::Error);
    m_ids.insert(QLatin1String("dsFunction"), HighLighterXmlReader::Function);
    m_ids.insert(QLatin1String("dsRegionMarker"), HighLighterXmlReader::RegionMarker);
    m_ids.insert(QLatin1String("dsBuiltIn"), HighLighterXmlReader::BuiltIn);
    m_ids.insert(QLatin1String("dsExtension"), HighLighterXmlReader::Extension);
    m_ids.insert(QLatin1String("dsOperator"), HighLighterXmlReader::Operator);
    m_ids.insert(QLatin1String("dsVariable"), HighLighterXmlReader::Variable);
    m_ids.insert(QLatin1String("dsAttribute"), HighLighterXmlReader::Attribute);
    m_ids.insert(QLatin1String("dsAnnotation"), HighLighterXmlReader::Annotation);
    m_ids.insert(QLatin1String("dsCommentVar"), HighLighterXmlReader::CommentVar);
    m_ids.insert(QLatin1String("dsImport"), HighLighterXmlReader::Import);
    m_ids.insert(QLatin1String("dsOthers"), HighLighterXmlReader::Others);
    m_ids.insert(QLatin1String("dsIdentifier"), HighLighterXmlReader::Identifier);
}

