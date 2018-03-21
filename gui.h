#ifndef GUI_H
#define GUI_H

#include <QWidget>
#include <QMainWindow>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QLabel>
#include <QString>
#include <QTcpSocket>
#include <QTextStream>
#include <iostream>
#include <QtGui>
#include <vector>
#include <QDebug>
#include "datatypes.hpp"

#include "button.h"

namespace Ui {
class Gui;
}

class Gui : public QMainWindow
{
    Q_OBJECT

public:
    explicit Gui(QMainWindow *parent = 0);
    ~Gui();

    void getError(position, int);

private:
    Ui::Gui *ui;

    //server or client mode
    bool _server;
    bool _client;

    //connected or disconnected
    bool _connected;

    //enable enemy field buttons
    bool _yourturn;

    //enable fieldand start buttons
    bool _setShipMode;
    bool _gamerunning;
    bool _readyToStart;

    //check if ship is legit
    bool errorcheck;

    //counts ships placed
    int _shipCounter;
    int _shipnumber;

    //counts ships destroyed
    int _4count;
    int _3count;
    int _2count;

    //field buttons
    std::vector< std::vector<Button*> > _map;
    std::vector< std::vector<Button*> > _enemmap;

    //location of one ship
    std::vector<std::pair<int, int>> _location;

    //coordinate clicked
    std::pair<int, int> _waitCoordinates;

    //extra features
    QString _yourName;



private slots:
    //set up two fields
    void setupFields();

    //initial mode
    void setServer();
    void setClient();

    //connect and disconnect
    void disconnectserver();
    void connectclient();

    //set ships or start game
    void startButton();

    //give out coordinate on status field
    //void output(std::pair<int, int>);

    //placing ships on own field
    void getCoordinates(std::pair<int, int>);

    //extra features
    void chatButton();


signals:

    // gui -> logic
    void giveShip(position);
    void giveShoot(coordinates);
    void giveStart();
    void sendLocation(std::pair<int, int>);

    // gui -> control
    void serverMode();
    void clientMode();

    //gui -> network
    void disconnectServer();
    void disconnectClient();
    void connectClient(QString, int);

    //extra features
    void giveChat(QString);


public slots:

    //connection logic -> gui
    void getUpdateField(std::pair<int, int> point, int flag, bool own);
    void getShoot(std::pair<int, int>);
    void getYourTurn(bool);
    void getWin(bool);
    void getShipDestroyed(int);

    //connection network -> gui
    void foundClient();
    void foundServer();

    //extra features
    void getChat(QString);

};

#endif // GUI_H
