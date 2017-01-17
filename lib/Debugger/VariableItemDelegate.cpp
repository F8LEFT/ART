//===- VariableItemDelegate.cpp - ART-DEBUGGER ------------------*- C++ -*-===//
//
//                     ANDROID REVERSE TOOLKIT
//
// This file is distributed under the GNU GENERAL PUBLIC LICENSE
// V3 License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

#include "VariableItemDelegate.h"
#include "VariableTreeView.h"

#include <QPainter>


void VariableItemDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option,
                               const QModelIndex &index) const {
    auto sitem = VariableModel::instance()->itemFromIndex(index);
    if(sitem == nullptr) {

    }
    auto item = (VariableTreeItem *)(sitem);
    if(item == nullptr) {
        QStyledItemDelegate::paint(painter, option, index);
        return;
    }
    item->paintItem(painter, option.rect, option.palette);
}

QWidget *VariableItemDelegate::createEditor(QWidget *parent,
                                            const QStyleOptionViewItem &option,
                                            const QModelIndex &index) const {
    auto sitem = VariableModel::instance()->itemFromIndex(index);
    if(sitem == nullptr) {
        return QStyledItemDelegate::createEditor(parent, option, index);
    }
    auto item = (VariableTreeItem *)(sitem);
    auto editor = new VariableEditor(item, parent);
    connect(editor, &VariableEditor::returnPressed, this, &VariableItemDelegate::commitAndCloseEditor);
    editor->setText("editext");
    return editor;
}

void VariableItemDelegate::commitAndCloseEditor()
{
    VariableEditor *editor = qobject_cast<VariableEditor *>(sender());
    commitData(editor);
    closeEditor(editor);
}

VariableEditor::VariableEditor(VariableTreeItem *item, QWidget *parent)
    : QLineEdit(parent), m_item(item)
{
    if(item != nullptr) {
        connect(this, &VariableEditor::returnPressed, [this]() {
            auto txt = text();
            m_item->applyEditValue(txt);
        });
        setText(m_item->getEditValue());
    }

}
