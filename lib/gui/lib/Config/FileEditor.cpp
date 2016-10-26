#include "FileEditor.h"
#include "ui_FileEditor.h"

FileEditor::FileEditor(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FileEditor)
{
    ui->setupUi(this);
}

FileEditor::~FileEditor()
{
    delete ui;
}
