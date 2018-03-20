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
    void messageSent(Message* msg);


public slots:
    void newConnection();
    void sendShot();
    void receiveData();
    void sendParameterData();
    void sendShotAnswer();
    void sendAnswer();
    void sendGameStart();
    void sendGroupID();
    void disconnectNow();
    void initServer();
    void receiveMessageLogic(Message *msg);

private:
    QTcpServer *server;
    QTcpSocket *_socket;
    QDataStream _stream;
};

#endif // MYTCPSERVER_H
