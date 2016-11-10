//===- FindResult.h - ART-GUI Find -----------------------------*- C++ -*-===//
//
//                     ANDROID REVERSE TOOLKIT
//
// This file is distributed under the GNU GENERAL PUBLIC LICENSE
// V3 License. See LICENSE.TXT for details.
//
//===---------------------------------------------------------------------===//
//
// Show Find Result.
//
//===----------------------------------------------------------------------===//

#ifndef FINDRESULT_H
#define FINDRESULT_H

#include <QWidget>

namespace Ui {
class FindResult;
}

class FindResult : public QWidget
{
    Q_OBJECT

public:
    explicit FindResult(QWidget *parent = 0);
    ~FindResult();

private:
    Ui::FindResult *ui;
};

#endif // FINDRESULT_H
