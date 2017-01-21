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
#include <BreakPoint/BreakPointManager.h>
// ------------------------------------------------------

SmaliEditor::SmaliEditor(QWidget *parent)
        : TextEditor(parent),
          m_highlighter(new SmaliHighlight(document()))
{
    setSidebar(new SmaliSideBar(this));
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
    readBreakMark();
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
    if(m_smalidata.isNull()) {
        return false;
    }
    auto line = block.firstLineNumber() + 1;
    for(auto i = 0, count = m_smalidata->methodCount(); i < count; i++) {
        auto method = m_smalidata->method(i);
        if(method->m_startline == line) {
            return true;
        }
    }
    return false;
}

bool SmaliEditor::isFolded(const QTextBlock &block) const
{
    if (!block.isValid())
        return false;
    const auto nextBlock = block.next();
    if (!nextBlock.isValid())
        return false;
    return !nextBlock.isVisible();
}

QTextBlock SmaliEditor::findFoldingRegionEnd(const QTextBlock &startBlock) const
{
    if(m_smalidata.isNull()) {
        return QTextBlock();
    }

    auto line = startBlock.firstLineNumber() + 1;
    int endLine = -1;
    for(auto i = 0, count = m_smalidata->methodCount(); i < count; i++) {
        auto method = m_smalidata->method(i);
        if(method->m_startline == line) {
            endLine = method->m_endline;
            break;
        }
    }
    if(endLine != -1) {
        auto block = startBlock;
        while(block.isValid()) {
            if(block.firstLineNumber()+1 >= endLine) {
                return block;
            }
            block = block.next();
        }
    }
    return QTextBlock();
}

void SmaliEditor::sidebarPaintEvent(QPaintEvent *event)
{
    TextEditor::sidebarPaintEvent(event);
}

void SmaliEditor::toggleBreakpoint() {
    BreakPointManager::instance()->toggleBreakpoint(m_filePath, currentLine());
    m_sideBarUpdateTimer.start(500);
}

void SmaliEditor::readBreakMark() {
    auto bookmarks = BreakPointManager::instance()->getBreakPoints(m_filePath);
    TextMarks marks;
    for(auto bookmark: bookmarks) {
        updateTextMark(bookmark, true);
    }
}

SmaliSideBar::SmaliSideBar(SmaliEditor *editor)
    : TextEditorSidebar(editor)
{

}

SmaliSideBar::~SmaliSideBar()
{

}


void SmaliSideBar::mouseReleaseEvent(QMouseEvent *event) {
    TextEditorSidebar::mouseReleaseEvent(event);
    auto block = m_textEditor->blockAtPosition(event->y());
    if(!block.isValid()) {
        QWidget::mouseReleaseEvent(event);
        return;
    }
    auto space = m_textEditor->fontMetrics().lineSpacing();

    if (event->x() < space) {
        // breakpoint hit event
        SmaliEditor* editor = (SmaliEditor*)m_textEditor;
        editor->toggleBreakpoint();
        return;
    }
}
