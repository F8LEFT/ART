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

class QuickSmaliHighilght;
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

public slots:
    void save();

private:
    void initColorListWidget();
    void initUnderlineCombobox();
    void initSizeCombobox();
    void initSchemeCombobox();
private:
    Ui::FileEditor *ui;
    QuickSmaliHighilght* mHighlight;

    QColor mForegroundColor;
    QColor mBackgroundColor;
    QColor mUnderlineColor;

    HighLightConfig* mCurrentConfig;
};
class QuickSmaliHighilght : public QSyntaxHighlighter
{
Q_OBJECT
public:
    QuickSmaliHighilght(QTextDocument *parent);


protected:
    void highlightBlock(const QString &text) Q_DECL_OVERRIDE;

public:
    QMap<HighLightConfig::FORMAT , QTextCharFormat> mFormatMap;

};


#endif // FILEEDITOR_H
