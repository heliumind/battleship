#ifndef MYCLIENT_H
#define MYCLIENT_H


#include <QTcpServer>
#include <QTcpSocket>
#include <QString>
#include <QDebug>
#include <QTextStream>
#include <QDataStream>
#include <QByteArray>
#include <QIODevice>
#include <QObject>
#include "messages.h"

class MyClient : public QObject
{
    Q_OBJECT
public:
    explicit MyClient(QObject *parent = 0);
    MyClient(MyClient&&);


signals:
    void messageSent(Message* msg);


public slots:
    void ConnectHost();
    void receiveServerData();
    void disconnectNow();
    void sendMessage(Message *msg);

public:
    QTcpSocket *_socket;
    QDataStream _dataStream;
};

#endif // MYCLIENT_H
