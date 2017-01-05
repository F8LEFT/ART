//===- BreakPointDelegate.h - ART-GUI BreakPoint --------------------*- C++ -*-===//
//
//                     ANDROID REVERSE TOOLKIT
//
// This file is distributed under the GNU GENERAL PUBLIC LICENSE
// V3 License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// BreakPointDelegate show how to parse a bookmark msg
//
//===----------------------------------------------------------------------===//

#ifndef ANDROIDREVERSETOOLKIT_BREAKPOINTDELEGATE_H
#define ANDROIDREVERSETOOLKIT_BREAKPOINTDELEGATE_H

#include <QStyledItemDelegate>

class BreakPointDelegate  : public QStyledItemDelegate
{
Q_OBJECT

public:
    BreakPointDelegate(QWidget *parent = 0) : QStyledItemDelegate(parent) {}

    void paint(QPainter *painter, const QStyleOptionViewItem &option,
               const QModelIndex &index) const Q_DECL_OVERRIDE;
    QSize sizeHint(const QStyleOptionViewItem &option,
                   const QModelIndex &index) const Q_DECL_OVERRIDE;
};


#endif //ANDROIDREVERSETOOLKIT_BREAKPOINTDELEGATE_H
