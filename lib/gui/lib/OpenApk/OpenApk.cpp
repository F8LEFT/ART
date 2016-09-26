#include "OpenApk.h"
#include "ui_OpenApk.h"

OpenApk::OpenApk(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::OpenApk)
{
    ui->setupUi(this);
}

OpenApk::~OpenApk()
{
    delete ui;
}
