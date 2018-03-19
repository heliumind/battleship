#ifndef MYTCPSERVER_H
#define MYTCPSERVER_H

#include <QTcpServer>
#include <QTcpSocket>
#include <QDebug>
#include <QString>
#include <QTextStream>
#include <QDataStream>
#include <QByteArray>
#include <QIODevice>
#include "messages.h"


class MyTcpServer : public QObject
{
    Q_OBJECT
public:
    explicit MyTcpServer(QObject *parent = 0);
    MyTcpServer(MyTcpServer&&);

signals:
    void messageSent(Message &Shot);
public slots:
    void newConnection();
    //void sendShotToClient();
    void receiveData();
    //void disconnectNow();
    //void sendParameterData();

private:
    QTcpServer *server;
    QTcpSocket *_socket1;
    QDataStream _stream;
};

#endif // MYTCPSERVER_H
