//===- CommandLineEdit.cpp - ART-GUI MainWindow ----------------*- C++ -*-===//
//
//                     ANDROID REVERSE TOOLKIT
//
// This file is distributed under the GNU GENERAL PUBLIC LICENSE
// V3 License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
#include "CommandLineEdit.h"


CommandLineEdit::CommandLineEdit(QWidget* parent)
    : HistoryLineEdit(parent)
{
    // QComboBox, all support proc
    mCmdScriptType = new QComboBox(this);
    mCmdScriptType->setSizeAdjustPolicy(QComboBox::AdjustToContents);
    mCmdScriptType->setStyleSheet("QComboBox::drop-down{border-style: none;}");

    mCmdScriptType->addItem(CmdMsg::procTypeDescription(CmdMsg::ProcType::cmd));
    //mCmdScriptType->addItem(cmdMsg::procTypeDescription(cmdMsg::ProcType::python));
    mCmdScriptType->addItem(CmdMsg::procTypeDescription(CmdMsg::ProcType::script));
    mCmdScriptType->setCurrentIndex(0);
    scriptTypeChanged(0);

    // Initialize QCompleter
    mCompleter = new QCompleter(QStringList(), this);
    mCompleter->setCaseSensitivity(Qt::CaseInsensitive);
    mCompleter->setCompletionMode(QCompleter::PopupCompletion);
    mCompleterModel = (QStringListModel*)mCompleter->model();
    this->setCompleter(mCompleter);

    // Setup signals & slots
    connect(mCompleter, SIGNAL(activated(const QString &)),
            this, SLOT(clear()), Qt::QueuedConnection);
    connect(this, SIGNAL(textEdited(QString)),
            this, SLOT(autoCompleteUpdate(QString)));
    connect(mCmdScriptType, SIGNAL(currentIndexChanged(int)),
            this, SLOT(scriptTypeChanged(int)));
    connect(this, SIGNAL(returnPressed()), this, SLOT(execute()));
}


void CommandLineEdit::keyPressEvent(QKeyEvent* event)
{
    if(event->type() == QEvent::KeyPress && event->key() == Qt::Key_Tab)
    {
        // TAB autocompletes the command
        QStringList stringList = mCompleterModel->stringList();

        if(stringList.size())
        {
            QAbstractItemView* popup = mCompleter->popup();
            QModelIndex currentModelIndex = popup->currentIndex();

            // If not item selected, select first one in the list
            if(currentModelIndex.row() < 0)
                currentModelIndex = mCompleter->currentIndex();

            // If popup list is not visible, selected next suggested command
            if(!popup->isVisible())
            {
                for(int row = 0; row < popup->model()->rowCount(); row++)
                {
                    QModelIndex modelIndex = popup->model()->index(row, 0);

                    // If the lineedit contains a suggested command,
                    // get the next suggested one
                    if(popup->model()->data(modelIndex) == this->text())
                    {
                        int nextModelIndexRow = (currentModelIndex.row() + 1)
                                                % popup->model()->rowCount();
                        currentModelIndex = popup->model()->
                                index(nextModelIndexRow, 0);
                        break;
                    }
                }
            }

            popup->setCurrentIndex(currentModelIndex);
            popup->hide();
        }
    }
    else if(event->type() == QEvent::KeyPress
            && event->modifiers() == Qt::ControlModifier)
    {
        int index = mCmdScriptType->currentIndex(), count = mCmdScriptType->count();
        if(event->key() == Qt::Key_Up)
        {
            // Ctrl + Up selects the previous language
            if(index > 0)
                index--;
            else
                index = count - 1;
        }
        else if(event->key() == Qt::Key_Down)
        {
            // Ctrl + Down selects the next language
            index = (index + 1) % count;
        }
        else
            HistoryLineEdit::keyPressEvent(event);
        mCmdScriptType->setCurrentIndex(index);
    }
    else
        HistoryLineEdit::keyPressEvent(event);
}

// Disables moving to Prev/Next child when pressing tab
bool CommandLineEdit::focusNextPrevChild(bool next)
{
    Q_UNUSED(next);
    return false;
}

void CommandLineEdit::execute()
{
    const QString & cmd = text();

    cmdexec(cmd, mCurrentScriptType, false);

    // Add this line to the history and clear text, regardless if it was executed
    addLineToHistory(cmd);
    emit textEdited("");
    setText("");
}

QWidget* CommandLineEdit::selectorWidget()
{
    return mCmdScriptType;
}

void CommandLineEdit::autoCompleteUpdate(const QString text)
{
    // No command, no completer
    if(text.length() <= 0)
    {
        mCompleterModel->setStringList(QStringList());
    }
    else
    {
        // Save current index
        QModelIndex modelIndex = mCompleter->popup()->currentIndex();

        // Restore index
        mCompleter->popup()->setCurrentIndex(modelIndex);
    }
}

void CommandLineEdit::autoCompleteAddCmd(const QString cmd)
{
    mDefaultCompletions << cmd.split(QChar('\1'), QString::SkipEmptyParts);
    mDefaultCompletions.removeDuplicates();
}

void CommandLineEdit::autoCompleteDelCmd(const QString cmd)
{
    QStringList deleteList = cmd.split(QChar('\1'), QString::SkipEmptyParts);

    for(int i = 0; i < deleteList.size(); i++)
        mDefaultCompletions.removeAll(deleteList.at(i));
}

void CommandLineEdit::autoCompleteClearAll()
{
    // Update internal list only
    mDefaultCompletions.clear();
}

void CommandLineEdit::scriptTypeChanged(int index)
{
    mCurrentScriptType = CmdMsg::getProcType(mCmdScriptType->itemText(index));

    // Force reset autocompletion (blank string)
    emit textEdited("");
}
