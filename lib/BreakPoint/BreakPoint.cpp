//===- BreakPoint.cpp - ART-GUI BreakPoint -------------------------*- C++ -*-===//
//
//                     ANDROID REVERSE TOOLKIT
//
// This file is distributed under the GNU GENERAL PUBLIC LICENSE
// V3 License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
#include "BreakPoint/BreakPoint.h"

#include "BreakPoint/BreakPointManager.h"

#include <utils/CmdMsgUtil.h>
#include <QtCore/QFileInfo>
#include <QPainter>
#include <QFontMetrics>

BreakPoint::BreakPoint(int lineNumber, BreakPointManager *manager) :
        TextMark(QString(), lineNumber),
        m_manager(manager)
{
    setIcon(m_manager->bookmarkIcon());
    QFont font;
    QFontMetrics fontMetrics(font);
    m_fontWidth = fontMetrics.width('9');
    m_fontHeight = fontMetrics.height();
}

void BreakPoint::removedFromEditor()
{
    m_manager->deleteBreakpoint(this);
}

void BreakPoint::updateLineNumber(int line)
{
    if (line != lineNumber()) {
        TextMark::updateLineNumber(line);
        m_manager->updateBreakpoint(this);
    }
}

void BreakPoint::move(int line)
{
    if (line != lineNumber()) {
        TextMark::move(line);
        m_manager->updateBreakpoint(this);
    }
}

void BreakPoint::updateBlock(const QTextBlock &block)
{
    if (m_lineText != block.text()) {
        m_lineText = block.text();
        m_manager->updateBreakpoint(this);
    }
}

void BreakPoint::updateFileName(const QString &fileName)
{
    const QString &oldFileName = this->fileName();
    TextMark::updateFileName(fileName);
    m_manager->updateBreakpointFileName(this, oldFileName);
}

void BreakPoint::setNote(const QString &note)
{
    m_note = note;
}

void BreakPoint::updateNote(const QString &note)
{
    setNote(note);
    m_manager->updateBreakpoint(this);
}

QString BreakPoint::lineText() const
{
    return m_lineText;
}

QString BreakPoint::note() const
{
    return m_note;
}

void BreakPoint::paintMark(QPainter *painter, const QRect &rect,
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

QSize BreakPoint::sizeHint() {
    return QSize(0, m_fontHeight * 2 + 5);
}
