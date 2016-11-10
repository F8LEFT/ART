//===- TextEditorWidget.cpp - ART-GUI Editor Tab ---------------*- C++ -*-===//
//
//                     ANDROID REVERSE TOOLKIT
//
// This file is distributed under the GNU GENERAL PUBLIC LICENSE
// V3 License. See LICENSE.TXT for details.
//
//===---------------------------------------------------------------------===//
#include "TextEditorWidget.h"
#include <QPainter>
#include <QTextBlock>
#include <QDebug>
#include <BookMark/BookMarkManager.h>
#include <QList>

TextEditorWidget::TextEditorWidget(QWidget *parent):
        QPlainTextEdit(parent)
{
    setLineWrapMode(QPlainTextEdit::NoWrap);

    lineNumberArea = allocLineArea();

    connect(this, SIGNAL(blockCountChanged(int)), this, SLOT(updateLineNumberAreaWidth(int)));
    connect(this, SIGNAL(updateRequest(QRect,int)), this, SLOT(updateLineNumberArea(QRect,int)));
    connect(this, SIGNAL(cursorPositionChanged()), this, SLOT(highlightCurrentLine()));

    updateLineNumberAreaWidth(0);
    highlightCurrentLine();
}

TextEditorWidget::~TextEditorWidget()
{
}

QString TextEditorWidget::documentPath()
{
    return mDocumentPath;
}

void TextEditorWidget::setDocumentPath(QString path)
{
    mDocumentPath = path;
}

void TextEditorWidget::lineNumberAreaPaintEvent(QPaintEvent *event)
{
    QPainter painter(lineNumberArea);
    painter.fillRect(event->rect(), Qt::lightGray);

    QTextBlock block = firstVisibleBlock();
    int blockNumber = block.blockNumber();
    int top = (int) blockBoundingGeometry(block).translated(contentOffset()).top();
    int bottom = top + (int)blockBoundingRect(block).height();

    while(block.isValid() && top <= event->rect().bottom()) {
        if (block.isVisible() && bottom >= event->rect().top()) {
            QString number = QString::number(blockNumber + 1);
            painter.setPen(Qt::black);
            painter.drawText(0, top, lineNumberArea->width(), fontMetrics().height(),
                             Qt::AlignRight, number);
        }

        block = block.next();
        top = bottom;
        bottom = top + (int) blockBoundingRect(block).height();
        ++blockNumber;
    }
}

int TextEditorWidget::lineNumberAreaWidth()
{
    int digits =1;
    int max = qMax(1, blockCount());
    while(max >= 10) {
        max /= 10;
        ++digits;
    }
    int space = 3+fontMetrics().width(QLatin1Char('9')) * digits;
    return space;
}

void TextEditorWidget::gotoLine(int line, int column, bool centerLine)
{
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
}

int TextEditorWidget::currentLine ()
{
    QTextCursor cursor = textCursor();
    QTextLayout *pLayout = cursor.block().layout();
    int nCurpos = cursor.position() - cursor.block().position();
    return pLayout->lineForTextPosition(nCurpos).lineNumber()
           + cursor.block().firstLineNumber() + 1;
}

void TextEditorWidget::resizeEvent(QResizeEvent *e)
{
    QPlainTextEdit::resizeEvent(e);

    QRect cr = contentsRect();
    lineNumberArea->setGeometry(QRect(cr.left(), cr.top(),
                                      lineNumberAreaWidth(), cr.height()));
}

void TextEditorWidget::keyPressEvent(QKeyEvent *e)
{
    if(e->type() == QEvent::KeyPress ) {
        if (e->modifiers() == (Qt::CTRL)) {
            switch (e->key()) {
                case Qt::Key_M:           // BookMark
                    updateCurrentLineBookMark();
                    return;
                case Qt::Key_F:
                    onCTRL_F_Click();
                    return;
                default:
                    break;
            }
        }
    }

    QPlainTextEdit::keyPressEvent(e);
}

void TextEditorWidget::updateLineNumberAreaWidth(int newBlockCount)
{
    setViewportMargins(lineNumberAreaWidth(), 0, 0, 0);
}

void TextEditorWidget::highlightCurrentLine()
{
    auto extra = extraSelections ();
    if(!extra.isEmpty ()) {
        extra.pop_front ();
    }

    if (!isReadOnly()) {
        QTextEdit::ExtraSelection selection;

        QColor lineColor = QColor(Qt::yellow).lighter(160);

        selection.format.setBackground(lineColor);
        selection.format.setProperty(QTextFormat::FullWidthSelection, true);
        selection.cursor = textCursor();
        selection.cursor.clearSelection();
        extra.push_front (selection);
    }
    setExtraSelections(extra);
}

void TextEditorWidget::updateLineNumberArea(const QRect &rect, int dy)
{
    if(dy != 0)
        lineNumberArea->scroll(0, dy);
    else
        lineNumberArea->update(0, rect.y(), lineNumberArea->width(), rect.height());
    if (rect.contains(viewport()->rect()))
        updateLineNumberAreaWidth(0);
}

QWidget *TextEditorWidget::allocLineArea ()
{
    return new LineNumberArea(this);
}

void TextEditorWidget::updateCurrentLineBookMark()
{
    QTextCursor cursor = textCursor();
    int nTextLine = currentLine ();

    auto* pBookMarkManager = BookMarkManager::instance ();

    // find existing bookmark
    auto &fileMap = pBookMarkManager->getFileBookMark (documentPath ());
    auto pBookMark = pBookMarkManager->findBookMark (fileMap, nTextLine);
    if(pBookMark != nullptr) {
        pBookMarkManager->delBookMark (documentPath (), pBookMark);
        return;;
    }

    // alloc new bookmark
    BookMark* nBook = pBookMarkManager->addBookMark(documentPath ());
    nBook->setHint(cursor.block().text());
    nBook->setFileName(documentTitle());
    nBook->setLine(nTextLine);
}

