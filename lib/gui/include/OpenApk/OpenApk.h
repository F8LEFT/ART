#ifndef OPENAPK_H
#define OPENAPK_H

#include <QDialog>

namespace Ui {
class OpenApk;
}

class OpenApk : public QDialog
{
    Q_OBJECT

public:
    explicit OpenApk(QWidget *parent = 0);
    ~OpenApk();

private:
    Ui::OpenApk *ui;
};

#endif // OPENAPK_H
