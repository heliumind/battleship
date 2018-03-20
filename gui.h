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

    //enable field buttons
    bool _setShipMode;
    bool _gamerunning;
    bool _readyToStart;
    bool errorcheck;

    int _shipCounter;

    int _4count;
    int _3count;
    int _2count;

    std::vector< std::vector<Button*> > _map;
    std::vector< std::vector<Button*> > _enemmap;


    std::vector<std::pair<int, int>> _location;
    int _shipnumber;

    std::pair<int, int> _waitCoordinates;



private slots:
    //set up two fields
    void setupFields();

    //initial mode
    void setServer();
    void setClient();

    //connect server
    void disconnectserver();

    //connect client
    void connectclient();

    //set ships
    void startButton();


signals:
    void sendLocation(std::pair<int, int>);

    // logic gui
    void giveShip(position);
    void giveShoot(coordinates);
    void giveStart();

    // gui -> control
    void serverMode();
    void clientMode();

    //gui ->network
    void disconnectServer();
    void disconnectClient();
    void connectClient(QString, int);


public slots:
    //void output(std::pair<int, int>);
    void getCoordinates(std::pair<int, int>);


    //connection logic gui
    void getUpdateField(std::pair<int, int> point, int flag, bool own);
    void getShoot(std::pair<int, int>);
    void getYourTurn(bool);
    void getWin(bool);
    void getShipDestroyed(int);

    //connection network gui
    void foundClient();
    void foundServer();

};

#endif // GUI_H
