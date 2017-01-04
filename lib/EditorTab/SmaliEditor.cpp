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
//    auto userdata = (SmaliBlockData*) block.userData();
//    if(userdata != nullptr) {
//        return userdata->m_foldable;
//    }
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

int SmaliEditor::sidebarWidth() const
{
    int digits = 1;
    auto count = blockCount();
    while (count >= 10) {
        ++digits;
        count /= 10;
    }
    return 4 + fontMetrics().width(QLatin1Char('9')) * digits + 2 * fontMetrics().lineSpacing();

}

void SmaliEditor::sidebarPaintEvent(QPaintEvent *event)
{
    TextEditor::sidebarPaintEvent(event);
    QPainter painter(m_sideBar);

    auto block = firstVisibleBlock();
    auto blockNumber = block.blockNumber();
    int top = blockBoundingGeometry(block).translated(contentOffset()).top();
    int bottom = top + blockBoundingRect(block).height();

//    const auto foldingMarkerSize = fontMetrics().lineSpacing();

    while (block.isValid() && top <= event->rect().bottom()) {
        // breakpoint
//        auto blockdata = (SmaliBlockData*)block.userData();
//        if(blockdata != nullptr && blockdata->m_breakpoint) {
//            QPixmap image(":/images/breakpoint.png");
//            painter.drawPixmap(1, top + 1,
//                               foldingMarkerSize - 2, foldingMarkerSize - 2, image);
//        }

        block = block.next();
        top = bottom;
        bottom = top + blockBoundingRect(block).height();
        ++blockNumber;
    }
}

void SmaliEditor::updateSidebarGeometry() {
    setViewportMargins(sidebarWidth(), 0, 0, 0);
    const auto r = contentsRect();
    m_sideBar->setGeometry(QRect(r.left(), r.top(), sidebarWidth(), r.height()));
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
//    auto blockstartdata = blockDataAtLine(startLine);
//    auto blockenddata = blockDataAtLine(endLine);
//    // TODO clear data between two block?
//    blockstartdata->m_foldable = true;
//    blockstartdata->m_foldType = type;
//    blockenddata->m_foldType = type;
}


void SmaliEditor::toggleBreakpoint(QTextBlock &startBlock) {
//    auto userdata = blockData(startBlock);
//    userdata->m_breakpoint = !userdata->m_breakpoint;   // TODO emit breakpoint change

    // redraw document
    document()->markContentsDirty(startBlock.position(), startBlock.next().position() - startBlock.position() + 1);

    // update scrollbars
    document()->documentLayout()->documentSizeChanged(document()->documentLayout()->documentSize());

}

SmaliSideBar::SmaliSideBar(SmaliEditor *editor)
    : TextEditorSidebar(editor)
{

}

SmaliSideBar::~SmaliSideBar()
{

}


void SmaliSideBar::mouseReleaseEvent(QMouseEvent *event) {
    auto block = m_textEditor->blockAtPosition(event->y());
    auto space = m_textEditor->fontMetrics().lineSpacing();

    if (event->x() < space) {
        // breakpoint
        SmaliEditor* editor = (SmaliEditor*)m_textEditor;
        editor->toggleBreakpoint(block);
        return;
    }

    TextEditorSidebar::mouseReleaseEvent(event);
}
