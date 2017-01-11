//===- TextEditor.cpp - ART-GUI Editor Tab ---------------------*- C++ -*-===//
//
//                     ANDROID REVERSE TOOLKIT
//
// This file is distributed under the GNU GENERAL PUBLIC LICENSE
// V3 License. See LICENSE.TXT for details.
//
//===---------------------------------------------------------------------===//
#include "EditorTab/TextEditor.h"

#include <utils/ScriptEngine.h>
#include <utils/Configuration.h>

#include <QFile>
#include <QApplication>
#include <QPalette>
#include <QTextBlock>
#include <QPainter>
#include <QDebug>
#include <QShortcut>
#include <BookMark/BookMarkManager.h>

TextEditor::TextEditor(QWidget *parent) :
        QPlainTextEdit(parent),
        m_sideBar(new TextEditorSidebar(this))
{
    setFont(QFontDatabase::systemFont(QFontDatabase::FixedFont));
    setLineWrapMode(QPlainTextEdit::NoWrap);

    resetTheme(QStringList());
    m_sideBarUpdateTimer.setSingleShot(true);

    connect(document(), &QTextDocument::contentsChange, this, &TextEditor::editorContentsChange);

    connect(this, &QPlainTextEdit::blockCountChanged, this, &TextEditor::updateSidebarGeometry);
    connect(this, &QPlainTextEdit::updateRequest, this, &TextEditor::updateSidebarArea);
    connect(this, &QPlainTextEdit::cursorPositionChanged, this, &TextEditor::highlightCurrentLine);

    ScriptEngine* engine = ScriptEngine::instance();
    connect(engine, &ScriptEngine::themeUpdate, this, &TextEditor::resetTheme);

    connect(&m_sideBarUpdateTimer, &QTimer::timeout, [this](){
        document()->documentLayout()->documentSizeChanged(document()->documentLayout()->documentSize());
    });

    updateSidebarGeometry();
    highlightCurrentLine();
}

TextEditor::~TextEditor()
{

}

void TextEditor::setSidebar(TextEditorSidebar *sidebar)
{
    m_sideBar->deleteLater();
    m_sideBar = sidebar;
    m_sideBar->setParent(this);
    m_sideBar->m_textEditor = this;
    updateSidebarGeometry();
}

bool TextEditor::openFile(const QString &fileName, int iLine)
{
    QFile f(fileName);
    if (!f.open(QFile::ReadOnly)) {
        qWarning() << "Failed to open" << fileName << ":" << f.errorString();
        return false;
    }

    clear();

    setDocumentTitle(fileName);
    m_filePath = fileName;
    setPlainText(QString::fromUtf8(f.readAll()));
    gotoLine(iLine, 0, false);

    readBookMark();
    return true;
}

void TextEditor::resizeEvent(QResizeEvent *event)
{
    QPlainTextEdit::resizeEvent(event);
    updateSidebarGeometry();
}

void TextEditor::resetTheme(QStringList name)
{
    auto theme = m_repository.theme(ConfigString("Highlight","Theme"));
    if(!theme.isValid()) {
        theme = (palette().color(QPalette::Base).lightness() < 128)
                ? m_repository.defaultTheme(KSyntaxHighlighting::Repository::DarkTheme)
                : m_repository.defaultTheme(KSyntaxHighlighting::Repository::LightTheme);
    }
    m_theme = theme;
    setTheme(m_theme);

    QFont font;
    font.setFamily(ConfigString("Highlight", "Font"));
    font.setPixelSize(ConfigUint("Highlight", "FontSize"));
    if(ConfigBool("Highlight", "Antialias")) {
        font.setStyleStrategy(QFont::PreferAntialias);
    }

    setFont(font);
}

