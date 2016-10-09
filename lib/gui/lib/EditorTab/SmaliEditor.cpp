//===- SmaliEditor.cpp - ART-GUI Editor Tab ----------------------*- C++ -*-===//
//
//                     ANDROID REVERSE TOOLKIT
//
// This file is distributed under the GNU GENERAL PUBLIC LICENSE
// V3 License. See LICENSE.TXT for details.
//
//===---------------------------------------------------------------------===//
#include "SmaliEditor.h"

#include <utils/Configuration.h>


#include <QtWidgets/QGridLayout>

SmaliEditor::SmaliEditor (QWidget *parent):Editor (parent)
{
    mHintEdit = new QPlainTextEdit(this);
    loadFromConfig();
}

SmaliEditor::~SmaliEditor ()
{
    saveToConfig();
}

void SmaliEditor::setTextLayout ()
{
    QLayout* layout = new QGridLayout(this);
    layout->setContentsMargins (0,0,0,0);
    mVSplitter = new QSplitter(Qt::Orientation::Vertical, this);
    mFileEdit->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Ignored);
    mHintEdit->setSizePolicy (QSizePolicy::Preferred,QSizePolicy::Ignored);
    mVSplitter->addWidget (mFileEdit);
    mVSplitter->addWidget (mHintEdit);
    layout->addWidget (mVSplitter);
    setLayout (layout);

    mVSplitter->setSizes (mVSplitterSize);
}

void SmaliEditor::loadFromConfig ()
{
    Editor::loadFromConfig ();
    Configuration *config = Config();

    mVSplitterSize << config->getUint ("SmaliEditor", "TopSplitterHeight")
              << config->getUint ("SmaliEditor", "BotSplitterHeight");
}

void SmaliEditor::saveToConfig ()
{
    Editor::saveToConfig ();
    Configuration *config = Config();

    mVSplitterSize = mVSplitter->sizes ();
    config->setUint ("SmaliEditor", "TopSplitterHeight", mVSplitterSize[0]);
    config->setUint ("SmaliEditor", "BotSplitterHeight", mVSplitterSize[1]);

}
