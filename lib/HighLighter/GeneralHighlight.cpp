//===- GeneralHighlight.cpp - ART-GUI HighLighter---------------*- C++ -*-===//
//
//                     ANDROID REVERSE TOOLKIT
//
// This file is distributed under the GNU GENERAL PUBLIC LICENSE
// V3 License. See LICENSE.TXT for details.
//
//===---------------------------------------------------------------------===//
#include "GeneralHighlight.h"
#include "HighLighterGenerator.h"

// TODO rewrite GerneralHighlight.
// see KateEditor
GeneralHighlight::GeneralHighlight(QTextDocument *parent, QString fileName)
        : QSyntaxHighlighter(parent){
    return ;
    HighLighterGenerator *generator = HighLighterGenerator::getInstance();
    definition = generator->getHighLightReader(fileName);

}

void GeneralHighlight::highlightBlock(const QString &text) {
    return;
    auto ctx = definition->context();
    for(auto &m_context : ctx) {
        switch (m_context->type()) {
            case Context::Keyword: {
                QString str = m_context->name();
                QRegExp patten = m_context->getRegExpr(definition.data());
                int index = patten.indexIn(text);
                if (m_context->region() == "BeginRegion") {
                    if (index >= 0) {
                        int length = patten.matchedLength();
                        const QTextCharFormat &format = definition->itemData(m_context->attribute())->getFormat();
                        setFormat(index, length, format);
                    }
                } else {
                    while(index >= 0) {
                        int length = patten.matchedLength();
                        const QTextCharFormat &format = definition->itemData(m_context->attribute())->getFormat();
                        setFormat(index, length, format);
                        index = patten.indexIn(text, index + length);
                    }
                }
            }
                break;
            case Context::RegExpr: {
                QString str = m_context->name();

                QRegExp patten = m_context->getRegExpr(definition.data());
                int index = patten.indexIn(text);
                while(index >= 0) {
                    int length = patten.matchedLength();
                    const QTextCharFormat &format = definition->itemData(m_context->attribute())->getFormat();
                    setFormat(index, length, format);
                    index = patten.indexIn(text, index + length);
                }
            }
                break;
        }
    }

    // check comment
//    setCurrentBlockState(0);
//    int startIndex = 0;
//    if (previousBlockState() != 1)
//        startIndex = commentStartExpression.indexIn(text);
//    while (startIndex >= 0) {
//        int endIndex = commentEndExpression.indexIn(text, startIndex);
//        int commentLength;
//        if (endIndex == -1) {
//            setCurrentBlockState(1);
//            commentLength = text.length() - startIndex;
//        } else {
//            commentLength = endIndex - startIndex
//                            + commentEndExpression.matchedLength();
//        }
//        setFormat(startIndex, commentLength, multiLineCommentFormat);
//        startIndex = commentStartExpression.indexIn(text, startIndex + commentLength);
//    }

}
