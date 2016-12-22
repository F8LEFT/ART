//===- FileTextStyleConfig.cpp - ART-GUI Config ----------------*- C++ -*-===//
//
//                     ANDROID REVERSE TOOLKIT
//
// This file is distributed under the GNU GENERAL PUBLIC LICENSE
// V3 License. See LICENSE.TXT for details.
//
//===---------------------------------------------------------------------===//
#include "FileTextStyleConfig.h"

#include <utils/StringUtil.h>
#include <themedata_p.h>

#include <QDebug>
#include <QColorDialog>
#include <QBrush>
#include <utils/Configuration.h>
#include <QInputDialog>
#include <QtWidgets/QMessageBox>
#include <QStandardPaths>
#include <QPainter>
#include <QtWidgets>
#include <EditorTab/SmaliEditor.h>

FileTextStyleConfig::FileTextStyleConfig (QWidget *parent)
        : QWidget(parent)
{
    // init sub item
    m_foreground = new ColorItem(this, tr("Foreground"));
    m_background = new ColorItem(this, tr("Background"));
    m_bold = new QCheckBox(tr("Bold"), this);
    m_italic = new QCheckBox(tr("Italic"), this);
    m_underline = new QCheckBox(tr("Underline"), this);
    m_strikThrough = new QCheckBox(tr("StrikThrough"), this);

    m_colorList = new QListWidget(this);
    for(int i = 0; i < (int)KSyntaxHighlighting::Theme::TextStyle::Others; i++) {
        m_colorList->addItem(new QListWidgetItem(
                KSyntaxHighlighting::Theme::getTextStyleName(i, true), m_colorList, i));
    }
    // connect signal slot
    m_colorList->setCurrentRow(0);

    connect(m_colorList, &QListWidget::currentItemChanged,
            [this](QListWidgetItem *current, QListWidgetItem *previous) {
                auto style = (KSyntaxHighlighting::Theme::TextStyle)current->type();
                m_foreground->setColor(m_theme.textColor(style));
                m_background->setColor(m_theme.backgroundColor(style));
                m_bold->setChecked(m_theme.isBold(style));
                m_italic->setChecked(m_theme.isItalic(style));
                m_underline->setChecked(m_theme.isUnderline(style));
                m_strikThrough->setChecked(m_theme.isStrikeThrough(style));
            });

    connect(m_foreground, &ColorItem::colorChanged, [this](QRgb rgb) {
        auto style = (KSyntaxHighlighting::Theme::TextStyle)m_colorList->currentItem()->type();
        m_theme.setTextColor(style, rgb);
         formatUpdate();
    });

    connect(m_background, &ColorItem::colorChanged, [this](QRgb rgb) {
        auto style = (KSyntaxHighlighting::Theme::TextStyle)m_colorList->currentItem()->type();
        m_theme.setBackgroundColor(style, rgb);
         formatUpdate();
    });

    connect(m_bold, &QCheckBox::clicked, [this](bool checked){
        auto style = (KSyntaxHighlighting::Theme::TextStyle)m_colorList->currentItem()->type();
        m_theme.setBold(style, checked);
         formatUpdate();
    });

    connect(m_italic, &QCheckBox::clicked, [this](bool checked){
        auto style = (KSyntaxHighlighting::Theme::TextStyle)m_colorList->currentItem()->type();
        m_theme.setItalic(style, checked);
         formatUpdate();
    });

    connect(m_underline, &QCheckBox::clicked, [this](bool checked){
        auto style = (KSyntaxHighlighting::Theme::TextStyle)m_colorList->currentItem()->type();
        m_theme.setUnderline(style, checked);
         formatUpdate();
    });

    connect(m_strikThrough, &QCheckBox::clicked, [this](bool checked){
        auto style = (KSyntaxHighlighting::Theme::TextStyle)m_colorList->currentItem()->type();
        m_theme.setStrikeThrough(style, checked);
         formatUpdate();
    });

    // setup basic ui;
    QVBoxLayout* vLayout = new QVBoxLayout(this);
    QHBoxLayout* hTopLayout = new QHBoxLayout();

    QVBoxLayout* m_colorConfigLayout = new QVBoxLayout();

    m_colorConfigLayout->addWidget(m_foreground);
    m_colorConfigLayout->addWidget(m_background);

    QHBoxLayout* checkBoxLayout = new QHBoxLayout();
    checkBoxLayout->addWidget(m_bold); checkBoxLayout->addWidget(m_italic);
    m_colorConfigLayout->addLayout(checkBoxLayout);
    checkBoxLayout = new QHBoxLayout();
    checkBoxLayout->addWidget(m_underline); checkBoxLayout->addWidget(m_strikThrough);
    m_colorConfigLayout->addLayout(checkBoxLayout);

    hTopLayout->addWidget(m_colorList);
    hTopLayout->addLayout(m_colorConfigLayout);
    vLayout->addLayout(hTopLayout);

    setLayout(vLayout);
}

FileTextStyleConfig::~FileTextStyleConfig()
{
}

void FileTextStyleConfig::setTheme(KSyntaxHighlighting::Theme theme)
{
    m_theme = theme;

    {
        bool enable = !m_theme.isReadOnly();
        m_foreground->setEnabled(enable);
        m_background->setEnabled(enable);
        m_bold->setEnabled(enable);
        m_italic->setEnabled(enable);
        m_underline->setEnabled(enable);
        m_strikThrough->setEnabled(enable);
    }

    // refresh all color list item data
    for(int i = 0; i < (int)KSyntaxHighlighting::Theme::TextStyle::Others; i++) {
        auto style = (KSyntaxHighlighting::Theme::TextStyle)i;
        auto* item = m_colorList->item(i);
        auto foreground = m_theme.textColor(style);
        if(foreground != 0) {
            item->setForeground(QBrush(foreground));
        }
        auto background = m_theme.backgroundColor(style);
        if(background != 0) {
            item->setBackground(QBrush(background));
        }

        QFont font;
        font.setBold(m_theme.isBold(style));
        font.setItalic(m_theme.isItalic(style));
        font.setUnderline(m_theme.isUnderline(style));
        font.setStrikeOut(m_theme.isStrikeThrough(style));
        item->setFont(font);
    }

    m_colorList->currentItemChanged(m_colorList->currentItem(), nullptr);
}
