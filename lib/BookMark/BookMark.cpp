//===- BookMark.cpp - ART-GUI BookMark -------------------------*- C++ -*-===//
//
//                     ANDROID REVERSE TOOLKIT
//
// This file is distributed under the GNU GENERAL PUBLIC LICENSE
// V3 License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
#include "BookMark/BookMark.h"

#include "BookMark/BookMarkManager.h"

#include <utils/CmdMsgUtil.h>
#include <QtCore/QFileInfo>
#include <QPainter>
#include <QFontMetrics>

BookMark::BookMark(int lineNumber, BookMarkManager *manager) :
        TextMark(QString(), lineNumber),
        m_manager(manager)
{
    setIcon(m_manager->bookmarkIcon());
    QFont font;
    QFontMetrics fontMetrics(font);
    m_fontWidth = fontMetrics.width('9');
    m_fontHeight = fontMetrics.height();
}

void BookMark::removedFromEditor()
{
    m_manager->deleteBookmark(this);
}

void BookMark::updateLineNumber(int line)
{
    if (line != lineNumber()) {
        TextMark::updateLineNumber(line);
        m_manager->updateBookmark(this);
    }
}

void BookMark::move(int line)
{
    if (line != lineNumber()) {
        TextMark::move(line);
        m_manager->updateBookmark(this);
    }
}

void BookMark::updateBlock(const QTextBlock &block)
{
    if (m_lineText != block.text()) {
        m_lineText = block.text();
        m_manager->updateBookmark(this);
    }
}

void BookMark::updateFileName(const QString &fileName)
{
    const QString &oldFileName = this->fileName();
    TextMark::updateFileName(fileName);
    m_manager->updateBookmarkFileName(this, oldFileName);
}

void BookMark::setNote(const QString &note)
{
    m_note = note;
}

void BookMark::updateNote(const QString &note)
{
    setNote(note);
    m_manager->updateBookmark(this);
}

QString BookMark::lineText() const
{
    return m_lineText;
}

QString BookMark::note() const
{
    return m_note;
}

void BookMark::paintMark(QPainter *painter, const QRect &rect,
                         const QPalette &palette) const {
    painter->save();
    painter->setPen(Qt::black);
    QString name = QFileInfo(fileName()).fileName();
    QString line =  QString::number(lineNumber());

    painter->drawText(rect.x(), rect.y(), rect.width() - m_fontWidth * line.length() - 2, rect.height(),
                      Qt::AlignLeft | Qt::AlignTop, name);
    painter->drawText(rect, Qt::AlignRight | Qt::AlignRight, line);
    painter->setPen(Qt::gray);
    painter->drawText(rect, Qt::AlignLeft | Qt::AlignBottom, m_lineText.trimmed());
    painter->restore();
}

QSize BookMark::sizeHint() {
    return QSize(0, m_fontHeight * 2 + 5);
}
