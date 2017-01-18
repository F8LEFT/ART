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
    if (index.data(VariableTreeItem::ItemRole::Item).canConvert<VariableTreeItem*>()) {
        VariableTreeItem* item = index.data(VariableTreeItem::ItemRole::Item).value<VariableTreeItem*>();

        if (option.state & QStyle::State_Selected)
            painter->fillRect(option.rect, option.palette.highlight());
        item->paintItem(painter, option.rect, option.palette);
    } else {
        QStyledItemDelegate::paint(painter, option, index);
    }
}

QWidget *VariableItemDelegate::createEditor(QWidget *parent,
                                            const QStyleOptionViewItem &option,
                                            const QModelIndex &index) const {
    if (index.data(VariableTreeItem::ItemRole::Item).canConvert<VariableTreeItem*>()) {
        VariableTreeItem* item = index.data(VariableTreeItem::ItemRole::Item).value<VariableTreeItem*>();
        auto editor = new VariableEditor(item, parent);
        connect(editor, &VariableEditor::returnPressed, this, &VariableItemDelegate::commitAndCloseEditor);
        return editor;
    } else {
        return QStyledItemDelegate::createEditor(parent, option, index);
    }
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
