#include "mytcpserver.h"
#include "messages.h"
#include <iostream>
#include <algorithm>
#include <vector>
#include "datatypes.hpp"

MyTcpServer::MyTcpServer(QObject *parent) : QObject(parent)
{

}

void MyTcpServer::initServer()
{
    server = new QTcpServer(this);

    if(!server->listen(QHostAddress::Any, /*gui input*/ 1234))
    {
        qDebug() << "Server could not start";
        server->deleteLater();
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
    std::vector<uint8_t> new_block;
    //save all incoming data into the vector
    while(_socket->bytesAvailable()) {

        inStream>> block;
        new_block.push_back(block);
        //qDebug()<<block;
    }

    //read first byte for identification
    uint8_t cmd = new_block[0];
    qDebug()<< new_block[0];

    switch(cmd)
    {
    // case 0x01 only sent from server

    case 0x02:
    {               GameStart gamestart = GameStart(0x02, 0x00);
                    Message *msgptr = &gamestart;
                    emit messageSent(msgptr);
    }
    break;

    case 0x03:       //fill in coordinates that where shot at
    {                Shot shot = Shot(0x03, 0x02);
                     //shot._cmd = block[0];
                     shot._coordinates_x = 1; // new_block[2];
                     shot._coordinates_y = 1; //new_block[3];
                     Message *msgptr = &shot;
                     //emitiert das shot angekommen ist
                     emit messageSent(msgptr);
    }
    break;

    case 0x10:

        {            //fill in anser on gamestart;
                     AnswerGame answergame = AnswerGame(0x10, 0x01);
                     qDebug() << answergame._status;
                     // answergame._status = new_block[2];
                     Message *msgptr =  &answergame;
                     emit messageSent(msgptr);

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
                     Message *msgptr = &shotanswer;
                     emit messageSent(msgptr);
        }
        break;
        case 0x01: {//case hit
                    ShotAnswer shotanswer = ShotAnswer(0x11,0x01);
                    shotanswer._status = new_block[2];
                    Message *msgptr = &shotanswer;
                    emit messageSent(msgptr);
        }
        break;
        case 0x02:{//case hit and sunk
                    ShotAnswer shotanswer = ShotAnswer(0x11, new_block[1]);
                    shotanswer._status = new_block[2];
                    //std::vector<std::pair<uint8_t,uint8_t>> position;
                    for(int i = 0; i >= shotanswer._dlc-5; i++)
                    {
                        //creat vector of coordinate pairs of sunken ship;
                        shotanswer._position.push_back(std::make_pair(new_block[3+2*i],new_block[4+2*i]));
                    }
                    Message *msgptr = &shotanswer;
                    emit messageSent(msgptr);
        }
        break;
        case 0x03:{     //case sunken ship and game end
                     ShotAnswer shotanswer = ShotAnswer(0x11, new_block[1]);
                     shotanswer._status = new_block[2];
                     //std::vector<std::pair<uint8_t,uint8_t>> position;
                     for(int i = 0; i >= shotanswer._dlc-5; i++)
                     {
                         //creat vector of coordinate pairs of sunken ship;
                         shotanswer._position.push_back(std::make_pair(new_block[3+2*i],new_block[4+2*i]));
                     }
                     Message *msgptr = &shotanswer;
                     emit messageSent(msgptr);
        }
        break;
        case 0x10: {
                    ShotAnswer shotanswer = ShotAnswer(0x11, 0x01);
                    shotanswer._status = new_block[2];
                    Message *msgptr = &shotanswer;
                    emit messageSent(msgptr);
        }
        break;
        case 0x11:{
                    ShotAnswer shotanswer = ShotAnswer(0x11, 0x01);
                    shotanswer._status = new_block[2];
                    Message *msgptr = &shotanswer;
                    emit messageSent(msgptr);

        }
        break;
        case 0x20:{
                    ShotAnswer shotanswer = ShotAnswer(0x11, 0x01);
                    shotanswer._status = new_block[2];
                    Message *msgptr = &shotanswer;
                    emit messageSent(msgptr);
        }
        break;

        default:{}
            //in statusleiste wasausgeben
        break;
      }

    }
    break;
    case 0x80: //fill in groupNumber
                     {
                     IdentificationGroup id = IdentificationGroup(0x80, 0x01);
                     id._groupNumber = new_block[2];
                     Message *msgptr = &id;
                     emit messageSent(msgptr);
    }
    break;
    default:
    {              //print in status window unknown message
                   qDebug() << "Unknown Message";
    }
    }

}

