#ifndef MYCLIENT_H
#define MYCLIENT_H


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

class MyClient : public QObject
{
    Q_OBJECT
public:
    explicit MyClient(QObject *parent = 0);
    MyClient(MyClient&&);


signals:
    // network -> logic (received Message)
    void receiveParameter(Parameter &msg);
    void receiveGameStart();
    void receiveShot(Shot &msg);
    void receiveAnswerGame(AnswerGame &msg);
    void receiveShotAnswer(ShotAnswer &msg);
    void receiveIdentificationGroup(IdentificationGroup &msg);

    // network -> gui
    void gotServer();
    void disconnectGui();


public slots:
    void ConnectHost(QString ip, int port);
    void receiveServerData();
    void disconnectNow();

    // logic -> network (Messages to send)
    void sendGameStart(GameStart &msg);
    void sendShot(Shot &msg);
    void sendAnswerGame(AnswerGame &msg);
    void sendShotAnswer(ShotAnswer &msg);
    void sendIdentificationGroup(IdentificationGroup &msg);

public:
    QTcpSocket *_socket;
    QDataStream _dataStream;
};

#endif // MYCLIENT_H
