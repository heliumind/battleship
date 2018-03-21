#ifndef MYTCPSERVER_H
#define MYTCPSERVER_H

#include <QTcpServer>
#include <QTcpSocket>
#include <QDebug>
#include <QString>
#include <QTextStream>
#include <QDataStream>
#include <QByteArray>
#include <QIODevice>
#include "messages.h"


class MyTcpServer : public QObject
{
    Q_OBJECT
public:
    friend class Control;
    explicit MyTcpServer(QObject *parent = 0);
    MyTcpServer(MyTcpServer&&);

signals:
    // network -> client
    void gotClient();
    void disconnectGuiServer();


    // network -> logic
    void    receiveGameStart();
    void    receiveShot(Shot &msg);
    void    receiveAnswerGame(AnswerGame &msg);
    void    receiveShotAnswer(ShotAnswer &msg);
    void    receiveGroupId(IdentificationGroup &msg);

public slots:
    void newConnection();
    void receiveData();
    void disconnectNow();
    void initServer();
    //void sendMessage(Message *msg);

    // logic -> network
    void    sendParameter(Parameter &msg);
    void    sendGameStart(GameStart &msg);
    void    sendShot(Shot &msg);
    void    sendAnswerGame(AnswerGame &msg);
    void    sendShotAnswer(ShotAnswer &msg);
    void    sendGroupId(IdentificationGroup &msg);

private:
    QTcpServer *server;
    QTcpSocket *_socket;
    QDataStream _stream;
};

#endif // MYTCPSERVER_H
