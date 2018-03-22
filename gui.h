/*******************************************************************************************************************//**
 *	@file		gui.h
 *  @brief		This file holds the data regarding gui and interface.
 *  @version 	V1.0
 *  @date		22.03.2018
 *	@author		Niklas Schwarz (Student @ TUM)
 **********************************************************************************************************************/
#ifndef GUI_H
#define GUI_H

/********************************************//**
 * Includes
 ***********************************************/
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

/**
 * @brief The Gui
 */
class Gui : public QMainWindow
{
    Q_OBJECT

public:
    explicit Gui(QMainWindow *parent = 0);
    ~Gui();

    /**
    * @brief Check if ship is correctly placed on own map
    *
    * Sorts incoming vector of selected coordinates of ship parts
    * and checks if all coordinates are all connected, in a straight line
    * and not colliding with another ship
    *
    * @param loc Vector of chosen coordinates for the ship (vector of x-y-coordiante pairs)
    * @param limit Size of ship
    */
    void getError(position loc, int limit);

private:
    Ui::Gui *ui;

    /**
     * @brief Etering game as Server
     */
    bool _server;
    /**
     * @brief Entering game as Client
     */
    bool _client;

    /**
     * @brief Being connected to Server or Client
     */
    bool _connected;

    /**
     * @brief Enable enemy field during own turn
     */
    bool _yourturn;

    /**
     * @brief Enable own field to set ships
     */
    bool _setShipMode;
    /**
     * @brief Game is currently running
     */
    bool _gamerunning;
    /**
     * @brief All ships set and ready to start game
     */
    bool _readyToStart;

    /**
     * @brief Ship was placed correctly
     */
    bool errorcheck;

    /**
     * @brief Counts already placed ships
     */
    int _shipCounter;
    /**
     * @brief Counts already placed parts of one ship
     */
    int _shipnumber;

    /**
     * @brief Counts how many enemy cruiser are destroyed
     */
    int _4count;
    /**
     * @brief Counts how many enemy destroyers are destroyed
     */
    int _3count;
    /**
     * @brief Counts how many enemy submarines are destroyed
     */
    int _2count;

    /**
     * @brief Button field for player ships (10*10 matrix with x-y-coordinate pairs)
     */
    std::vector< std::vector<Button*> > _map;
    /**
     * @brief Button field for enemy player ships (10*10 matrix with x-y-coordinate pairs)
     */
    std::vector< std::vector<Button*> > _enemmap;

    /**
     * @brief Vector of x and y coordinates with location of last placed ship
     */
    std::vector<std::pair<int, int>> _location;

    /**
     * @brief x and y Coordinate of last clicked field
     */
    std::pair<int, int> _waitCoordinates;

    /**
     * @brief good movie
     */
    QString _yourName;
    /**
     * @brief Name of enemy
     */
    int _enemygroup;


private slots:
    /**
    * @brief set up two 10*10 button fields for player and enemy
    *
    * Generates 100 buttons in two grid-layouts which are initialized
    * with a coordinate each
    */
    void setupFields();

    /**
    * @brief Setting up gui for actiong as Server
    */
    void setServer();
    /**
    * @brief Setting up gui for acting as Client
    */
    void setClient();

    /**
    * @brief Searching as Client for a Server or disconnect from it
    */
    void connectclient();
    /**
    * @brief Creating a Server
    */
    void connectserver();
    /**
    * @brief Closing the Server
    */
    void disconnectserver();

    /**
    * @brief Start setting ships or start the game after all ships being placed
    */
    void startButton();

    /**
    * @brief Placing ships on own field
    *
    * Runs through switch cases to document the number of complete ships placed
    * and runs through even more swithc cases to collect
    * the number of currently selected coordinates for ship-parts
    * #switchception
    * Also checks for correct placement of each ship and sends the location of
    * all complete ships to the Logic
    *
    * @param point Coordinate of ship part
    */
    void getCoordinates(std::pair<int, int> point);

    /**
    * @brief Choosing are target field where to shoot on players turn
    *
    * @param loc Coordinates of target field
    */
    void getShoot(std::pair<int, int> loc);

    /**
    * @brief Message for chat
    */
    void chatButton();


signals:

    // gui -> logic
    /**
    * @brief Sending a complete ship to logic
    *
    * @param position Location of ship (vector of coordinates)
    */
    void giveShip(position);
    /**
    * @brief Sending target of own shot to logic
    *
    * @param coordinates Coordinate (x and y) of shot
    */
    void giveShoot(coordinates);
    /**
    * @brief Sending all ships placed and ready to start game to logic
    */
    void giveStart();

    // gui -> control
    /**
    * @brief Sending that player acts as Server
    */
    void serverMode();
    /**
    * @brief Sending that player acts as Client
    */
    void clientMode();

    //gui -> network
    /**
    * @brief Sending open the Server on selected port to Network
    *
    * @param int Port where server is opened
    */
    void openServer(int);

    /**
    * @brief Sending closing the Server to Network
    */
    void disconnectServer();
    /**
    * @brief Sending disconnection from Server to Network
    */
    void disconnectClient();
    /**
    * @brief Sending connection to Server to Network
    *
    * @param QString IP adress of server
    * @param int Port
    */
    void connectClient(QString, int);

    /**
    * @brief Sending chat message to Network
    *
    * @param QString Message
    */
    void giveChat(QString);


public slots:
    //connection network -> gui
    /**
    * @brief Getting Client succesfully connected to Server
    */
    void foundServer();

    /**
    * @brief Getting Server succesfully connected to Client
    */
    void foundClient();

    //connection logic -> gui
    /**
    * @brief Getting enemy or own shot on field
    *
    * Updates both field (with colors red, blue or black) to see where hits land and wheter they
    * hit, miss or destroy an enemy ship
    *
    * @param point Coordinate where own or enemy shot hit
    * @param flag Determination of hit, miss or destroying of ship
    * @param own Enemy or own field to update
    */
    void getUpdateField(std::pair<int, int> point, int flag, bool own);

    /**
    * @brief Getting status of which ones turn it is
    *
    * @param turn Own or enemy turn
    */
    void getYourTurn(bool turn);

    /**
    * @brief Getting ending of game
    *
    * @param win Own or enemy win
    */
    void getWin(bool win);

    /**
    * @brief Getting update of target list on gui for destryed enemy ships
    *
    * Changes color of enemy ship on target list from green to red if a ship is destroyed
    *
    * @param target Which enemy ship was destroyed
    */
    void getShipDestroyed(int target);

    /**
    * @brief Getting chat message from enemy
    *
    * @param message Message send
    */
    void getChat(QString message);

    /**
    * @brief Getting name of enemy group
    *
    * @param name Integer for group
    */
    void getName(int name);
};

#endif // GUI_H
