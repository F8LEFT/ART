//===- SmaliTree.h - ART-GUI Analysis engine --------------------*- cpp -*-===//
//
//                     ANDROID REVERSE TOOLKIT
//
// This file is distributed under the GNU GENERAL PUBLIC LICENSE
// V3 License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// Use QTreeView to show SmaliFile data
//
//===----------------------------------------------------------------------===//


#ifndef ANDROIDREVERSETOOLKIT_SMALITREE_H
#define ANDROIDREVERSETOOLKIT_SMALITREE_H


#include <QTreeView>
#include <QAbstractItemModel>

class SmaliAnalysis;

class SmaliTree: public QTreeView{
    Q_OBJECT
public:
    SmaliTree(QWidget* parent = nullptr);
    ~SmaliTree();

protected slots:
    void onItemDoubleClicked(const QModelIndex &index);

private:
    SmaliAnalysis* m_smaliData;
};


#endif //ANDROIDREVERSETOOLKIT_SMALITREE_H