// gui-> click
void MyTcpServer::disconnectNow()
{
    _socket->close();
}

void MyTcpServer::sendMessage(Message *msg)
{
    switch(msg->_cmd){
    case 0x01:{
        Parameter *parameter = dynamic_cast<Parameter*> (msg);
        QDataStream outStream(_socket);
        quint8 data1 = parameter->_cmd;
        quint8 data2 = parameter->_dlc;
        quint8 data3 = parameter->_field_x;
        quint8 data4 = parameter->_field_y;
        quint8 data5 = parameter->_n_battleship;
        quint8 data6 = parameter->_n_cruiser;
        quint8 data7 = parameter->_n_destroyer;
        quint8 data8 = parameter->_n_submarine;
        outStream << data1 << data2 << data3 << data4 << data5 << data6 << data7 << data8;
    }
    break;
    case 0x02:{
        GameStart *gamestart = dynamic_cast<GameStart*> (msg);
        QDataStream outStream(_socket);
        quint8 data1 = gamestart->_cmd;
        quint8 data2 = gamestart->_dlc;
        outStream << data1 << data2;
    }
    break;

    case 0x03:{
        Shot *shot = dynamic_cast<Shot*> (msg);
        QDataStream outStream(_socket);
        quint8 data1 = shot->_cmd;
        quint8 data2 = shot->_dlc;
        quint8 data3 = shot->_coordinates_x;
        quint8 data4 = shot->_coordinates_y;
        outStream << data1 << data2 << data3 <<data4;
    }
    break;
    case 0x10:{
        AnswerGame *answergame = dynamic_cast<AnswerGame*> (msg);
        QDataStream outStream(_socket);
        quint8 data1 = answergame->_cmd;
        quint8 data2 = answergame->_dlc;
        quint8 data3 = answergame->_status;
        outStream << data1 << data2 << data3;
    }
    break;

    case 0x11:{
        ShotAnswer *shotanswer = dynamic_cast<ShotAnswer*>(msg);
        QDataStream outStream(_socket);
        quint8 data1 = shotanswer->_cmd;
        quint8 data2 = shotanswer->_dlc;
        quint8 data3 = shotanswer->_status;
        if(data3 == 0x02 || data3 == 0x03)
        {
                quint8 data4 = shotanswer->_position[0].first;
                quint8 data5 = shotanswer->_position[0].second;
                quint8 data6 = shotanswer->_position[1].first;
                quint8 data7 = shotanswer->_position[1].second;
                quint8 data8 = shotanswer->_position[2].first;
                quint8 data9 = shotanswer->_position[2].second;
                quint8 data10 = shotanswer->_position[3].first;
                quint8 data11 = shotanswer->_position[3].second;
                quint8 data12 = shotanswer->_position[4].first;
                quint8 data13 = shotanswer->_position[4].second;
                outStream << data1 << data2 << data3 << data4 <<
                             data5 << data6 << data7 << data8 <<
                             data9 << data10 << data11 << data12 <<
                             data13;

        }
        else
        {
            outStream<< data1 << data2 << data3;
        }
    }
    break;
    case 0x80:{
        IdentificationGroup *idgroup = dynamic_cast<IdentificationGroup*>(msg);
        QDataStream outStream(_socket);
        quint8 data1 = idgroup->_cmd;
        quint8 data2 = idgroup->_dlc;
        quint8 data3 = idgroup->_groupNumber;
        outStream << data1 << data2 << data3;
    }
    break;
    }
}
