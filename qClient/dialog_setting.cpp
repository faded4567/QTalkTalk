#include "dialog_setting.h"
#include "ui_dialog_setting.h"
#include <QDebug>
#include <QNetworkInterface>
Dialog_setting::Dialog_setting(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_setting)
{
    ui->setupUi(this);

    ui->cb_ips->clear();
    //获取全部地址
    auto vecAllAddress = QNetworkInterface::allAddresses();
    if(!vecAllAddress.empty())
    {
        //向下拉选项中添加可选地址
        for(auto it : vecAllAddress)
        {
            //筛选出IPV4的地址，添加
            if(QAbstractSocket::NetworkLayerProtocol::IPv4Protocol==it.protocol())
            {
                qDebug()<<it.toString();
                ui->cb_ips->addItem(it.toString());
            }
        }
    }
}

Dialog_setting::~Dialog_setting()
{
    delete ui;
}

void Dialog_setting::showEvent(QShowEvent *event)
{
    qDebug()<<"dlg show";

    ui->cb_ips->clear();
    //获取全部地址
    auto vecAllAddress = QNetworkInterface::allAddresses();
    if(!vecAllAddress.empty())
    {
        //向下拉选项中添加可选地址
        for(auto it : vecAllAddress)
        {
            //筛选出IPV4的地址，添加
            if(QAbstractSocket::NetworkLayerProtocol::IPv4Protocol==it.protocol())
            {
                qDebug()<<it.toString();
                ui->cb_ips->addItem(it.toString());
            }
        }
    }


}

//获取本地IP
QString Dialog_setting::getLocalIP()
{
    //当前框里的文本
    return ui->cb_ips->currentText();
}

//获取服务端IP
QString Dialog_setting::getServerIP()
{
    return ui->ServerIP->text();
}

//获取端口号
int Dialog_setting::getServerPort()
{
    return ui->PortNum->text().toUInt();
}


void Dialog_setting::on_pushButton_2_clicked()
{
    //点击取消、隐藏窗口
    qDebug()<<"Dialog_setting hide";
    this->hide();
}

void Dialog_setting::on_pushButton_clicked()
{
    qDebug()<<"Dialog_setting OK Button";
    //点击OK按钮处理
    this->done(1);
}

void Dialog_setting::on_cb_ips_activated(const QString &arg1)
{

}
