//===- StatusLabel.h - ART-GUI MainWindow -----------------------*- C++ -*-===//
//===----------------------------------------------------------------------===//
//
// This file is copyed from X64Dbg project.
//
//===----------------------------------------------------------------------===//
#ifndef STATUSLABEL_H
#define STATUSLABEL_H
#include <QLabel>
#include <QStatusBar>

class StatusLabel : public QLabel
{
    Q_OBJECT
public:
    StatusLabel(QStatusBar* parent = 0);

public slots:
    void logUpdate(QString message);

private:
    QString labelText;
};

#endif // STATUSLABEL_H
