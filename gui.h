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

    /**
    * @brief check for correct ship placement
    *
    * @param loc vector of placed fields
    * @param limit size of ship
    */
    void getError(position loc, int limit);

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

    //user name
    QString _yourName;



private slots:
    /**
    * @brief set up two fields
    */
    void setupFields();

    /**
    * @brief initial Mode Server
    */
    void setServer();
    /**
    * @brief initial Mode Server
    */
    void setClient();

    /**
    * @brief connect and disconnect of client
    */
    void connectclient();
    /**
    * @brief creating server
    */
    void connectserver();
    /**
    * @brief closing of server
    */
    void disconnectserver();

    /**
    * @brief start setting ships or start game
    */
    void startButton();

    /**
    * @brief placing ships on own field
    *
    * @param coordinate of ship part
    */
    void getCoordinates(std::pair<int, int> point);

    /**
    * @brief choosing are target field where to shoot
    *
    * @param loc coordinates of target field
    */
    void getShoot(std::pair<int, int> loc);

    /**
    * @brief message for chat
    */
    void chatButton();


signals:

    // gui -> logic
    /**
    * @brief sending full ship to logic
    *
    * @param position location of ship
    */
    void giveShip(position);
    /**
    * @brief sending target of own shot to logic
    *
    * @param coordinates coordinate of shot
    */
    void giveShoot(coordinates);
    /**
    * @brief sending ready to start game to logic
    */
    void giveStart();

    // gui -> control
    /**
    * @brief sending Server Mode
    */
    void serverMode();
    /**
    * @brief sending Client Mode
    */
    void clientMode();

    //gui -> network
    /**
    * @brief sending open the Server
    *
    * @param port where server is opened
    */
    void openServer(int);

    /**
    * @brief sending closing server to network
    */
    void disconnectServer();
    /**
    * @brief sending disconnection from server to network
    */
    void disconnectClient();
    /**
    * @brief sending connection to server to network
    *
    * @param QString IP adress of server
    * @param int port
    */
    void connectClient(QString, int);

    /**
    * @brief sending chat message to network
    *
    * @param QString message
    */
    void giveChat(QString);


public slots:
    //connection network -> gui
    /**
    * @brief getting client succesfully connected to server
    */
    void foundServer();

    /**
    * @brief getting client succesfully connected to server
    */
    void foundClient();

    //connection logic -> gui
    /**
    * @brief getting enemy shot on own field
    *
    * @param point coordinate where own or enemy shot hit
    * @param flag determination of hit, miss or destroying of ship
    * @param own enemy or own field
    */
    void getUpdateField(std::pair<int, int> point, int flag, bool own);

    /**
    * @brief getting status of which ones turn it is
    *
    * @param turn own or enemy turn
    */
    void getYourTurn(bool turn);

    /**
    * @brief getting ending of game
    *
    * @param win own or enemy win
    */
    void getWin(bool win);

    /**
    * @brief getting update of target list on gui for destryed enemy ships
    *
    * @param target which enemy ship was destroyed
    */
    void getShipDestroyed(int target);

    /**
    * @brief getting chat message from enemy
    *
    * @param message message send
    */
    void getChat(QString message);

};

#endif // GUI_H
