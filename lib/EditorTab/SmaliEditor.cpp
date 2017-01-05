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
    reloadSmaliData();
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
    return QTextBlock();
}

void SmaliEditor::sidebarPaintEvent(QPaintEvent *event)
{
    TextEditor::sidebarPaintEvent(event);
}

void SmaliEditor::reloadSmaliData() {
    // TODO parse data in another thread
//    m_smalidata.reset(new SmaliFile("", toPlainText().toStdString()));
//
//    auto root = m_smalidata->m_smali;
//
//    // for foldable
//    auto annotations = root->annotation();
//    for(auto &annotation: annotations) {
//        setAnnotationFold(annotation);
//    }
//    auto methods = root->method();
//    for(auto& method: methods) {
//        auto startLine = method->METHOD_DIRECTIVE()->getSymbol()->getLine() - 1;
//        auto endLine = method->END_METHOD_DIRECTIVE()->getSymbol()->getLine() - 1;
//        setFoldableArea(startLine, endLine, SmaliParser::METHOD_DIRECTIVE);
//    }
}

void SmaliEditor::setAnnotationFold(SmaliParser::AnnotationContext *annotation) {
    auto startLine = annotation->ANNOTATION_DIRECTIVE()->getSymbol()->getLine() - 1;
    auto endLine = annotation->END_ANNOTATION_DIRECTIVE()->getSymbol()->getLine() - 1;
    setFoldableArea(startLine, endLine, SmaliParser::ANNOTATION_DIRECTIVE);
}

void SmaliEditor::setFoldableArea(int startLine, int endLine, int type) {

}


void SmaliEditor::toggleBreakpoint() {
    BreakPointManager::instance()->toggleBreakpoint(m_filePath, currentLine());
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
