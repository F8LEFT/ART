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

TextEditorWidget::TextEditorWidget(QWidget *parent):
        QPlainTextEdit(parent)
{
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

void TextEditorWidget::resizeEvent(QResizeEvent *e)
{
    QPlainTextEdit::resizeEvent(e);

    QRect cr = contentsRect();
    lineNumberArea->setGeometry(QRect(cr.left(), cr.top(), lineNumberAreaWidth(), cr.height()));
}

void TextEditorWidget::keyPressEvent(QKeyEvent *e)
{
    if (e->modifiers() == (Qt::ControlModifier)) {
        switch (e->key()) {
            case Qt::Key_M:           // BookMark
                return;
            default:
                break;
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
    QList<QTextEdit::ExtraSelection> extraSelections;
    if (!isReadOnly()) {
        QTextEdit::ExtraSelection selection;

        QColor lineColor = QColor(Qt::yellow).lighter(160);

        selection.format.setBackground(lineColor);
        selection.format.setProperty(QTextFormat::FullWidthSelection, true);
        selection.cursor = textCursor();
        selection.cursor.clearSelection();
        extraSelections.append(selection);
    }
    setExtraSelections(extraSelections);
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
