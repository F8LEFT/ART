//===- GeneralHighlight.cpp - ART-GUI HighLighter---------------*- C++ -*-===//
//
//                     ANDROID REVERSE TOOLKIT
//
// This file is distributed under the GNU GENERAL PUBLIC LICENSE
// V3 License. See LICENSE.TXT for details.
//
//===---------------------------------------------------------------------===//
#include "GeneralHighlight.h"
#include "KateHighlight/katesyntaxmanager.h"
#include <QDebug>


GeneralHighlight::GeneralHighlight(QTextDocument *parent, QString fileName)
        : QSyntaxHighlighter(parent){
    mHl = KateHlManager::self ()->getHlWithFileName (fileName);
    if(mHl != nullptr) {
        qDebug() << "GeneralHighlight: use " << mHl->getIdentifier ()
                 << " for file " << fileName;
    }
    mHl->getKateExtendedAttributeListCopy ("", mAttrlist);
}

void GeneralHighlight::highlightBlock(const QString &text) {
    if(mHl == nullptr)
        return;
    auto bcurrent = currentBlock ();
    auto bprevious = bcurrent.previous ();
    auto bnext = bcurrent.next ();

    GeneralHlTextData* prevLine = nullptr;
    if(bprevious.isValid ()) {
        GeneralHlTextData* prevLine = (GeneralHlTextData*)bprevious.userData ();
        if(prevLine == nullptr) {
            prevLine = new GeneralHlTextData(bprevious);
        }
    }

    GeneralHlTextData* textLine = nullptr;
    if(bcurrent.isValid ()) {
        textLine = (GeneralHlTextData*)bcurrent.userData ();
        if(textLine == nullptr) {
            textLine = new GeneralHlTextData(bcurrent);
        } else {
            textLine->mTextData->setText (text);
        };
    }

    GeneralHlTextData* nextLine = nullptr;
    if(bnext.isValid ()) {
        nextLine = (GeneralHlTextData*)bnext.userData ();
        if(nextLine == nullptr) {
            nextLine = new GeneralHlTextData(bnext);
        }
    }

    bool ctxChange = false;
    mHl->doHighlight (prevLine != nullptr? prevLine->mTextData: nullptr,
                      textLine->mTextData,
                      nextLine != nullptr? nextLine->mTextData: nullptr,
                      ctxChange);
    if(textLine != nullptr) {
        foreach(const Kate::TextLineData::Attribute& attr,
                textLine->mTextData->attributesList ()) {
                setFormat (attr.offset, attr.length,
                           mAttrlist.at (attr.attributeValue)->toCharFormat ());
            }
    }
    return;

    //    auto ctx = definition->context();
//    for(auto &m_context : ctx) {
//        switch (m_context->type()) {
//            case Context::Keyword: {
//                QString str = m_context->name();
//                QRegExp patten = m_context->getRegExpr(definition.data());
//                int index = patten.indexIn(text);
//                if (m_context->region() == "BeginRegion") {
//                    if (index >= 0) {
//                        int length = patten.matchedLength();
//                        const QTextCharFormat &format = definition->itemData(m_context->attribute())->getFormat();
//                        setFormat(index, length, format);
//                    }
//                } else {
//                    while(index >= 0) {
//                        int length = patten.matchedLength();
//                        const QTextCharFormat &format = definition->itemData(m_context->attribute())->getFormat();
//                        setFormat(index, length, format);
//                        index = patten.indexIn(text, index + length);
//                    }
//                }
//            }
//                break;
//            case Context::RegExpr: {
//                QString str = m_context->name();
//
//                QRegExp patten = m_context->getRegExpr(definition.data());
//                int index = patten.indexIn(text);
//                while(index >= 0) {
//                    int length = patten.matchedLength();
//                    const QTextCharFormat &format = definition->itemData(m_context->attribute())->getFormat();
//                    setFormat(index, length, format);
//                    index = patten.indexIn(text, index + length);
//                }
//            }
//                break;
//        }
//    }

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

GeneralHlTextData::GeneralHlTextData (QTextBlock& b)
{
    mTextData = new Kate::TextLineData(b.text ());
    b.setUserData (this);
}

GeneralHlTextData::~GeneralHlTextData ()
{
    delete mTextData;
}
