#ifndef FILEEDITOR_H
#define FILEEDITOR_H

#include <QWidget>

namespace Ui {
class FileEditor;
}

class FileEditor : public QWidget
{
    Q_OBJECT

public:
    explicit FileEditor(QWidget *parent = 0);
    ~FileEditor();

private:
    Ui::FileEditor *ui;
};

#endif // FILEEDITOR_H
