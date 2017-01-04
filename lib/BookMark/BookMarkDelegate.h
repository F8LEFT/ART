//===- BookMarkDelegate.h - ART-GUI BookMark --------------------*- C++ -*-===//
//
//                     ANDROID REVERSE TOOLKIT
//
// This file is distributed under the GNU GENERAL PUBLIC LICENSE
// V3 License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// BookMarkDelegate show how to parse a bookmark msg
//
//===----------------------------------------------------------------------===//

#ifndef ANDROIDREVERSETOOLKIT_BOOKMARKDELEGATE_H
#define ANDROIDREVERSETOOLKIT_BOOKMARKDELEGATE_H

#include <QStyledItemDelegate>

class BookMarkDelegate  : public QStyledItemDelegate
{
Q_OBJECT

public:
    BookMarkDelegate(QWidget *parent = 0) : QStyledItemDelegate(parent) {}

    void paint(QPainter *painter, const QStyleOptionViewItem &option,
               const QModelIndex &index) const Q_DECL_OVERRIDE;
    QSize sizeHint(const QStyleOptionViewItem &option,
                   const QModelIndex &index) const Q_DECL_OVERRIDE;
};


#endif //ANDROIDREVERSETOOLKIT_BOOKMARKDELEGATE_H
