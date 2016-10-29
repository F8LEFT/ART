#ifndef CONFIG_H
#define CONFIG_H

#include <QDialog>
#include <QListWidget>

namespace Ui {
class Config;
}

class FileEditor;

class Config : public QDialog
{
    Q_OBJECT

public:
    explicit Config(QWidget *parent = 0);
    ~Config();

protected slots:
    void onConfigTabChange(QListWidgetItem *current, QListWidgetItem *previous);


private:
    Ui::Config *ui;

    QVector<QWidget*> mWidgetList;
    QVector<QString> mWidgetNativeNameList;
    QVector<QIcon> mIconList;

    FileEditor* mFileEditor;


};

#endif // CONFIG_H
