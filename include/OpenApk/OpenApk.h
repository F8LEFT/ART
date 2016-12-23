//===- OpenApk.h - ART-GUI OpenApk dialog ----------------------*- C++ -*-===//
//
//                     ANDROID REVERSE TOOLKIT
//
// This file is distributed under the GNU GENERAL PUBLIC LICENSE
// V3 License. See LICENSE.TXT for details.
//
//===---------------------------------------------------------------------===//
//
// This file defines ART-GUI OpenApk dialog's behaviour. It ask for compile or
// decompile option for target apk/dex file.
//
//===----------------------------------------------------------------------===//
#ifndef OPENAPK_H
#define OPENAPK_H

#include <QDialog>

namespace Ui {
class OpenApk;
}

class OpenApk : public QDialog
{
    Q_OBJECT

public:
    explicit OpenApk(QString file, QWidget *parent = 0);
    ~OpenApk();

    // configuration
    void loadFromConfig();
    void saveToConfig();

    QString getDecompileCmd();
    QString getCompileCmd();
    QString getFileName();
protected slots:
    void accept();
    void decompileOptionChanged();
    void compileOptionChanged();
private:
    Ui::OpenApk *ui;
    QString mFilePath;
    QString mFileName;
    QString mDecCmd;
    QString mComCmd;
};

#endif // OPENAPK_H
