#include <QCoreApplication>
#include "TalkServer.h"
#include <QTextCodec>
int main(int argc, char *argv[])
{
    QTextCodec *codec = QTextCodec::codecForName("GBK");//或者"GBK",不分大小写
        QTextCodec::setCodecForLocale(codec);

    QCoreApplication a(argc, argv);
    TalkServer server;
    server.init();
    return a.exec();
}
