//===- Config.cpp - ART-GUI Config -----------------------------*- C++ -*-===//
//
//                     ANDROID REVERSE TOOLKIT
//
// This file is distributed under the GNU GENERAL PUBLIC LICENSE
// V3 License. See LICENSE.TXT for details.
//
//===---------------------------------------------------------------------===//
#include "Config/Config.h"
#include "ui_Config.h"

#include "FileEditor.h"

#include <QGridLayout>


Config::Config(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Config)
{
    ui->setupUi(this);

    mFileEditor = new FileEditor((QWidget*)this);

    mWidgetList.push_back (mFileEditor);
    mWidgetNativeNameList.push_back (tr("Text Editot"));
    mIconList.push_back (QIcon(QPixmap(":/images/editorsettings.png")));

    ui->mConfigWidget->layout ()->addWidget (mFileEditor);

    for(int i = 0, count = mWidgetList.size (); i < count; i++) {
        ui->mConfigList->addItem (
                new QListWidgetItem(mIconList[i], mWidgetNativeNameList[i],
                ui->mConfigList));
        ui->mConfigWidget->layout()->addWidget(mWidgetList[i]);
        mWidgetList[i]->hide ();
    }

    connect(ui->mConfigList, SIGNAL(currentItemChanged(QListWidgetItem*, QListWidgetItem*)),
            this, SLOT(onConfigTabChange (QListWidgetItem*, QListWidgetItem*)));

    connect(ui->buttonBox, SIGNAL(accepted ()), mFileEditor, SLOT(save()));
    connect((const QObject*)ui->buttonBox->button (QDialogButtonBox::Apply), SIGNAL(clicked()),
            mFileEditor, SLOT(save()));

    ui->mConfigList->setCurrentRow (0);
}

Config::~Config()
{
    delete ui;
}

void Config::onConfigTabChange (QListWidgetItem *current,QListWidgetItem *previous)
{
    if(previous != nullptr){
        auto name = previous->text ();
        auto idx = mWidgetNativeNameList.indexOf (name);
        if(idx != -1)
            mWidgetList[idx]->hide ();
    }
    if(current != nullptr){
        auto name = current->text ();
        auto idx = mWidgetNativeNameList.indexOf (name);
        if(idx != -1)
            mWidgetList[idx]->show ();
        ui->mWidgetTitle->setText (name);
    }
}
