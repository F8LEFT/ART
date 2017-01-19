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

class VariableModel;

struct VariableTreeItem: public QStandardItem {
public:
    VariableTreeItem(const QString &name); // for normal field
    VariableTreeItem(int index);           // for array
    ~VariableTreeItem();

    enum ItemRole {
        Item = Qt::UserRole + 1,
    };

    QVariant data(int role = Qt::UserRole + 1) const;
    void setData(const QVariant &value, int role = Qt::UserRole + 1);

    VariableTreeItem* findchild(const QString& name);
    static VariableTreeItem* findchild(QStandardItem* parent, const QString& name);

    QString name() { return m_fieldName; }
    JDWP::JValue &value() { return m_value; }
    void setValue(JDWP::JValue value);

    // for JT_OBJECT
    void setObjectType(QString type);
    QString objectType() { return m_classType; }
    void setRefTypeId(JDWP::RefTypeId refId) { m_refType = refId; }
    JDWP::RefTypeId refTypeId() { return m_refType; }
    // for JT_STRING
    void setJTStringValue(const QString & str) { m_StringValue = str; }
    QString JTStringValue() { return m_StringValue; }
    // for JT_ARRAY
    bool isArrayElement() const { return m_arrayindex & 0x80000000; }
    int arrayElementIndex() const { return isArrayElement() ? -1 : m_arrayindex & 0x7FFFFFFF; }

    // show item value
    void paintItem(QPainter *painter, const QRect &rect, const QPalette &palette) const;
    bool applyEditValue(const QString &val);
    QString getEditValue() const;
    bool isEditable() const;
private:
    bool m_inited = false;

    QString m_fieldName;    // if item is normal field, this is valid
    int m_arrayindex = 0;   // if item is array element, tihs is valid

    JDWP::JValue m_value;
    bool m_updated = false;

    QString m_classType;            // this field is used for JT_OBJECT type, in jni sig
    QString m_objectType;           // this field is used for JT_OBJECT type, in java sig
    JDWP::RefTypeId m_refType = 0;  // this field is used for JT_OBJECT type(object reference)

    QString m_StringValue;  // this field is used for JT_STRING type

    // support for tree model

};

Q_DECLARE_METATYPE(VariableTreeItem*)


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
