//===- BreakPoint.h - ART-GUI BreakPoint ---------------------------*- C++ -*-===//
//
//                     ANDROID REVERSE TOOLKIT
//
// This file is distributed under the GNU GENERAL PUBLIC LICENSE
// V3 License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file defines BreakPoint used in Editor.
//
//===----------------------------------------------------------------------===//
#ifndef BREAKPOINT_H
#define BREAKPOINT_H

#include <EditorTab/TextMark.h>

#include <QWidget>
#include <QTextBlock>

class BreakPointManager;
class BreakPoint: public TextMark {
public:
    BreakPoint(int lineNumber, BreakPointManager *manager);

    void updateLineNumber(int lineNumber);
    void move(int line);
    void updateBlock(const QTextBlock &block);
    void updateFileName(const QString &fileName);
    void removedFromEditor();

    QString lineText() const;
    void setLineText(const QString& line);

    void paintMark(QPainter *painter, const QRect &rect, const QPalette &palette) const;
    QSize sizeHint();
private:
    BreakPointManager *m_manager;
    QString m_lineText;

    int m_fontWidth;
    int m_fontHeight;
};

Q_DECLARE_METATYPE(BreakPoint*)

#endif // BREAKPOINT_H
