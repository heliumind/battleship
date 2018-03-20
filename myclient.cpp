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

//    //init. sending shot coordinates to server -> senden nur bei funktionsaudfruf durch die logik
//    connect(_socket, &QTcpSocket::readyRead,
//            this, &MyClient::sendShotToServer);

    //init. reading from server
    connect(_socket, &QTcpSocket::readyRead,
            this, &MyClient::receiveServerData);


}

void MyClient::ConnectHost()
{
    //QByteArray data;
   _socket->connectToHost("localhost",1234);

   QObject::connect(_socket, &QTcpSocket::readyRead,
               this, &MyClient::receiveServerData);

}


//receive shot data from server
void MyClient::receiveServerData()
{
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
    case 0x01:
    {
                      Parameter parameter = Parameter(0x01, 0x06);
                      parameter._field_x = new_block[2];
                      parameter._field_y = new_block[3];
                      parameter._n_battleship = new_block[4];
                      parameter._n_cruiser = new_block[5];
                      parameter._n_destroyer = new_block[6];
                      parameter._n_submarine = new_block[7];
                      Message *msgptr = &parameter;
                      emit messageSent(msgptr);
    }

    break;

    case 0x02:
    {                GameStart gamestart = GameStart(0x02, 0x00);
                     Message *msgptr = &gamestart;
                     emit messageSent(msgptr);

    }

    break;

    case 0x03:       //fill in coordinates that where shot at
    {                Shot shot = Shot(0x03, 0x02);
                     qDebug() << shot._coordinates_x;
                     //shot._cmd = block[0];
                     shot._coordinates_x = new_block[2];
                     shot._coordinates_y = new_block[3];
                     qDebug() << shot._coordinates_x;
                     Message *msgptr = &shot;
                     //emitiert das shot angekommen ist
                     emit messageSent(msgptr);
    }
    break;

    case 0x10:
        {            //fill in anser on gamestart;
                     AnswerGame answergame = AnswerGame(0x10, 0x01);
                     qDebug() << answergame._status;
                     answergame._status = new_block[2];
                     Message *msgptr =  &answergame;
                     emit messageSent(msgptr);
        }

    break;

    case 0x11:       //fill in shot answer
     {
                      ShotAnswer shotanswer = ShotAnswer(0x11, /*variable*/0x01);
                      shotanswer._status = new_block[2];
                      Message *msgptr = &shotanswer;
                      emit messageSent(msgptr);
     }

    case 0x80: //fill in groupNumber
                     {
                     IdentificationGroup id = IdentificationGroup(0x80, 0x01);
                     id._groupNumber = new_block[2];
                     Message *msgptr = &id;
                     emit messageSent(msgptr);
    }

    default: qDebug() << "Unknown Message";
    break;
    }

}

void MyClient::sendShot()
{
    Shot shot = Shot(0x03, 0x02);

    QDataStream outStream(_socket);
    quint8 data1 = shot._cmd;
    quint8 data2 = shot._dlc;
    quint8 data3 = shot._coordinates_x;
    quint8 data4 = shot._coordinates_y;
    outStream << data1 << data2 << data3 << data4;

}


void MyClient::sendShotAnswer()
{
    ShotAnswer shotanswer = ShotAnswer(0x11, /*variable*/ 0x01);
    QDataStream outStream(_socket);
    quint8 data1 = shotanswer._cmd;
    //quint8 data2 = shotanswer._dlc_shotanswer;
    quint8 data3 = shotanswer._status;

    outStream << data1 /*<< data2*/ << data3;
}

void MyClient::sendAnswer()
{
    AnswerGame answergame = AnswerGame(0x10, 0x01);
    QDataStream outStream(_socket);
    quint8 data1 = answergame._cmd;
    quint8 data2 = answergame._dlc;
    quint8 data3 = answergame._status;
    outStream << data1 << data2 << data3;
}

void MyClient::sendGroupID()
{
    IdentificationGroup idgroup = IdentificationGroup(0x80, 0x01);

    QDataStream outStream(_socket);
    quint8 data1 = idgroup._cmd;
    quint8 data2 = idgroup._dlc;
    quint8 data3 = idgroup._groupNumber;

    outStream << data1 << data2 << data3;
}

void MyClient::sendGameStart()
{
    GameStart gamestart = GameStart(0x02, 0x00);
    QDataStream outStream(_socket);
    quint8 data1 = gamestart._cmd;
    quint8 data2 = gamestart._dlc;
    outStream << data1 << data2;
}

void MyClient::disconnectNow()
{

    _socket->close();
}
