//===- BookMark.h - ART-GUI BookMark ---------------------------*- C++ -*-===//
//
//                     ANDROID REVERSE TOOLKIT
//
// This file is distributed under the GNU GENERAL PUBLIC LICENSE
// V3 License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file defines BookMark used in Editor.
//
//===----------------------------------------------------------------------===//
#ifndef BOOKMARK_H
#define BOOKMARK_H

#include <EditorTab/TextMark.h>

#include <QWidget>
#include <QTextBlock>

class BookMarkManager;
class BookMark: public TextMark {
public:
    BookMark(int lineNumber, BookMarkManager *manager);

    void updateLineNumber(int lineNumber);
    void move(int line);
    void updateBlock(const QTextBlock &block);
    void updateFileName(const QString &fileName);
    void setNote(const QString &note);
    void updateNote(const QString &note);
    void removedFromEditor();

    QString lineText() const;
    QString note() const;

    void paintMark(QPainter *painter, const QRect &rect, const QPalette &palette) const;
    QSize sizeHint();
private:
    BookMarkManager *m_manager;
    QString m_lineText;
    QString m_note;

    int m_fontWidth;
    int m_fontHeight;
};

Q_DECLARE_METATYPE(BookMark*)

#endif // BOOKMARK_H
