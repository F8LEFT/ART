//===- Environment.h - ART-GUI Config --------------------------*- C++ -*-===//
//
//                     ANDROID REVERSE TOOLKIT
//
// This file is distributed under the GNU GENERAL PUBLIC LICENSE
// V3 License. See LICENSE.TXT for details.
//
//===---------------------------------------------------------------------===//
//
// Configure java, adb path.
//
//===----------------------------------------------------------------------===//
#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

#include <QWidget>

namespace Ui {
class Environment;
}

class Environment : public QWidget
{
    Q_OBJECT
public:
    explicit Environment(QWidget *parent = 0);
    ~Environment();

    void save();

private:
    Ui::Environment *ui;
};

#endif // ENVIRONMENT_H
