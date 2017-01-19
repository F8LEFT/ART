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

#include <QTreeView>
#include <QAbstractItemModel>

class VariableModel;

struct VariableTreeItem {
public:
    VariableTreeItem(const QString &name); // for normal field
    VariableTreeItem(int index);           // for array
    ~VariableTreeItem();

    enum ItemRole {
        Item = Qt::UserRole + 1,
    };

    QVariant data(int role = Qt::UserRole + 1) const;
    bool setData(const QVariant &value, int role);
    QString display() const;
    QString valueString() const;

    VariableTreeItem* findchild(const QString& name);
    static VariableTreeItem* findchild(VariableTreeItem* parent, const QString& name);

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
public:
    Qt::ItemFlags flags() const;

    VariableTreeItem *child(int row, int column = 0) const;
    int rowCount() const;
    int columnCount() const;
    void appendRow(VariableTreeItem *item);
    void removeRows(int row, int count);

    int row() const;

    VariableModel *model() const { return m_model; }
private:
    QList<VariableTreeItem*> m_childItems;
    VariableTreeItem *m_parentItem = nullptr;
    VariableModel *m_model = nullptr;

    friend class VariableModel;
};

Q_DECLARE_METATYPE(VariableTreeItem*)


class VariableModel: public QAbstractItemModel {
    Q_OBJECT

public:
    explicit VariableModel(QObject *parent = 0);
    ~VariableModel();

    // the model function
    QVariant data(const QModelIndex &index, int role) const Q_DECL_OVERRIDE;
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) Q_DECL_OVERRIDE;
    Qt::ItemFlags flags(const QModelIndex &index) const Q_DECL_OVERRIDE;
    QModelIndex index(int row, int column,
                      const QModelIndex &parent = QModelIndex()) const Q_DECL_OVERRIDE;
    int rowCount(const QModelIndex &parent = QModelIndex()) const Q_DECL_OVERRIDE;
    int columnCount(const QModelIndex &parent = QModelIndex()) const Q_DECL_OVERRIDE;
//    bool insertRows(int row, int count, const QModelIndex &parent = QModelIndex());
    QModelIndex parent(const QModelIndex &child) const;

    QItemSelectionModel *selectionModel() const { return m_selectionModel; }

    static VariableModel* instance();

public:
    bool appendRow(VariableTreeItem *parent, VariableTreeItem *item);
    bool removeRows(VariableTreeItem *parent, int row, int count);

    VariableTreeItem* invisibleRootItem() const { return m_rootItem; };
    VariableTreeItem *itemFromIndex(const QModelIndex &index) const;
    QModelIndex indexFromItem(const VariableTreeItem *item) const;
    void clear();
private:
    QItemSelectionModel *m_selectionModel;

    VariableTreeItem* m_rootItem;

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
