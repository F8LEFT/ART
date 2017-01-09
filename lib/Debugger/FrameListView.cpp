//===- FrameListView.cpp - ART-DEBUGGER ---------------------------*- C++ -*-===//
//
//                     ANDROID REVERSE TOOLKIT
//
// This file is distributed under the GNU GENERAL PUBLIC LICENSE
// V3 License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
#include "FrameListView.h"
#include <SmaliAnalysis/SmaliAnalysis.h>
#include <utils/StringUtil.h>

QString FrameListModel::FrameData::display() {
    return description;
}

void FrameListModel::FrameData::update() {
    if(classSig.isEmpty()) {
        return;
    }
    auto filedata = SmaliAnalysis::instance()->getSmaliFileBySig(classSig);
    if(!filedata.isNull()) {
        hasSource = true;
        sourceFile = filedata->sourceFile();
        auto method = filedata->method(methodName, methodSig);
        if(method == nullptr) {
            sourceLine = 1;
        } else {
            // TODO get sourceline with dex_pc
            sourceLine = method->m_startline;
        }
    }

    description.clear();
    if(methodName.isEmpty()) {
        description.append('@');
        description.append(QString::number(location.method_id, 16));
    } else {
        description.append(methodName);
    }

    description.append(':');
    if(sourceLine != -1) {
        description.append(QString::number(sourceLine));
    } else {
        if(location.dex_pc == (size_t)-1) {
            description.append("-1");
        } else {
            description.append(QString::number(location.dex_pc));
        }
    }
    description.append(", ");
    if(classSig.isEmpty()) {
        description.append('@');
        description.append(QString::number(location.class_id, 16));
    } else {
        auto sig = jniSigToJavaSig(classSig);
        auto index = sig.lastIndexOf('.');
        if(index != -1) {
            auto sigclass = sig.left(index);
            auto signame = sig.right(sig.length() - index - 1);
            description.append(signame);
            description.append(" (");
            description.append(sigclass);
            description.append(')');
        } else {
            description.append(sig);
        }
    }
}

FrameListModel::FrameListModel(QObject* parent)
    : QAbstractListModel(parent)
{
}

FrameListModel::~FrameListModel()
{
    qDeleteAll(m_framedataList);
}

QModelIndex FrameListModel::index(int row, int column, const QModelIndex &parent) const
{
    if (parent.isValid())
        return QModelIndex();
    else
        return createIndex(row, column);
}

QModelIndex FrameListModel::parent(const QModelIndex &) const
{
    return QModelIndex();
}

int FrameListModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;
    else
        return m_framedataList.count();
}

QVariant FrameListModel::data(const QModelIndex &index, int role) const {
    if (!index.isValid() || index.column() != 0 || index.row() < 0 ||
        index.row() >= m_framedataList.count())
        return QVariant();

    auto *framedata = m_framedataList.at(index.row());
    switch (role) {
        case Qt::DisplayRole:
            return framedata->display();
        case Qt::BackgroundRole:
            if (framedata->hasSource) {
                return QVariant(QBrush(Qt::white));
            } else {
                return QVariant(QBrush(Qt::yellow));
            }
        case Qt::ForegroundRole:
            if (framedata->hasSource) {
                return QVariant(QBrush(Qt::black));
            } else {
                return QVariant(QBrush(Qt::gray));
            }
        default:
            break;
    }
    return QVariant();
}


Qt::ItemFlags FrameListModel::flags(const QModelIndex &index) const
{
    if (!index.isValid() || index.column() !=0 || index.row() < 0 || index.row() >= m_framedataList.count())
        return Qt::NoItemFlags;
    return Qt::ItemIsEnabled | Qt::ItemIsSelectable;
}


void FrameListModel::updateFrameData(FrameData *frameData)
{
    const int idx = m_framedataList.indexOf(frameData);
    if (idx == -1)
        return;
    frameData->update();
    dataChanged(index(idx, 0, QModelIndex()), index(idx, 2, QModelIndex()));
}


void FrameListModel::removeAllFramedatas()
{
    if (m_framedataList.isEmpty())
        return;
    beginRemoveRows(QModelIndex(), 0, m_framedataList.size() - 1);

    qDeleteAll(m_framedataList);
    m_framedataList.clear();
    endRemoveRows();
}

void FrameListModel::deleteFramedata(FrameData *frameData)
{
    int idx = m_framedataList.indexOf(frameData);
    beginRemoveRows(QModelIndex(), idx, idx);
    delete frameData;

    m_framedataList.removeAt(idx);
    endRemoveRows();
}

FrameListModel::FrameData *FrameListModel::framedataForIndex(const QModelIndex &index) const
{
    if (!index.isValid() || index.row() >= m_framedataList.size())
        return 0;
    return m_framedataList.at(index.row());
}

FrameListModel::FrameData *FrameListModel::framedataForFrameId(JDWP::ObjectId frameId) const {
    for(auto frame: m_framedataList) {
        if(frame->frame_id == frameId) {
            return frame;
        }
    }
    return nullptr;
}


bool FrameListModel::gotoFrameData(FrameData *frameData)
{
    return true;
}

void FrameListModel::addFrameData(FrameData *frameData)
{
    beginInsertRows(QModelIndex(), m_framedataList.size(), m_framedataList.size());
    m_framedataList.append(frameData);
    endInsertRows();
}

//void FrameListModel::setFramedatas(QList<JDWP::FrameId> frames) {
//    removeAllFramedatas();
//    beginInsertRows(QModelIndex(), m_framedataList.size(), m_framedataList.size());
//    for(auto id: frames) {
//        auto frameData = new FrameData;
//        frameData->frame_id = id;
//        m_framedataList.append(frameData);
//    }
//    endInsertRows();
//}

QList<FrameListModel::FrameData *> FrameListModel::getFrameDatas() {
    return m_framedataList;
}


FrameListView::FrameListView(QWidget *parent)
        : QListView(parent) {

}

FrameListView::~FrameListView() {

}

FrameListModel *FrameListView::showModel(JDWP::ObjectId threadId) {
    FrameListModel* model;
    if(m_frameModelsMap.contains(threadId)) {
        model = m_frameModelsMap[threadId];
    } else {
        model = new FrameListModel(this);
        m_frameModelsMap[threadId] = model;
    }
    setModel(model);
    return model;
}

FrameListView *FrameListView::instance() {
    static FrameListView *mPtr = nullptr;
    if(mPtr == nullptr) {
        mPtr = new FrameListView;
    }
    return mPtr;
}


