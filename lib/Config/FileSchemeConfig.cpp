//===- FileSchemeConfig.cpp - ART-GUI Config -------------------*- C++ -*-===//
//
//                     ANDROID REVERSE TOOLKIT
//
// This file is distributed under the GNU GENERAL PUBLIC LICENSE
// V3 License. See LICENSE.TXT for details.
//
//===---------------------------------------------------------------------===//

#include "FileSchemeConfig.h"
#include "ui_FileSchemeConfig.h"

#include <utils/StringUtil.h>

#include <QDebug>
#include <QColorDialog>
#include <QBrush>
#include <utils/Configuration.h>
#include <QInputDialog>
#include <QtWidgets/QMessageBox>
#include <HighLighter/HighLighter.h>

FileSchemeConfig::FileSchemeConfig (QWidget *parent,const QString &cfgDir,
                                    const QString &defName,const QString &sampleFile,
                                    HighLightConfig::CfgType type)
        : ui(new Ui::FileSchemeConfig),
          QWidget(parent), mForegroundColor(Qt::black), mBackgroundColor(Qt::black),
          mUnderlineColor(Qt::black), mCurrentConfig(nullptr), mHighlight(nullptr)
{
    ui->setupUi(this);

    mCfgDir = cfgDir;
    mCfgType = type;
    mDefName = defName;
    mSampleFile = sampleFile;


    ui->mColorEditor->setLineWrapMode(QPlainTextEdit::NoWrap);

    QFile file(mSampleFile);
    if(file.open (QFile::ReadOnly | QFile::Text)) {
        ui->mColorEditor->setPlainText (file.readAll ());
        ui->mColorEditor->setReadOnly (true);
    }

    initSizeCombobox ();
    initColorListWidget ();
    initUnderlineCombobox ();
    initSchemeCombobox ();

    // signal slots
    connect(ui->mForegroundColorBtn, SIGNAL(clicked(bool)),
            this, SLOT(onForegroundColorBtnClick()));
    connect(ui->mForegroundClearBtn, SIGNAL(clicked(bool)),
            this, SLOT(onForegroundClearBtnClick()));
    connect(ui->mBackgroundColorBtn, SIGNAL(clicked(bool)),
            this, SLOT(onBackgroundColorBtnClick()));
    connect(ui->mBackgroundClearBtn, SIGNAL(clicked(bool)),
            this, SLOT(onBackgroundClearBtnClick()));
    connect(ui->mUnderlineColorBtn, SIGNAL(clicked(bool)),
            this, SLOT(onUnderlineColorBtnClick()));
    connect(ui->mUnderlineClearBtn, SIGNAL(clicked(bool)),
            this, SLOT(onUnderlineClearBtnClick()));


    connect (ui->mForegroundColorBtn, SIGNAL(clicked(bool)),
             this, SLOT(onFormatUpdate ()));
    connect (ui->mForegroundClearBtn, SIGNAL(clicked(bool)),
             this, SLOT(onFormatUpdate ()));
    connect(ui->mBackgroundColorBtn, SIGNAL(clicked(bool)),
            this, SLOT(onFormatUpdate ()));
    connect (ui->mBackgroundClearBtn, SIGNAL(clicked(bool)),
             this, SLOT(onFormatUpdate ()));
    connect (ui->mUnderlineColorBtn, SIGNAL(clicked(bool)),
             this, SLOT(onFormatUpdate ()));
    connect(ui->mUnderlineClearBtn, SIGNAL(clicked(bool)),
            this, SLOT(onFormatUpdate ()));
    connect (ui->mUnderlineCombobox, SIGNAL(currentIndexChanged(int)),
             this, SLOT(onFormatUpdate ()));
    connect (ui->mFontComboBox, SIGNAL(currentIndexChanged(int)),
             this, SLOT(onFormatUpdate()));
    connect(ui->mSizeComboBox, SIGNAL(currentTextChanged(const QString &)),
            this, SLOT(onFormatUpdate()));
    connect (ui->mZoomCombobox, SIGNAL(currentIndexChanged(int)),
             this, SLOT(onFormatUpdate()));
    connect(ui->mAntialiasCheckBox, SIGNAL(stateChanged(int)),
            this, SLOT(onFormatUpdate ()));
    connect(ui->mItalicCheck,SIGNAL(stateChanged(int)),
            this, SLOT(onFormatUpdate ()));
    connect(ui->mBoldCheck, SIGNAL(stateChanged(int)),
            this, SLOT(onFormatUpdate ()));

    connect(ui->mCopyBtn, SIGNAL(clicked(bool)),
            this, SLOT(onSchemeCopyBtnClick ()));
    connect(ui->mDeleteBtn, SIGNAL(clicked(bool)),
            this, SLOT(onSchemeDeleteBtnClick ()));

    ui->mColorListWidget->setCurrentRow (0);

}

