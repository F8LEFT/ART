//===- BookMark.h - ART-GUI BookMark ---------------------------*- C++ -*-===//
//
//                     ANDROID REVERSE TOOLKIT
//
// This file is distributed under the GNU GENERAL PUBLIC LICENSE
// V3 License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file defines BookMark used in Editor.
//
//===----------------------------------------------------------------------===//
#ifndef BOOKMARK_H
#define BOOKMARK_H

#include <QWidget>

namespace Ui {
class BookMark;
}


class BookMark : public QWidget
{
    Q_OBJECT

public:
    explicit BookMark(QString file, QWidget *parent = 0);
    ~BookMark();

    void setHint(QString hint);
    void setLine(int line);

    QString filePath();
    QString hint();
    int line();

    void onClicked(BookMark* pBook);
signals:

private:
    Ui::BookMark *ui;
    QString mFilePath;
    QString mHint;
    int mLine;
};

#endif // BOOKMARK_H
