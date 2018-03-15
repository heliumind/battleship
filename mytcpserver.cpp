#include "mytcpserver.h"
#include <iostream>

MyTcpServer::MyTcpServer(QObject *parent) : QObject(parent)
{
       server = new QTcpServer(this);
       _stream.setDevice(_socket1);

       // whenever a user connects, it will emit signal
       connect(server, &QTcpServer::newConnection,
               this, &MyTcpServer::newConnection);

            //listen for a client to connect
       if(!server->listen(QHostAddress::Any, 1234))
       {
           qDebug() << "Server could not start";
       }
       else
       {
           qDebug() << "Server started!";
       }

}

void MyTcpServer::newConnection()
{
    //w8ing for the next connection
    _socket1 = server->nextPendingConnection();

    //init. reading from client
    connect(_socket1, &QTcpSocket::readyRead,
            this, &MyTcpServer::receiveClientData );

    //send data to client
    connect(_socket1, &QTcpSocket::readyRead,
            this, &MyTcpServer::sendDataToClient);


    // tell client he is connected
    qDebug()<<"Client agrees\n";

    //server connection close
    //socket->write("Connection to Server lost");
    //socket->close();
}

void MyTcpServer::receiveClientData()
{
       QDataStream inStream(_socket1);
       quint8 block;
       //the client sends 2 bytes while server received just one
       //with while(..) u can timeout to get every byte sended
       while(_socket1->bytesAvailable()) {
           inStream>> block;
           qDebug()<<block;
       }
}


void MyTcpServer::sendDataToClient()
{
    QDataStream outStream(_socket1);
    quint8 data = 0x01;
    outStream << data;
    data =67;
    outStream<<data;
}


