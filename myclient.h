/*******************************************************************************************************************//**
 *	@file		myclient.hpp
 *  @brief		This file holds the nedded class for the Client and the communication between network and gui, network and logical,
 *              network and opponent server.
 *  @version 	V1.0
 *  @date		22.03.2018
 *	@author		Arber Salihu (Student @ TUM)
 **********************************************************************************************************************/

#ifndef MYCLIENT_H
#define MYCLIENT_H

/********************************************//**
 * Includes
 ***********************************************/

#include <QTcpServer>
#include <QTcpSocket>
#include <QString>
#include <QDebug>
#include <QTextStream>
#include <QDataStream>
#include <QByteArray>
#include <QIODevice>
#include <QObject>
#include "messages.h"

/**
 * @brief The MyClient class MyClient inherits from the QObjet class
 */
class MyClient : public QObject
{
    Q_OBJECT

public:

    explicit MyClient(QObject *parent = 0);
    /**
     * @brief MyClient  move constructor
     */
    MyClient(MyClient&&);


signals:    
    /**
     * @brief receiveParameter  emits signal when parameter data are received
     * @param msg
     */
    void receiveParameter(Parameter &msg);

    /**
     * @brief receiveGameStart  emits signal when the game start question is received
     */
    void receiveGameStart();

    /**
     * @brief receiveShot   emits signal when a shot is received.
     * @param msg
     */
    void receiveShot(Shot &msg);

    /**
     * @brief receiveAnswerGame emits signal when the answer game respond is received
     * @param msg
     */
    void receiveAnswerGame(AnswerGame &msg);

    /**
     * @brief receiveShotAnswer emits signal when the shot answer is received
     * @param msg
     */
    void receiveShotAnswer(ShotAnswer &msg);

    /**
     * @brief receiveIdentificationGroup    emits signal when the group id is received
     * @param msg
     */
    void receiveIdentificationGroup(IdentificationGroup &msg);

    /**
     * @brief gotServer emits signal when the client connects to the server.
     */
    void gotServer();

    /**
     * @brief disconnectGui emits signal when the client is disconnected from the server
     */
    void disconnectGui();

    /**
     * @brief receiveChat   emits signal when a chat message is received
     * @param text
     */
    void receiveChat(QString text);


public slots:
    /**
     * @brief ConnectHost Slot  method that connects the clients to the sever.
     * @param ip
     * @param port
     */
    void ConnectHost(QString ip, int port);

    /**
     * @brief receiveServerData method that receives all incoming messages from the server.
     */
    void receiveServerData();

    /**
     * @brief disconnectNow method that disconnects from the server.
     */
    void disconnectNow();

    /**
     * @brief sendGameStart method that sends the game start question to the server.
     * @param msg
     */
    void sendGameStart(GameStart &msg);

    /**
     * @brief sendShot  method that sends the shot to the server.
     * @param msg
     */
    void sendShot(Shot &msg);

    /**
     * @brief sendAnswerGame    method that sends the answer game respond to the server.
     * @param msg
     */
    void sendAnswerGame(AnswerGame &msg);

    /**
     * @brief sendShotAnswer    method that sends the shot answer to the server.
     * @param msg
     */
    void sendShotAnswer(ShotAnswer &msg);

    /**
     * @brief sendIdentificationGroup method that sends the group id to the server.
     * @param msg
     */
    void sendIdentificationGroup(IdentificationGroup &msg);

    /**
     * @brief sendChat  method that sends the chat message to the server.
     * @param _text
     */
    void sendChat(QString _text);

public:
    /**
     * @brief _socket   creating a QTcpSocket object
     */
    QTcpSocket *_socket;

    /**
     * @brief _dataStream   creating a QDataStream object
     */
    QDataStream _dataStream;
};

#endif // MYCLIENT_H
