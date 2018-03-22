#include "mytcpserver.h"
#include "messages.h"
#include <iostream>
#include <algorithm>
#include <vector>
#include "datatypes.hpp"

MyTcpServer::MyTcpServer(QObject *parent) : QObject(parent)
{

}

void MyTcpServer::initServer(int port)
{
    server = new QTcpServer(this);

    if(!server->listen(QHostAddress::Any, port))
    {
        qDebug() << "Server could not start";
        //server->deleteLater();
    }
    else
    {
        qDebug() << "Server started!";
        // whenever a user connects, it will emit signal
        connect(server, &QTcpServer::newConnection,
                this, &MyTcpServer::newConnection);
        //sendShot();

    }

}

//start connection with
void MyTcpServer::newConnection()
{
    _stream.setDevice(_socket);
    //w8ing for the next connection
    _socket = server->nextPendingConnection();

    //send shot data to client -> data ready permanent activated



    connect(_socket, &QTcpSocket::readyRead,
             this, &MyTcpServer::receiveData);

    // tell client he is connected
    emit gotClient();
    qDebug()<<"Client agrees\n";

}


//receive shot data from client
void MyTcpServer::receiveData()
{

     QDataStream inStream(_socket);
     quint8 block;
    //creat vector to catch all incoming bytes
    std::vector<quint8> new_block;
    //save all incoming data into the vector
    while(_socket->bytesAvailable()) {

        inStream>> block;
        new_block.push_back(block);
        //qDebug()<<block;
    }

    //read first byte for identification
    uint8_t cmd = new_block[0];
    //qDebug()<< "Hier" <<new_block[0];

    switch(cmd)
    {
    // case 0x01 only sent from server

    case 0x02:
    {               GameStart gamestart = GameStart(0x02, 0x00);
                    qDebug() << "Gamstart cmd: " << gamestart._cmd;
                    qDebug() << "Gemstart dlc: " << gamestart._dlc;
                    emit receiveGameStart();

    }
    break;

    case 0x03:       //fill in coordinates that where shot at
    {                Shot shot = Shot(0x03, 0x02);
                     //shot._cmd = block[0];
                     shot._coordinates_x = new_block[2];
                     shot._coordinates_y = new_block[3];
                     //emitiert das shot angekommen ist
                     emit receiveShot(shot);
    }
    break;

    case 0x10:

        {            //fill in anser on gamestart;
                     AnswerGame answergame = AnswerGame(0x10, 0x01);
                     qDebug() << "AnswerGAme:" << answergame._status;
                     // answergame._status = new_block[2];
                     emit receiveAnswerGame(answergame);

        }

    break;

   case 0x11:       //fill in shot answer
    {
        uint8_t status = new_block[2];
        switch(status)
        {
        case 0x00: { //case not hit
                     ShotAnswer shotanswer = ShotAnswer(0x11,0x01);
                     shotanswer._status = new_block[2];
                     qDebug() << "Antwort schuss mit value :0";
                     emit receiveShotAnswer(shotanswer);
        }
        break;
        case 0x01: {//case hit
                    ShotAnswer shotanswer = ShotAnswer(0x11,0x01);
                    shotanswer._status = new_block[2];
                    qDebug() << "Antwort schuss mit value :1";
                    emit receiveShotAnswer(shotanswer);
        }
        break;
        case 0x02:{//case hit and sunk
                    ShotAnswer shotanswer = ShotAnswer(0x11, new_block[1]);
                    shotanswer._status = new_block[2];
                    position _location;
                    for (size_t i = 3; i < new_block.size(); i+=2) {
                        _location.push_back(std::make_pair(new_block[i], new_block[i+1]));
                    }
                    shotanswer._position = _location;

                    emit receiveShotAnswer(shotanswer);
        }
        break;
        case 0x03:{     //case sunken ship and game end
                     ShotAnswer shotanswer = ShotAnswer(0x11, new_block[1]);
                     shotanswer._status = new_block[2];
                     position _location;
                     for (size_t i = 3; i < new_block.size(); i+=2) {
                         _location.push_back(std::make_pair(new_block[i], new_block[i+1]));
                     }
                     shotanswer._position = _location;

                     emit receiveShotAnswer(shotanswer);
        }
        break;
        case 0x10: {
                    ShotAnswer shotanswer = ShotAnswer(0x11, 0x01);
                    shotanswer._status = new_block[2];
                    qDebug() << "Antwort schuss mit value :10";
                    emit receiveShotAnswer(shotanswer);
        }
        break;
        case 0x11:{
                    ShotAnswer shotanswer = ShotAnswer(0x11, 0x01);
                    shotanswer._status = new_block[2];
                    emit receiveShotAnswer(shotanswer);

        }
        break;
        case 0x20:{
                    ShotAnswer shotanswer = ShotAnswer(0x11, 0x01);
                    shotanswer._status = new_block[2];
                    emit receiveShotAnswer(shotanswer);
        }
        break;

        default:{
                    qDebug() << "Default output in case 11";
        }
            //in statusleiste wasausgeben
        break;
      }

    }
    break;

    case 0x80: //fill in groupNumber
                     {
                     IdentificationGroup id = IdentificationGroup(0x80, 0x01);
                     id._groupNumber = new_block[2];
                     emit receiveGroupId(id);
    }
    break;

    case 0x82: //get the text msg
    {
                    QString text;
                    for(size_t i=6; i<new_block.size(); i++)
                    {
                        text = text + (QChar)new_block[i];
                    }
                    emit receiveChat(text);
    }
    break;

    default:
    {              //print in status window unknown message
                   qDebug() << "Default message";
    }
    break;
    }
}


