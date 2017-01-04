//===- TextMark.h - ART-GUI TextEditorWidget Tab ---------------*- C++ -*-===//
//
//                     ANDROID REVERSE TOOLKIT
//
// This file is distributed under the GNU GENERAL PUBLIC LICENSE
// V3 License. See LICENSE.TXT for details.
//
//===---------------------------------------------------------------------===//
//
// Special text mark for breakpoint, bookmark, etc.
//
//===----------------------------------------------------------------------===//

#ifndef ANDROIDREVERSETOOLKIT_TEXTMARK_H
#define ANDROIDREVERSETOOLKIT_TEXTMARK_H

#include <QString>
#include <QIcon>
#include <QTextDocument>
#include <QColor>

class TextMarkRegistry;

class TextMark {
public:
    TextMark(const QString &fileName, int lineNumber):
            m_fileName(fileName),
            m_lineNumber(lineNumber),
            m_priority(NormalPriority),
            m_visible(true),
            m_widthFactor(1.0){}
    virtual ~TextMark() {};

    TextMark(TextMark &&other) Q_DECL_NOEXCEPT
        : m_fileName(std::move(other.m_fileName)),
          m_lineNumber(std::move(other.m_lineNumber)),
          m_priority(std::move(other.m_priority)),
          m_visible(std::move(other.m_visible)),
          m_icon(std::move(other.m_icon)),
          m_color(std::move(other.m_color)),
          m_widthFactor(std::move(other.m_widthFactor)) {}

    // determine order on markers on the same line.
    enum Priority
    {
        LowPriority,
        NormalPriority,
        HighPriority // shown on top.
    };

    QString fileName() const { return m_fileName; };
    int lineNumber() const { return m_lineNumber; };
    // print mark icon
    virtual void paint(QPainter *painter, const QRect &rect) const {
        m_icon.paint(painter, rect, Qt::AlignCenter);};
    /// called if the filename of the document changed
    virtual void updateFileName(const QString &fileName) {
        if (fileName == m_fileName)
            return;
        m_fileName = fileName;
    };
    virtual void updateLineNumber(int lineNumber) {m_lineNumber = lineNumber;};
    virtual void updateBlock(const QTextBlock &block) {};
    virtual void move(int line) {
        if (line == m_lineNumber)
            return;
//        const int previousLine = m_lineNumber;
        m_lineNumber = line;
    };
    virtual void removedFromEditor() {};
    virtual bool isClickable() const { return false; }
    virtual void clicked() {};
    virtual bool isDraggable() const { return false; }
    virtual void dragToLine(int lineNumber) { Q_UNUSED(lineNumber); };

    void setIcon(const QIcon &icon) { m_icon = icon; };
    // call this if the icon has changed.
    void updateMarker() {} ;
    Priority priority() const { return m_priority; };
    void setPriority(Priority prioriy) { m_priority = prioriy; }
    bool isVisible() const { return m_visible; }
    void setVisible(bool isVisible) { m_visible = isVisible; }
    double widthFactor() const { return m_widthFactor; }
    void setWidthFactor(double factor) { m_widthFactor = factor; };


private:
    Q_DISABLE_COPY(TextMark)
    friend class TextMarkRegistry;

    QString m_fileName;
    int m_lineNumber;
    Priority m_priority;
    bool m_visible;
    QIcon m_icon;
    QColor m_color;
    double m_widthFactor;
};



#endif //ANDROIDREVERSETOOLKIT_TEXTMARK_H
