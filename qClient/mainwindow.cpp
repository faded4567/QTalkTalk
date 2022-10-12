#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "dialog_setting.h"

#include <QDebug>
#include <QApplication>
#include <qhostaddress.h>
#include <QAbstractSocket>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow), m_strLocalIP(""),m_strServerIP(""),m_iPort(0)
{
    ui->setupUi(this);
    this->setWindowFlag(Qt::FramelessWindowHint);
    //绑定函数 用于接收连接成功和失败的消息
    auto con=[&](){

        ui->textBrowser->append(m_strLocalIP+" is Connectted");
    };
    connect(&m_tTcpSocket,&QAbstractSocket::connected,this,con);

    auto discon=[&](){
        ui->textBrowser->append(m_strLocalIP+" is DisConnectted");
    };
    connect(&m_tTcpSocket,&QAbstractSocket::disconnected,this,discon);

    connect(&m_tTcpSocket,&QAbstractSocket::readyRead,this,&MainWindow::DealClientRead);

    connect(&m_tTcpSocket,&QTcpSocket::stateChanged,this,&MainWindow::DealStateChanged);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::ConnetServer()
{
    qDebug()<<"Connet Begin!!!";
    //连接服务端
    //关闭上次socket
    m_tTcpSocket.close();

    //获取连接所用的信息
    m_strLocalIP = m_Dialog.getLocalIP();
    m_strServerIP = m_Dialog.getServerIP();
    m_iPort = m_Dialog.getServerPort();
    qDebug()<<"m_strLocalIP="<<m_strLocalIP;
    qDebug()<<"m_strServerIP="<<m_strServerIP;
    qDebug()<<"m_iPort="<<m_iPort;
    //1.绑定
    m_tTcpSocket.bind(QHostAddress(m_strLocalIP));
    //2.连接
    m_tTcpSocket.connectToHost(QHostAddress(m_strServerIP),m_iPort);

    ui->textBrowser->append("Waitting For "+m_strLocalIP+" Connecttion.....");
    //连接等待，如果connectToHost连接成功，则立即返回true，否则到达最延迟后返回false
    if (m_tTcpSocket.waitForConnected(5000)){
       qDebug() << m_strLocalIP<<"is is Connected!!" << endl;
    }
    else{
       qDebug() << m_strLocalIP<<" Connecttion Failed！！" << endl;
       ui->textBrowser->append(m_strLocalIP+"  Connecttion Failed！！");
       m_tTcpSocket.close();
    }


}

void MainWindow::DealClientRead()
{
    //存起来
    m_buffer.push_back(m_tTcpSocket.readAll());
    //校验数据包
    //设计的协议为 数据头（1字节）+数据长度（2字节）+指令（1字节）+内容
    if(m_buffer.size()>=4 && m_buffer[0].operator== (0x66))
    {
        //将数据长度取出
        quint16 len = (m_buffer[2]<<8 & 0xFF00)|static_cast<quint16>(m_buffer[1]);
        if(m_buffer.size()>=len)
        {
            //取出数据包
            QByteArray arr = m_buffer.mid(0,len);
            m_buffer = m_buffer.mid(len);
            DealPackage(arr);
        }
    }
}

void MainWindow::DealPackage(QByteArray arr)
{
    //处理数据包
    qDebug()<<"DealPackage begin";
    char cmd = arr[3];
    qDebug()<<arr[3];
    QByteArray data = arr.mid(4);
    qDebug()<<data;
    if(0x01 == cmd)
    {
        //心跳包。客户端向服务端发送，检测服务端是否还在响应
        //开启定时器，

    }
    else if(0x02 == cmd)
    {
       //发送的数据包
       ui->textBrowser->append("<font color='green'>我发送:"+data);
    }
    else if(0x03 == cmd)
    {
        //接收的数据包
         ui->textBrowser->append("<font color='blue'>接收:"+data);
    }
}

void MainWindow::DealStateChanged(QAbstractSocket::SocketState socketstate)
{
    qDebug()<<"SocketState is changed to "<<socketstate;
}



void MainWindow::on_SendButton_clicked()
{
    //点击发送按钮处理
    qDebug()<<"Main::on_SendButton_clickede";
    auto str=ui->textEdit->toPlainText();
    ui->textEdit->clear();

    QByteArray arr = str.toUtf8();
    quint16 len=arr.size()+4;
    //数据头
    arr.insert(0,0x66);
    //长度
    arr.insert(1,static_cast<char>(len & 0x00FF));
    arr.insert(2,static_cast<char>(len>>8 & 0XFF00));
    //指令
    arr.insert(3,0x03);

    for(int i=0;i<4;i++)
    {
        //打印协议内容
        qDebug()<<QString("%1").arg((unsigned char)arr.at(i),2,16,QLatin1Char('0'))+' ';
    }
    qDebug()<<"client send :"<<str<<endl;

    m_tTcpSocket.write(arr);

}

void MainWindow::on_ExitButton_clicked()
{
    //点击退出按钮处理
    exit(0);
}

void MainWindow::on_toolButton_clicked()
{
    qDebug()<<"Main::setting clicked";
    //点击设置处理
    //显示dialog
    if(m_Dialog.exec())
    {

        ConnetServer();

    }

}
