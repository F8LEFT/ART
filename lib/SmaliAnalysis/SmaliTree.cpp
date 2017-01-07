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

#include <QHeaderView>


SmaliTree::SmaliTree(QWidget *parent)
        : QTreeView(parent)
{
    setHeaderHidden(true);

    m_smaliData = SmaliAnalysis::instance();


    setWindowIcon(QIcon(":/images/sourceFolder.png"));
    setModel(m_smaliData);

}

SmaliTree::~SmaliTree() {

}
