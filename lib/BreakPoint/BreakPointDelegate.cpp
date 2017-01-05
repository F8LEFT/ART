//===- BreakPointDelegate.cpp - ART-GUI BreakPoint ------------------*- C++ -*-===//
//
//                     ANDROID REVERSE TOOLKIT
//
// This file is distributed under the GNU GENERAL PUBLIC LICENSE
// V3 License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

#include "BreakPointDelegate.h"

#include <BreakPoint/BreakPoint.h>

#include <QVariant>
#include <QPainter>

void BreakPointDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option,
                        const QModelIndex &index) const {
    if (index.data().canConvert<BreakPoint*>()) {
        BreakPoint* mark = index.data().value<BreakPoint*>();

        if (option.state & QStyle::State_Selected)
            painter->fillRect(option.rect, option.palette.highlight());

        mark->paintMark(painter, option.rect, option.palette);
    } else {
        QStyledItemDelegate::paint(painter, option, index);
    }
}

QSize BreakPointDelegate::sizeHint(const QStyleOptionViewItem &option,
                                 const QModelIndex &index) const {
    if (index.data().canConvert<BreakPoint*>()) {
        BreakPoint* mark = index.data().value<BreakPoint*>();
        return mark->sizeHint();
    } else {
        return QStyledItemDelegate::sizeHint(option, index);
    }
}

