//===- Environment.cpp - ART-GUI Config --------------------------*- C++ -*-===//
//
//                     ANDROID REVERSE TOOLKIT
//
// This file is distributed under the GNU GENERAL PUBLIC LICENSE
// V3 License. See LICENSE.TXT for details.
//
//===---------------------------------------------------------------------===//
#include "Environment.h"
#include "ui_Environment.h"

#include <utils/Configuration.h>
#include <utils/StringUtil.h>


#include <QProcess>
#include <QDebug>
#include <QtWidgets/QFileDialog>

Environment::Environment(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Environment)
{
    ui->setupUi(this);

    Configuration *config = Config();
    if(config->getBool("System", "UseDefaultAdb")) {
        ui->mDefaultToolsBtn->setChecked(true);
    } else {
        ui->mCustomToolsBtn->setChecked(true);
    }

    if(isJavaValid()) {
        ui->mJavaPathEdit->setText(getJavaPath());
        ui->mJavaVersionLabel->setText(getJavaVersion());
    }

    if(isAdbValid()) {
        ui->mAdbPathEdit->setText(getAdbPath());
        ui->mAdbVersionLabel->setText(getAdbVersion());
    }

    connect(ui->mJavaPathBrowseBtn, &QPushButton::clicked, [this]() {
        QString fileName = QFileDialog::getOpenFileName(this, tr("Select Java Location"));
        if(fileName.isEmpty()) {
            return;
        }
        ui->mJavaPathEdit->setText(fileName);
    });

    connect(ui->mAdbPathBrowseBtn, &QPushButton::clicked, [this]() {
        QString fileName = QFileDialog::getOpenFileName(this, tr("Select Adb Location"));
        if(fileName.isEmpty()) {
            return;
        }
        ui->mAdbPathEdit->setText(fileName);
    });
}

Environment::~Environment()
{
    delete ui;
}

void Environment::save()
{

}

bool Environment::isJavaValid() {
    // check process java
    return !getJavaPath().isEmpty();
}

bool Environment::isAdbValid() {
    // check process adb
    return !getAdbPath().isEmpty();
}

QString Environment::getJavaPath() {
    auto configpath = ConfigString("System", "JavaPath");
    if(!configpath.isEmpty()) {
        return configpath;
    }

    auto path = getProcessDir("java");
    if(path.isEmpty()) {
        return QString();
    }
    return path.takeFirst();
}

QString Environment::getAdbPath() {
    if(ui->mDefaultToolsBtn->isChecked()) {
        return GetThirdPartyPath("adb/adb");
    }

    auto configpath = ConfigString("System", "AdbPath");
    if(!configpath.isEmpty()) {
        return configpath;
    }

    auto path = getProcessDir("adb");
    if(path.isEmpty()) {
        return QString();
    }
    return path.takeFirst();
}

QString Environment::getJavaVersion() {
    auto javapath = getJavaPath();
    if(javapath.isEmpty()) {
        return QString();
    }

    QString version;
    QProcess process;
    process.start(javapath, QStringList() << "-version", QIODevice::ReadOnly);
    process.waitForFinished();
    version = QString::fromLocal8Bit(process.readLine());
    if(version.isEmpty()) {
        version = "Unknown java version";
    }
    return version;
}

QString Environment::getAdbVersion() {
    auto adbpath = getAdbPath();
    if (adbpath.isEmpty()) {
        return QString();
    }

    QString version;
    QProcess process;
    process.setWorkingDirectory(GetSoftPath());
    process.start(adbpath, QIODevice::ReadOnly);
    process.waitForFinished();
    version = QString::fromLocal8Bit(process.readLine());
    if(version.isEmpty()) {
        version = "Unknown adb version";
    }
    return version;
}


QStringList Environment::getProcessDir(QString name) {

#if _WIN32 || _WIN64
    QString pathTool = "where";
#else
    QString pathTool = "which";
#endif
    QStringList result;

    QProcess process;
    process.start(pathTool, QStringList() << name, QIODevice::ReadOnly);
    process.waitForFinished();
    QString path = QString::fromLocal8Bit(process.readAllStandardOutput());
    if(path.isEmpty()) {
        return result;
    }
    QStringList list = path.split(QRegExp("\\s+"), QString::SkipEmptyParts);
    for(auto &p: list) {
        if(p.contains(name)) {
            result.push_back(p);
        }
    }

    return result;
}



