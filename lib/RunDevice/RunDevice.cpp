//===- RunDevice.cpp - ART-GUI  --------------------------------*- C++ -*-===//
//
//                     ANDROID REVERSE TOOLKIT
//
// This file is distributed under the GNU GENERAL PUBLIC LICENSE
// V3 License. See LICENSE.TXT for details.
//
//===---------------------------------------------------------------------===//
#include "RunDevice/RunDevice.h"
#include "ui_RunDevice.h"

#include <utils/ScriptEngine.h>
#include <utils/ProjectInfo.h>
#include <utils/StringUtil.h>
#include <utils/CmdMsgUtil.h>
#include <utils/AdbUtil.h>

#include <QRegExp>
#include <QtConcurrent/QtConcurrent>
#include <QAtomicInteger>

void getDeviceMsgThread(RunDevice* e);

RunDevice::RunDevice(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RunDevice)
{
    ui->setupUi(this);

    setWindowTitle("Select Deployment Target");
    setWindowFlags(windowFlags()& ~Qt::WindowMaximizeButtonHint);
    setFixedSize(this->width(), this->height());

    ScriptEngine* script = ScriptEngine::instance();
    connect(script, &ScriptEngine::build, this, &RunDevice::onBuildAction);
    connect(script, &ScriptEngine::install, this, &RunDevice::onInstallAction);
    connect(script, &ScriptEngine::run, this, &RunDevice::onRunAction);
    connect(script, &ScriptEngine::debug, this, &RunDevice::onDebugAction);
    connect(script, &ScriptEngine::stop, this, &RunDevice::onStopAction);
    connect(script, &ScriptEngine::devices, this, &RunDevice::exec);


    connect(this, SIGNAL(addDeviceList(QString)), this, SLOT(onNewDevice(QString)));
    connect(ui->mRefreshBtn, SIGNAL(clicked(bool)), this, SLOT(onRefreshDeviceList()));
}

RunDevice::~RunDevice()
{
    delete ui;
}

RunDevice *RunDevice::instance(QWidget * parent)
{
    static RunDevice* mPtr = nullptr;
    if(mPtr == nullptr) {
        Q_ASSERT (parent != nullptr && "Rundevice should init in MainWindow");
        mPtr = new RunDevice(parent);
    }
    return mPtr;
}

void RunDevice::accept()
{
    if (ui->mDevicesList->currentRow() == -1)
        return QDialog::reject();
    QString devices = ui->mDevicesList->currentItem()->text();
    QStringList devMsg = devices.split('$', QString::SkipEmptyParts);
    if (devMsg.size() > 1) {
        mDeviceId = devMsg.last();
        useDefault = ui->mSameCheckBox->isChecked();
        ProjectInfo::sConfig().m_deviceId = mDeviceId;
    }
    QDialog::accept();
}

void RunDevice::reject()
{
    QDialog::reject();
}

void RunDevice::onBuildAction ()
{
    if(!ProjectInfo::isProjectOpened()) {
        return;
    }
    auto pinfo = ProjectInfo::current();
    // build
    QString buildCmd = pinfo->config().m_compileCmd;
    cmdexec(buildCmd, CmdMsg::cmd);

    // signed
    QStringList signArgs;
    signArgs << "-jar"
             << "./thirdparty/signapk/signapk.jar"
             << "./cfgs/keystore/FDA.x509.pem"
             << "./cfgs/keystore/FDA.pk8"
             << pinfo->getBuildPath() + "/unsigned.apk"
             << pinfo->getBuildPath() + "/signed.apk";
    cmdexec("java", signArgs, CmdMsg::cmd);
}


void RunDevice::onInstallAction()
{
    if(!ProjectInfo::isProjectOpened()) {
        return;
    }
    auto pinfo = ProjectInfo::current();
    QString devId = getValidDeviceId();
    if (devId.isEmpty())
        return;
    cmdmsg()->addCmdMsg ("install apk package " + pinfo->config().m_packageName);

    QStringList args;
    args << "-s"
         << mDeviceId
         << "install"
         << "-r"
         << pinfo->getBuildPath() + "/signed.apk";
    ScriptEngine::instance()->adbShell(args);
}

