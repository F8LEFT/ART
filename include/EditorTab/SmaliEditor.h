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

#include "SmaliAnalysis/SmaliFile.h"


#include <SyntaxHighlighter>
#include <QPlainTextEdit>
#include <QSharedPointer>

class SmaliHighlight;
class SmaliBlockData;
class SmaliSideBar;

class SmaliEditor : public TextEditor
{
    Q_OBJECT
public:
    explicit SmaliEditor(QWidget *parent = Q_NULLPTR);
    virtual ~SmaliEditor();

    bool openFile(const QString &fileName, int iLine = 1);

    void setTheme(const KSyntaxHighlighting::Theme &theme);
public:
    void sidebarPaintEvent(QPaintEvent *event);

    bool isFoldable(const QTextBlock &block) const;
    bool isFolded(const QTextBlock &block) const;
    QTextBlock findFoldingRegionEnd(const QTextBlock &startBlock) const;

    void toggleBreakpoint();

    void setSmaliData(QSharedPointer<SmaliFile> smalidata) { m_smalidata = smalidata; }
private:
    void readBreakMark();

private:
    SmaliHighlight *m_highlighter;
    QSharedPointer<SmaliFile> m_smalidata;

    friend class SmaliSideBar;
};

class SmaliSideBar: public TextEditorSidebar
{
Q_OBJECT
public:
    explicit SmaliSideBar(SmaliEditor *editor);
    ~SmaliSideBar();

protected:
    void mouseReleaseEvent(QMouseEvent *event) Q_DECL_OVERRIDE;

private:

    friend class SmaliEditor;
};

#endif //ANDROIDREVERSETOOLKIT_SMALIEDITOR_H
