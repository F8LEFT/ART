//===- HighLighterXmlReader.h - ART-GUI HighLighter-------------*- C++ -*-===//
//
//                     ANDROID REVERSE TOOLKIT
//
// This file is distributed under the GNU GENERAL PUBLIC LICENSE
// V3 License. See LICENSE.TXT for details.
//
//===---------------------------------------------------------------------===//
//
// HighLighterXmlReader will parse xml file
//
//===----------------------------------------------------------------------===//

#ifndef PROJECT_HIGHLIGHTERXMLREADER_H
#define PROJECT_HIGHLIGHTERXMLREADER_H

#include <QXmlStreamReader>
#include <QtXml/QXmlAttributes>
#include <QSharedPointer>
#include "KeywordList.h"
#include "HighlightDefinition.h"


class HighLighterXmlReader {
public:
    HighLighterXmlReader(const QSharedPointer<HighlightDefinition> &definition, QString filepath);
    bool loadXmlFile();
    QSharedPointer<HighlightDefinition> getHighLighterDefine();

    enum TextFormatId {
        Normal,
        VisualWhitespace,
        Keyword,
        DataType,
        Comment,
        Decimal,
        BaseN,
        Float,
        Char,
        SpecialChar,
        String,
        Alert,
        Information,
        Warning,
        Error,
        Function,
        RegionMarker,
        BuiltIn,
        Extension,
        Operator,
        Variable,
        Attribute,
        Annotation,
        CommentVar,
        Import,
        Others,
        Identifier
    };
private:
    QString xmlfile;
    bool startDocument();

    bool endDocument();

    bool startElement(const QStringRef &namespaceURI, const QStringRef &name, const QXmlStreamAttributes &atts);

    bool endElement(const QStringRef &namespaceURI, const QStringRef &name);

    bool characters(const QStringRef &ch);

    //创建新的list到m_currentList中，等待处理(添加新数据list)
    void listElementStarted(const QXmlStreamAttributes &atts);    // read list name=xxx data
    void listElementEnded();
    //读取item数据，添加到m_currentList中
    void itemElementStarted(const QXmlStreamAttributes &atts);
    void itemElementEnded();
    // 读取关键词数据，关键词对应的list存放在string属性中
    void keywordElementStarted(const QXmlStreamAttributes& atts);
    void keywordElementEnded();
    // 含正则匹配的高亮
    void regExprElementStarted(const QXmlStreamAttributes &atts);
    void regExprElementEnded();
    void contextElementStarted(QSharedPointer<Context> ctx, const QXmlStreamAttributes &atts);
    // 高亮设置
    void itemDataElementStarted(const QXmlStreamAttributes &atts);
    void itemDataElementEnded();
    // 注释类型
    void commentElementStarted(const QXmlStreamAttributes &atts);
    void commentElementEnded();
    // 关键字，是否大小写敏感
    void keywordsElementStarted(const QXmlStreamAttributes &atts);
    void keywordsElementEnded();
//        void foldingElementStarted(const QXmlStreamAttributes &atts);

private:
    QSharedPointer<HighlightDefinition> m_definition;

    QSharedPointer<KeywordList> m_currentList;                  // 当前正在操作的itemlist对象
    bool isLoaded = false;
};


#endif //PROJECT_HIGHLIGHTERXMLREADER_H
