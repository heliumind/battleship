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

class MyClient : public QObject
{
    Q_OBJECT
public:
    explicit MyClient(QObject *parent = 0);

signals:

public slots:
    void ConnectHost();
//    void readyReadDataServer();
    void sendDataToServer();
    void receiveServerData();

private:
    QTcpSocket *_socket;
    QDataStream _dataStream;


};

#endif // MYCLIENT_H
