//===- VariableTreeView.h - ART-DEBUGGER ------------------------*- C++ -*-===//
//
//                     ANDROID REVERSE TOOLKIT
//
// This file is distributed under the GNU GENERAL PUBLIC LICENSE
// V3 License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// VariableTreeView is used to show/edit variable value in current frame.
//
//===----------------------------------------------------------------------===//

#ifndef ANDROIDREVERSETOOLKIT_VARIABLETREEVIEW_H
#define ANDROIDREVERSETOOLKIT_VARIABLETREEVIEW_H

#include "Jdwp/jdwp.h"

#include <QStandardItem>
#include <QStandardItemModel>
#include <QTreeView>

struct VariableTreeItem: public QStandardItem {
public:
    explicit VariableTreeItem(const QString &name,
                              const JDWP::JValue &data = JDWP::JValue());
    ~VariableTreeItem();

    QVariant data(int role = Qt::UserRole + 1) const;
    QString display() const;
    QString value() const;

    VariableTreeItem* findchild(const QString& name);
    static VariableTreeItem* findchild(QStandardItem* parent, const QString& name);

    QString m_fieldName;
    JDWP::JValue m_data;
};

class VariableModel: public QStandardItemModel {
    Q_OBJECT

public:
    explicit VariableModel(QObject *parent = 0);
    ~VariableModel();

    static VariableModel* instance();
private:
};

class VariableTreeView: public QTreeView {
    Q_OBJECT
public:
    VariableTreeView(QWidget* parent = nullptr);
    ~VariableTreeView();

protected slots:
//    void onItemDoubleClicked(const QModelIndex &index);

private:
};


#endif //ANDROIDREVERSETOOLKIT_VARIABLETREEVIEW_H
