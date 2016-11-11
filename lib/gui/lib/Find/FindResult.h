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
#include <QtGui/QTextDocument>
#include <QThread>
#include <QDir>
#include <QtWidgets/QTreeWidgetItem>

namespace Ui {
    class FindResult;
}

class FindThread;
class FindResult : public QWidget
{
Q_OBJECT

public:
    explicit FindResult(QWidget *parent = 0);

    ~FindResult();
    void startNewFind(const QString &subString,const QString &directory,
                      QTextDocument::FindFlags options,
                      bool useRegexp,bool needReplace);

private slots:
    void onReplaceClick();

public slots:
    void onNewResult(QString filePath, QStringList text, QList<int> line);
    void onTreeFileOpen(QTreeWidgetItem *item, int column);

private:
    Ui::FindResult *ui;
    FindThread* mThread;

    QString mSearchPath;
    QString mSubString;
    QTextDocument::FindFlags mOptions;
    bool mUseRegexp;
    bool mNeedReplace;

    const static int treeFileItemType = QTreeWidgetItem::UserType + 1;
    const static int treeLineItemType = QTreeWidgetItem::UserType + 2;

};


class FindThread : public QThread
{
Q_OBJECT
public:
    FindThread(QObject *parent = Q_NULLPTR);
    void setFind(const QString &subString,const QString &directory,
                 QTextDocument::FindFlags options,
                 bool useRegexp);
signals:
    void newResult(QString filePath, QStringList text, QList<int> line);
protected:
    void run();

    void searchDirectory (QDir dir);
    void searchFile (QString filePath);

private:
    int currentline(const QTextCursor& cursor);
private:
    QString mSearchPath;
    QString mSubString;
    QTextDocument::FindFlags mOptions;
    bool mUseRegexp;
};
#endif // FINDRESULT_H
