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


GeneralHighlight::GeneralHighlight(QTextDocument *parent, QString fileName,
                                   HighLightConfig* config)
        : QSyntaxHighlighter(parent){
    mHl = KateHlManager::self ()->getHlWithFileName (fileName);
    if(mHl != nullptr) {
        qDebug() << "GeneralHighlight: use " << mHl->getIdentifier ()
                 << " for file " << fileName;
    }
    mAttrlist = mHl->attributes ("Theme", config);

    mConfig = config;
    connect(mConfig, SIGNAL(onConfigUpdate()), this, SLOT(hlAttrUpdate()));

}

void GeneralHighlight::highlightBlock(const QString &text) {
    if(mHl == nullptr)
        return;
    if(text.isEmpty ())
        return;

    auto bcurrent = currentBlock ();
    auto bprevious = bcurrent.previous ();
    auto bnext = bcurrent.next ();

    GeneralHlTextData* prevLine = nullptr;
    while(bprevious.isValid ()) {
        if(bprevious.text ().isEmpty ()) {
            bprevious = bprevious.previous ();
            continue;
        }
        GeneralHlTextData* prevLine = (GeneralHlTextData*)bprevious.userData ();
        if(prevLine == nullptr) {
            prevLine = new GeneralHlTextData(bprevious);
        }
        break;
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
    while(bnext.isValid ()) {
        if(bnext.text ().isEmpty ()) {
            bnext = bnext.next ();
            continue;
        }
        nextLine = (GeneralHlTextData*)bnext.userData ();
        if(nextLine == nullptr) {
            nextLine = new GeneralHlTextData(bnext);
        }
        break;
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
                           *mAttrlist.at (attr.attributeValue));
            }
    }
    return;
}

void GeneralHighlight::hlAttrUpdate ()
{
    mHl->reload ();
    mAttrlist = mHl->attributes ("Theme", mConfig);
    rehighlight ();
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
