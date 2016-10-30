#include "FileEditor.h"
#include "ui_FileEditor.h"

#include <utils/StringUtil.h>

#include "SmaliLexer.h"
#include <sstream>


#include <QDebug>
#include <QColorDialog>
#include <QBrush>
#include <utils/Configuration.h>
#include <QInputDialog>
#include <QtWidgets/QMessageBox>

using namespace Analysis;


FileEditor::FileEditor(QWidget *parent) :
    QWidget(parent), mForegroundColor(Qt::black), mBackgroundColor(Qt::black),
    mUnderlineColor(Qt::black), ui(new Ui::FileEditor), mCurrentConfig(nullptr)
{
    ui->setupUi(this);


    QFile file(GetCfgsPath("sample.smali"));
    if(file.open (QFile::ReadOnly | QFile::Text)) {
        ui->mColorEditor->setPlainText (file.readAll ());
        ui->mColorEditor->setReadOnly (true);
    }
    mHighlight = new QuickSmaliHighilght (ui->mColorEditor->document ());

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

    connect(ui->mColorListWidget, SIGNAL(currentItemChanged(QListWidgetItem*,QListWidgetItem*)),
            this, SLOT(onColorListItemChange(QListWidgetItem*,QListWidgetItem*)));

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


}

FileEditor::~FileEditor()
{
    delete ui;
}

void FileEditor::onForegroundColorBtnClick()
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

void FileEditor::onForegroundClearBtnClick()
{
    mForegroundColor = Qt::transparent;
    ui->mForegroundColorBtn->setStyleSheet ("");

    ui->mColorListWidget->currentItem ()->setForeground (mForegroundColor);
}

void FileEditor::onBackgroundColorBtnClick()
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

void FileEditor::onBackgroundClearBtnClick()
{
    mBackgroundColor = Qt::transparent;

    ui->mBackgroundColorBtn->setStyleSheet ("");

    ui->mColorListWidget->currentItem ()->setBackgroundColor (mBackgroundColor);
}

void FileEditor::onUnderlineColorBtnClick()
{
    QColor color;
    color = QColorDialog::getColor(mUnderlineColor, this);
    if(color.isValid ()) {
        mUnderlineColor = color;
        QString style = "background-color: " + color.name ();
        ui->mUnderlineColorBtn->setStyleSheet (style);
    }
}

void FileEditor::onUnderlineClearBtnClick()
{
    mUnderlineColor = Qt::transparent;
    ui->mUnderlineColorBtn->setStyleSheet ("");
}

void FileEditor::onColorListItemChange(
        QListWidgetItem *current, QListWidgetItem *prev)
{
    if(current == nullptr)
        return;
    HighLightConfig::FORMAT type = (HighLightConfig::FORMAT)current->type ();
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

void FileEditor::onSchemeComboboxChange (const QString &text)
{
    if(mCurrentConfig != nullptr) {
        mCurrentConfig->deleteLater ();
        mCurrentConfig = nullptr;
    }
    mCurrentConfig = new HighLightConfig(
            GetCfgsPath ("smaliTheme/" + text), this);

    auto colorCount = ui->mColorListWidget->count ();
    for(auto i = 0; i < colorCount; i++) {
        auto item = ui->mColorListWidget->item (i);
        auto &format = mCurrentConfig->mFormatMap[
                (HighLightConfig::FORMAT)item->type ()];
        item->setForeground (format.foreground ());
        item->setBackground (format.background ());
    }


    mHighlight->mFormatMap = mCurrentConfig->mFormatMap;
    mHighlight->rehighlight ();
}

void FileEditor::onFormatUpdate()
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

    mHighlight->mFormatMap[ (HighLightConfig::FORMAT)
            ui->mColorListWidget->currentItem ()->type ()] = format;
    mCurrentConfig->mFormatMap[ (HighLightConfig::FORMAT)
            ui->mColorListWidget->currentItem ()->type ()] = format;
    mHighlight->rehighlight ();
}

void FileEditor::onSchemeCopyBtnClick ()
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

void FileEditor::onSchemeDeleteBtnClick ()
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

void FileEditor::initColorListWidget ()
{
    auto widget = ui->mColorListWidget;
    widget->addItem (new QListWidgetItem(HighLightConfig::getFormatName (
            HighLightConfig::FKeyword), widget, HighLightConfig::FKeyword));
    widget->addItem (new QListWidgetItem(HighLightConfig::getFormatName (
            HighLightConfig::FOp), widget, HighLightConfig::FOp));
    widget->addItem (new QListWidgetItem(HighLightConfig::getFormatName (
            HighLightConfig::FSymbol), widget, HighLightConfig::FSymbol));
    widget->addItem (new QListWidgetItem(HighLightConfig::getFormatName (
            HighLightConfig::FCString), widget, HighLightConfig::FCString));
    widget->addItem (new QListWidgetItem(HighLightConfig::getFormatName (
            HighLightConfig::FNameString), widget, HighLightConfig::FNameString));
    widget->addItem (new QListWidgetItem(HighLightConfig::getFormatName (
            HighLightConfig::FComment), widget, HighLightConfig::FComment));
    widget->addItem (new QListWidgetItem(HighLightConfig::getFormatName (
            HighLightConfig::FClassType), widget, HighLightConfig::FClassType));
    widget->addItem (new QListWidgetItem(HighLightConfig::getFormatName (
            HighLightConfig::FFlag), widget, HighLightConfig::FFlag));
    widget->addItem (new QListWidgetItem(HighLightConfig::getFormatName (
            HighLightConfig::FRegd), widget, HighLightConfig::FRegd));
    widget->addItem (new QListWidgetItem(HighLightConfig::getFormatName (
            HighLightConfig::FNumber), widget, HighLightConfig::FNumber));
    widget->addItem (new QListWidgetItem(HighLightConfig::getFormatName (
            HighLightConfig::FDefault), widget, HighLightConfig::FDefault));

}

