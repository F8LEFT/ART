//===- CodeEditor.h - ART-GUI Editor Tab -----------------------*- C++ -*-===//
//
//                     ANDROID REVERSE TOOLKIT
//
// This file is distributed under the GNU GENERAL PUBLIC LICENSE
// V3 License. See LICENSE.TXT for details.
//
//===---------------------------------------------------------------------===//
//
// CodeEditor is used for edit normal file(with ksyntaxhighlighting).
//
//===----------------------------------------------------------------------===//

#ifndef ANDROIDREVERSETOOLKIT_CODEEDITOR_H
#define ANDROIDREVERSETOOLKIT_CODEEDITOR_H

#include "TextEditor.h"

namespace KSyntaxHighlighting {
    class SyntaxHighlighter;
}

class CodeEditor: public TextEditor
{
    Q_OBJECT
public:
    explicit CodeEditor(QWidget *parent = Q_NULLPTR);
    virtual ~CodeEditor();

    bool openFile(const QString &fileName, int iLine = 1);
protected:
    void setTheme(const KSyntaxHighlighting::Theme &theme);

    bool isFoldable(const QTextBlock &block) const;
    bool isFolded(const QTextBlock &block) const;
     QTextBlock findFoldingRegionEnd(const QTextBlock &startBlock) const;

private:
    KSyntaxHighlighting::SyntaxHighlighter *m_highlighter;
};


#endif //ANDROIDREVERSETOOLKIT_CODEEDITOR_H
