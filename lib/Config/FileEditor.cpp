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
#include <QMessageBox>
#include <QInputDialog>
#include <QFile>
#include <QTextStream>
#include <utils/ScriptEngine.h>


FileEditor::FileEditor(QWidget *parent)
        : ui(new Ui::FileEditor),
        QWidget(parent)
{
    ui->setupUi(this);


    m_Editor = new SmaliEditor(this);
    m_Editor->setTheme(m_theme);
    m_Editor->openFile("./cfgs/sample.smali");
    ((QVBoxLayout*)layout())->addWidget(m_Editor);

    m_textStyleConfig = new FileTextStyleConfig (this);
    ui->mTabWidget->addTab (m_textStyleConfig, tr("TextStyle"));
    m_editorColorConfig = new FileEditorColorConfig(this);
    ui->mTabWidget->addTab(m_editorColorConfig, tr("EditorRole"));
    m_fontConfig = new FileFontConfig(this);
    ui->mTabWidget->addTab(m_fontConfig, tr("Font"));

    m_theme.makeData();
    auto theme = m_repository.theme(ConfigString("Highlight","Theme"));
    if(!theme.isValid()) {
        theme = palette().color(QPalette::Base).lightness() < 128
                ? m_repository.defaultTheme(KSyntaxHighlighting::Repository::DarkTheme)
                : m_repository.defaultTheme(KSyntaxHighlighting::Repository::LightTheme);
    }

    QFont font;
    font.setFamily(ConfigString("Highlight","Font"));
    font.setPixelSize(ConfigUint("Highlight", "FontSize"));
    if(ConfigBool("Highlight", "Antialias")) {
        font.setStyleStrategy(QFont::PreferAntialias);
    }
    m_fontConfig->setFont(font);
    m_Editor->setFont(font);

    setTheme(theme);
    setupThemeGroup();

    // connect signal slots
    connect(m_textStyleConfig, &FileTextStyleConfig::formatUpdate, [this](){
        m_Editor->setTheme(m_theme);
    });
    connect(m_editorColorConfig, &FileEditorColorConfig::formatUpdate, [this](){
        m_Editor->setTheme(m_theme);
    });
    connect(m_fontConfig, &FileFontConfig::formatUpdate, [this](QFont font){
        m_Editor->setFont(font);
    });

}

FileEditor::~FileEditor()
{
    delete ui;
}


void FileEditor::save ()
{
    auto fileName = m_theme.name();

    if(!m_theme.isReadOnly()) {
        QFile file(GetCfgsPath ("themes/" + fileName + ".theme"));
        if(file.open(QFile::WriteOnly | QFile::Truncate | QFile::Text)) {
            QMessageBox::warning(nullptr, tr("Save Error"),
                                 tr("Unable to save config to file!!"));
            file.write(m_theme.getThemeConfig());
            file.close();
        }
        m_repository.reload();
    }

    Config()->setString("Highlight","Theme", fileName);
    auto font = m_fontConfig->getFont();
    Config()->setString("Highlight", "Font", font.family());
    Config()->setUint("Highlight", "FontSize", font.pixelSize());
    Config()->setBool("Highlight", "Antialias", font.styleStrategy() == QFont::PreferAntialias);

    ScriptEngine* engine = ScriptEngine::instance();
    emit engine->repaint(QStringList());
}


void FileEditor::setupThemeGroup()
{
    auto themes = m_repository.themes();
    for(auto& theme: themes) {
        ui->mSchemeComboBox->addItem(theme.name());
    }

    ui->mSchemeComboBox->setCurrentText(m_theme.name());

    connect(ui->mCopyBtn, &QPushButton::clicked, this, &FileEditor::onSchemeCopyBtnClick);
    connect(ui->mDeleteBtn, &QPushButton::clicked, this, &FileEditor::onSchemeDeleteBtnClick);
    connect(ui->mSchemeComboBox, &QComboBox::currentTextChanged, [this](const QString& name){
        auto theme = m_repository.theme(name);
        if(theme.isValid()) {
            setTheme(theme);  // update all theme config
        }
    });
}


void FileEditor::onSchemeCopyBtnClick ()
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

void FileEditor::onSchemeDeleteBtnClick ()
{
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

void FileEditor::setTheme(KSyntaxHighlighting::Theme theme)
{
    m_theme.loadFromJson(theme.getThemeConfig());
    if(m_theme.isReadOnly()) {
        ui->mDeleteBtn->setEnabled(false);
    } else {
        ui->mDeleteBtn->setEnabled(true);
    }
    m_textStyleConfig->setTheme(m_theme);
    m_editorColorConfig->setTheme(m_theme);
    m_Editor->setTheme(m_theme);
}
