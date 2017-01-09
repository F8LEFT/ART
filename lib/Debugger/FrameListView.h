//===- FrameListView.h - ART-DEBUGGER ---------------------------*- C++ -*-===//
//
//                     ANDROID REVERSE TOOLKIT
//
// This file is distributed under the GNU GENERAL PUBLIC LICENSE
// V3 License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// FrameListView is used to show thread frame information while debugging.
//
//===----------------------------------------------------------------------===//
#ifndef ANDROIDREVERSETOOLKIT_FRAMELISTVIEW_H
#define ANDROIDREVERSETOOLKIT_FRAMELISTVIEW_H

#include <QListView>
#include <QAbstractListModel>
#include <BreakPoint/BreakPoint.h>
#include <QModelIndex>
#include "Jdwp/jdwp.h"


class FrameListModel: public QAbstractListModel {
    Q_OBJECT
public:
    struct FrameData {
        bool hasSource = false;
        QString sourceFile;
        int sourceLine = -1;

        JDWP::FrameId frame_id;
        JDWP::JdwpLocation location;
        QByteArray classSig;
        QByteArray methodName;
        QByteArray methodSig;

        QString description;

        QString display();
        void update();
    };
public:
    FrameListModel(QObject* parent = nullptr);
    ~FrameListModel();

//    void setFramedatas(QList<JDWP::FrameId > frames);
    void addFrameData(FrameData *frameData);
    void deleteFramedata(FrameData *frameData);
    void removeAllFramedatas();
    void updateFrameData(FrameData *frameData);
    QList<FrameData *> getFrameDatas();
    bool gotoFrameData(FrameData *frameData);

    FrameListModel::FrameData *framedataForIndex(const QModelIndex &index) const;
    FrameListModel::FrameData *framedataForFrameId(JDWP::ObjectId frameId) const;

    // Model stuff
    QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const;
    QModelIndex parent(const QModelIndex &child) const;
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
//    int columnCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    Qt::ItemFlags flags(const QModelIndex &index) const;

private:


    QList<FrameData *> m_framedataList;
};

class FrameListView: public QListView {
    Q_OBJECT
public:
    FrameListView(QWidget* parent = nullptr);
    ~FrameListView();

    static FrameListView* instance();

    // shelect the itemmodel with threadid
    // this method will create FrameListModel if threadId is not exist;
    FrameListModel* showModel(JDWP::ObjectId threadId);
private:
    QMap<JDWP::ObjectId, FrameListModel*> m_frameModelsMap; // map for threadId, frames
};


#endif //ANDROIDREVERSETOOLKIT_FRAMELISTVIEW_H
