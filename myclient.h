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

class MyClient : public QObject
{
    Q_OBJECT
public:
    explicit MyClient(QObject *parent = 0);


signals:

public slots:
    void ConnectHost();
    void receiveServerData();
    void sendShotToServer();

    //void disconnectNow();

public:
    QTcpSocket *_socket;
    QDataStream _dataStream;
};

#endif // MYCLIENT_H
