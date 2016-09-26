//===- HistoryLineEdit.h - ART-GUI MainWindow -------------------*- C++ -*-===//
//
//                     ANDROID REVERSE TOOLKIT
//
// This file is distributed under the GNU GENERAL PUBLIC LICENSE
// V3 License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// HistoryLineEdit will save all input.
//
//===----------------------------------------------------------------------===//
#ifndef HISTORYLINEEDIT_H
#define HISTORYLINEEDIT_H

#include <QLineEdit>
#include <QKeyEvent>

class HistoryLineEdit : public QLineEdit
{
    Q_OBJECT

public:
    explicit HistoryLineEdit(QWidget* parent = 0);
    void keyPressEvent(QKeyEvent* event);
    void addLineToHistory(QString parLine);
    void setFocus();

signals:
    void keyPressed(int parKey);

private:
    QList<QString> mCmdHistory;
    int mCmdIndex;
    bool bSixPressed;
};

#endif // HISTORYLINEEDIT_H
