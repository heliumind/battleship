/*******************************************************************************************************************//**
 *	@file		datatypes.hpp
 *  @brief		This file holds the needed definitions of custom datatypes used
 *              in this project
 *  @version 	V1.0
 *  @date		22.03.2018
 *	@author		Henry He (Student @ TUM)
 **********************************************************************************************************************/

#ifndef GAME_HPP
#define GAME_HPP

/********************************************//**
 * Includes
 ***********************************************/
#include <QCoreApplication>
#include <QDebug>
#include "datatypes.hpp"
#include "board.hpp"
#include "ship.hpp"
#include "messages.h"

/**
 * @brief The Game class
 *
 * The Game class implements the logic module and itself implements
 * the rules and order of procedures of an battleship match.
 */
class Game : public QObject
{
    Q_OBJECT /// Needed for signals and slots
public:
    /**
     * @brief Game constructor
     * @param parent
     */
    explicit Game(QObject *parent = 0);

    /**
     * @brief Game move constructor
     * Explicit definition needed because of the use of custom datatypes
     */
    Game(Game&&);

    /**
     * @brief Game copy constructor
     * Explicit definition needed because of the use of custom datatypes
     */
    Game(Game&) = default;

    /**
     * @brief updates _myturn depending on who's turn it is
     *
     * Notifys a change everytime via signal to gui
     */
    void    update_myturn();

    /**
     * @brief checks if the running game is over
     *
     * Iterates through the own board and checks if it merely consists
     */
    void    checkWin();

private:
    /**
     * @brief
     */
    bool          _lost;
    Board         _matchboard;
    Board         _enemyboard;
    bool          _myturn;
    uint8_t       _statuscode;
    coordinates   _lastShot;
    int           _startmsgcounter;

signals:
    // logic -> gui
    /**
     * @brief emits signal when _myturn changes
     */
    void    sendMyturn(bool);

    /**
     * @brief emits signal when the game is over
     */
    void    sendWin(bool);

    /**
     * @brief emits signal when a field has changed its value
     * @param point coordinates of the field to change
     * @param flag  the value to change the given field into
     * @param own   whether to change own or opponents's board
     */
    void    updateField(coordinates point, int flag, bool own);

    /**
     * @brief emit signal when a ship has been destroyed
     * @param size length of the destroyed ship
     */
    void    shipDestroyed(int size);

    // logic -> network (Message to send)
    /**
     * @brief emit signal when player wants to send its field parameter
     * @param msg field parameter stored in a message of type Parameter
     */
    void    sendParameter(Parameter &msg);

    /**
     * @brief emit signal when player is done setting ships and
     *        wants to start the game
     * @param msg
     */
    void    sendGameStart(GameStart &msg);

    /**
     * @brief emit signal when player fires a shot
     * @param msg coordinates of the fired field are stored in a message of
     *        type Shot
     */
    void    sendShot(Shot &msg);

    /**
     * @brief emit signal when opponents wants to start the game
     * @param msg message containing players answer (ready or not ready)
     */
    void    sendAnswerGame(AnswerGame &msg);

    /**
     * @brief emit signal in response to an opponent's shot
     * @param msg message containing wheter or not the shot hit a ship
     */
    void    sendShotAnswer(ShotAnswer &msg);

    /**
     * @brief sendName
     * @param enemyname
     */
    void    sendName(int enemyname);

public slots:
    // logic -> network
    /**
     * @brief method that sets the given parameter for the match
     * @param msg contains the match's parameter
     */
    void    receiveParameter(Parameter &msg);

    /**
     * @brief method that processes opponents wish to start the game
     */
    void    receiveGameStart();

    /**
     * @brief method that checks wheter or not opponents shot hit a ship
     * @param msg contains shot's coordinates
     */
    void    receiveShot(Shot &msg);

    /**
     * @brief method that decides who is allowed to begin
     * @param msg information about whether the opponent is ready or not
     */
    void    receiveAnswerGame(AnswerGame &msg);

    /**
     * @brief method that sets own field depending on the success of the last shot
     * @param msg
     */
    void    receiveShotAnswer(ShotAnswer &msg);
    // void    receiveGroupId(IdentificationGroup &msg);

    /**
     * @brief sends player's desired game parameters to network
     */
    void    sendParameterNet();

    /**
     * @brief receives the opponents group ID
     * @param msg contains the opponents group ID
     */
    void    receiveGroupID(IdentificationGroup &msg);

    // logic -> gui
    /**
     * @brief method that responds to player's desire to start the game
     */
    void    start();

    /**
     * @brief hands off player's shot coordinates to the gui
     * @param point coordinates of the shot
     */
    void    sendShotGui(const coordinates point);

    /**
     * @brief sets players ship to desired location
     * @param location list of coordinates
     */
    void    setship(const position location);
};

#endif // GAME_HPP
