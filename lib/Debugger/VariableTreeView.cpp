//===- VariableTreeView.cpp - ART-DEBUGGER ----------------------*- C++ -*-===//
//
//                     ANDROID REVERSE TOOLKIT
//
// This file is distributed under the GNU GENERAL PUBLIC LICENSE
// V3 License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
#include "VariableTreeView.h"
#include <utils/StringUtil.h>

// VariableTreeItem
VariableTreeItem::VariableTreeItem(const QString &name, const JDWP::JValue &data)
    : m_fieldName(name), m_value(data), m_updated(false)
{
}

VariableTreeItem::~VariableTreeItem()
{
}

void VariableTreeItem::setValue(JDWP::JValue value) {
    m_updated = m_value == value;
    m_value = value;
}


QVariant VariableTreeItem::data(int role) const {
    switch (role) {
        case Qt::DisplayRole:
            return display();
        case Qt::EditRole:
            return valueString();
        case Qt::ForegroundRole:
            if(m_updated) {
                return QBrush(QColor(Qt::red));
            } else {
                return QBrush(QColor(Qt::black));
            }
        default:
            break;
    }
    return QStandardItem::data(role);
}

QString VariableTreeItem::display() const {
    QString rel = m_fieldName;
    rel.append(" = ");
    auto val = valueString();
    if(m_value.tag == JDWP::JT_BYTE) {
        val.push_front('\'');
        val.push_back('\'');
    } else if (m_value.tag == JDWP::JT_STRING) {
        val.push_back('\"');
        val.push_front('\"');
    }
    rel.append(val);
    return rel;
}

QString VariableTreeItem::valueString() const {
    QString rel;
    switch (m_value.tag) {
        case JDWP::JT_VOID:
            rel = "null";
            break;
        case JDWP::JT_BYTE:
            rel.append(QByteArray((char*)&m_value.B, 1).toHex());
            break;
        case JDWP::JT_BOOLEAN:
            if(m_value.Z) {
                rel = "true";
            } else {
                rel = "false";
            }
            break;
        case JDWP::JT_CHAR:
            rel.append(QString().setUtf16((ushort*) &m_value.C, 1));
            break;
        case JDWP::JT_SHORT:
            rel.append(QString::number(m_value.S));
            break;
        case JDWP::JT_FLOAT:
            rel.append(QString::number(m_value.F));
            break;
        case JDWP::JT_INT:
            rel.append(QString::number(m_value.I));
            break;
        case JDWP::JT_ARRAY:
            rel.append("ARRAY@");
            rel.append(QString::number(m_value.a));
            break;
        case JDWP::JT_OBJECT:
            rel.append(m_objectType);
            rel.append("@");
            if(m_value.L == 0) {
                rel.append("null");
            } else {
                rel.append(QString::number(m_value.L));
            }
            break;
        case JDWP::JT_STRING:
            if(m_value.s == 0) {
                rel.append("null");
            } else {
                rel.append(m_StringValue);
            }
            break;
        case JDWP::JT_THREAD:
            rel.append("THREAD@");
            rel.append(QString::number(m_value.t));
            break;
        case JDWP::JT_THREAD_GROUP:
            rel.append("THREADGROUP@");
            rel.append(QString::number(m_value.g));
            break;
        case JDWP::JT_CLASS_LOADER:
            rel.append("CLASSLOADER@");
            rel.append(QString::number(m_value.l));
            break;
        case JDWP::JT_CLASS_OBJECT:
            rel.append("CLASSOBJECT@");
            rel.append(QString::number(m_value.c));
            break;
        case JDWP::JT_DOUBLE:
            rel.append(QString::number(m_value.D));
            break;
        case JDWP::JT_LONG:
            rel.append(QString::number(m_value.J));
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

void VariableTreeItem::setObjectType(QString type) {
    m_classType = type;
    auto sig = jniSigToJavaSig(type);
    auto index = sig.lastIndexOf('.');
    if(index != -1) {
        m_objectType = sig.right(sig.length() - index - 1);
    } else {
        m_objectType = type;
    }
}

// VariableModel
VariableModel::VariableModel(QObject *parent)
        : QStandardItemModel(parent),
          m_selectionModel(new QItemSelectionModel(this, this))
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
    setHeaderHidden(true);
    setObjectName("VariableTree");

    auto smodel = VariableModel::instance();
    setModel(smodel);

    connect(this, &VariableTreeView::expanded, [this](const QModelIndex &index) {
        auto smodel = (VariableModel*)model();
        auto item = (VariableTreeItem*)smodel->itemFromIndex(index);
        if(item != nullptr) {
            if(item->value().tag == JDWP::JdwpTag::JT_OBJECT) {
                itemExpanded(item);
            }
        }
    });
}

VariableTreeView::~VariableTreeView() {

}