// gui-> click
void MyTcpServer::disconnectNow()
{
    qDebug() << "wir sind bei disconnect";
    emit disconnectGuiServer();
    _socket->close();

}

void MyTcpServer::sendParameter(Parameter &msg)
{
            QDataStream outStream(_socket);
            quint8 data1 = msg._cmd;
            quint8 data2 = msg._dlc;
            quint8 data3 = msg._field_x;
            quint8 data4 = msg._field_y;
            quint8 data5 = msg._n_battleship;
            quint8 data6 = msg._n_cruiser;
            quint8 data7 = msg._n_destroyer;
            quint8 data8 = msg._n_submarine;
            outStream << data1 << data2 << data3 << data4 << data5 << data6 << data7 << data8;
}



void MyTcpServer::sendGameStart(GameStart &msg)
{
    QDataStream outStream(_socket);
    quint8 data1 = msg._cmd;
    quint8 data2 = msg._dlc;
    outStream << data1 << data2;


}

void MyTcpServer::sendShot(Shot &msg)
{
    QDataStream outStream(_socket);
    quint8 data1 = msg._cmd;
    quint8 data2 = msg._dlc;
    quint8 data3 = msg._coordinates_x;
    quint8 data4 = msg._coordinates_y;
    outStream << data1 << data2 << data3 <<data4;

}

void MyTcpServer::sendAnswerGame(AnswerGame &msg)
{
    QDataStream outStream(_socket);
    quint8 data1 = msg._cmd;
    quint8 data2 = msg._dlc;
    quint8 data3 = msg._status;
    outStream << data1 << data2 << data3;
}

void MyTcpServer::sendShotAnswer(ShotAnswer &msg)
{
    QDataStream outStream(_socket);
    quint8 data1 = msg._cmd;
    quint8 data2 = msg._dlc;
    quint8 data3 = msg._status;
    if(data3 == 0x02 || data3 == 0x03)
    {
        outStream<< data1 << data2 << data3;
        for (auto &point: msg._position) {
            outStream << quint8(point.first) << quint8(point.second);
        }

    }
    else
    {
        outStream<< data1 << data2 << data3;

    }
}

void MyTcpServer::sendGroupId()
{
    QDataStream outStream(_socket);
    quint8 data1 = 0x80;
    quint8 data2 = 0x01;
    quint8 data3 = 0x06;
    outStream << data1 << data2 << data3;

}


void MyTcpServer::sendChat(QString _text)
{
    QDataStream outStream(_socket);
    quint8 data1 = 0x82;
    quint8 data2 = 0x01;
    QString data3 = _text;

    outStream << data1 << data2 << data3;
}
