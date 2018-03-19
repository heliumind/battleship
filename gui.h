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
    int _shipCounter;
    bool _gamerunning;

    std::vector< std::vector<Button*> > _map;
    std::vector< std::vector<Button*> > _enemmap;

    QTcpSocket  _mySocket;
    QTextStream _myStream;

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
    void connectserver();
    void disconnectserver();

    //connect client
    void connectclient();

    //set ships
    void setShips();


signals:
    void sendLocation(std::pair<int, int>);

    //errorcheck logic gui
    //void giveShipError(std::vector<std::pair<int, int>>);


public slots:
    void output(std::pair<int, int>);
    void getCoordinates(std::pair<int, int>);

    //playtime
    void shoot();
    void fieldupdate(int, std::pair<int, int>);
    void enemyfieldupdate(int, std::pair<int, int>);

    //ending
    void win();
    void loose();

    //connection logic gui
    void getUpdateField(std::pair<int, int> point, int flag, bool own);



};

#endif // GUI_H
