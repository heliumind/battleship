#include "myclient.h"
#include "messages.h"
#include <iostream>
#include <algorithm>
#include <vector>

#include <QDebug>

MyClient::MyClient(QObject *parent) : QObject(parent)
{
    _socket = new QTcpSocket(this);
    _dataStream.setDevice(_socket);

//    //init. sending shot coordinates to server
//    connect(_socket, &QTcpSocket::readyRead,
//            this, &MyClient::sendShotToServer);

//    //init. reading from server
//    connect(_socket, &QTcpSocket::readyRead,
//            this, &MyClient::receiveServerData);


}

void MyClient::ConnectHost()
{
    //QByteArray data;
   _socket->connectToHost("localhost",1234);

   QObject::connect(_socket, &QTcpSocket::readyRead,
               this, &MyClient::receiveServerData);

}

void MyClient::sendShotToServer()
{
    //creat outstream
    QDataStream outStream(_socket);

    //write a quint data to test the connection and if server receives everything
    quint8 data1 = 0x80;
    quint8 data2 = 0x02;
    quint8 data3 = 0x05;
    quint8 data4 = 0x05;
    outStream << data1 << data2 << data3 << data4;

    //_socket->write(block);
    //_socket->flush();
}


//receive shot data from server
void MyClient::receiveServerData()
{
    Shot shot;

    qDebug() << "In receive";
    QDataStream inStream(_socket);
    quint8 block;
    //creat vector to catch all incoming bytes
    std::vector<uint8_t> new_block;
    while(_socket->bytesAvailable()) {
        inStream >> block;
        new_block.push_back(block);
        qDebug()<<block;
    }
    //read first byte for identification
    uint8_t cmd=new_block[0];
    qDebug()<< new_block[0];
    switch(cmd)
    {
    case 0x01: qDebug()<< "Parameter Message";
    break;

    case 0x02: qDebug() << "Gamestart question";
    break;

    case 0x03: qDebug() << "Shot Message";
                            qDebug() << shot._coordinates_x;
                            shot._coordinates_x = new_block[2];
                            shot._coordinates_y = new_block[3];
                            qDebug() << shot._coordinates_x;
                            //signal zu emiitiert das gefüllt

    break;

    case 0x10: qDebug() << "Answer on game start";
    break;

    case 0x11: qDebug() << "Answer on shot";
    break;

    case 0x80: qDebug() << "Identication group";
    break;

    default: qDebug() << "Unknown Message";
    break;
    }

}

//void MyClient::disconnectNow()
//{

//    _socket->close();
//}
