/*******************************************************************************************************************//**
 *	@file		mytcpserver.hpp
 *  @brief		This file holds the needed class for the Server and the communication between network and gui, network and logic,
 *              and network and opponent client.
 *  @version 	V1.0
 *  @date		22.03.2018
 *	@author		Arber Salihu (Student @ TUM)
 **********************************************************************************************************************/

#ifndef MYTCPSERVER_H
#define MYTCPSERVER_H

/********************************************//**
 * Includes
 ***********************************************/

#include <QTcpServer>
#include <QTcpSocket>
#include <QDebug>
#include <QString>
#include <QTextStream>
#include <QDataStream>
#include <QByteArray>
#include <QIODevice>
#include "messages.h"

/**
 * @brief The MyTcpServer class MyTcpServer inherits fromt he QObject class
 */
class MyTcpServer : public QObject
{
    Q_OBJECT
public:

    friend class Control;

    explicit MyTcpServer(QObject *parent = 0);

    MyTcpServer(MyTcpServer&&);

signals:

    /**
     * @brief gotClient emits signal when client connects to server
     */
    void gotClient();

    /**
     * @brief disconnectGuiServer   emits signal when server closes the connection
     */
    void disconnectGuiServer();

    /**
     * @brief receiveGameStart emits signal when the game start question is received
     */
    void    receiveGameStart();

    /**
     * @brief receiveShot   emits signal when a shot is received
     * @param msg
     */
    void    receiveShot(Shot &msg);

    /**
     * @brief receiveAnswerGame emits signal when the answer game respond is received
     * @param msg
     */
    void    receiveAnswerGame(AnswerGame &msg);

    /**
     * @brief receiveShotAnswer emits signal when the shot answer is received
     * @param msg
     */
    void    receiveShotAnswer(ShotAnswer &msg);

    /**
     * @brief receiveGroupId    emits signal when the group id is received
     * @param msg
     */
    void    receiveGroupId(IdentificationGroup &msg);

    /**
     * @brief receiveChat   emits signal when chat message is received
     * @param text
     */
    void    receiveChat(QString text);

    /**
     * @brief sendparams emits signal when parameter data is received
     */
    void    sendparams();

public slots:
    /**
     * @brief newConnection method that listen for a client
     */
    void newConnection();

    /**
     * @brief receiveData   method that receives all data
     */
    void receiveData();

    /**
     * @brief disconnectNow method that disconnects from client
     */
    void disconnectNow();

    /**
     * @brief initServer    method that initializes the server
     * @param port
     */
    void initServer(int port);

    /**
     * @brief sendParameter method that sends the parameter data
     * @param msg
     */
    void    sendParameter(Parameter &msg);

    /**
     * @brief sendGameStart method that sends the game start question
     * @param msg
     */
    void    sendGameStart(GameStart &msg);

    /**
     * @brief sendShot  method that sends the shot
     * @param msg
     */
    void    sendShot(Shot &msg);

    /**
     * @brief sendAnswerGame    method that sends the gamestart respond
     * @param msg
     */
    void    sendAnswerGame(AnswerGame &msg);

    /**
     * @brief sendShotAnswer    method that sends the shot answer to the opponent
     * @param msg
     */
    void    sendShotAnswer(ShotAnswer &msg);

    /**
     * @brief sendGroupId   method that sends the group id
     */
    void    sendGroupId();

    /**
     * @brief sendChat  method that sends the chat message
     * @param _text
     */
    void    sendChat(QString _text);

private:
    /**
     * @brief server creating a QTcpServer object
     */
    QTcpServer *server;

    /**
     * @brief _socket   creating a QTcpSocket object
     */
    QTcpSocket *_socket;

    /**
     * @brief _stream   creating a QDataStream object
     */
    QDataStream _stream;
};

#endif // MYTCPSERVER_H