void TextEditor::setTheme(const KSyntaxHighlighting::Theme &theme)
{
    m_theme = theme;

    auto pal = qApp->palette();
    if (theme.isValid()) {
        pal.setColor(QPalette::Base, theme.editorColor(KSyntaxHighlighting::Theme::BackgroundColor));
        pal.setColor(QPalette::Text, theme.textColor(KSyntaxHighlighting::Theme::Normal));
        pal.setColor(QPalette::Highlight, theme.editorColor(KSyntaxHighlighting::Theme::TextSelection));
    }
    setPalette(pal);

    highlightCurrentLine();
}

int TextEditor::sidebarWidth() const
{
    int digits = 1;
    auto count = blockCount();
    while (count >= 10) {
        ++digits;
        count /= 10;
    }
    return 4 + fontMetrics().width(QLatin1Char('9')) * digits + 2 * fontMetrics().lineSpacing();
}

void TextEditor::sidebarPaintEvent(QPaintEvent *event)
{
    QPainter painter(m_sideBar);
    painter.fillRect(event->rect(), m_theme.editorColor(KSyntaxHighlighting::Theme::IconBorder));

    auto block = firstVisibleBlock();
    auto blockNumber = block.blockNumber();
    int top = blockBoundingGeometry(block).translated(contentOffset()).top();
    int bottom = top + blockBoundingRect(block).height();
    const int currentBlockNumber = textCursor().blockNumber();

    const auto foldingMarkerSize = fontMetrics().lineSpacing();

    while (block.isValid() && top <= event->rect().bottom()) {
        if (block.isVisible() && bottom >= event->rect().top()) {
            const auto number = QString::number(blockNumber + 1);
            painter.setPen(m_theme.editorColor(
                    (blockNumber == currentBlockNumber) ? KSyntaxHighlighting::Theme::CurrentLineNumber
                                                        : KSyntaxHighlighting::Theme::LineNumbers));
            painter.drawText(0, top, m_sideBar->width() - 2 - foldingMarkerSize, fontMetrics().height(), Qt::AlignRight, number);
        }

        // marks
        auto userdata = blockData(block);
        for(auto mark: userdata->m_marks) {
            mark->paint(&painter, QRect(0, top, foldingMarkerSize, foldingMarkerSize));
        }

        // folding marker
        if (block.isVisible() && isFoldable(block)) {
            QPolygonF polygon;
            if (isFolded(block)) {
                polygon << QPointF(foldingMarkerSize * 0.4, foldingMarkerSize * 0.25);
                polygon << QPointF(foldingMarkerSize * 0.4, foldingMarkerSize * 0.75);
                polygon << QPointF(foldingMarkerSize * 0.8, foldingMarkerSize * 0.5);
            } else {
                polygon << QPointF(foldingMarkerSize * 0.25, foldingMarkerSize * 0.4);
                polygon << QPointF(foldingMarkerSize * 0.75, foldingMarkerSize * 0.4);
                polygon << QPointF(foldingMarkerSize * 0.5, foldingMarkerSize * 0.8);
            }
            painter.save();
            painter.setRenderHint(QPainter::Antialiasing);
            painter.setPen(Qt::NoPen);
            painter.setBrush(QColor(m_theme.editorColor(KSyntaxHighlighting::Theme::CodeFolding)));
            painter.translate(m_sideBar->width() - foldingMarkerSize, top);
            painter.drawPolygon(polygon);
            painter.restore();
        }



        block = block.next();
        top = bottom;
        bottom = top + blockBoundingRect(block).height();
        ++blockNumber;
    }
}

void TextEditor::updateSidebarGeometry()
{
    setViewportMargins(sidebarWidth(), 0, 0, 0);
    const auto r = contentsRect();
    m_sideBar->setGeometry(QRect(r.left(), r.top(), sidebarWidth(), r.height()));
}

void TextEditor::updateSidebarArea(const QRect &rect, int dy)
{
    if (dy)
        m_sideBar->scroll(0, dy);
    else
        m_sideBar->update(0, rect.y(), m_sideBar->width(), rect.height());
}

