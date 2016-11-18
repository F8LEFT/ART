//===- FileSchemeConfig.h - ART-GUI Config ---------------------*- C++ -*-===//
//
//                     ANDROID REVERSE TOOLKIT
//
// This file is distributed under the GNU GENERAL PUBLIC LICENSE
// V3 License. See LICENSE.TXT for details.
//
//===---------------------------------------------------------------------===//
//
// Set Scheme Config
//
//===----------------------------------------------------------------------===//

#ifndef FILESCHEMECONFIG_H
#define FILESCHEMECONFIG_H

#include <HighLighter/HighLightConfig.h>


#include <QWidget>
#include <QColor>
#include <QtGui/QSyntaxHighlighter>
#include <QMap>
#include <QtWidgets/QListWidgetItem>
#include  <QFont>

namespace Ui {
class FileSchemeConfig;
}

class FileSchemeConfig : public QWidget
{
    Q_OBJECT

public:
    explicit FileSchemeConfig (QWidget *parent,const QString &cfgDir,
                               const QString &defName,const QString &sampleFile,
                               HighLightConfig::CfgType type);
    ~FileSchemeConfig();



    void save();

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

private:
    void initColorListWidget();
    void initUnderlineCombobox();
    void initSizeCombobox();
    void initSchemeCombobox();
private:
    Ui::FileSchemeConfig *ui;

    QColor mForegroundColor;
    QColor mBackgroundColor;
    QColor mUnderlineColor;

    QSyntaxHighlighter *mHighlight;
    HighLightConfig* mCurrentConfig;

    QString mCfgDir;
    QString mDefName;
    HighLightConfig::CfgType mCfgType;
    QString mSampleFile;
};

#endif // FILESCHEMECONFIG_H
