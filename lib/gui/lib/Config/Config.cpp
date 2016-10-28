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
    ui->mConfigWidget->layout()->addWidget(mFileEditor);

    connect(ui->buttonBox, SIGNAL(accepted ()), mFileEditor, SLOT(save()));
}

Config::~Config()
{
    delete ui;
}
