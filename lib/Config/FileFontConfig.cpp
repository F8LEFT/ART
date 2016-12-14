//===- FileFontConfig.cpp - ART-GUI Config ---------------------*- C++ -*-===//
//
//                     ANDROID REVERSE TOOLKIT
//
// This file is distributed under the GNU GENERAL PUBLIC LICENSE
// V3 License. See LICENSE.TXT for details.
//
//===---------------------------------------------------------------------===//
//
// Editor Font Config
//
//===----------------------------------------------------------------------===//

#include "FileFontConfig.h"


#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>

FileFontConfig::FileFontConfig(QWidget *parent)
        : QWidget(parent)
{
    // init basic item
    m_fontComboBox = new QFontComboBox(this);
    m_fontSizeComboBox = new QComboBox(this);
    m_fontSizeComboBox->setEditable(true);
    m_antialis = new QCheckBox(tr("Antialias"), this);

    int fontSizes[] = {6, 7, 8, 9, 10, 11, 12, 14, 16, 18, 20, 22, 24, 26, 28,
                       36, 48, 72};
    for (auto size: fontSizes) {
        m_fontSizeComboBox->addItem(QString::number(size));
    }

    // connect signal slots
    // TODO get Font config and set
    connect(m_fontComboBox, &QFontComboBox::currentTextChanged, this, &FileFontConfig::fontUpdate);
    connect(m_fontSizeComboBox, &QComboBox::currentTextChanged, this, &FileFontConfig::fontUpdate);
    connect(m_antialis, &QCheckBox::clicked, this, &FileFontConfig::fontUpdate);

    // setup basic ui
    QVBoxLayout* layout = new QVBoxLayout(this);

    QHBoxLayout* mTopHLayout = new QHBoxLayout();
    mTopHLayout->setContentsMargins(0, 0, 0, 0);
    mTopHLayout->addWidget(new QLabel(tr("Family:"), this));
    mTopHLayout->addWidget(m_fontComboBox);
    mTopHLayout->addWidget(new QLabel(tr("Size:"), this));
    mTopHLayout->addWidget(m_fontSizeComboBox);
    mTopHLayout->addStretch();

    layout->addLayout(mTopHLayout);
    layout->addWidget(m_antialis);
    layout->addStretch();

    setLayout(layout);
}

FileFontConfig::~FileFontConfig()
{
}



void FileFontConfig::fontUpdate()
{
    emit formatUpdate(getFont());
}

QFont FileFontConfig::getFont() {
    QFont font = m_fontComboBox->currentFont();
    font.setPixelSize(m_fontSizeComboBox->currentText().toInt());
    if(m_antialis->isChecked()) {
        font.setStyleStrategy(QFont::PreferAntialias);
    }
    return font;
}

void FileFontConfig::setFont(const QFont &font) {
    m_fontComboBox->setCurrentText(font.family());
    m_fontSizeComboBox->setCurrentText(QString::number(font.pixelSize()));
    m_antialis->setChecked(font.styleStrategy() == QFont::PreferAntialias);
}