FileSchemeConfig::~FileSchemeConfig()
{
    delete ui;
}


void FileSchemeConfig::onForegroundColorBtnClick()
{
    QColor color;
    color = QColorDialog::getColor(mForegroundColor, this);
    if(color.isValid ()) {
        mForegroundColor = color;
        QString style = "background-color: " + color.name ();
        ui->mForegroundColorBtn->setStyleSheet (style);
        ui->mColorListWidget->currentItem ()->setForeground (mForegroundColor);
    }
}

void FileSchemeConfig::onForegroundClearBtnClick()
{
    mForegroundColor = Qt::transparent;
    ui->mForegroundColorBtn->setStyleSheet ("");

    ui->mColorListWidget->currentItem ()->setForeground (mForegroundColor);
}

void FileSchemeConfig::onBackgroundColorBtnClick()
{
    QColor color;
    color = QColorDialog::getColor(mBackgroundColor, this);
    if(color.isValid ()) {
        mBackgroundColor = color;
        QString style = "background-color: " + color.name ();
        ui->mBackgroundColorBtn->setStyleSheet (style);
        ui->mColorListWidget->currentItem ()->setBackgroundColor (mBackgroundColor);
    }
}

void FileSchemeConfig::onBackgroundClearBtnClick()
{
    mBackgroundColor = Qt::transparent;

    ui->mBackgroundColorBtn->setStyleSheet ("");

    ui->mColorListWidget->currentItem ()->setBackgroundColor (mBackgroundColor);
}

void FileSchemeConfig::onUnderlineColorBtnClick()
{
    QColor color;
    color = QColorDialog::getColor(mUnderlineColor, this);
    if(color.isValid ()) {
        mUnderlineColor = color;
        QString style = "background-color: " + color.name ();
        ui->mUnderlineColorBtn->setStyleSheet (style);
    }
}

void FileSchemeConfig::onUnderlineClearBtnClick()
{
    mUnderlineColor = Qt::transparent;
    ui->mUnderlineColorBtn->setStyleSheet ("");
}

void FileSchemeConfig::onColorListItemChange(
        QListWidgetItem *current, QListWidgetItem *prev)
{
    if(current == nullptr)
        return;
    int type = current->type ();
    auto &format = mCurrentConfig->mFormatMap[type];
    auto fColor = format.foreground ().color ();
    auto bColor = format.background ().color ();
    auto uColor = format.underlineColor ();
    auto uType = format.underlineStyle ();
    auto font = format.font ();

    if(fColor.isValid ()) {
        mForegroundColor = fColor;
        QString style = "background-color: " + fColor.name ();
        ui->mForegroundColorBtn->setStyleSheet (style);
    } else {
        ui->mForegroundColorBtn->setStyleSheet ("");
    }
    if(bColor.isValid ()) {
        mBackgroundColor = bColor;
        QString style = "background-color: " + bColor.name ();
        ui->mBackgroundColorBtn->setStyleSheet (style);
    } else {
        ui->mBackgroundColorBtn->setStyleSheet ("");
    }
    if(uColor.isValid ()) {
        mUnderlineColor = uColor;
        QString style = "background-color: " + uColor.name ();
        ui->mUnderlineColorBtn->setStyleSheet (style);
    } else {
        ui->mUnderlineColorBtn->setStyleSheet ("");
    }
    ui->mUnderlineCombobox->setCurrentIndex ((int)uType);
    ui->mFontComboBox->setFont (font.family ());
    ui->mItalicCheck->setChecked (font.italic ());
    ui->mBoldCheck->setChecked (font.bold ());
    ui->mAntialiasCheckBox->setChecked (
            font.styleStrategy () == QFont::PreferAntialias);
    ui->mSizeComboBox->setEditText (QString::number (font.pointSize ()));

}

