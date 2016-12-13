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

FileSchemeConfig::FileSchemeConfig (QWidget *parent,
                                    const QString &themeName,const QString &sampleFile)
        : ui(new Ui::FileSchemeConfig),
          QWidget(parent)
{
    ui->setupUi(this);
    m_theme.makeData();

    m_sampleFile = sampleFile;
    m_colorEditor = new SmaliEditor(this);
    m_colorEditor->setTheme(m_theme);
    m_colorEditor->openFile(m_sampleFile);

    setupThemeGroup();
    setupFontGroup();
    setupColorGroup();

    themeChanged(themeName);
}

FileSchemeConfig::~FileSchemeConfig()
{
    delete ui;
}


void FileSchemeConfig::save ()
{
//    auto cfg = Config ();
//    mCurrentConfig->save ();
//    auto configFileName = QFileInfo(mCurrentConfig->mSetFile).fileName ();
//    if(mCfgType == HighLightConfig::SMALI) {
//        cfg->setString ("Highlight", "SmaliHighlight", configFileName);
//    } else {
//        cfg->setString ("Highlight", "GenHighlight", configFileName);
//    }
//
//    auto pHighLightConfig = HighLightConfig::instance (
//            mCfgType, mCfgDir + "/" + configFileName);
//    pHighLightConfig->mFormatMap = mCurrentConfig->mFormatMap;
//    pHighLightConfig->onConfigUpdate ();
}

void FileSchemeConfig::setupThemeGroup()
{
    auto themes = m_repository.themes();
    for(auto& theme: themes) {
        ui->mSchemeComboBox->addItem(theme.name());
    }

    connect(ui->mCopyBtn, &QPushButton::clicked, this, &FileSchemeConfig::onSchemeCopyBtnClick);
    connect(ui->mDeleteBtn, &QPushButton::clicked, this, &FileSchemeConfig::onSchemeDeleteBtnClick);
}


void FileSchemeConfig::onSchemeCopyBtnClick ()
{
    auto curScheme = ui->mSchemeComboBox->currentText ();

    bool doCopy;
    auto fileName = QInputDialog::getText(nullptr, tr("Input filename"),
                                          tr("Please input your scheme name"), QLineEdit::Normal,
                                          curScheme ,&doCopy);
    if(doCopy) {
        if(ui->mSchemeComboBox->findText (fileName) != -1) {
            QMessageBox::warning(nullptr, tr("Copy Error"),
                                 tr("you must input a different file name!"));
            return;
        }

        QFile file(GetCfgsPath ("themes/" + fileName + ".theme"));
        if(!file.open(QFile::WriteOnly | QFile::Truncate | QFile::Text)) {
            QMessageBox::warning(nullptr, tr("Copy Error"),
                                 tr("Some error occurred while copying file!"));
            return;
        }

        m_theme.setReadOnly(false);
        m_theme.setName(fileName);

        QTextStream out(&file);
        out << m_theme.getThemeConfig();
        out.flush();
        file.close();

        m_repository.reload();

        ui->mSchemeComboBox->addItem (fileName);
        ui->mSchemeComboBox->setCurrentText (fileName);
    }
}

void FileSchemeConfig::onSchemeDeleteBtnClick ()
{
    if(m_theme.isReadOnly()) {
        QMessageBox::warning (nullptr, tr("Delete Error"),
                              tr("You can't delete default scheme file"));
        return;
    }

    auto curScheme = ui->mSchemeComboBox->currentText ();
    auto doDelete = QMessageBox::information( this, tr("Delete Scheme"),
                                              tr("Do you really want to delete ") + curScheme + "?",
                                              tr("No"), tr("Yes"),
                                              0, 1 );
    if(!doDelete)
        return;;

    QFile file(GetCfgsPath ("themes/" + curScheme + ".theme"));
    if(!file.remove ()) {
        QMessageBox::warning(nullptr, tr("Delete Error"),
                             tr("Some error occurred while deleting file!"));
    } else {
        ui->mSchemeComboBox->removeItem (
                ui->mSchemeComboBox->findText (curScheme));
    }
    m_repository.reload();
    ui->mSchemeComboBox->removeItem (ui->mSchemeComboBox->findText (curScheme));

    // TODO selected latest theme or default theme
}

void FileSchemeConfig::setupFontGroup()
{
    int fontSizes[] = {6, 7, 8, 9, 10, 11, 12, 14, 16, 18, 20, 22, 24, 26, 28,
                       36, 48, 72};
    for (auto size: fontSizes) {
        ui->mSizeComboBox->addItem(QString::number(size));
    }

    connect(ui->mSizeComboBox, SIGNAL(currentTextChanged(QString)), this, SLOT(fontUpdate()));
    connect(ui->mFontComboBox, SIGNAL(currentTextChanged(QString)), this, SLOT(fontUpdate()));
    connect(ui->mAntialiasCheckBox, SIGNAL(clicked(bool)), this, SLOT(fontUpdate()));
}

