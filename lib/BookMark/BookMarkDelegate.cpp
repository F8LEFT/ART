//===- BookMarkDelegate.cpp - ART-GUI BookMark ------------------*- C++ -*-===//
//
//                     ANDROID REVERSE TOOLKIT
//
// This file is distributed under the GNU GENERAL PUBLIC LICENSE
// V3 License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

#include "BookMarkDelegate.h"

#include <BookMark/BookMark.h>

#include <QVariant>
#include <QPainter>

void BookMarkDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option,
                        const QModelIndex &index) const {
    if (index.data().canConvert<BookMark*>()) {
        BookMark* mark = index.data().value<BookMark*>();

        if (option.state & QStyle::State_Selected)
            painter->fillRect(option.rect, option.palette.highlight());

        mark->paintMark(painter, option.rect, option.palette);
    } else {
        QStyledItemDelegate::paint(painter, option, index);
    }
}

QSize BookMarkDelegate::sizeHint(const QStyleOptionViewItem &option,
                                 const QModelIndex &index) const {
    if (index.data().canConvert<BookMark*>()) {
        BookMark* mark = index.data().value<BookMark*>();
        return mark->sizeHint();
    } else {
        return QStyledItemDelegate::sizeHint(option, index);
    }
}

