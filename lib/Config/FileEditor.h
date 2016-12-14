//===- FileEditor.h - ART-GUI Config ---------------------------*- C++ -*-===//
//
//                     ANDROID REVERSE TOOLKIT
//
// This file is distributed under the GNU GENERAL PUBLIC LICENSE
// V3 License. See LICENSE.TXT for details.
//
//===---------------------------------------------------------------------===//
//
// Set Text Editor config.
//
//===----------------------------------------------------------------------===//
#ifndef FILEEDITOR_H
#define FILEEDITOR_H

#include "FileTextStyleConfig.h"
#include "FileFontConfig.h"
#include "FileEditorColorConfig.h"

#include <EditorTab/SmaliEditor.h>


#include <QWidget>
#include <QList>


namespace Ui {
class FileEditor;
}

class FileEditor : public QWidget
{
    Q_OBJECT

public:
    explicit FileEditor(QWidget *parent = 0);
    ~FileEditor();
    void save();

    void setTheme(KSyntaxHighlighting::Theme theme);

private:
    void setupThemeGroup();

protected slots:
    void onSchemeCopyBtnClick();
    void onSchemeDeleteBtnClick();

private:
    Ui::FileEditor *ui;

    FileSchemeConfig* m_textStyleConfig;
    FileFontConfig* m_fontConfig;
    FileEditorColorConfig* m_editorColorConfig;


    KSyntaxHighlighting::Repository m_repository;
    KSyntaxHighlighting::Theme m_theme;

    SmaliEditor* m_Editor;
};


#endif // FILEEDITOR_H
