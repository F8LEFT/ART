#include "Find/FindWidget.h"
#include "ui_FindWidget.h"

FindWidget::FindWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FindWidget)
{
    ui->setupUi(this);
}

FindWidget::~FindWidget()
{
    delete ui;
}
