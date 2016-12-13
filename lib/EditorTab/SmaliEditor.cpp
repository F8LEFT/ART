//===- SmaliEditor.cpp - ART-GUI Editor Tab ----------------------*- C++ -*-===//
//
//                     ANDROID REVERSE TOOLKIT
//
// This file is distributed under the GNU GENERAL PUBLIC LICENSE
// V3 License. See LICENSE.TXT for details.
//
//===---------------------------------------------------------------------===//


#include "EditorTab/SmaliEditor.h"
#include "SmaliHighlight.h"

#include <QPainter>

SmaliEditor::SmaliEditor(QWidget *parent)
        : TextEditor(parent),
          m_highlighter(new SmaliHighlight(document()))
{
    m_highlighter->setTheme(m_theme);
}

SmaliEditor::~SmaliEditor()
{

}

bool SmaliEditor::openFile(const QString &fileName, int iLine)
{
    if(!TextEditor::openFile(fileName, 1)) {
        return false;
    }
    // TODO parse smali file and generate highlighter
    return true;
}

void SmaliEditor::setTheme(const KSyntaxHighlighting::Theme &theme)
{
    m_highlighter->setTheme(theme);
    m_highlighter->rehighlight();
    TextEditor::setTheme(theme);
}

bool SmaliEditor::isFoldable(const QTextBlock &block) const
{
    return TextEditor::isFoldable(block);
}

bool SmaliEditor::isFolded(const QTextBlock &block) const
{
    return TextEditor::isFolded(block);
}

QTextBlock SmaliEditor::findFoldingRegionEnd(const QTextBlock &startBlock) const
{
    return TextEditor::findFoldingRegionEnd(startBlock);
}

int SmaliEditor::sidebarWidth() const {
    return TextEditor::sidebarWidth();
}

void SmaliEditor::sidebarPaintEvent(QPaintEvent *event) {
    TextEditor::sidebarPaintEvent(event);
}

void SmaliEditor::updateSidebarGeometry() {
    setViewportMargins(sidebarWidth(), 0, 0, 0);
    const auto r = contentsRect();
    m_sideBar->setGeometry(QRect(r.left(), r.top(), sidebarWidth(), r.height()));
}
