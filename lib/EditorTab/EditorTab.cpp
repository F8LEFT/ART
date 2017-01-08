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

#include <utils/CmdMsgUtil.h>
#include <BookMark/BookMarkManager.h>
#include <utils/ScriptEngine.h>
#include <utils/ProjectInfo.h>
#include <utils/Configuration.h>
#include <SmaliAnalysis/SmaliAnalysis.h>

#include <QStackedWidget>
#include <QFile>
#include <QFileInfo>
#include <QInputDialog>
#include <BreakPoint/BreakPointManager.h>


EditorTab::EditorTab(QWidget *parent) :
        QWidget(parent),
        ui(new Ui::EditorTab),
        m_fieldIcon(":/images/field.png"),
        m_methodIcon(":/images/method.png")
{
    ui->setupUi(this);
    connect(ui->mCloseButton, SIGNAL(clicked(bool)),
            this, SLOT(documentCloseClick(bool)));

    connect(ui->mDocumentCombo, SIGNAL(currentIndexChanged(int)), this, SLOT(documentIndxChanged(int)));
    connect(ui->mMethodCombo, SIGNAL(currentIndexChanged(int)), this, SLOT(methodIndexChanged(int)));

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

    auto bookmarkManager = BookMarkManager::instance();
    connect(bookmarkManager, &BookMarkManager::updateBookMark, this, &EditorTab::onTextMarkUpdate);
    auto breakpointManager = BreakPointManager::instance();
    connect(breakpointManager, &BreakPointManager::updateBreakPoint, this, &EditorTab::onTextMarkUpdate);
    auto smalianalysis = SmaliAnalysis::instance();
    connect(smalianalysis, &SmaliAnalysis::fileAnalysisFinished,
            [this](const QString &file) {
                if(ui->mDocumentCombo->currentData().toString() == file) {
                    updateEditorMsg(file);
                }
            });
    connect(&m_fileWatcher, &QFileSystemWatcher::fileChanged, this, &EditorTab::reloadFile);
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
            TextEditorWidget* p = (TextEditorWidget*)ui->mEditStackedWidget->widget(iComIdx);
            p->editor()->gotoLine (iLine);
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

void EditorTab::toggleBreakPoint() {
    TextEditorWidget* e = (TextEditorWidget*)ui->mEditStackedWidget->currentWidget();
    if(e == nullptr)
        return;
    SmaliEditor* editor = qobject_cast<SmaliEditor*>(e->editor());
    if(editor != nullptr) {
        editor->toggleBreakpoint();
    }
}

void EditorTab::toggleBookMark() {
    TextEditorWidget* e = (TextEditorWidget*)ui->mEditStackedWidget->currentWidget();
    if(e == nullptr)
        return;
    e->editor()->toggleBookmark();
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
    QString cfgPath = ProjectInfo::last()->getConfigPath();
    Configuration cfg (cfgPath);

    for (int i = 0, count = ui->mEditStackedWidget->count (); i < count; i++) {
        TextEditorWidget* p = (TextEditorWidget*)ui->mEditStackedWidget->widget(i);
        cfg.setUint ("EditorTab", p->getFilePath (), p->currentLine ());
    }
    closeAll ();
}

void EditorTab::onTextMarkUpdate(TextMark *mark, bool isAdd) {
    QString filePath = mark->fileName();
    int iComIdx = ui->mDocumentCombo->findData(filePath);
    if (iComIdx != -1) {
        TextEditorWidget* p = (TextEditorWidget*)ui->mEditStackedWidget->widget(iComIdx);
        p->editor()->updateTextMark(mark, isAdd);
    }
}

void EditorTab::documentIndxChanged(int index) {
    if(index == -1) {
        ui->mMethodCombo->clear();
        return;
    }
    ui->mEditStackedWidget->setCurrentIndex(index);
    updateEditorMsg(ui->mDocumentCombo->currentData().toString());
}

void EditorTab::updateEditorMsg(QString file) {
    ui->mMethodCombo->clear();
    auto smalianalysis = SmaliAnalysis::instance();
    auto filedata = smalianalysis->getSmaliFile(file);
    if(filedata.isNull()) {
        return;
    }
    for(auto i = 0, count = filedata->fieldCount(); i < count; i++) {
        auto field = filedata->field(i);
        ui->mMethodCombo->addItem(m_fieldIcon, field->m_name, field->m_line);
    }
    for(auto i = 0, count = filedata->methodCount(); i < count; i++) {
        auto method = filedata->method(i);
        ui->mMethodCombo->addItem(m_methodIcon, method->m_name, method->m_startline);
    }
}

void EditorTab::methodIndexChanged(int index) {
    if(index == -1) {
        return;
    }
    auto line = ui->mMethodCombo->currentData().toInt();
    TextEditorWidget* e = (TextEditorWidget*)ui->mEditStackedWidget->currentWidget();
    if(e == nullptr)
        return;
    e->editor()->gotoLine (line);
}

void EditorTab::reloadFile(QString filePath) {
    int iComIdx = ui->mDocumentCombo->findData(filePath);
    if (iComIdx != -1) {
        TextEditorWidget* p = (TextEditorWidget*)ui->mEditStackedWidget->widget(iComIdx);
        p->reload(1500);
    }
}



