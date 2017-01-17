//===- VariableTreeView.cpp - ART-DEBUGGER ----------------------*- C++ -*-===//
//
//                     ANDROID REVERSE TOOLKIT
//
// This file is distributed under the GNU GENERAL PUBLIC LICENSE
// V3 License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
#include "VariableTreeView.h"
#include "VariableItemDelegate.h"

#include <utils/StringUtil.h>

#include <QPainter>

// VariableTreeItem
VariableTreeItem::VariableTreeItem(const QString &name)
    : m_fieldName(name), m_updated(false)
{
    setSelectable(true);
}

VariableTreeItem::VariableTreeItem(int index)
        : m_updated(false)
{
    m_arrayindex = index | 0x80000000;
}

VariableTreeItem::~VariableTreeItem()
{
}

void VariableTreeItem::setValue(JDWP::JValue value) {
    m_updated = m_inited ? m_value == value : false;
    m_inited = true;
    m_value = value;
    setEditable(isEditable());
}


QVariant VariableTreeItem::data(int role) const {
//    switch (role) {
//        case Qt::DisplayRole:
//            return display();
//        case Qt::EditRole:
//            return valueString();
//        case Qt::ForegroundRole:
//            if(m_updated) {
//                return QBrush(QColor(Qt::red));
//            } else {
//                return QBrush(QColor(Qt::black));
//            }
//        default:
//            break;
//    }
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

    auto arraycount = type.indexOf('L');
    if(arraycount == -1) {
        return;
    } else if(arraycount != 0) {
        type = type.right(type.length() - arraycount);
    }
    auto sig = jniSigToJavaSig(type);
    auto index = sig.lastIndexOf('.');
    if(index != -1) {
        m_objectType = sig.right(sig.length() - index - 1);
    } else {
        m_objectType = type;
    }
    while(arraycount != 0) {
        m_objectType.append("[]");
        arraycount--;
    }
}

void VariableTreeItem::paintItem(QPainter *painter, const QRect &rect,
                                 const QPalette &palette) const {
    painter->save();
    QFontMetrics fontMetrics(painter->font());
    auto width = 0;

    QString head;
    if(isArrayElement()) {
        head.append(QString("[%1]").arg(arrayElementIndex()));
    } else {
        head.append(m_fieldName);
    }
    head.append(" = ");
    painter->setPen(QColor(0xbf2b00));

    painter->drawText(rect.x(), rect.y(), rect.width(), rect.height(),
                      Qt::AlignLeft | Qt::AlignVCenter, head);

    width = fontMetrics.width(head);
    if(!m_inited) {
        painter->setPen(Qt::red);
        painter->drawText(rect.x() + width, rect.y(), rect.width() - width, rect.height(),
                          Qt::AlignLeft | Qt::AlignVCenter, "INVALID");
        return;
    }


    QString type;
    QString value;
    if(isEditable()) {
        if(m_value.tag == JDWP::JT_STRING && m_value.s == 0) {
            value = "null";
        } else {
            value = getEditValue();
            if (m_value.tag == JDWP::JT_CHAR) {
                value.push_back('\'');
                value.push_front('\'');
            } else if(m_value.tag == JDWP::JT_STRING) {
                value.push_back('\"');
                value.push_front('\"');
            }
        }
    } else if(m_value.tag == JDWP::JT_VOID){
        value = "void";
    } else {
        if(m_value.L == 0) {
            value = "null";
        } else {
            switch (m_value.tag) {
                case JDWP::JT_ARRAY:
                case JDWP::JT_OBJECT:
                case JDWP::JT_THREAD:
                case JDWP::JT_THREAD_GROUP:
                case JDWP::JT_CLASS_LOADER:
                case JDWP::JT_CLASS_OBJECT:
                    type = QString("{%1@%2}").arg(m_objectType).arg(m_value.L, 0, 16);
                    break;
                default:
                    value = "INVALID";
                    break;
            }
        }
    }
    if(!type.isEmpty()) {
        painter->setPen(Qt::gray);
        painter->drawText(rect.x() + width, rect.y(), rect.width() - width, rect.height(),
                          Qt::AlignLeft | Qt::AlignVCenter, type);
        width += fontMetrics.width(type + " ");
    }
    if(!value.isEmpty()) {
        if(m_updated) {
            painter->setPen(Qt::red);
        } else {
            painter->setPen(Qt::black);
        }
        painter->drawText(rect.x() + width, rect.y(), rect.width() - width, rect.height(),
                          Qt::AlignLeft | Qt::AlignVCenter, value);
    }
    painter->restore();
}

void VariableTreeItem::applyEditValue(const QString &val) {
    // TODO apply value changed to remote vm
}

QString VariableTreeItem::getEditValue() const {
    QString value;
    switch (m_value.tag) {
        case JDWP::JT_BYTE:
            value.append(QByteArray((char*)&m_value.B, 1).toHex());
            break;
        case JDWP::JT_BOOLEAN:
            if(m_value.Z) {
                value = "true";
            } else {
                value = "false";
            }
            break;
        case JDWP::JT_CHAR:
            value.append(QString().setUtf16((ushort*) &m_value.C, 1));
            break;
        case JDWP::JT_SHORT:
            value.append(QString::number(m_value.S));
            break;
        case JDWP::JT_FLOAT:
            value.append(QString::number(m_value.F));
            break;
        case JDWP::JT_INT:
            value.append(QString::number(m_value.I));
            break;
        case JDWP::JT_DOUBLE:
            value.append(QString::number(m_value.D));
            break;
        case JDWP::JT_LONG:
            value.append(QString::number(m_value.J));
            break;
        case JDWP::JT_STRING:
            value.append(m_StringValue);
            break;
        default:
            value.append("IVNALID");
            break;
    }
    return value;
}

bool VariableTreeItem::isEditable() const {
    if(!m_inited) {
        return false;
    }
    switch (m_value.tag) {
        case JDWP::JT_BYTE:
        case JDWP::JT_BOOLEAN:
        case JDWP::JT_CHAR:
        case JDWP::JT_SHORT:
        case JDWP::JT_FLOAT:
        case JDWP::JT_INT:
        case JDWP::JT_STRING:
        case JDWP::JT_DOUBLE:
        case JDWP::JT_LONG:
            return true;
        default:
            return false;
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
    setItemDelegate(new VariableItemDelegate(this));

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
