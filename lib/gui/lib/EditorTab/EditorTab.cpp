//===- EditorTab.cpp - ART-GUI Editor Tab --------------------*- C++ -*-===//
//
//                     ANDROID REVERSE TOOLKIT
//
// This file is distributed under the GNU GENERAL PUBLIC LICENSE
// V3 License. See LICENSE.TXT for details.
//
//===---------------------------------------------------------------------===//

#include "EditorTab/EditorTab.h"
#include "ui_EditorTab.h"

#include "Editor.h"

#include <utils/ScriptEngine.h>
#include <QStackedWidget>
#include <QFile>

EditorTab::EditorTab(QWidget *parent) :
        QWidget(parent),
        ui(new Ui::EditorTab)
{
    ui->setupUi(this);
    connect(ui->mCloseButton, SIGNAL(clicked(bool)),
            this, SLOT(documentCloseClick(bool)));

    ScriptEngine* script = ScriptEngine::instance();
    connect(script, SIGNAL(saveAllFile(QStringList)), this, SLOT(saveAll()));
    connect(script, SIGNAL(closeAllFile(QStringList)), this, SLOT(closeAll()));
    connect(script, SIGNAL(saveFile(QStringList)), this, SLOT(saveFile(QStringList)));
    connect(script, SIGNAL(closeFile(QStringList)), this, SLOT(closeFile(QStringList)));
    connect(script, SIGNAL(openFile(QStringList)), this, SLOT(openFile(QStringList)));
}

EditorTab::~EditorTab()
{
    delete ui;
}

bool EditorTab::openFile(QString filePath, QString fileName)
{
    int iComIdx = ui->mDocumentCombo->findData(filePath);
    if (iComIdx != -1) {
        ui->mDocumentCombo->setCurrentIndex(iComIdx);
        return true;
    }
    // find wether the file is opened
    if (!filePath.isEmpty()) {
        auto p = new Editor(this);
        if (p->openFile(filePath, fileName)) {
            ui->mEditStackedWidget->insertWidget(0, p);
            ui->mDocumentCombo->insertItem(0, fileName, filePath);
            ui->mDocumentCombo->setCurrentIndex(0);
            return true;
        } else {
            delete p;
        }
    }
    return false;
}

bool EditorTab::closeFile(QString filePath)
{
    int idx = ui->mDocumentCombo->findData(filePath);
    if (idx != -1) {
        Editor* p = (Editor*)ui->mEditStackedWidget->widget(idx);
        ui->mEditStackedWidget->removeWidget(p);
        ui->mDocumentCombo->removeItem(idx);
        delete p;
        return true;
    }
    return false;
}

bool EditorTab::closeAll()
{
    int idx;
    while((idx = ui->mDocumentCombo->currentIndex()) != -1) {
        closeFile(ui->mDocumentCombo->itemData(idx).toString());
    }
    return true;
}

void EditorTab::saveFile(QStringList files)
{
            foreach(QString file, files) {
            saveFile(file);
        }
}

void EditorTab::closeFile(QStringList files)
{
            foreach(QString file, files) {
            closeFile(file);
        }
}

void EditorTab::openFile(QStringList args)
{
    if (args.size() == 1) {     // filepath
        QString path = args.at(0);
        QFile file(path);
        openFile(path, file.fileName());
        if (args.size() > 1) {

        }
    } else if (args.size() > 1) {        // filepath, iLine (How?)

    }
}

bool EditorTab::saveFile(QString filePath)
{
    int idx = ui->mDocumentCombo->findData(filePath);
    if (idx != -1) {
        Editor* p = (Editor*)ui->mEditStackedWidget->widget(idx);
        return p->saveFile();
    }
    return false;
}

bool EditorTab::saveAll()
{
    int idx;
    while((idx = ui->mDocumentCombo->currentIndex()) != -1) {
        saveFile(ui->mDocumentCombo->itemData(idx).toString());
    }
    return true;
}

void EditorTab::documentCloseClick(bool)
{
    int idx = ui->mDocumentCombo->currentIndex();
    if (idx != -1) {
        closeFile(ui->mDocumentCombo->itemData(idx).toString());
    }
}

void EditorTab::fileChanged(QString path)
{
    int idx = ui->mDocumentCombo->findData(path);
    if (idx != -1) {
        Editor* p = (Editor*)ui->mEditStackedWidget->widget(idx);
        p->reload();
    }
}