void RunDevice::onRunAction()
{
    if(!ProjectInfo::isProjectOpened()) {
        return;
    }
    auto pinfo = ProjectInfo::current();

    QString devId = getValidDeviceId();
    if (devId.isEmpty())
        return;

    cmdmsg()->addCmdMsg ("Running apk file " + pinfo->config().m_packageName);

    QStringList args;
    args << "-s"
         << mDeviceId
         << "shell"
         << "am"
         << "start"
         << pinfo->config().m_packageName + "/" + pinfo->config().m_activityEntryName;
    ScriptEngine::instance()->adbShell(args);
}

void RunDevice::onDebugAction()
{
    if(!ProjectInfo::isProjectOpened()) {
        return;
    }
    auto pinfo = ProjectInfo::current();

    QString devId = getValidDeviceId();
    if (devId.isEmpty())
        return;

    cmdmsg()->addCmdMsg ("Running apk file " + pinfo->config().m_packageName);

    QStringList args;
    args << "-s"
         << mDeviceId
         << "shell"
         << "am"
         << "start"
         << "-D"
         << "-n"
         << pinfo->config().m_packageName + "/" + pinfo->config().m_activityEntryName;
    ScriptEngine::instance()->adbShell(args);
    cmdexec("DebugStart", pinfo->config().m_packageName);
}

void RunDevice::onStopAction()
{
    if(!ProjectInfo::isProjectOpened()) {
        return;
    }
    auto pinfo = ProjectInfo::current();

    QString devId = getValidDeviceId();
    if (devId.isEmpty())
        return;

    cmdmsg()->addCmdMsg ("Stoping apk file " + pinfo->config().m_packageName);

    QStringList args;
    args << "-s"
         << mDeviceId
         << "shell"
         << "am"
         << "force-stop"
         << pinfo->config().m_packageName;
    ScriptEngine::instance()->adbShell(args);
}

void RunDevice::onNewDevice(QString dev)
{
    ui->mDevicesList->addItem(dev);
    ui->mDevicesList->setCurrentRow(0);
}

void RunDevice::onRefreshDeviceList()
{
    AdbUtil adbUtil;
    adbUtil.execute("kill-server");
    ui->mDevicesList->clear();
    QtConcurrent::run(getDeviceMsgThread, this);
}

int RunDevice::exec()
{
    ui->mDevicesList->clear();
    QtConcurrent::run(getDeviceMsgThread, this);
    return QDialog::exec();
}

QStringList RunDevice::getCurDeviceIdList()
{
    AdbUtil adbUtil;
    QStringList devs = adbUtil.execute("devices");
    // deviceId status
    QStringList devId;
    foreach(QString deviceMsg, devs) {
        QStringList device = deviceMsg.split(QRegExp("\\s+"), QString::SkipEmptyParts);
        if (device.size() != 2) {
            continue;
        }
        if(device[1].compare("device", Qt::CaseInsensitive) != 0) {
            // only online device is abled to use
            continue;
        }
        devId.push_back(device[0]);
    }
    return devId;
}

bool RunDevice::hasValidDefaultDeviceId()
{
    if (!useDefault)
        return false;
    if (!getCurDeviceIdList().contains(mDeviceId)) {
        return false;
    }
    return true;
}

QString RunDevice::getValidDeviceId()
{
    if (!hasValidDefaultDeviceId() && exec() != QDialog::Accepted )
        return QString();
    return mDeviceId;
}


void getDeviceMsgThread(RunDevice* runDevice) {
    static QAtomicInteger<bool> running;
    if(running) {
        return;
    }
    running = true;

    AdbUtil adbUtil;
    QStringList devIds = runDevice->getCurDeviceIdList();
    foreach(const QString& deviceId, devIds) {
            QStringList propList = adbUtil.execute("-s " + deviceId + " shell getprop");
            QMap<QString, QString> propMap;
            foreach(QString prop, propList) {
                    prop.remove(QRegExp("[ \\[\\]]"));
                    auto keyvalue = prop.split(':', QString::SkipEmptyParts);
                    if(keyvalue.size() == 2) {
                        propMap[keyvalue[0]] = keyvalue[1];
                    }
                }
            QString deviceMsg =
                propMap["ro.product.manufacturer"] + " " +
                propMap["ro.product.model"] + " (" +
                "Android " + propMap["ro.build.version.release"] +
                ", API " + propMap["ro.build.version.sdk"]   + ")" +
                "$" + deviceId;
         runDevice->addDeviceList(deviceMsg);
    }
    running = false;
}

