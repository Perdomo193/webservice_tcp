#include "tcpservervo.h"
#include <QDebug>

TcpServerVo::TcpServerVo(QObject *parent) : QTcpServer(parent){}

void TcpServerVo::startServer(int port) {
    if(!this->listen(QHostAddress::Any, port)) {
        qDebug() << "Could not start server";
    } else {
        qDebug() << "Server start " << port << ": Now is listening..." ;
    }
}

void TcpServerVo::incomingConnection(qintptr handle) {
    TcpSocketVo *socket = new TcpSocketVo( this);
    socket->SetSocket(handle);
}
