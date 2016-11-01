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
    void setFindEditFocus();
    void setFindText(const QString s);

signals:
    void closeWidget();
    void find(const QString &subString, QTextDocument::FindFlags options
                                        = QTextDocument::FindFlags());
    void replace(const QString &subString, const QString &replaceWith);
    void replaceAll(const QString &subString, const QString &replaceWith);
public slots:
    void onFindPrevBtnClick();
    void onFindNextBtnClick();
    void onReplaceBtnClick();
    void onReplaceNextBtnClick();
    void onReplaceAllBtnClick();

    void onCloseBtnClicked();


private:
    Ui::FindWidget *ui;
};

#endif // FINDWIDGET_H
