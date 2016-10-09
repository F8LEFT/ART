//===- SmaliEditor.h - ART-GUI Editor Tab ----------------------*- C++ -*-===//
//
//                     ANDROID REVERSE TOOLKIT
//
// This file is distributed under the GNU GENERAL PUBLIC LICENSE
// V3 License. See LICENSE.TXT for details.
//
//===---------------------------------------------------------------------===//
//
// SmaliEditor is a widget to open/modify/save *.smali file.
//
//===----------------------------------------------------------------------===//


#ifndef PROJECT_SMALIEDITOR_H
#define PROJECT_SMALIEDITOR_H

#include "Editor.h"

#include <QtWidgets/QSplitter>
#include <QMap>


class SmaliEditor : public Editor
{
    Q_OBJECT
public:
    SmaliEditor(QWidget *parent = 0);
    ~SmaliEditor();

    void setTextLayout();

    void loadFromConfig();
    void saveToConfig();

protected slots:
    void editCursorChanged();

private:
    static void setHintMap();
private:
    QPlainTextEdit* mHintEdit;
    QSplitter* mVSplitter;
    QList<int> mVSplitterSize;
    static QMap<int, QString> mHintMap;
};


#endif //PROJECT_SMALIEDITOR_H
