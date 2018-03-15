#include "myclient.h"
#include <iostream>

MyClient::MyClient(QObject *parent) : QObject(parent)
{
    _socket = new QTcpSocket(this);
    _dataStream.setDevice(_socket);

    //init. sending data to the server
    connect(_socket, &QTcpSocket::connected,
            this, &MyClient::sendDataToServer);

//    //init. reading incoming data from sever
//    connect(_socket, &QTcpSocket::readyRead,
//            this, &MyClient::readyReadDataServer);

    //init. reading from server
    connect(_socket, &QTcpSocket::readyRead,
            this, &MyClient::receiveServerData );

}

void MyClient::ConnectHost()
{
    //QByteArray data;
   _socket->connectToHost("localhost",1234);
}


//get the messages the server emits
//void MyClient::readyReadDataServer()
//{
//    //read all data
//    QByteArray dataServer = _socket->readAll();
//    //give out all data collected
//    qDebug()<<dataServer.data();
//}

void MyClient::sendDataToServer()
{
    //creat outstream
    QDataStream outStreamC(_socket);

    //write a quint data to test the connection and if server receives everything

    quint8 data = 4;
    outStreamC << data;
    data = 65;
    outStreamC << data;

    //_socket->write(block);
    //_socket->flush();
}


void MyClient::receiveServerData()
{

    QDataStream inStreamC(_socket);
    quint8 block;

    while(_socket->bytesAvailable())
    {
        inStreamC>> block;
        qDebug()<<block;

    }
}
