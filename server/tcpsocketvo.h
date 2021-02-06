#ifndef TCPSOCKETVO_H
#define TCPSOCKETVO_H

#include <QObject>
#include <QTcpSocket>
#include <QThreadPool>
#include "ovtaskimage.h"

class TcpSocketVo : public QObject {
    Q_OBJECT
public:
    explicit TcpSocketVo(QObject *parent = nullptr);
    void SetSocket(qintptr descriptor);

signals:

public slots:
    void connected();
    void disconnected();
    void readyRead();

    void TaskResponse(QByteArray response);

private:
    QTcpSocket *socket;
};

#endif // TCPSOCKETVO_H
