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
#include <QGridLayout>


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
