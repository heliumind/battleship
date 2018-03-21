
#include "myclient.h"
#include "messages.h"
#include <iostream>
#include <algorithm>
#include <vector>

#include <QDebug>

MyClient::MyClient(QObject *parent) : QObject(parent)
{
//    _socket = new QTcpSocket(this);
//    _dataStream.setDevice(_socket);

//    //init. sending shot coordinates to server -> senden nur bei funktionsaudfruf durch die logik
//    connect(_socket, &QTcpSocket::readyRead,
//            this, &MyClient::sendShotToServer);

    //init. reading from server
//    connect(_socket, &QTcpSocket::readyRead,
//            this, &MyClient::receiveServerData);


}

void MyClient::ConnectHost(QString ip, int port)
{
    _socket = new QTcpSocket(this);
    _dataStream.setDevice(_socket);

    //QByteArray data;
    _socket->connectToHost(ip, port);
    emit gotServer();

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
    std::vector<quint8> new_block;
    while(_socket->bytesAvailable()) {
        inStream >> block;
        new_block.push_back(block);
        qDebug() <<"------ oben";
        qDebug()<< "Debug ausgabe in while: "<< block;
        qDebug() << "------unten";
    }

    //read first byte for identification
    uint8_t cmd=new_block[0];
    qDebug()<< "nach block[0]" << new_block[0];
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
                      emit receiveParameter(parameter);
    }

    break;

    case 0x02:
    {                GameStart gamestart = GameStart(0x02, 0x00);
        qDebug() << "Gamstart received cmd: " << gamestart._cmd;
        qDebug() << "Gemstart received dlc: " << gamestart._dlc;
                     emit receiveGameStart();

    }

    break;

    case 0x03:       //fill in coordinates that where shot at
    {                Shot shot = Shot(0x03, 0x02);
                     qDebug() << shot._coordinates_x;
                     //shot._cmd = block[0];
                     shot._coordinates_x = new_block[2];
                     shot._coordinates_y = new_block[3];
                     qDebug() << shot._coordinates_x;
                     //emitiert das shot angekommen ist
                     emit receiveShot(shot);
    }
    break;

    case 0x10:
        {            //fill in anser on gamestart;
                     AnswerGame answergame = AnswerGame(0x10, 0x01);
                     qDebug() << answergame._status;
                     answergame._status = new_block[2];
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
                      emit receiveShotAnswer(shotanswer);
         }
         break;

         case 0x01: {//case hit
                     ShotAnswer shotanswer = ShotAnswer(0x11,0x01);
                     shotanswer._status = new_block[2];
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
//                     for (auto iter = new_block.begin() + 3; iter != new_block.end(); iter+=2) {
//                         _location.push_back(std::make_pair(*iter, *iter++));
//                     }

//                     for(int i = 0; i >= shotanswer._dlc-3; i++)
//                     {
//                         //creat vector of coordinate pairs of sunken ship;
//                         shotanswer._position.push_back(std::make_pair(new_block[3+2*i],new_block[4+2*i]));
//                     }
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
//                      std::vector<uint8_t>::iterator iter;
//                      for (iter += 3; iter != new_block.end(); iter+=2) {
//                          _location.push_back(std::make_pair(*iter, *iter++));
//                      }
//                      shotanswer._position = _location;
//                      for(int i = 0; i >= shotanswer._dlc-3; i++)
//                      {
//                          //creat vector of coordinate pairs of sunken ship;
//                          shotanswer._position.push_back(std::make_pair(new_block[3+2*i],new_block[4+2*i]));
//                      }
                      emit receiveShotAnswer(shotanswer);
         }
         break;

         case 0x10: {
                     ShotAnswer shotanswer = ShotAnswer(0x11, 0x01);
                     shotanswer._status = new_block[2];
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
                     qDebug() << "Default Output in case 11";
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
                     emit receiveIdentificationGroup(id);
    }
    break;

    default: qDebug() << "Default out put ";
    break;
    }

}

void MyClient::disconnectNow()
{
    emit disconnectGui();
    _socket->close();
}

void MyClient::sendGameStart(GameStart &msg)
{
    QDataStream outStream(_socket);
    quint8 data1 = msg._cmd;
    quint8 data2 = msg._dlc;
    outStream << data1 << data2;
}

void MyClient::sendShot(Shot &msg)
{
    QDataStream outStream(_socket);
    quint8 data1 = msg._cmd;
    quint8 data2 = msg._dlc;
    quint8 data3 = msg._coordinates_x;
    quint8 data4 = msg._coordinates_y;
    outStream << data1 << data2 << data3 <<data4;
}

void MyClient::sendAnswerGame(AnswerGame &msg)
{
    QDataStream outStream(_socket);
    quint8 data1 = msg._cmd;
    quint8 data2 = msg._dlc;
    quint8 data3 = msg._status;
    outStream << data1 << data2 << data3;
}

void MyClient::sendShotAnswer(ShotAnswer &msg)
{
    QDataStream outStream(_socket);
    quint8 data1 = msg._cmd;
    quint8 data2 = msg._dlc;
    quint8 data3 = msg._status;

    if(data3 == 0x02 || data3 == 0x03)
    {
        outStream<< data1 << data2 << data3;
        qDebug() << "no points: " << msg._position.size();
        for (auto &point: msg._position) {
            outStream << quint8(point.first) << quint8(point.second);
            qDebug() << "point.first= " <<point.first << "; point.second= " << point.second;
        }
//    if(data3 == 0x02 || data3 == 0x03)
//    {
//            quint8 data4 = msg._position[0].first;
//            quint8 data5 = msg._position[0].second;
//            quint8 data6 = msg._position[1].first;
//            quint8 data7 = msg._position[1].second;
//            quint8 data8 = msg._position[2].first;
//            quint8 data9 = msg._position[2].second;
//            quint8 data10 = msg._position[3].first;
//            quint8 data11 = msg._position[3].second;
//            quint8 data12 = msg._position[4].first;
//            quint8 data13 = msg._position[4].second;
//            outStream << data1 << data2 << data3 << data4 <<
//                         data5 << data6 << data7 << data8 <<
//                         data9 << data10 << data11 << data12 <<
//                         data13;
    }
    else
    {
        outStream<< data1 << data2 << data3;
    }
}

void MyClient::sendIdentificationGroup(IdentificationGroup &msg)
{
    QDataStream outStream(_socket);
    quint8 data1 = msg._cmd;
    quint8 data2 = msg._dlc;
    quint8 data3 = msg._groupNumber;

    outStream << data1 << data2 << data3;
}
