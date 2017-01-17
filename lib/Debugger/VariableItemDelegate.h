//===- VariableItemDelegate.h - ART-DEBUGGER ---------------------*- C++ -*-===//
//
//                     ANDROID REVERSE TOOLKIT
//
// This file is distributed under the GNU GENERAL PUBLIC LICENSE
// V3 License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// Show Variable item value
//
//===----------------------------------------------------------------------===//

#ifndef ANDROIDREVERSETOOLKIT_VARIABLEITEMDELEGATE_H
#define ANDROIDREVERSETOOLKIT_VARIABLEITEMDELEGATE_H

#include <QLineEdit>
#include <QStyledItemDelegate>

class VariableTreeItem;

class VariableEditor: public QLineEdit {
    Q_OBJECT
public:
    VariableEditor(VariableTreeItem* item, QWidget *parent = Q_NULLPTR);
private:
    VariableTreeItem* m_item;
};

class VariableItemDelegate: public QStyledItemDelegate {
    Q_OBJECT

public:
    VariableItemDelegate(QWidget *parent = 0) : QStyledItemDelegate(parent) {}

    void paint(QPainter *painter, const QStyleOptionViewItem &option,
               const QModelIndex &index) const Q_DECL_OVERRIDE;

    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option,
                          const QModelIndex &index) const Q_DECL_OVERRIDE;
private slots:
    void commitAndCloseEditor();
};


#endif //ANDROIDREVERSETOOLKIT_VARIABLEITEMDELEGATE_H
