//===- EditorTab.cpp - ART-GUI TextEditorWidget Tab --------------------*- C++ -*-===//
//
//                     ANDROID REVERSE TOOLKIT
//
// This file is distributed under the GNU GENERAL PUBLIC LICENSE
// V3 License. See LICENSE.TXT for details.
//
//===---------------------------------------------------------------------===//

#include "EditorTab/EditorTab.h"
#include "ui_EditorTab.h"

#include "TextEditorWidget.h"
#include "EditorTab/TextEditor.h"
#include "EditorTab/SmaliEditor.h"
#include "EditorTab/CodeEditor.h"

#include <utils/ScriptEngine.h>
#include <utils/ProjectInfo.h>
#include <utils/Configuration.h>

#include <QStackedWidget>
#include <QFile>
#include <QFileInfo>
#include <QInputDialog>
#include <utils/CmdMsgUtil.h>

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

    connect(script, SIGNAL(undo(QStringList)), this, SLOT(undo()));
    connect(script, SIGNAL(redo(QStringList)), this, SLOT(redo()));
    connect(script, SIGNAL(cut(QStringList)), this, SLOT(cut()));
    connect(script, SIGNAL(copy(QStringList)), this, SLOT(copy()));
    connect(script, SIGNAL(paste(QStringList)), this, SLOT(paste()));
    connect(script, SIGNAL(deleteR(QStringList)), this, SLOT(deleteR()));
    connect(script, SIGNAL(selectAll(QStringList)), this, SLOT(selectAll()));
    connect(script, SIGNAL(find(QStringList)), this, SLOT(find(QStringList)));
    connect(script, SIGNAL(gotoLine(QStringList)), this, SLOT(gotoLine(QStringList)));

    connect(script, SIGNAL(projectOpened(QStringList)),
            this, SLOT(onProjectOpened(QStringList)));
    connect(script, SIGNAL(projectClosed(QStringList)),
            this, SLOT(onProjectClosed ()));
}

EditorTab::~EditorTab()
{
    delete ui;
}

bool EditorTab::openFile(QString filePath, int iLine)
{
    QFileInfo fileInfo(filePath);
    if(!fileInfo.exists () && !fileInfo.isFile ()) {
        return false;
    }
    filePath = fileInfo.canonicalFilePath ();
    QString fileName = fileInfo.fileName ();

    // find wether the file has been opened
    int iComIdx = ui->mDocumentCombo->findData(filePath);
    if (iComIdx != -1) {
        ui->mDocumentCombo->setCurrentIndex(iComIdx);
        if(iLine != -1) {
            TextEditor* p = (TextEditor*)ui->mEditStackedWidget->widget(iComIdx);
            p->gotoLine (iLine);
        }
        cmdexec("OpenWindow", "EditorTab", CmdMsg::script, true, false);
        return true;
    }
    if (!filePath.isEmpty()) {
        TextEditorWidget* p = new TextEditorWidget(this);

        iLine = (iLine == -1) ? 1 : iLine;
        if (p->openFile(filePath, iLine)) {

            ui->mEditStackedWidget->insertWidget(0, p);
            ui->mDocumentCombo->insertItem(0, fileName, filePath);
            ui->mDocumentCombo->setCurrentIndex(0);
            cmdexec("OpenWindow", "EditorTab", CmdMsg::script, true, false);
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
        TextEditorWidget* p = (TextEditorWidget*)ui->mEditStackedWidget->widget(idx);
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
    if (args.size() > 0) {     // filepath
        QString path = args.at(0);
        QFile file(path);
        int iLine = -1;
        if (args.size () > 1) {
            iLine = args.at (1).toInt ();
        }
        openFile(path, iLine);
    }
}

void EditorTab::undo()
{
    TextEditorWidget* e = (TextEditorWidget*)ui->mEditStackedWidget->currentWidget();
    if(e == nullptr)
        return;
    e->editor()->undo ();
}

void EditorTab::redo()
{
    TextEditorWidget* e = (TextEditorWidget*)ui->mEditStackedWidget->currentWidget();
    if(e == nullptr)
        return;
    e->editor()->redo ();
}

void EditorTab::cut()
{
    TextEditorWidget* e = (TextEditorWidget*)ui->mEditStackedWidget->currentWidget();
    if(e == nullptr)
        return;
    e->editor()->cut ();
}

void EditorTab::copy()
{
    TextEditorWidget* e = (TextEditorWidget*)ui->mEditStackedWidget->currentWidget();
    if(e == nullptr)
        return;
    e->editor()->copy ();
}

void EditorTab::paste()
{
    TextEditorWidget* e = (TextEditorWidget*)ui->mEditStackedWidget->currentWidget();
    if(e == nullptr)
        return;
    e->editor()->paste ();
}

void EditorTab::deleteR()
{
    TextEditorWidget* e = (TextEditorWidget*)ui->mEditStackedWidget->currentWidget();
    if(e == nullptr)
        return;
    e->editor()->insertPlainText (QString());
}

void EditorTab::selectAll()
{
    TextEditorWidget* e = (TextEditorWidget*)ui->mEditStackedWidget->currentWidget();
    if(e == nullptr)
        return;
    e->editor()->selectAll ();
}

void EditorTab::find(QStringList args)
{
    TextEditorWidget* e = (TextEditorWidget*)ui->mEditStackedWidget->currentWidget();
    if(e == nullptr)
        return;
    e->onFindAction ();
}

void EditorTab::gotoLine(QStringList args)
{
    TextEditorWidget* e = (TextEditorWidget*)ui->mEditStackedWidget->currentWidget();
    if(e == nullptr)
        return;
    bool doGo;
    auto line = QInputDialog::getText(nullptr, tr("Goto Line"),
                                          tr("Please input target line"), QLineEdit::Normal,
                                          QString::number (e->currentLine ()) ,&doGo);
    if(doGo) {
        e->editor()->gotoLine (line.toInt ());
    }
}

bool EditorTab::saveFile(QString filePath)
{
    int idx = ui->mDocumentCombo->findData(filePath);
    if (idx != -1) {
        TextEditorWidget* p = (TextEditorWidget*)ui->mEditStackedWidget->widget(idx);
        return p->saveFile();
    }
    return false;
}

bool EditorTab::saveAll()
{
    for(auto idx = 0, count = ui->mDocumentCombo->count ();
            idx < count; idx ++) {
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
        TextEditorWidget* p = (TextEditorWidget*)ui->mEditStackedWidget->widget(idx);
        p->reload();
    }
}

void EditorTab::onProjectOpened (QStringList args)
{
    QString cfgPath = ProjectInfo::current()->getConfigPath();
    Configuration cfg(cfgPath);

    auto &openMap = cfg.Uints["EditorTab"];
    for (auto it = openMap.begin (), end = openMap.end (); it != end; it++) {
        openFile (it.key (), it.value ());
    }
}

void EditorTab::onProjectClosed ()
{
    QString cfgPath = ProjectInfo::current()->getConfigPath();
    Configuration cfg (cfgPath);

    for (int i = 0, count = ui->mEditStackedWidget->count (); i < count; i++) {
        TextEditorWidget* p = (TextEditorWidget*)ui->mEditStackedWidget->widget(i);
        cfg.setUint ("EditorTab", p->getFilePath (), p->currentLine ());
    }
    closeAll ();
}

