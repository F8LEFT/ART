#ifndef FILEEDITOR_H
#define FILEEDITOR_H

#include <QWidget>
#include <QColor>
#include <>

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

private:
    Ui::FileEditor *ui;

    QColor mForegroundColor;
    QColor mBackgroundColor;
    QColor mUnderlineColor;
};

#endif // FILEEDITOR_H
