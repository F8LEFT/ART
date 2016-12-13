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

#include <Repository>
#include <Theme>

#include <QPlainTextEdit>

class TextEditorSidebar;

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

protected:
    void resizeEvent(QResizeEvent *event) Q_DECL_OVERRIDE;

public:
    virtual void setTheme(const KSyntaxHighlighting::Theme &theme);

protected:
    friend class TextEditorSidebar;
    virtual int sidebarWidth() const;
    virtual void sidebarPaintEvent(QPaintEvent *event);
    virtual void updateSidebarGeometry();
    void updateSidebarArea(const QRect &rect, int dy);
    void highlightCurrentLine();

    QTextBlock blockAtPosition(int y) const;
    virtual bool isFoldable(const QTextBlock &block) const;
    virtual bool isFolded(const QTextBlock &block) const;
    virtual QTextBlock findFoldingRegionEnd(const QTextBlock &startBlock) const;
    void toggleFold(const QTextBlock &block);

    TextEditorSidebar *m_sideBar;
    KSyntaxHighlighting::Repository m_repository;
    KSyntaxHighlighting::Theme m_theme;
};



class TextEditorSidebar : public QWidget
{
Q_OBJECT
public:
    explicit TextEditorSidebar(TextEditor *editor);
    virtual ~TextEditorSidebar();
    QSize sizeHint() const Q_DECL_OVERRIDE;

protected:
    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;
    void mouseReleaseEvent(QMouseEvent *event) Q_DECL_OVERRIDE;

private:
    TextEditor *m_textEditor;
    friend class TextEditor;
};

#endif //ANDROIDREVERSETOOLKIT_TEXTEDITOR_H
