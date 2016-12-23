//===- SmaliEditor.h - ART-GUI Editor Tab ----------------------*- C++ -*-===//
//
//                     ANDROID REVERSE TOOLKIT
//
// This file is distributed under the GNU GENERAL PUBLIC LICENSE
// V3 License. See LICENSE.TXT for details.
//
//===---------------------------------------------------------------------===//
//
// SmaliEditor is a widget to open/modify/save *.smali file.
//
//===----------------------------------------------------------------------===//


#ifndef ANDROIDREVERSETOOLKIT_SMALIEDITOR_H
#define ANDROIDREVERSETOOLKIT_SMALIEDITOR_H

#include "TextEditor.h"

#include "SmaliFile.h"


#include <SyntaxHighlighter>
#include <QPlainTextEdit>
#include <QSharedPointer>

class SmaliHighlight;
class SmaliBlockData;

class SmaliEditor : public TextEditor
{
    Q_OBJECT
public:
    explicit SmaliEditor(QWidget *parent = Q_NULLPTR);
    virtual ~SmaliEditor();

    bool openFile(const QString &fileName, int iLine = 1);

    void setTheme(const KSyntaxHighlighting::Theme &theme);

    void reloadSmaliData();

public:
    int sidebarWidth() const;
    void sidebarPaintEvent(QPaintEvent *event);

    void updateSidebarGeometry();

    bool isFoldable(const QTextBlock &block) const;
    bool isFolded(const QTextBlock &block) const;
    QTextBlock findFoldingRegionEnd(const QTextBlock &startBlock) const;

private:
    void setAnnotationFold(SmaliParser::AnnotationContext* annotation);
    void setFoldableArea(int startLine, int endLine, int type);
    SmaliBlockData* blockDataAtLine(int line);

private:
    SmaliHighlight *m_highlighter;
    QSharedPointer<SmaliFile> m_smalidata;
};

class SmaliData: public QTextBlockUserData
{
public:
    SmaliData();
    ~SmaliData();

private:
    bool m_breakpoint;

};

class SmaliSideBar: public TextEditorSidebar
{
Q_OBJECT
public:
    explicit SmaliSideBar(SmaliEditor *editor);
    ~SmaliSideBar();

    QSize sizeHint() const Q_DECL_OVERRIDE;

protected:
    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;
    void mouseReleaseEvent(QMouseEvent *event) Q_DECL_OVERRIDE;

private:
    friend class SmaliEditor;
};

#endif //ANDROIDREVERSETOOLKIT_SMALIEDITOR_H
