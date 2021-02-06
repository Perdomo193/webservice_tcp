#ifndef TCPSERVERVO_H
#define TCPSERVERVO_H

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <QAbstractSocket>
#include "tcpsocketvo.h"

class TcpServerVo : public QTcpServer {
    Q_OBJECT
public:
    explicit TcpServerVo(QObject *parent = nullptr);
    void startServer(int port);

protected:
    void incomingConnection(qintptr handle);
};
#endif // TCPSERVERVO_H