void FileSchemeConfig::setupColorGroup()
{
    QVBoxLayout* vLayout = new QVBoxLayout();
    QHBoxLayout* hTopLayout = new QHBoxLayout();
    // setup color list
    m_colorList = new QListWidget(this);
    for(int i = 0; i < (int)KSyntaxHighlighting::Theme::TextStyle::Others; i++) {
        m_colorList->addItem(new QListWidgetItem(
                KSyntaxHighlighting::Theme::getTextStyleName(i, true), m_colorList, i));
    }
    QVBoxLayout* m_colorConfigLayout = new QVBoxLayout();

    m_foreground = new ColorItem(this, tr("Foreground"));
    m_background = new ColorItem(this, tr("Background"));
    m_colorConfigLayout->addWidget(m_foreground);
    m_colorConfigLayout->addWidget(m_background);

    m_bold = new QCheckBox(tr("Bold"), this);
    m_italic = new QCheckBox(tr("Italic"), this);
    m_underline = new QCheckBox(tr("Underline"), this);
    m_strikThrough = new QCheckBox(tr("StrikThrough"), this);
    QHBoxLayout* checkBoxLayout = new QHBoxLayout();
    checkBoxLayout->addWidget(m_bold); checkBoxLayout->addWidget(m_italic);
    m_colorConfigLayout->addLayout(checkBoxLayout);
    checkBoxLayout = new QHBoxLayout();
    checkBoxLayout->addWidget(m_underline); checkBoxLayout->addWidget(m_strikThrough);
    m_colorConfigLayout->addLayout(checkBoxLayout);

    hTopLayout->addWidget(m_colorList);
    hTopLayout->addLayout(m_colorConfigLayout);
    vLayout->addLayout(hTopLayout);
    vLayout->addWidget(m_colorEditor);

    ui->mColorGroupBox->setLayout(vLayout);

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
    });

    connect(m_background, &ColorItem::colorChanged, [this](QRgb rgb) {
        auto style = (KSyntaxHighlighting::Theme::TextStyle)m_colorList->currentItem()->type();
        m_theme.setBackgroundColor(style, rgb);
    });

    connect(m_bold, &QCheckBox::clicked, [this](bool checked){
        auto style = (KSyntaxHighlighting::Theme::TextStyle)m_colorList->currentItem()->type();
        m_theme.setBold(style, checked);
    });

    connect(m_italic, &QCheckBox::clicked, [this](bool checked){
        auto style = (KSyntaxHighlighting::Theme::TextStyle)m_colorList->currentItem()->type();
        m_theme.setItalic(style, checked);
    });

    connect(m_underline, &QCheckBox::clicked, [this](bool checked){
        auto style = (KSyntaxHighlighting::Theme::TextStyle)m_colorList->currentItem()->type();
        m_theme.setUnderline(style, checked);
    });

    connect(m_strikThrough, &QCheckBox::clicked, [this](bool checked){
        auto style = (KSyntaxHighlighting::Theme::TextStyle)m_colorList->currentItem()->type();
        m_theme.setStrikeThrough(style, checked);
    });
}

void FileSchemeConfig::themeChanged(const QString &themeName)
{
    auto theme = m_repository.theme(themeName);
    if(!theme.isValid()) {
        m_theme.loadFromJson(m_repository.defaultTheme().getThemeConfig());
    } else {
        m_theme.loadFromJson(theme.getThemeConfig());
    }

    if(m_theme.isReadOnly()) {
        m_foreground->setEnabled(false);
        m_background->setEnabled(false);
        m_bold->setEnabled(false);
        m_italic->setEnabled(false);
        m_underline->setEnabled(false);
        m_strikThrough->setEnabled(false);
    } else {
        m_foreground->setEnabled(true);
        m_background->setEnabled(true);
        m_bold->setEnabled(true);
        m_italic->setEnabled(true);
        m_underline->setEnabled(true);
        m_strikThrough->setEnabled(true);
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
    m_colorEditor->setTheme(m_theme);
}

void FileSchemeConfig::fontUpdate()
{
    // TODO reset font data
}

ColorItem::ColorItem(QWidget *parent, const QString &name):
    QWidget(parent),
    m_rgb(0)
{
    QHBoxLayout* layout = new QHBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);

    QLabel *label = new QLabel(this);
    label->setText(name);
    m_colorBtn = new ColorButton(this);
    m_clearBtn = new QPushButton(this);
    m_clearBtn->setIcon(QIcon(":/images/close.png"));

    layout->addWidget(label);
    layout->addWidget(m_colorBtn);
    layout->addWidget(m_clearBtn);

    setLayout(layout);

    connect(m_colorBtn, &QPushButton::clicked, [this]() {
        QColor color;
        color = QColorDialog::getColor(QColor(m_rgb), this);
        if(color.isValid()) {
            setColor(color.rgb());
            emit colorChanged(m_rgb);
        }
    });

    connect(m_clearBtn, &QPushButton::clicked, [this]() {
        setColor(0);
        emit colorChanged(m_rgb);
    });
}

void ColorItem::setColor(QRgb c)
{
    m_rgb = c;
    m_colorBtn->paintColor(m_rgb);
}

void ColorButton::paintColor(QRgb rgb)
{
    m_rgb = rgb;
    repaint();
}

void ColorButton::paintEvent(QPaintEvent *event) {
    QPushButton::paintEvent(event);

    QPainter painter(this);

    QStyleOptionButton opt;
    opt.rect = rect();
    opt.palette = palette();


    style()->drawControl(QStyle::CE_PushButton, &opt, &painter, this);
    style()->subElementRect(QStyle::SE_PushButtonContents, &opt, this);
    opt.rect.adjust(1, 1, -1, -1);

    if(m_rgb != 0) {
        QColor c(m_rgb);
        painter.fillRect(opt.rect, c);
    } else {
        painter.fillRect(opt.rect, Qt::white);
        painter.drawText(opt.rect, tr("None"), QTextOption(Qt::AlignCenter));
    }

    qDrawShadePanel(&painter, opt.rect, opt.palette, true, 1, NULL);
}
