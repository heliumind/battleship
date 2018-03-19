#include "mytcpserver.h"
#include "messages.h"
#include <iostream>
#include <algorithm>
#include <vector>

MyTcpServer::MyTcpServer(QObject *parent) : QObject(parent)
{
       server = new QTcpServer(this);
       _stream.setDevice(_socket);

       // whenever a user connects, it will emit signal
       connect(server, &QTcpServer::newConnection,
               this, &MyTcpServer::newConnection);

            //listen for a client to connect
       if(!server->listen(QHostAddress::Any, /*gui input*/ 1234))
       {
           qDebug() << "Server could not start";
       }
       else
       {
           qDebug() << "Server started!";
       }
}

//start connection with
void MyTcpServer::newConnection()
{
    //w8ing for the next connection
    _socket = server->nextPendingConnection();

    //send shot data to client -> data ready permanent activated
   connect(_socket, &QTcpSocket::readyRead,
            this, &MyTcpServer::receiveData);

    // tell client he is connected
    qDebug()<<"Client agrees\n";

}


//receive shot data from client
void MyTcpServer::receiveData()
{
    // QDataStream inStream(_socket);
    // quint8 block;
    //creat vector to catch all incoming bytes
    //std::vector<uint8_t> new_block;
    //save all incoming data into the vector
//    while(_socket->bytesAvailable()) {

//        inStream>> block;
//        new_block.push_back(block);
//        //qDebug()<<block;
//    }

    //read first byte for identification
    //uint8_t cmd=new_block[0];
    //qDebug()<< new_block[0];
    uint8_t cmd = 0x03;
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
                     qDebug() << shot._coordinates_x;
                     //shot._cmd = block[0];
                     shot._coordinates_x = 1; // new_block[2];
                     shot._coordinates_y = 1; //new_block[3];
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
                     // answergame._status = new_block[2];
                     Message *msgptr =  &answergame;
                     emit messageSent(msgptr);
        }

    break;

   case 0x11:       //fill in shot answer
    {
                     ShotAnswer shotanswer = ShotAnswer(0x11, /*variable*/0x01);
                     // shotanswer._status = new_block[2];
                     Message *msgptr = &shotanswer;
                     emit messageSent(msgptr);
    }
    break;
    case 0x80: //fill in groupNumber
                     {
                     IdentificationGroup id = IdentificationGroup(0x80, 0x01);
                     // id._groupNumber = new_block[2];
                     Message *msgptr = &id;
                     emit messageSent(msgptr);
    }
    break;
    default:
    {
                   qDebug() << "Unknown Message";
    }
    }

}
// gui-> click
void MyTcpServer::disconnectNow()
{
    _socket->close();
}


void MyTcpServer::sendShot()
{
    Shot shot = Shot(0x03, 0x02);
    QDataStream outStream(_socket);
    quint8 data1 = shot._cmd;
    quint8 data2 = shot._dlc;
    quint8 data3 = shot._coordinates_x;
    quint8 data4 = shot._coordinates_y;
    outStream << data1 << data2 << data3 << data4;

}


void MyTcpServer::sendParameterData()
{
     Parameter parameter = Parameter(0x01, 0x06);
     QDataStream outStream(_socket);
     quint8 data1 = parameter._cmd;
     quint8 data2 = parameter._dlc;
     quint8 data3 = parameter._field_x;
     quint8 data4 = parameter._field_y;
     quint8 data5 = parameter._n_battleship;
     quint8 data6 = parameter._n_cruiser;
     quint8 data7 = parameter._n_destroyer;
     quint8 data8 = parameter._n_submarine;
     outStream << data1 << data2 << data3 << data4 << data5 << data6 << data7 << data8;

}

void MyTcpServer::sendShotAnswer()
{
    ShotAnswer shotanswer = ShotAnswer(0x11, 0x01);
    QDataStream outStream(_socket);
    quint8 data1 = shotanswer._cmd;
    //quint8 data2 = shotanswer._dlc_shotanswer;
    quint8 data3 = shotanswer._status;

    outStream << data1 /*<< data2*/ << data3;
}

void MyTcpServer::sendAnswer()
{
    AnswerGame answergame = AnswerGame(0x10, 0x01);

    QDataStream outStream(_socket);
    quint8 data1 = answergame._cmd;
    quint8 data2 = answergame._dlc;
    quint8 data3 = answergame._status;
    outStream << data1 << data2 << data3;
}

void MyTcpServer::groupID()
{
    IdentificationGroup idgroup = IdentificationGroup(0x80, 0x01);
    QDataStream outStream(_socket);
    quint8 data1 = idgroup._cmd;
    quint8 data2 = idgroup._dlc;
    quint8 data3 = idgroup._groupNumber;
    outStream << data1 << data2 << data3;
}

void MyTcpServer::sendGameStart()
{
    GameStart gamestart = GameStart(0x02, 0x00);
    QDataStream outStream(_socket);
    quint8 data1 = gamestart._cmd;
    quint8 data2 = gamestart._dlc;
    outStream << data1 << data2;

}
