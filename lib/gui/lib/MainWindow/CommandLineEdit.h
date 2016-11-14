//===- CommandLineEdit.h - ART-GUI MainWindow ------------------*- C++ -*-===//
//
//                     ANDROID REVERSE TOOLKIT
//
// This file is distributed under the GNU GENERAL PUBLIC LICENSE
// V3 License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// CommandLineEdit can handle input, then execute script.
//
//===----------------------------------------------------------------------===//
#ifndef COMMANDLINEEDIT_H
#define COMMANDLINEEDIT_H
#include <QAbstractItemView>
#include <QCompleter>
#include <QComboBox>
#include <QStringListModel>
#include <utils/CmdMsgUtil.h>
#include "HistoryLineEdit.h"

class CommandLineEdit : public HistoryLineEdit
{
    Q_OBJECT

public:
    explicit CommandLineEdit(QWidget* parent = 0);
    void keyPressEvent(QKeyEvent *event);
    bool focusNextPrevChild(bool next);


    QWidget* selectorWidget();

public slots:

    void autoCompleteUpdate(const QString text);
    void autoCompleteAddCmd(const QStringList& cmds);
    void autoCompleteAddCmd(const QString cmd);
    void autoCompleteDelCmd(const QString cmd);
    void autoCompleteClearAll();
    void scriptTypeChanged(int index);

    void execute();
private:
    QComboBox* mCmdScriptType;
    QCompleter* mCompleter;
    QStringListModel* mCompleterModel;
    QStringList mDefaultCompletions;
    CmdMsg::ProcType mCurrentScriptType;
};

#endif // COMMANDLINEEDIT_H