void TextEditor::highlightCurrentLine()
{
    QTextEdit::ExtraSelection selection;
    selection.format.setBackground(QColor(m_theme.editorColor(KSyntaxHighlighting::Theme::CurrentLine)));
    selection.format.setProperty(QTextFormat::FullWidthSelection, true);
    selection.cursor = textCursor();
    selection.cursor.clearSelection();

    QList<QTextEdit::ExtraSelection> extraSelections;
    extraSelections.append(selection);
    setExtraSelections(extraSelections);
}

QTextBlock TextEditor::blockAtPosition(int y) const
{
    auto block = firstVisibleBlock();
    if (!block.isValid())
        return QTextBlock();

    int top = blockBoundingGeometry(block).translated(contentOffset()).top();
    int bottom = top + blockBoundingRect(block).height();
    do {
        if (top <= y && y <= bottom)
            return block;
        block = block.next();
        top = bottom;
        bottom = top + blockBoundingRect(block).height();
    } while (block.isValid());
    return QTextBlock();
}

QTextBlock TextEditor::blockAtLine(int l) const {
    return document()->findBlockByLineNumber(l - 1);
}

bool TextEditor::isFoldable(const QTextBlock &block) const
{
    return false;
}

bool TextEditor::isFolded(const QTextBlock &block) const
{
    return false;
}

QTextBlock TextEditor::findFoldingRegionEnd(const QTextBlock &startBlock) const {
    return QTextBlock();
}

void TextEditor::toggleFold(const QTextBlock &startBlock)
{
// we also want to fold the last line of the region, therefore the ".next()"
    const auto endBlock = findFoldingRegionEnd(startBlock).next();
    if(!endBlock.isValid()) {
        return;
    }

    if (isFolded(startBlock)) {
        // unfold
        auto block = startBlock.next();
        while (block.isValid() && !block.isVisible()) {
            block.setVisible(true);
            block.setLineCount(block.layout()->lineCount());
            block = block.next();
        }

    } else {
        // fold
        auto block = startBlock.next();
        while (block.isValid() && block != endBlock) {
            block.setVisible(false);
            block.setLineCount(0);
            block = block.next();
        }
    }

    // redraw document
    document()->markContentsDirty(startBlock.position(), endBlock.position() - startBlock.position() + 1);

    // update scrollbars
    m_sideBarUpdateTimer.start(500);
}

void TextEditor::gotoLine(int line, int column, bool centerLine) {
    const int blockNumber = qMin(line, document()->blockCount()) - 1;
    const QTextBlock &block = document()->findBlockByLineNumber(blockNumber);
    if (block.isValid()) {
        QTextCursor cursor(block);
        if (column > 0) {
            cursor.movePosition(QTextCursor::Right, QTextCursor::MoveAnchor, column);
        } else {
            int pos = cursor.position();
            while(document()->characterAt(pos).category() == QChar::Separator_Space) {
                ++pos;
            }
            cursor.setPosition(pos);
        }
        setTextCursor(cursor);
        if (centerLine) {
            centerCursor();
        } else {
            ensureCursorVisible();
        }
    }
    setFocus();
    raise();
}

int TextEditor::currentLine() {
    return textCursor().blockNumber() + 1;
}

bool TextEditor::saveFile() {
    if(!document()->isModified()) {
        return true;
    }
    QFile file(m_filePath);
    if (!file.open(QFile::WriteOnly | QFile::Truncate | QFile::Text)) {
        return false;
    }
    QTextStream out(&file);
    out<<toPlainText();
    out.flush();
    file.close();
    document()->setModified(false);
    return true;
}

bool TextEditor::reload()
{
    return openFile(m_filePath, currentLine());
}

