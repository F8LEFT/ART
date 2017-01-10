//===- VariableTreeView.cpp - ART-DEBUGGER ----------------------*- C++ -*-===//
//
//                     ANDROID REVERSE TOOLKIT
//
// This file is distributed under the GNU GENERAL PUBLIC LICENSE
// V3 License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
#include "VariableTreeView.h"

// VariableTreeItem
VariableTreeItem::VariableTreeItem(const QString &name, const JDWP::JValue &data)
    : m_fieldName(name), m_data(data)
{
}

VariableTreeItem::~VariableTreeItem()
{
}

QVariant VariableTreeItem::data(int role) const {
    switch (role) {
        case Qt::DisplayRole:
            return display();
        case Qt::EditRole:
            return value();
        default:
            break;
    }
    return QStandardItem::data(role);
}

QString VariableTreeItem::display() const {
    QString rel = m_fieldName;
    rel.append(" = ");
    auto val = value();
    if(m_data.tag == JDWP::JT_BYTE) {
        val.push_front('\'');
        val.push_back('\'');
    }
    rel.append(val);
    return rel;
}

QString VariableTreeItem::value() const {
    QString rel;
    switch (m_data.tag) {
        case JDWP::JT_VOID:
            rel = "null";
            break;
        case JDWP::JT_BYTE:
            rel.append(QByteArray((char*)&m_data.B, 1).toHex());
            break;
        case JDWP::JT_BOOLEAN:
            if(m_data.Z) {
                rel = "true";
            } else {
                rel = "false";
            }
            break;
        case JDWP::JT_CHAR:
            rel.append(QString().setUtf16((ushort*) &m_data.C, 1));
            break;
        case JDWP::JT_SHORT:
            rel.append(QString::number(m_data.S));
            break;
        case JDWP::JT_FLOAT:
            rel.append(QString::number(m_data.F));
            break;
        case JDWP::JT_INT:
            rel.append(QString::number(m_data.I));
            break;
        case JDWP::JT_ARRAY:
            rel.append("ARRAY@");
            rel.append(QString::number(m_data.a));
            break;
        case JDWP::JT_OBJECT:
            rel.append("OBJECT@");
            rel.append(QString::number(m_data.L));
            break;
        case JDWP::JT_STRING:
            rel.append("STRING@");
            rel.append(QString::number(m_data.s));
            break;
        case JDWP::JT_THREAD:
            rel.append("THREAD@");
            rel.append(QString::number(m_data.t));
            break;
        case JDWP::JT_THREAD_GROUP:
            rel.append("THREADGROUP@");
            rel.append(QString::number(m_data.g));
            break;
        case JDWP::JT_CLASS_LOADER:
            rel.append("CLASSLOADER@");
            rel.append(QString::number(m_data.l));
            break;
        case JDWP::JT_CLASS_OBJECT:
            rel.append("CLASSOBJECT@");
            rel.append(QString::number(m_data.c));
            break;
        case JDWP::JT_DOUBLE:
            rel.append(QString::number(m_data.D));
            break;
        case JDWP::JT_LONG:
            rel.append(QString::number(m_data.J));
            break;
        default:
            rel.append("IVNALID");
            break;
    }
    return rel;
}

VariableTreeItem *VariableTreeItem::findchild(const QString& name) {
    return findchild(this, name);
}

VariableTreeItem *VariableTreeItem::findchild(QStandardItem *parent, const QString& name) {
    for(auto i = 0, count = parent->rowCount(); i < count; i++) {
        auto child = (VariableTreeItem *)parent->child(i, 0);
        if(child->m_fieldName == name) {
            return child;
        }
    }
    return nullptr;
}


// VariableModel
VariableModel::VariableModel(QObject *parent)
        : QStandardItemModel(parent)
{
}

VariableModel::~VariableModel()
{
}

VariableModel *VariableModel::instance() {
    static VariableModel* mPtr = nullptr;
    if(mPtr == nullptr) {
        mPtr = new VariableModel;
    }
    return mPtr;
}

VariableTreeView::VariableTreeView(QWidget *parent)
        : QTreeView(parent)
{
    setObjectName("VariableTree");

    auto model = VariableModel::instance();
    setModel(model);
}

VariableTreeView::~VariableTreeView() {

}
