//===- SmaliEditor.h - ART-GUI Editor Tab ----------------------*- C++ -*-===//
//
//                     ANDROID REVERSE TOOLKIT
//
// This file is distributed under the GNU GENERAL PUBLIC LICENSE
// V3 License. See LICENSE.TXT for details.
//
//===---------------------------------------------------------------------===//
//
// SmaliEditor is a widget to open/modify/save *.smali file.
//
//===----------------------------------------------------------------------===//


#ifndef ANDROIDREVERSETOOLKIT_SMALIEDITOR_H
#define ANDROIDREVERSETOOLKIT_SMALIEDITOR_H

#include "TextEditor.h"

#include "SmaliHighlight.h"

#include <SyntaxHighlighter>
#include <QPlainTextEdit>

class SmaliEditor : public TextEditor
{
    Q_OBJECT
public:
    explicit SmaliEditor(QWidget *parent = Q_NULLPTR);
    virtual ~SmaliEditor();

    bool openFile(const QString &fileName, int iLine = 1);

protected:
    void setTheme(const KSyntaxHighlighting::Theme &theme);
    int sidebarWidth() const;
    void sidebarPaintEvent(QPaintEvent *event);

    void updateSidebarGeometry();
    void updateButtombarInfo();

    bool isFoldable(const QTextBlock &block) const;
    bool isFolded(const QTextBlock &block) const;
    QTextBlock findFoldingRegionEnd(const QTextBlock &startBlock) const;

private:
    SmaliHighlight *m_highlighter;

    friend class SmaliEditorButtomBar;
};

#endif //ANDROIDREVERSETOOLKIT_SMALIEDITOR_H
