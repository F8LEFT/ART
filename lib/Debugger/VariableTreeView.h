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
    QString valueString() const;

    VariableTreeItem* findchild(const QString& name);
    static VariableTreeItem* findchild(QStandardItem* parent, const QString& name);

    QString name() { return m_fieldName; }
    JDWP::JValue &value() { return m_value; }
    void setValue(JDWP::JValue value);

    void setObjectType(QString type);
    QString objectType() { return m_classType; }
    void setJTStringValue(const QString & str) { m_StringValue = str; }
private:
    QString m_fieldName;
    QString m_objectType;
    JDWP::JValue m_value;
    bool m_updated;

    QString m_classType;    // for JT_OBJECT type
    QString m_StringValue;  // for JT_STRING type
};

class VariableModel: public QStandardItemModel {
    Q_OBJECT

public:
    explicit VariableModel(QObject *parent = 0);
    ~VariableModel();

    QItemSelectionModel *selectionModel() const { return m_selectionModel; }

    static VariableModel* instance();
private:
    QItemSelectionModel *m_selectionModel;
};

class VariableTreeView: public QTreeView {
    Q_OBJECT
public:
    VariableTreeView(QWidget* parent = nullptr);
    ~VariableTreeView();

signals:
    void itemExpanded(VariableTreeItem* item);
protected slots:
//    void onItemDoubleClicked(const QModelIndex &index);

private:
};


#endif //ANDROIDREVERSETOOLKIT_VARIABLETREEVIEW_H