void FileEditor::initUnderlineCombobox ()
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

void FileEditor::initSizeCombobox ()
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

void FileEditor::initSchemeCombobox ()
{
    connect(ui->mSchemeComboBox, SIGNAL(currentTextChanged(const QString &)),
            this, SLOT(onSchemeComboboxChange (const QString &)));

    auto combobox = ui->mSchemeComboBox;
    QDir dir(GetCfgsPath ("smaliTheme"));
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
        combobox->addItem (0, "default.xml");
    }
    auto curTheme = ConfigString("FileEdit", "SmaliHighlight");
    if(curTheme.isEmpty ())
        curTheme = "default.xml";
    auto index = combobox->findText (curTheme);
    if(index == -1) {
        combobox->setCurrentText ("default.xml");
    } else {
        combobox->setCurrentIndex (index);
    }

}


void FileEditor::save ()
{
    auto cfg = Config ();
    mCurrentConfig->save ();
    auto configFileName = QFileInfo(mCurrentConfig->mSetFile).fileName ();
    cfg->setString ("FileEdit", "SmaliHighlight", configFileName);
    auto pHighLightConfig = HighLightConfig::instance (
            GetCfgsPath ("smaliTheme/" + configFileName));
    pHighLightConfig->mFormatMap = mCurrentConfig->mFormatMap;
    pHighLightConfig->onConfigUpdate ();
}




QuickSmaliHighilght::QuickSmaliHighilght (QTextDocument *parent)
        : QSyntaxHighlighter(parent) {

}

void QuickSmaliHighilght::highlightBlock (const QString &text)
{
    SmaliLexer lexer;
    auto str = text.toStdString ();
    std::istringstream is(str);
    lexer.switch_streams (&is,nullptr);
    while(true)
    {
        auto token = lexer.get_next_token ();
        auto type = token.token ();
        if (type == SmaliParser::token::TOKEN_END)
            break;
        if (type == SmaliParser::token::TOKEN_EOL)
        {
            continue;
        }
        HighLightConfig::FORMAT format;
        if(type > SmaliParser::token::TOKEN_KEYWORD_BEGIN
           && type < SmaliParser::token::TOKEN_KEYWORD_END) {
           format = HighLightConfig::FKeyword;
        } else
        if (type > SmaliParser::token::TOKEN_OP_BEGIN
            && type < SmaliParser::token::TOKEN_OP_END) {
            format = HighLightConfig::FOp;
        } else
        if (type > SmaliParser::token::TOKEN_SYMBOL_BEGIN
            && type < SmaliParser::token::TOKEN_SYMBOL_END) {
            format = HighLightConfig::FSymbol;
        } else {
            switch (type) {
                case SmaliParser::token::TOKEN_STRING_LITERAL:
                case SmaliParser::token::TOKEN_CHAR_LITERAL:
                    format = HighLightConfig::FCString;
                    break;
                case SmaliParser::token::TOKEN_SIMPLE_NAME:
                case SmaliParser::token::TOKEN_MEMBER_NAME:
                    format = HighLightConfig::FNameString;
                    break;
                case SmaliParser::token::TOKEN_LINE_COMMENT:
                    format = HighLightConfig::FComment;
                    break;
                case SmaliParser::token::TOKEN_CLASS_DESCRIPTOR:
                case SmaliParser::token::TOKEN_PRIMITIVE_TYPE:
                case SmaliParser::token::TOKEN_ARRAY_TYPE_PREFIX:
                case SmaliParser::token::TOKEN_VOID_TYPE:
                case SmaliParser::token::TOKEN_PARAM_LIST_OR_ID_PRIMITIVE_TYPE:
                    format = HighLightConfig::FClassType;
                    break;
                case SmaliParser::token::TOKEN_FLAG:
                    format = HighLightConfig::FFlag;
                    break;
                case SmaliParser::token::TOKEN_REGISTER:
                    format = HighLightConfig::FRegd;
                    break;
                case SmaliParser::token::TOKEN_NEGATIVE_INTEGER_LITERAL:
                case SmaliParser::token::TOKEN_POSITIVE_INTEGER_LITERAL:
                case SmaliParser::token::TOKEN_LONG_LITERAL:
                case SmaliParser::token::TOKEN_SHORT_LITERAL:
                case SmaliParser::token::TOKEN_BYTE_LITERAL:
                case SmaliParser::token::TOKEN_FLOAT_LITERAL_OR_ID:
                case SmaliParser::token::TOKEN_DOUBLE_LITERAL_OR_ID:
                case SmaliParser::token::TOKEN_FLOAT_LITERAL:
                case SmaliParser::token::TOKEN_DOUBLE_LITERAL:
                    format = HighLightConfig::FNumber;
                    break;
                default:
                    format = HighLightConfig::FDefault;
                    break;
            }
        }
        setFormat (lexer.column () - 1, lexer.curTokenLen (), mFormatMap[format]);
    }
}
