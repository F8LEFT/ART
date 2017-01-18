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
}

VariableTreeItem::VariableTreeItem(int index)
        : m_updated(false)
{
    m_arrayindex = index | 0x80000000;
}

VariableTreeItem::~VariableTreeItem()
{
    qDeleteAll(m_childItems);
    m_childItems.clear();
}

void VariableTreeItem::setValue(JDWP::JValue value) {
    m_updated = m_inited ? m_value == value : false;
    m_inited = true;
    m_value = value;
}


QVariant VariableTreeItem::data(int role) const {
    switch(role) {
        case ItemRole::Item :
            return QVariant::fromValue<VariableTreeItem*>((VariableTreeItem*)this);
        default:
            break;
    }
    return QVariant();

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

VariableTreeItem *VariableTreeItem::findchild(VariableTreeItem *parent, const QString& name) {
    for(auto i = 0, count = parent->rowCount(); i < count; i++) {
        auto child = parent->child(i, 0);
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

Qt::ItemFlags VariableTreeItem::flags() const {
    Qt::ItemFlags flag = Qt::ItemIsEnabled | Qt::ItemIsSelectable;
    if(isEditable()) {
        flag |= Qt::ItemIsEditable;
    }
    return flag;
}

VariableTreeItem *VariableTreeItem::child(int row, int column) const {
    if(row < rowCount()) {
        return m_childItems.at(row);
    }
    return nullptr;
}

int VariableTreeItem::rowCount() const {
    return m_childItems.size();
}

int VariableTreeItem::columnCount() const {
    return 1;
}

void VariableTreeItem::appendRow(VariableTreeItem *item) {
    m_model->appendRow(this, item);
}

void VariableTreeItem::removeRows(int row, int count) {
    m_model->removeRows(this, row, count);
}

int VariableTreeItem::row() const {
    if (m_parentItem)
        return m_parentItem->m_childItems.indexOf(const_cast<VariableTreeItem*>(this));

    return 0;
}

// VariableModel
VariableModel::VariableModel(QObject *parent)
        : QAbstractItemModel(parent),
          m_selectionModel(new QItemSelectionModel(this, this))
{
    m_rootItem = new VariableTreeItem("");
    m_rootItem->m_model = this;
}

VariableModel::~VariableModel()
{
    m_rootItem = new VariableTreeItem("");
}

VariableModel *VariableModel::instance() {
    static VariableModel* mPtr = nullptr;
    if(mPtr == nullptr) {
        mPtr = new VariableModel();
    }
    return mPtr;
}

QVariant VariableModel::data(const QModelIndex &index, int role) const {
    if (!index.isValid())
        return QVariant();

    VariableTreeItem *item = itemFromIndex(index);

    return item->data(role);
}

Qt::ItemFlags VariableModel::flags(const QModelIndex &index) const {
    auto item = itemFromIndex(index);
    if(item == nullptr) {
        return QAbstractItemModel::flags(index);
    }
    return item->flags();
}

QModelIndex VariableModel::index(int row, int column, const QModelIndex &parent) const {
    if (!hasIndex(row, column, parent))
        return QModelIndex();
    VariableTreeItem *parentItem;

    if (!parent.isValid())
        parentItem = invisibleRootItem();
    else
        parentItem = itemFromIndex(parent);

    VariableTreeItem *childItem = parentItem->child(row);
    if (childItem)
        return indexFromItem(childItem);
    else
        return QModelIndex();
}

int VariableModel::rowCount(const QModelIndex &parent) const {
    VariableTreeItem *parentItem;
    if (parent.column() > 0)
        return 0;

    if (!parent.isValid())
        parentItem = invisibleRootItem();
    else
        parentItem = itemFromIndex(parent);

    return parentItem->rowCount();
}

int VariableModel::columnCount(const QModelIndex &parent) const {
    if (parent.isValid())
        return itemFromIndex(parent)->columnCount();
    else
        return invisibleRootItem()->columnCount();
}

QModelIndex VariableModel::parent(const QModelIndex &child) const {
    if (!child.isValid())
        return QModelIndex();

    auto childItem = itemFromIndex(child);
    auto parentItem = childItem->m_parentItem;

    if (parentItem == m_rootItem)
        return QModelIndex();

    return indexFromItem(parentItem);
}

VariableTreeItem *VariableModel::itemFromIndex(const QModelIndex &index) const {
    if(!index.isValid()) {
        return nullptr;
    }
    auto item = static_cast<VariableTreeItem*>(index.internalPointer());
    return item;
}

QModelIndex VariableModel::indexFromItem(const VariableTreeItem *item) const {
    if(item == nullptr) {
        return QModelIndex();
    }
    return createIndex(item->row(), 0, (VariableTreeItem *)item);
}

void VariableModel::clear() {
    beginResetModel();
    delete m_rootItem;
    m_rootItem = new VariableTreeItem("");
    m_rootItem->m_model = this;
    endResetModel();
}

bool VariableModel::appendRow(VariableTreeItem *parent, VariableTreeItem *item) {
    if(item == nullptr || parent == nullptr) {
        return false;
    }

    beginInsertRows(indexFromItem(parent), parent->rowCount(), parent->rowCount());
    item->m_parentItem = parent;
    item->m_model = this;
    parent->m_childItems.append(item);
    endInsertRows();
    return true;
}

bool VariableModel::removeRows(VariableTreeItem *parent, int row, int count) {
    if(parent == nullptr) {
        return false;
    }
    auto rowCount = parent->rowCount();
    auto rowRemoveStart = row < rowCount? row: rowCount;
    auto rowRemoveCount = rowCount - rowRemoveStart;
    rowRemoveCount = rowRemoveCount < count ? rowRemoveCount: count;
    if(rowRemoveCount <= 0) {
        return false;
    }
    beginRemoveRows(indexFromItem(parent), rowRemoveStart, rowRemoveCount);
    while(rowRemoveCount > 0) {
        auto item = parent->m_childItems.takeLast();
        delete item;
        rowRemoveCount --;
    }
    endRemoveRows();
    return true;
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
        auto item = smodel->itemFromIndex(index);
        if(item != nullptr) {
            if(item->value().tag == JDWP::JdwpTag::JT_OBJECT) {
                itemExpanded(item);
            }
        }
    });
}

VariableTreeView::~VariableTreeView() {

}
