//===- TextEditor.h - ART-GUI Editor Tab -----------------------*- C++ -*-===//
//
//                     ANDROID REVERSE TOOLKIT
//
// This file is distributed under the GNU GENERAL PUBLIC LICENSE
// V3 License. See LICENSE.TXT for details.
//
//===---------------------------------------------------------------------===//
//
// TextEditor defines the base editor action for text file.
//
//===----------------------------------------------------------------------===//

#ifndef ANDROIDREVERSETOOLKIT_TEXTEDITOR_H
#define ANDROIDREVERSETOOLKIT_TEXTEDITOR_H

#include "TextMark.h"

#include <Repository>
#include <Theme>

#include <QPlainTextEdit>
#include <syntaxhighlighter.h>
#include <QShortcut>
#include <QTimer>


class TextEditorSidebar;
class TextMark;
class UserBlockExtraData;

typedef QList<TextMark *> TextMarks;

class TextEditor : public QPlainTextEdit {
    Q_OBJECT
public:
    explicit TextEditor(QWidget *parent = Q_NULLPTR);
    virtual ~TextEditor();

    void setSidebar(TextEditorSidebar* sidebar);
    virtual bool openFile(const QString &fileName, int iLine = 1);
    virtual bool saveFile();
    virtual bool reload();

    void gotoLine (int line,int column = 0,bool centerLine = true);
    int currentLine();

    void updateTextMark(TextMark* textMark, bool add);
public slots:
    void toggleBookmark();
    void editorContentsChange(int position, int charsRemoved, int charsAdded);

protected:
    void resizeEvent(QResizeEvent *event) Q_DECL_OVERRIDE;
    virtual void keyPressEvent(QKeyEvent *e) Q_DECL_OVERRIDE;
public:
    virtual void setTheme(const KSyntaxHighlighting::Theme &theme);
    void resetTheme(QStringList name);
protected:
    friend class TextEditorSidebar;
    virtual int sidebarWidth() const;
    virtual void sidebarPaintEvent(QPaintEvent *event);
    virtual void updateSidebarGeometry();
    void updateSidebarArea(const QRect &rect, int dy);
    void highlightCurrentLine();

    virtual QTextBlock findFoldingRegionEnd(const QTextBlock &startBlock) const;

    void updateBookMark();
    void updateTextMark(TextMarks marks);

protected:
    QTimer m_sideBarUpdateTimer;
private:
    void updateMarksLineNumber();
    void updateMarksBlock(QTextBlock &block);
public:
    QTextBlock blockAtPosition(int y) const;
    QTextBlock blockAtLine(int l) const;
    UserBlockExtraData* blockData(QTextBlock& block);
    virtual bool isFoldable(const QTextBlock &block) const;
    virtual bool isFolded(const QTextBlock &block) const;
    void toggleFold(const QTextBlock &block);

    TextEditorSidebar *m_sideBar;
    KSyntaxHighlighting::Repository m_repository;
    KSyntaxHighlighting::Theme m_theme;

    QString m_filePath;
};

class TextEditorSidebar : public QWidget
{
    Q_OBJECT
public:
    explicit TextEditorSidebar(TextEditor *editor);
    virtual ~TextEditorSidebar();
    virtual QSize sizeHint() const Q_DECL_OVERRIDE;

protected:
    virtual void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;
    virtual void mouseReleaseEvent(QMouseEvent *event) Q_DECL_OVERRIDE;

    TextEditor *m_textEditor;
    friend class TextEditor;
};

class UserBlockExtraData: public QTextBlockUserData {
public:
    TextMarks m_marks;
};

// TextMark is used for marking special block, such for bookmark, breakpoint


#endif //ANDROIDREVERSETOOLKIT_TEXTEDITOR_H
