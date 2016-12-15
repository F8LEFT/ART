//===- CodeEditor.cpp - ART-GUI Editor Tab ---------------------*- C++ -*-===//
//
//                     ANDROID REVERSE TOOLKIT
//
// This file is distributed under the GNU GENERAL PUBLIC LICENSE
// V3 License. See LICENSE.TXT for details.
//
//===---------------------------------------------------------------------===//

#include "EditorTab/CodeEditor.h"

#include <syntaxhighlighter.h>
#include <definition.h>



CodeEditor::CodeEditor(QWidget *parent)
        : TextEditor(parent),
          m_highlighter(new KSyntaxHighlighting::SyntaxHighlighter(document()))
{
    m_highlighter->setTheme(m_theme);
}

CodeEditor::~CodeEditor()
{

}

bool CodeEditor::openFile(const QString &fileName, int iLine)
{
    const auto def = m_repository.definitionForFileName(fileName);
    m_highlighter->setDefinition(def);
    if(!TextEditor::openFile(fileName, iLine)) {
        return false;
    }

    return true;
}

void CodeEditor::setTheme(const KSyntaxHighlighting::Theme &theme)
{
    m_highlighter->setTheme(theme);
    m_highlighter->rehighlight();
    TextEditor::setTheme(theme);
}

bool CodeEditor::isFoldable(const QTextBlock &block) const
{
    return m_highlighter->startsFoldingRegion(block);
}

bool CodeEditor::isFolded(const QTextBlock &block) const
{
    if (!block.isValid())
        return false;
    const auto nextBlock = block.next();
    if (!nextBlock.isValid())
        return false;
    return !nextBlock.isVisible();
}

QTextBlock CodeEditor::findFoldingRegionEnd(const QTextBlock &startBlock) const
{
    return m_highlighter->findFoldingRegionEnd(startBlock);
}

