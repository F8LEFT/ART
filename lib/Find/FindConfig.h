//===- FindConfig.h - ART-GUI Find -----------------------------*- C++ -*-===//
//
//                     ANDROID REVERSE TOOLKIT
//
// This file is distributed under the GNU GENERAL PUBLIC LICENSE
// V3 License. See LICENSE.TXT for details.
//
//===---------------------------------------------------------------------===//
//
// Allow user to input search config.
//
//===----------------------------------------------------------------------===//

#ifndef FINDCONFIG_H
#define FINDCONFIG_H

#include <QWidget>
#include <QtGui/QTextDocument>

namespace Ui {
class FindConfig;
}

class FindConfig : public QWidget
{
    Q_OBJECT

public:
    explicit FindConfig(QWidget *parent = 0);
    ~FindConfig();

    void reset(const QString &root, const QString &selectdir);
signals:
    void startNewFind(const QString &subString, const QString &directory,
                      QTextDocument::FindFlags options, bool useRegexp, bool needReplace);

protected slots:
    void onSearchStart();
    void onReplaceStart();

private:
    void onSearch(bool needReplace);

private:
    Ui::FindConfig *ui;
};

#endif // FINDCONFIG_H
