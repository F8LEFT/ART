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
// ---------------------------- BlockData ---------------
class SmaliBlockData : public QTextBlockUserData {
public:
    SmaliBlockData() {};
    ~SmaliBlockData() {};

    bool m_bookmark = false;    // How to change bookmark to blockdata?

    bool m_breakpoint = false;
    bool m_foldable = false;
    bool m_foloded = false;

    int m_foldType = 0;
};
// ------------------------------------------------------

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
    auto userdata = (SmaliBlockData*) block.userData();
    if(userdata != nullptr) {
        return userdata->m_foldable;
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
    auto userdata = (SmaliBlockData*) startBlock.userData();
    if(userdata == nullptr)
        return QTextBlock();
    auto type = userdata->m_foldType;
    auto block = startBlock.next();
    while(block.isValid()) {
        userdata = (SmaliBlockData*) block.userData();
        if(userdata != nullptr && userdata->m_foldType == type) {
            break;
        }
        block = block.next();
    }
    return block;
}

int SmaliEditor::sidebarWidth() const
{
    return TextEditor::sidebarWidth();
}

void SmaliEditor::sidebarPaintEvent(QPaintEvent *event)
{
    TextEditor::sidebarPaintEvent(event);
}

void SmaliEditor::updateSidebarGeometry() {
    setViewportMargins(sidebarWidth(), 0, 0, 0);
    const auto r = contentsRect();
    m_sideBar->setGeometry(QRect(r.left(), r.top(), sidebarWidth(), r.height()));
}

void SmaliEditor::reloadSmaliData() {
    m_smalidata.reset(new SmaliFile("", toPlainText().toStdString()));

    auto root = m_smalidata->m_smali;

    // for foldable
    auto annotations = root->annotation();
    for(auto &annotation: annotations) {
        setAnnotationFold(annotation);
    }
    auto methods = root->method();
    for(auto& method: methods) {
        auto startLine = method->METHOD_DIRECTIVE()->getSymbol()->getLine() - 1;
        auto endLine = method->END_METHOD_DIRECTIVE()->getSymbol()->getLine() - 1;
        setFoldableArea(startLine, endLine, SmaliParser::METHOD_DIRECTIVE);
    }
}

void SmaliEditor::setAnnotationFold(SmaliParser::AnnotationContext *annotation) {
    auto startLine = annotation->ANNOTATION_DIRECTIVE()->getSymbol()->getLine() - 1;
    auto endLine = annotation->END_ANNOTATION_DIRECTIVE()->getSymbol()->getLine() - 1;
    setFoldableArea(startLine, endLine, SmaliParser::ANNOTATION_DIRECTIVE);
}

void SmaliEditor::setFoldableArea(int startLine, int endLine, int type) {
    auto blockstartdata = blockDataAtLine(startLine);
    auto blockenddata = blockDataAtLine(endLine);
    // TODO clear data between two block?
    blockstartdata->m_foldable = true;
    blockstartdata->m_foldType = type;
    blockenddata->m_foldType = type;
}

SmaliBlockData *SmaliEditor::blockDataAtLine(int line) {
    auto block = blockAtLine(line);
    auto userdata = (SmaliBlockData*)block.userData();
    if(userdata == nullptr) {
        userdata = new SmaliBlockData();
        block.setUserData(userdata);
    }
    return userdata;
}



SmaliData::SmaliData() {

}

SmaliData::~SmaliData() {

}

SmaliSideBar::SmaliSideBar(SmaliEditor *editor)
    : TextEditorSidebar(editor)
{

}

SmaliSideBar::~SmaliSideBar()
{

}

QSize SmaliSideBar::sizeHint() const {
    return TextEditorSidebar::sizeHint();
}

void SmaliSideBar::paintEvent(QPaintEvent *event) {
    TextEditorSidebar::paintEvent(event);
}

void SmaliSideBar::mouseReleaseEvent(QMouseEvent *event) {
    TextEditorSidebar::mouseReleaseEvent(event);
}
