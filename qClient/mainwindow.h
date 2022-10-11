#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpSocket>
#include "dialog_setting.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void ConnetServer();
    void DealClientRead();
    void DealPackage(QByteArray arr);
    void DealStateChanged(QAbstractSocket::SocketState socketstate);
private slots:

    void on_SendButton_clicked();

    void on_ExitButton_clicked();

    void on_toolButton_clicked();

private:
    Ui::MainWindow *ui;
    Dialog_setting m_Dialog;    //设置dialog
    QString m_strLocalIP;       //本地IP
    QString m_strServerIP;      //服务端IP
    int m_iPort;                //端口号

    QTcpSocket m_tTcpSocket;    //socket对象

    QByteArray m_buffer;
    int m_iPackageLen;

};
#endif // MAINWINDOW_H