void FileSchemeConfig::onSchemeComboboxChange (const QString &text)
{
    if(mCurrentConfig != nullptr) {
        mCurrentConfig->deleteLater ();
        mCurrentConfig = nullptr;
    }
    if(mHighlight != nullptr) {
        mHighlight->deleteLater ();
        mHighlight = nullptr;
    }
    mCurrentConfig = new HighLightConfig(
            mCfgDir + "/" + text, mCfgType, this);
    mHighlight = setHighLighter (ui->mColorEditor->document (), mSampleFile,
                                 mCurrentConfig);

    auto colorCount = ui->mColorListWidget->count ();
    for(auto i = 0; i < colorCount; i++) {
        auto item = ui->mColorListWidget->item (i);
        auto &format = mCurrentConfig->mFormatMap[item->type ()];
        item->setForeground (format.foreground ());
        item->setBackground (format.background ());
    }

    emit mCurrentConfig->onConfigUpdate ();
}

void FileSchemeConfig::onFormatUpdate()
{
    QTextCharFormat format;
    QFont font = ui->mFontComboBox->currentFont ();
    font.setBold (ui->mBoldCheck->isChecked ());
    font.setItalic (ui->mItalicCheck->isChecked ());
    if(ui->mAntialiasCheckBox->isChecked ()) {
        font.setStyleStrategy (QFont::PreferAntialias);
    } else {
        font.setStyleStrategy (QFont::NoAntialias);
    }
    font.setBold (ui->mBoldCheck->isChecked ());
    font.setPointSize (ui->mSizeComboBox->currentText ().toInt ());

    format.setFont (font);

    if(mForegroundColor.isValid ()) {
        format.setForeground (QBrush(mForegroundColor));
    }
    if(mBackgroundColor.isValid ()){
        format.setBackground (QBrush(mBackgroundColor));
    }
    format.setFontUnderline (true);
    format.setUnderlineStyle ((QTextCharFormat::UnderlineStyle)
                                      ui->mUnderlineCombobox->currentData ().toInt ());
    if(mUnderlineColor.isValid ()) {
        format.setUnderlineColor (mUnderlineColor);
    }



    mCurrentConfig->mFormatMap[ui->mColorListWidget->currentItem ()->type ()] = format;
    emit mCurrentConfig->onConfigUpdate ();
}

void FileSchemeConfig::onSchemeCopyBtnClick ()
{
    auto curScheme = ui->mSchemeComboBox->currentText ();

    bool doCopy;
    auto fileName = QInputDialog::getText(nullptr, tr("Input filename"),
                                          tr("Please input your scheme name"), QLineEdit::Normal,
                                          curScheme ,&doCopy);
    if(doCopy) {
        if(!fileName.endsWith (".xml")) {
            fileName += ".xml";
        }
        if(ui->mSchemeComboBox->findText (fileName) != -1) {
            QMessageBox::warning(nullptr, tr("Copy Error"),
                                 tr("you must input a different file name!"));
            return;
        }
        if(!QFile::copy (GetCfgsPath ("smaliTheme/" + curScheme),
                         GetCfgsPath ("smaliTheme/" + fileName))) {
            QMessageBox::warning(nullptr, tr("Copy Error"),
                                 tr("Some error occurred while copying file!"));
            return;
        }
        ui->mSchemeComboBox->addItem (fileName);
        ui->mSchemeComboBox->setCurrentText (fileName);
    }
}

void FileSchemeConfig::onSchemeDeleteBtnClick ()
{
    auto curScheme = ui->mSchemeComboBox->currentText ();
    if(curScheme == "default.xml") {
        QMessageBox::warning (nullptr, tr("Delete Error"),
                              tr("You can't delete default scheme file"));
        return;
    }
    auto doDelete = QMessageBox::information( this, tr("Delete Scheme"),
                                              tr("Do you really want to delete ") + curScheme + "?",
                                              tr("No"), tr("Yes"),
                                              0, 1 );
    if(!doDelete)
        return;;

    ui->mSchemeComboBox->setCurrentText ("default.xml");
    QFile file(GetCfgsPath ("smaliTheme/" + curScheme));
    if(!file.remove ()) {
        QMessageBox::warning(nullptr, tr("Delete Error"),
                             tr("Some error occurred while deleting file!"));
    } else {
        ui->mSchemeComboBox->removeItem (
                ui->mSchemeComboBox->findText (curScheme));
    }

}

