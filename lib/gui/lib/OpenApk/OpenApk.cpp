//===- OpenApk.cpp - ART-GUI OpenApk Dialog --------------------*- C++ -*-===//
//
//                     ANDROID REVERSE TOOLKIT
//
// This file is distributed under the GNU GENERAL PUBLIC LICENSE
// V3 License. See LICENSE.TXT for details.
//
//===---------------------------------------------------------------------===//
#include "OpenApk/OpenApk.h"
#include "ui_OpenApk.h"

#include "utils/StringUtil.h"
#include "utils/ProjectInfo.h"

#include <QDir>
#include <utils/Configuration.h>

OpenApk::OpenApk(QString file, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::OpenApk)
{
    ui->setupUi(this);
    setWindowTitle("open new file");
    setWindowFlags(windowFlags()& ~Qt::WindowMaximizeButtonHint);
    setFixedSize(this->width(), this->height());

    mFilePath = file;
    int slashPos = mFilePath.lastIndexOf('/');
    int dotPos = mFilePath.lastIndexOf('.');
    mFileName = mFilePath.mid(slashPos + 1,
                                 dotPos - slashPos - 1);
    ui->mTargetFileLabel->setText("open file:" + mFilePath);

    connect(ui->mApkToolListWidget, SIGNAL(itemDoubleClicked(QListWidgetItem*)),
            this, SLOT(accept()));

    bool isApk = file.endsWith(".apk");
    if (isApk) {
        mDecCmd = "java -jar $(tool) d $(target)";
        mComCmd = "java -jar $(tool) b $(target)";
        // connect decompile option
        connect(ui->mDsBox, SIGNAL(stateChanged(int)),
                this, SLOT(decompileOptionChanged()));
        connect(ui->mDrBox, SIGNAL(stateChanged(int)),
                this, SLOT(decompileOptionChanged()));
        connect(ui->mDdfBox, SIGNAL(stateChanged(int)),
                this, SLOT(decompileOptionChanged()));
        connect(ui->mDn9Box, SIGNAL(stateChanged(int)),
                this, SLOT(decompileOptionChanged()));
        connect(ui->mDirBox, SIGNAL(stateChanged(int)),
                this, SLOT(decompileOptionChanged()));
        connect(ui->mDfuiBox, SIGNAL(stateChanged(int)),
                this, SLOT(decompileOptionChanged()));
        connect(ui->mDmcBox, SIGNAL(stateChanged(int)),
                this, SLOT(decompileOptionChanged()));
        connect(ui->mDxnBox, SIGNAL(stateChanged(int)),
                this, SLOT(decompileOptionChanged()));

        // connect compile option
        connect(ui->mCdfBox, SIGNAL(stateChanged(int)),
                this, SLOT(compileOptionChanged()));
        connect(ui->mCfBox, SIGNAL(stateChanged(int)),
                this, SLOT(compileOptionChanged()));
        connect(ui->mCfndBox, SIGNAL(stateChanged(int)),
                this, SLOT(compileOptionChanged()));

        ui->mDecompileEdit->setText(mDecCmd);
        ui->mCompileEdit->setText(mComCmd);
        ui->mDdfBox->setChecked(true);
    } else {
        mDecCmd = "java -jar $(tool) bs $(target)";
        mComCmd = "java -jar $(tool) s $(target)";
        ui->decompileGroup->setEnabled(false);
        ui->compileGroup->setEnabled(false);
        ui->mDecompileEdit->setText(mDecCmd);
        ui->mCompileEdit->setText(mComCmd);
    }

    // find apk tool
    QDir dir(QApplication::applicationDirPath() + "/thirdparty/apktool");
    if (dir.exists()) {
        dir.setFilter(QDir::Files | QDir::NoSymLinks);
        QFileInfoList list = dir.entryInfoList();
        int fCount = list.count();
        if (fCount > 0) {
            QStringList strList;
            for (int i = 0; i < fCount; i++) {
                QFileInfo fInfo = list.at(i);
                QString suffix = fInfo.suffix();

                if (suffix.compare("jar", Qt::CaseInsensitive) == 0) {
                    ui->mApkToolListWidget->addItem(fInfo.fileName());
                }
            }
            ui->mApkToolListWidget->setCurrentRow(0);
        }
    }
}

OpenApk::~OpenApk()
{
    delete ui;
}

QString OpenApk::getDecompileCmd()
{
    return mDecCmd;
}

QString OpenApk::getCompileCmd()
{
    return mComCmd;
}

QString OpenApk::getFileName()
{
    return mFileName;
}

void OpenApk::accept()
{
    QString apkToolName = ui->mApkToolListWidget->count() ?
                    ui->mApkToolListWidget->currentItem()->text()
                    : "";
    QString exePath = QApplication::applicationDirPath();
    QString apkToolPath = "./thirdparty/apktool/" + apkToolName;
    QString projectPath = "./Projects/" + mFileName + "/Project";
    QString genApk = "./Projects/" + mFileName + "/Bin/unsigned.apk";

    QString cmd = ui->mDecompileEdit->text();
    cmd.replace("$(tool)", apkToolPath);
    cmd.replace("$(target)", mFilePath);
    cmd += " -f -o " + projectPath;
    mDecCmd = cmd;

    cmd = ui->mCompileEdit->text();
    cmd.replace("$(tool)", apkToolPath);
    cmd.replace("$(target)", projectPath);
    cmd += " -o " + genApk;
    mComCmd = cmd;


    // set information
    QString projectsRoot = GetProjectsPath ();
    QDir dir(projectsRoot);
    if(!dir.exists (mFileName)) {
        dir.mkdir (mFileName);
    } 

    QString cfgPath = GetProjectsPath (mFileName) + "/Config.ini" ;

    Configuration cfg(cfgPath);
    cfg.setString ("ProjectInfo", "CompileCmd", mComCmd);
    cfg.setString ("ProjectInfo", "DecompileCmd", mDecCmd);

    QDialog::accept();
}

void OpenApk::decompileOptionChanged()
{
    QString cmd = mDecCmd;
    bool noSrc = ui->mDsBox->isChecked();
    bool noRes = ui->mDrBox->isChecked();
    bool df = ui->mDdfBox->isChecked();
    bool n9 = ui->mDn9Box->isChecked();
    bool ir = ui->mDirBox->isChecked();
    bool fui = ui->mDfuiBox->isChecked();
    bool mc = ui->mDmcBox->isChecked();
    bool xn =ui->mDxnBox->isChecked();

    noSrc ? cmd += " -s":0;
    noRes ? cmd += " -r":0;
    df ? cmd += " -df":0;
    n9 ? cmd += " -n9":0;
    ir ? cmd += " -ir":0;
    fui ? cmd += " -fui":0;
    mc ? cmd += " -mc":0;
    xn ? cmd += " -xn":0;
    ui->mDecompileEdit->setText(cmd);
}

void OpenApk::compileOptionChanged()
{
    QString cmd = mComCmd;
    bool f = ui->mCfBox->isChecked();
    bool df = ui->mCdfBox->isChecked();
    bool fnd = ui->mCfndBox->isChecked();

    f ? cmd += " -f":0;
    df ? cmd += " -df":0;
    fnd ? cmd += " -fnd":0;
    ui->mCompileEdit->setText(cmd);
}

