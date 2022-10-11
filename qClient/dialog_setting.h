#ifndef DIALOG_SETTING_H
#define DIALOG_SETTING_H

#include <QDialog>

namespace Ui {
class Dialog_setting;
}

class Dialog_setting : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog_setting(QWidget *parent = nullptr);
    ~Dialog_setting();

    virtual void showEvent(QShowEvent *event);

    QString getLocalIP();
    QString getServerIP();
    int getServerPort();

private slots:

    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

    void on_cb_ips_activated(const QString &arg1);

private:
    Ui::Dialog_setting *ui;
};

#endif // DIALOG_SETTING_H
