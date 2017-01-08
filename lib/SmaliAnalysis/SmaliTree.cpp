//===- SmaliTree.cpp - ART-GUI Analysis engine ------------------*- cpp -*-===//
//
//                     ANDROID REVERSE TOOLKIT
//
// This file is distributed under the GNU GENERAL PUBLIC LICENSE
// V3 License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

#include "SmaliAnalysis/SmaliTree.h"
#include "SmaliAnalysis/SmaliAnalysis.h"

#include <utils/CmdMsgUtil.h>


#include <QHeaderView>


SmaliTree::SmaliTree(QWidget *parent)
        : QTreeView(parent)
{
    header()->setSectionResizeMode(QHeaderView::ResizeToContents);
    setHeaderHidden(true);

    m_smaliData = SmaliAnalysis::instance();


    setWindowIcon(QIcon(":/images/sourceFolder.png"));
    setModel(m_smaliData);

    connect(this, &SmaliTree::doubleClicked, this, &SmaliTree::onItemDoubleClicked);

}

SmaliTree::~SmaliTree() {

}

void SmaliTree::onItemDoubleClicked(const QModelIndex &index) {
    auto smaliModel = (SmaliAnalysis*)model();
    auto item = smaliModel->itemFromIndex(index);
    if(item == nullptr) {
        return;
    }
    auto line = item->data(SmaliAnalysis::ItemRole::Line);
    if(!line.isValid()) {
        return;
    }
    auto source = item->parent()->data(SmaliAnalysis::ItemRole::Source);

    QStringList args;
    args<< source.toString()
        << QString::number(line.toInt());
    cmdexec("OpenFile", args, CmdMsg::script, true, false);
}
