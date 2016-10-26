#include "FileEditor.h"
#include "ui_FileEditor.h"

#include <QDebug>
#include <QColorDialog>

FileEditor::FileEditor(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FileEditor)
{
    ui->setupUi(this);

    ui->mForegroundColorBtn->setAutoFillBackground(true);
    ui->mBackgroundColorBtn->setAutoFillBackground(true);
    ui->mUnderlineColorBtn->setAutoFillBackground(true);

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

}

FileEditor::~FileEditor()
{
    delete ui;
}

void FileEditor::onForegroundColorBtnClick()
{
    QColor color = QColorDialog::getColor(Qt::white, this, "Select ForegroundColor", QColorDialog::ShowAlphaChannel);
    if(color.isValid ()) {
        QString style = "background-color: " + color.name ();
        ui->mForegroundColorBtn->setStyleSheet (style);
    }

}

void FileEditor::onForegroundClearBtnClick()
{
    ui->mForegroundColorBtn->setStyleSheet ("");
}

void FileEditor::onBackgroundColorBtnClick()
{
    QColor color = QColorDialog::getColor(Qt::white, this, "Select ForegroundColor", QColorDialog::ShowAlphaChannel);
    if(color.isValid ()) {
        QString style = "background-color: " + color.name ();
        ui->mBackgroundColorBtn->setStyleSheet (style);
    }
}

void FileEditor::onBackgroundClearBtnClick()
{
    ui->mBackgroundColorBtn->setStyleSheet ("");
}

void FileEditor::onUnderlineColorBtnClick()
{
    QColor color = QColorDialog::getColor(Qt::white, this, "Select ForegroundColor", QColorDialog::ShowAlphaChannel);
    if(color.isValid ()) {
        QString style = "background-color: " + color.name ();
        ui->mUnderlineColorBtn->setStyleSheet (style);
    }
}

void FileEditor::onUnderlineClearBtnClick()
{
    ui->mUnderlineColorBtn->setStyleSheet ("");
}
