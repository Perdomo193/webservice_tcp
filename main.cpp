#include <QCoreApplication>
#include <QDebug>
#include "server/tcpservervo.h"

int main(int argc, char *argv[]) {
    QCoreApplication a(argc, argv);
    TcpServerVo tcpservervo;
    tcpservervo.startServer(4242);
    return a.exec();
}
