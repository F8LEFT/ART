//===- FileEditor.h - ART-GUI Config ---------------------------*- C++ -*-===//
//
//                     ANDROID REVERSE TOOLKIT
//
// This file is distributed under the GNU GENERAL PUBLIC LICENSE
// V3 License. See LICENSE.TXT for details.
//
//===---------------------------------------------------------------------===//
//
// Set Text Editor config.
//
//===----------------------------------------------------------------------===//
#ifndef FILEEDITOR_H
#define FILEEDITOR_H

#include "HighLighter/HighLightConfig.h"

#include <QWidget>
#include <QColor>
#include <QtGui/QSyntaxHighlighter>
#include <QMap>
#include <QtWidgets/QListWidgetItem>
#include  <QFont>

namespace Ui {
class FileEditor;
}

class FileEditor : public QWidget
{
    Q_OBJECT

public:
    explicit FileEditor(QWidget *parent = 0);
    ~FileEditor();

protected slots:
    void onForegroundColorBtnClick();
    void onForegroundClearBtnClick();
    void onBackgroundColorBtnClick();
    void onBackgroundClearBtnClick();
    void onUnderlineColorBtnClick();
    void onUnderlineClearBtnClick();

    void onColorListItemChange(QListWidgetItem* current, QListWidgetItem* prev);

    void onSchemeComboboxChange(const QString &text);

    void onFormatUpdate();

    void onSchemeCopyBtnClick();
    void onSchemeDeleteBtnClick();

public slots:
    void save();

private:
    void initColorListWidget();
    void initUnderlineCombobox();
    void initSizeCombobox();
    void initSchemeCombobox();
private:
    Ui::FileEditor *ui;

    QColor mForegroundColor;
    QColor mBackgroundColor;
    QColor mUnderlineColor;

    QSyntaxHighlighter *mHighlight;
    HighLightConfig* mCurrentConfig;
};


#endif // FILEEDITOR_H
