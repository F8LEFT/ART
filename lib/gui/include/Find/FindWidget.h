//===- FindWidget.h - ART-GUI Find -----------------------------*- C++ -*-===//
//
//                     ANDROID REVERSE TOOLKIT
//
// This file is distributed under the GNU GENERAL PUBLIC LICENSE
// V3 License. See LICENSE.TXT for details.
//
//===---------------------------------------------------------------------===//
//
// Show find widget and search file opened.
//
//===----------------------------------------------------------------------===//
#ifndef FINDWIDGET_H
#define FINDWIDGET_H

#include <QWidget>
#include <QTextDocument>

namespace Ui {
class FindWidget;
}

class FindWidget : public QWidget
{
    Q_OBJECT

public:
    explicit FindWidget(QWidget *parent = 0);
    ~FindWidget();

private:
    Ui::FindWidget *ui;
    QTextDocument* mDocument;
};

#endif // FINDWIDGET_H
