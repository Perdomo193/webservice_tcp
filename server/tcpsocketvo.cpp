#include "tcpsocketvo.h"

#include <QJsonObject>
#include <QJsonDocument>

TcpSocketVo::TcpSocketVo(QObject *parent) : QObject(parent) {
    QThreadPool::globalInstance()->setMaxThreadCount(5);
}

void TcpSocketVo::SetSocket(qintptr descriptor) {
    socket = new QTcpSocket(this);
    connect(socket, SIGNAL(connected()), this, SLOT(connected()));
    connect(socket, SIGNAL(disconnected()), this, SLOT(disconnected()));
    connect(socket, SIGNAL(readyRead()), this, SLOT(readyRead()));
    socket->setSocketDescriptor(descriptor);
}

void TcpSocketVo::connected() { qDebug() << "Client connected event"; }
void TcpSocketVo::disconnected() { qDebug() << "Client disconnected"; }

void TcpSocketVo::readyRead() {
    QJsonParseError parseError;
    QByteArray socketInput = socket->readAll();

    QJsonDocument inputDocJson = QJsonDocument::fromJson(socketInput, &parseError);
    //if(parseError.error == QJsonParseError::NoError) { return; };

    OvTaskImage *ovimage = new OvTaskImage(inputDocJson.object());
    ovimage->setAutoDelete(true);
    connect(ovimage, SIGNAL(Response(QByteArray)), this, SLOT(TaskResponse(QByteArray)), Qt::QueuedConnection);
    QThreadPool::globalInstance()->start(ovimage);
}

void TcpSocketVo::TaskResponse(QByteArray response) {
    socket->write(response);
}
