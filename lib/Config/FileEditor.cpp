//===- FileEditor.cpp - ART-GUI Config--------------------------*- C++ -*-===//
//
//                     ANDROID REVERSE TOOLKIT
//
// This file is distributed under the GNU GENERAL PUBLIC LICENSE
// V3 License. See LICENSE.TXT for details.
//
//===---------------------------------------------------------------------===//
#include "FileEditor.h"
#include "ui_FileEditor.h"

#include <utils/StringUtil.h>
#include <utils/Configuration.h>


FileEditor::FileEditor(QWidget *parent)
        : ui(new Ui::FileEditor),
        QWidget(parent)
{
    ui->setupUi(this);

    mSmaliScheme = new FileSchemeConfig (this,
                                              ConfigString("Highlight","SmaliHighlight"),
                                              "./cfgs/sample.smali");
    ui->mTabWidget->addTab (mSmaliScheme, tr("SmaliScheme"));

}

FileEditor::~FileEditor()
{
    delete ui;
}


void FileEditor::save ()
{
    mSmaliScheme->save();
}
