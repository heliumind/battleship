#ifndef MTCPSERVER_H
#define MTCPSERVER_H

#include <QTcpServer>
#include <QTcpSocket>
#include <QDebug>
#include <QString>
#include <QTextStream>
#include <QDataStream>
#include <QByteArray>
#include <QIODevice>



class MyTcpServer : public QObject
{
    Q_OBJECT
public:
    explicit MyTcpServer(QObject *parent = 0);

signals:

public slots:
    void newConnection();
    void receiveClientData();
    void sendDataToClient();
    //void disconnected();


private:
    QTcpServer *server;
    QTcpSocket *_socket1;
    QDataStream _stream;



};

#endif // MYTCPSERVER_H
