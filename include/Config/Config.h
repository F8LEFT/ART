//===- Config.h - ART-GUI Config -------------------------------*- C++ -*-===//
//
//                     ANDROID REVERSE TOOLKIT
//
// This file is distributed under the GNU GENERAL PUBLIC LICENSE
// V3 License. See LICENSE.TXT for details.
//
//===---------------------------------------------------------------------===//
//
// Config Dialog.
//
//===----------------------------------------------------------------------===//
#ifndef CONFIG_H
#define CONFIG_H

#include <QDialog>
#include <QListWidget>
#include <QList>

namespace Ui {
class Config;
}

class FileEditor;

class Config : public QDialog
{
    Q_OBJECT

public:
    explicit Config(QWidget *parent = 0);
    ~Config();

protected slots:
    void onConfigTabChange(QListWidgetItem *current, QListWidgetItem *previous);

    void save();

private:
    Ui::Config *ui;

    QVector<QWidget*> mWidgetList;
    QVector<QString> mWidgetNativeNameList;
    QVector<QIcon> mIconList;

    FileEditor* mFileEditor;


};

#endif // CONFIG_H
