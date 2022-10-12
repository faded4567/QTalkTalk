#ifndef TALKSERVER_H
#define TALKSERVER_H
#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <QtDebug>
#include <QAbstractSocket>

//tcp信息结构体
struct TCPinfo
{
    QTcpSocket *socket;
    QByteArray arrData;
};
class TalkServer:public QObject{
    Q_OBJECT
public:
    TalkServer()
    {
    }
    ~TalkServer()
    {

    }
    void init()
    {
        qDebug()<<"TalkServer is init!";
        m_tcpServer.listen(QHostAddress::Any,1234);
        connect(&m_tcpServer,&QTcpServer::newConnection,this,&TalkServer::DealNewConnection);
        //connect(&m_tcpServer,SIGNAL(error(QAbstractSocket::SocketError)),this,SLOT( TalkServer::DealConnectionError(QAbstractSocket::SocketError error)));
        qDebug()<<"TalkServer is running!!!";
    }
    void DealConnectionError(QAbstractSocket::SocketError error)
    {
        qDebug()<<"connection is error.ErrorCode is "<<error;
    }
    void DealNewConnection()
    {
        qDebug()<<"DealNewConnection() Begin!";
        //获取socket
        auto * socket = m_tcpServer.nextPendingConnection();
        TCPinfo tcpinfo{socket};
        m_stSocketinfo<<tcpinfo;
        connect(socket,&QTcpSocket::readyRead,this,&TalkServer::DealRead);

    }
    void DealRead()
    {
        qDebug()<<"DealRead() Begin!";
        //获取发送源对象
        QTcpSocket *socket=static_cast<QTcpSocket *>(sender());
        auto data =socket->readAll();


        for(int i=0;i<m_stSocketinfo.size();i++)
        {

            //找到匹配的对象，发送者
            if(socket==m_stSocketinfo[i].socket)
            {
                m_stSocketinfo[i].arrData.append(data);
                DealPack(i);
                break;

            }
        }
    }
    //处理数据包
    void DealPack(int i)
    {
        qDebug()<<"DealPack() Begin!";
        qDebug()<<"DealPack():i= "<<i;
        auto info = m_stSocketinfo[i];
        m_stSocketinfo[i].arrData.clear();
        for(int i=0;i<4;i++)
        {
            //打印协议内容
            qDebug()<<QString("%1").arg((unsigned char)info.arrData.at(i),2,16,QLatin1Char('0'))+' ';
        }
        if(info.arrData.size()>=4 && info.arrData[0].operator== (0x66))
        {
            //将数据长度取出
            quint16 len = (info.arrData[2]<<8 & 0xFF00)|static_cast<quint16>(info.arrData[1]);
            qDebug()<<"len = "<<len<<" info.arrData.size()="<<info.arrData.size()<<endl;
            if(info.arrData.size()>=len)
            {
                //取出数据包
                QByteArray arr = info.arrData.mid(0,len);
                DealRec(arr,info);
                info.arrData = info.arrData.mid(len);
            }
            else
            {
                qDebug()<<"[ServerError]len > data.size!!!"<<endl;
            }
        }
    }
    void DealRec(QByteArray arr,TCPinfo info)
    {
        qDebug()<<"DealRec Begin!!!";

        char cmd = arr[3];
        qDebug()<<arr[3];
        QByteArray data = arr.mid(4);
        qDebug()<<data;
        if(0x01 == cmd)
        {
            //心跳包。客户端向服务端发送，检测服务端是否还在响应
            //开启定时器

        }

//        else if(0x02 == cmd)
//        {
//           //发送的数据包
//           ui->textBrowser->append("<front color='green'>我发送:"+data);
//        }
        else if(0x03 == cmd)
        {
            //附加发送源
            //data.insert(0,(info.socket->peerAddress().toString()+":").toUtf8());
            //将数据包发送给所有客户端
            QByteArray arrsendBuffer;//除发送者外的客户端
             //数据头
             arrsendBuffer.append(0x66);
             //长度
             quint16 len=arr.size();
             arrsendBuffer.append(static_cast<char>(len & 0x00FF));
             arrsendBuffer.append(static_cast<char>(len>>8 & 0XFF00));
             //指令
             arrsendBuffer.append(0x03);
             //内容
             arrsendBuffer.append(data);
             for(int i=0;i<4;i++)
             {
                 //打印协议内容
                 qDebug()<<QString("%1").arg((unsigned char)arrsendBuffer.at(i),2,16,QLatin1Char('0'))+' ';
             }
            for(int i = 0;i<m_stSocketinfo.size();i++)
            {
                if(m_stSocketinfo[i].socket==info.socket)
                {
                    //发送者
                    arrsendBuffer[3]=0x02;
                    m_stSocketinfo[i].socket->write(arrsendBuffer);
                    continue;
                }
                //接受者
                arrsendBuffer[3]=0x03;
                m_stSocketinfo[i].socket->write(arrsendBuffer);
            }

        }

    }
private:
    QTcpServer m_tcpServer;

    QList<TCPinfo> m_stSocketinfo;
};
#endif // TALKSERVER_H
