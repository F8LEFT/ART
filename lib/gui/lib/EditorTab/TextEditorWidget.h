//===- TextEditorWidget.h - ART-GUI Editor Tab -----------------*- C++ -*-===//
//
//                     ANDROID REVERSE TOOLKIT
//
// This file is distributed under the GNU GENERAL PUBLIC LICENSE
// V3 License. See LICENSE.TXT for details.
//
//===---------------------------------------------------------------------===//
//
// This file defines an Editor to modify text.
//
//===----------------------------------------------------------------------===//
#ifndef PROJECT_TEXTEDITOR_H
#define PROJECT_TEXTEDITOR_H
#include <QWidget>
#include <QPlainTextEdit>
#include <QAction>
#include <QList>
#include <BookMark/BookMark.h>

class LineNumberArea;
class TextEditorWidget: public QPlainTextEdit
{
    Q_OBJECT

public:
    TextEditorWidget (QWidget *parent = 0);

    ~TextEditorWidget () override;

    QString documentPath ();
    void setDocumentPath (QString path);

    void lineNumberAreaPaintEvent (QPaintEvent *event);
    int lineNumberAreaWidth ();

    void gotoLine (int line,int column = 0,bool centerLine = true);
    int currentLine();
protected:
    void resizeEvent (QResizeEvent *e) Q_DECL_OVERRIDE;

    void keyPressEvent (QKeyEvent *event) Q_DECL_OVERRIDE;

    virtual QWidget* allocLineArea ();

private slots:
    void updateLineNumberAreaWidth (int newBlockCount);

    void highlightCurrentLine ();

    void updateLineNumberArea (const QRect &,int);

private:
    void updateCurrentLineBookMark();       // add or delete bookmark for currentline

private:
    QWidget *lineNumberArea;

    QString mDocumentPath;

};

// LineNumberArea show linenumber in the TextEditorWidget
class LineNumberArea : public QWidget
{
public:
    LineNumberArea(TextEditorWidget* editor) : QWidget(editor) {
        textEditor = editor;
    }

    QSize sizeHint() const Q_DECL_OVERRIDE {
        return QSize(textEditor->lineNumberAreaWidth(), 0);
    }

protected:
    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE {
        textEditor->lineNumberAreaPaintEvent(event);
    }

private:
    TextEditorWidget* textEditor;
};

#endif //PROJECT_TEXTEDITOR_H
