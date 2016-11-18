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

    auto* smaliScmeme = new FileSchemeConfig (this,GetCfgsPath ("smaliTheme"),
                                              ConfigString("Highlight","SmaliHighlight"),
                                              "./cfgs/sample.smali",
                                              HighLightConfig::SMALI);
    ui->mTabWidget->addTab (smaliScmeme, tr("SmaliScheme"));
    mTabs.push_back (smaliScmeme);

    auto* genScmeme = new FileSchemeConfig (this,GetCfgsPath ("genHlTheme"),
                                            ConfigString("Highlight","GenHighlight"),
                                            "./cfgs/sample.xml",HighLightConfig::GENERAL);
    ui->mTabWidget->addTab (genScmeme, tr("GeneralScheme"));
    mTabs.push_back (genScmeme);


}

FileEditor::~FileEditor()
{
    delete ui;
}


void FileEditor::save ()
{
    foreach(FileSchemeConfig* tab, mTabs) {
            tab->save ();
        }
}
