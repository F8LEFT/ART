//===- FindDialog.h - ART-GUI Find -----------------------------*- C++ -*-===//
//
//                     ANDROID REVERSE TOOLKIT
//
// This file is distributed under the GNU GENERAL PUBLIC LICENSE
// V3 License. See LICENSE.TXT for details.
//
//===---------------------------------------------------------------------===//
//
// Show find dialog and search all project file.
//
//===----------------------------------------------------------------------===//

#ifndef FINDDIALOG_H
#define FINDDIALOG_H

#include <QWidget>
#include <QtGui/QTextDocument>

namespace Ui {
class FindDialog;
}

class FindConfig;

class FindDialog : public QWidget
{
    Q_OBJECT

public:
    explicit FindDialog(QWidget *parent = 0);
    ~FindDialog();

public slots:
    bool closeAll();

    void onProjectOpened(QStringList args);
    void onProjectClosed ();
    void onSearchDirectory(const QString& dir);

    void onNewFind(const QString &subString, const QString &directory,
                   QTextDocument::FindFlags options,
                   bool useRegexp, bool needReplace);
private:
    Ui::FindDialog *ui;

    FindConfig* mFindConfig;
};

#endif // FINDDIALOG_H
