#ifndef CHOOSEPROCESS_H
#define CHOOSEPROCESS_H

#include <QDialog>

namespace Ui {
class ChooseProcess;
}

class ChooseProcess : public QDialog
{
    Q_OBJECT

public:
    explicit ChooseProcess(const QString &host, int port, const QString &filter,
                               bool bindJdwp, QWidget *parent);
    ~ChooseProcess();

    // configuration
    void loadFromConfig();
    void saveToConfig();

    int getTargetPid() { return m_pid; }
    QString getHostname() { return m_host; };
    int getPort() { return m_port; }

    bool isValid() { return m_pid != 0 && m_port != 0 && !m_host.isEmpty(); }

    bool bindJdwp() { return m_bindJdwp; }
protected :
    void accept();

private:
    void resetProcessInfo();

private:
    Ui::ChooseProcess *ui;

    int m_pid;
    QString m_host;
    int m_port;
    bool m_bindJdwp;
};

#endif // CHOOSEPROCESS_H
