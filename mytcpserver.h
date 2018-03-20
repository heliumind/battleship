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
    friend class Control;
    explicit MyTcpServer(QObject *parent = 0);
    MyTcpServer(MyTcpServer&&);

signals:
    void messageSent(Message* msg);
    void gotClient();

public slots:
    void newConnection();
    void receiveData();
    void disconnectNow();
    void initServer();
    void sendMessage(Message *msg);

private:
    QTcpServer *server;
    QTcpSocket *_socket;
    QDataStream _stream;
};

#endif // MYTCPSERVER_H
