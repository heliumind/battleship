#include "mytcpserver.h"
#include "messages.h"
#include <iostream>
#include <algorithm>
#include <vector>

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

MyTcpServer::MyTcpServer(MyTcpServer &&)
{

}

//start connection with
void MyTcpServer::newConnection()
{
    //w8ing for the next connection
    _socket1 = server->nextPendingConnection();

    //send data to client
//    connect(_socket1, &QTcpSocket::readyRead,
//            this, &MyTcpServer::sendShotToClient);

    //send shot data to client
   connect(_socket1, &QTcpSocket::readyRead,
            this, &MyTcpServer::receiveData);

    // tell client he is connected
    qDebug()<<"Client agrees\n";

    //server connection close
    //socket->close();
}


//receive shot data from client
void MyTcpServer::receiveData()
{
    Shot shot;
//    QDataStream inStream(_socket1);
//    quint8 block;
//    //creat vector to catch all incoming bytes
//    std::vector<uint8_t> new_block;
//    //save all incoming data into the vector
//    while(_socket1->bytesAvailable()) {

//        inStream>> block;
//        new_block.push_back(block);
//        //qDebug()<<block;
//    }

    //read first byte for identification
    uint8_t cmd= 0x03;//new_block[0];
    // qDebug()<< new_block[0];
    switch(cmd)
    {
    case 0x01: qDebug()<< "Parameter werden vom Server gestellt!!";
    break;

    case 0x02: qDebug() << "Gamestart question";
    break;

    case 0x03: qDebug() << "Shot Message";
                           qDebug() << shot._coordinates_x;
                           shot._coordinates_x = 1; //new_block[2];
                           shot._coordinates_y = 1; //new_block[3];
                           qDebug() << shot._coordinates_x;
                           emit messageSent(shot);


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

//void MyTcpServer::disconnectNow()
//{
//    _socket1->close();
//}


//void MyTcpServer::sendShotToClient()
//{
//    Shot shot;

//    QDataStream outStream(_socket1);
//    quint8 data1 = shot.cmd;
//    quint8 data2 = shot.dlc;
//    quint8 data3 = shot.coordinates_x;
//    quint8 data4 = shot.coordinates_y;
//    outStream << data1 << data2 << data3 << data4;

//}

//void MyTcpServer::sendParameterData()
//{
//     Parameter parameter;

//     QDataStream outStream(_socket1);
//     quint8 data1 = parameter.cmd;
//     quint8 data2 = parameter.dlc;
//     quint8 data3 =

//}





//void MyTcpServer::sendParameterData()
//{
//Parameter parameter;
//QDataStream outStream(_socket1);
//quint8 data1 = parameter.cmd;
//quint8 data2 = parameter.dlc;
//quint8 data3 = parameter.field_x;
//quint8 data4 = parameter.field_y;
//quint8 data5 = parameter.n_battleship;
//quint8 data6 = parameter.n_cruiser;
//quint8 data7 = parameter.n_destroyer;
//quint8 data8 = parameter.n_submarine;
//outStream << data1 << data2 << data3
//             << data4 << data5 << data6
//             << data7 << data8;
//}
