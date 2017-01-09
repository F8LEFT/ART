#include "ChooseProcess.h"
#include "ui_ChooseProcess.h"

#include <utils/AdbUtil.h>
#include <utils/ProjectInfo.h>
#include <utils/Configuration.h>

ChooseProcess::ChooseProcess(const QString &host, int port, const QString &filter,
                             bool bindJdwp, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ChooseProcess)
{
    ui->setupUi(this);

    m_host = host;
    m_port = port;
    m_pid = 0;
    m_bindJdwp = bindJdwp;

    // setup header view
    QStringList headername;
    headername << "PID" << "NAME";

    ui->mTableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->mTableWidget->setHorizontalHeaderLabels(headername);
    ui->mTableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->mTableWidget->setSortingEnabled(true);

    QHeaderView * hHeader = ui->mTableWidget->horizontalHeader();
    hHeader->setSectionResizeMode(QHeaderView::Stretch);
    hHeader->setStretchLastSection(false);
    ui->mTableWidget->verticalHeader()->hide();

    resetProcessInfo();
    ui->mHostEdit->setText(m_host);
    ui->mPortEdit->setText(QString::number(m_port));

    // connect signal slots
    connect(ui->mRefreshButton, &QPushButton::clicked, [this]{
        resetProcessInfo();
    });
    connect(ui->mFilterEdit, &QLineEdit::textChanged, [this](QString filter){
        bool empty = filter.isEmpty();
        for( int i = 0; i < ui->mTableWidget->rowCount(); ++i ) {
            bool hidden = false;
            QTableWidgetItem *item = ui->mTableWidget->item(i, 1);
            if(!empty && !item->text().contains(filter)) {
                hidden = true;
            }
            ui->mTableWidget->setRowHidden(i, hidden);
        }
    });
    connect(ui->mTableWidget, &QTableWidget::itemDoubleClicked, this, &ChooseProcess::accept);

    ui->mFilterEdit->setText(filter);
    ui->mJdwpBindCheck->setChecked(m_bindJdwp);
}

ChooseProcess::~ChooseProcess()
{
    delete ui;
}

void ChooseProcess::accept() {
    m_host = ui->mHostEdit->text();
    m_port = ui->mPortEdit->text().toUInt();
    if(ui->mTableWidget->currentRow() >= 0) {
        m_pid = ui->mTableWidget->item(ui->mTableWidget->currentRow(), 0)->text().toUInt();
    }
    m_bindJdwp = ui->mJdwpBindCheck->isChecked();
    QDialog::accept();
}

void ChooseProcess::resetProcessInfo()
{
    ui->mTableWidget->clear();

    AdbUtil adbUtil;
    auto deviceId = ProjectInfo::sConfig().m_deviceId;
    auto procinfo = adbUtil.getProcessInfo(deviceId);
    ui->mTableWidget->setRowCount(procinfo.size());
    ui->mTableWidget->setColumnCount(2);
    int i = 0;
    for(auto& info: procinfo) {
        ui->mTableWidget->setItem(i, 0, new QTableWidgetItem(QString::number(info.pid)));
        ui->mTableWidget->setItem(i, 1, new QTableWidgetItem(info.name));
        i++;
    }
    ui->mTableWidget->sortItems(0, Qt::DescendingOrder);
}

void ChooseProcess::loadFromConfig()
{
    Configuration *config = Config();
    restoreGeometry(config->getByte("ChooseProcess", "Geometry"));
}

void ChooseProcess::saveToConfig()
{
    Configuration *config = Config();
    config->setByte("ChooseProcess", "Geometry", saveGeometry());
}
