#ifndef CONFIG_H
#define CONFIG_H

#include <QDialog>

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


private:
    Ui::Config *ui;

    FileEditor* mFileEditor;
};

#endif // CONFIG_H