UserBlockExtraData *TextEditor::blockData(QTextBlock &block) {
    auto userdata = (KSyntaxHighlighting::TextBlockUserData*)block.userData();
    if(userdata == nullptr) {
        userdata = new KSyntaxHighlighting::TextBlockUserData();
        block.setUserData(userdata);
    }
    if(userdata->data == nullptr) {
        userdata->data = new UserBlockExtraData();
    }
    return (UserBlockExtraData *)userdata->data;
}

void TextEditor::toggleBookmark() {
    BookMarkManager::instance()->toggleBookmark(m_filePath, currentLine());
}

void TextEditor::keyPressEvent(QKeyEvent *e) {
//    if(e->type() == QEvent::KeyPress && e->modifiers() == Qt::ControlModifier) {
//        switch (e->key()) {
//            case Qt::Key_M:
//                toggleBookmark();
//                return;
//            default:
//                break;
//        }
//    }
    QPlainTextEdit::keyPressEvent(e);
}

void TextEditor::readBookMark() {
    auto bookmarks = BookMarkManager::instance()->getBookMarks(m_filePath);
    TextMarks marks;
    for(auto bookmark: bookmarks) {
        updateTextMark(bookmark, true);
    }
}

void TextEditor::updateTextMark(TextMark *textMark, bool add) {
    auto line = textMark->lineNumber();
    auto block = blockAtLine(line);
    if(!block.isValid()) {
        return;
    }
    auto data = blockData(block);
    if(add == data->m_marks.contains(textMark)) {
        return;
    }
    if(add) {
        data->m_marks.push_back(textMark);
        textMark->updateBlock(block);
    } else {
        data->m_marks.removeOne(textMark);
    }

    m_sideBarUpdateTimer.start(500);
}

void TextEditor::editorContentsChange(int position, int charsRemoved,
                                      int charsAdded) {
    QTextDocument *doc = document();
    QTextBlock posBlock = doc->findBlock(position);

    // Keep the line numbers and the block information for the text marks updated
    if (charsRemoved != 0) {
        updateMarksLineNumber();
        updateMarksBlock(posBlock);
    } else {
        QTextBlock nextBlock = doc->findBlock(position + charsAdded);
        if (posBlock != nextBlock) {
            updateMarksLineNumber();
            updateMarksBlock(posBlock);
            updateMarksBlock(nextBlock);
        } else {
            updateMarksBlock(posBlock);
        }
    }
    m_sideBarUpdateTimer.start(500);
}

void TextEditor::updateMarksLineNumber() {
    QTextBlock block = document()->begin();
    int blockNumber = 0;
    while (block.isValid()) {
        auto userData = blockData(block);
        for(auto mark: userData->m_marks) {
            mark->updateLineNumber(blockNumber + 1);
        }
        block = block.next();
        ++blockNumber;
    }
}

void TextEditor::updateMarksBlock(QTextBlock &block) {
    auto userData = blockData(block);
    for(auto mark: userData->m_marks) {
        mark->updateBlock(block);
    }
}

// -------------------class TextEditorSidebar---------------------------

TextEditorSidebar::TextEditorSidebar(TextEditor *editor):
    QWidget(editor),
    m_textEditor(editor)
{

}

TextEditorSidebar::~TextEditorSidebar()
{

}

QSize TextEditorSidebar::sizeHint() const
{
    return QSize(m_textEditor->sidebarWidth(), 0);
}

void TextEditorSidebar::paintEvent(QPaintEvent *event)
{
    m_textEditor->sidebarPaintEvent(event);
}

void TextEditorSidebar::mouseReleaseEvent(QMouseEvent *event)
{
    auto block = m_textEditor->blockAtPosition(event->y());
    if(!block.isValid()) {
        QWidget::mouseReleaseEvent(event);
        return;
    }

    if (event->x() >= width() - m_textEditor->fontMetrics().lineSpacing()
        && m_textEditor->isFoldable(block)) {
        m_textEditor->toggleFold(block);
        return;
    }
    m_textEditor->gotoLine(block.firstLineNumber() + 1, 1, false);

    QWidget::mouseReleaseEvent(event);
}