void FileSchemeConfig::initColorListWidget ()
{
    auto widget = ui->mColorListWidget;
    for(auto i = 0; i < HighLightConfig::getFormatSize (mCfgType); i++) {
            widget->addItem (new QListWidgetItem(
                    HighLightConfig::getFormatName (i,mCfgType, true), widget,i));
    }


    connect(ui->mColorListWidget, SIGNAL(currentItemChanged(QListWidgetItem*,QListWidgetItem*)),
            this, SLOT(onColorListItemChange(QListWidgetItem*,QListWidgetItem*)));


}

void FileSchemeConfig::initUnderlineCombobox ()
{
    auto combobox = ui->mUnderlineCombobox;
    combobox->addItem (tr("No Underline"), QTextCharFormat::NoUnderline);
    combobox->addItem (tr("Single Underline"), QTextCharFormat::SingleUnderline);
    combobox->addItem (tr("Dot Underline"), QTextCharFormat::DotLine);
    combobox->addItem (tr("Dash Underline"), QTextCharFormat::DashUnderline);
    combobox->addItem (tr("Dash-Dot Underline"), QTextCharFormat::DashDotLine);
    combobox->addItem (tr("Dash-Dot-Dot Underline"), QTextCharFormat::DashDotDotLine);
    combobox->addItem (tr("Wave Underline"), QTextCharFormat::WaveUnderline);

}

void FileSchemeConfig::initSizeCombobox ()
{
    auto combobox = ui->mSizeComboBox;
    combobox->addItem ("6");
    combobox->addItem ("7");
    combobox->addItem ("8");
    combobox->addItem ("9");
    combobox->addItem ("10");
    combobox->addItem ("11");
    combobox->addItem ("12");
    combobox->addItem ("14");
    combobox->addItem ("16");
    combobox->addItem ("18");
    combobox->addItem ("20");
    combobox->addItem ("22");
    combobox->addItem ("24");
    combobox->addItem ("26");
    combobox->addItem ("28");
    combobox->addItem ("36");
    combobox->addItem ("48");
    combobox->addItem ("72");
}

void FileSchemeConfig::initSchemeCombobox ()
{
    connect(ui->mSchemeComboBox, SIGNAL(currentTextChanged(const QString &)),
            this, SLOT(onSchemeComboboxChange (const QString &)));

    auto combobox = ui->mSchemeComboBox;
    QDir dir(mCfgDir);
    if (dir.exists()) {
        dir.setFilter(QDir::Files | QDir::NoSymLinks);
                foreach(QFileInfo mfi ,dir.entryInfoList())
            {
                if(mfi.isFile ())
                {
                    if(mfi.fileName ().endsWith (".xml")) {
                        combobox->addItem (mfi.fileName ());
                    }
                }
            }
    }

    if(combobox->findText ("default.xml") == -1) {
        combobox->addItem ("default.xml");
    }
    auto curTheme = mDefName;
    if(curTheme.isEmpty ())
        curTheme = "default.xml";
    auto index = combobox->findText (curTheme);
    if(index == -1) {
        combobox->setCurrentText ("default.xml");
    } else {
        combobox->setCurrentIndex (index);
    }
}


void FileSchemeConfig::save ()
{
    auto cfg = Config ();
    mCurrentConfig->save ();
    auto configFileName = QFileInfo(mCurrentConfig->mSetFile).fileName ();
    if(mCfgType == HighLightConfig::SMALI) {
        cfg->setString ("Highlight", "SmaliHighlight", configFileName);
    } else {
        cfg->setString ("Highlight", "GenHighlight", configFileName);
    }

    auto pHighLightConfig = HighLightConfig::instance (
            mCfgType, mCfgDir + "/" + configFileName);
    pHighLightConfig->mFormatMap = mCurrentConfig->mFormatMap;
    pHighLightConfig->onConfigUpdate ();
}
