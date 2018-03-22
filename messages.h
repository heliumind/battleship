/*******************************************************************************************************************//**
 *	@file		messages.hpp
 *  @brief		This file holds the needed classes for the messages that are needed to communicate with
 *              the logic and the opponent.
 *  @version 	V1.0
 *  @date		22.03.2018
 *	@author		Arber Salihu (Student @ TUM)
 **********************************************************************************************************************/

#ifndef SHOT_H
#define SHOT_H

/********************************************//**
 * Includes
 ***********************************************/

#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>
#include "datatypes.hpp"

//class for the first message the parameters
/**
 * @brief The Message class
 *
 */
class Message
{

public:
    /**
     * @brief Message Constructor
     * @param cmd   unique identificaton number of the message
     * @param dlc   unique length of the message
     */
    Message( uint8_t cmd, uint8_t dlc);
    virtual ~Message() = default;

    /**
     * @brief _cmd  unique Identification number of the message
     */
    const uint8_t _cmd;

    /**
     * @brief _dlc  unique length of the message
     */
    const uint8_t _dlc;
};

/**
 * @brief The Parameter class   Class to initializes the parameter data that are sent to the client
 * Inherits the identification and length of a message form the Message class
 */
class Parameter: public Message
{

public:
    /**
     * @brief Parameter Constructor with inherited Identification and length
     * @param cmd
     * @param dlc
     */
    Parameter(uint8_t cmd,uint8_t dlc);

    /**
     * @brief _field_x  attribute that declares the field size in x
     */
    uint8_t _field_x = 10;

    /**
     * @brief _field_y  attribute that declares the field size in y
     */
    uint8_t _field_y = 10;

    /**
     * @brief _n_battleship attribute that declares the number of battleships
     */
    uint8_t _n_battleship = 1;

    /**
     * @brief _n_cruiser    attribute that declares the number of cruisers
     */
    uint8_t _n_cruiser = 2;

    /**
     * @brief _n_destroyer  attribute that declares the number of destroyers
     */
    uint8_t _n_destroyer = 3;

    /**
     * @brief _n_submarine  attribute that declares the number of submarines
     */
    uint8_t _n_submarine = 4;

};

/**
 * @brief The GameStart class   Class for the message to start the game
 * Inherits the identification and length of a message form the Message class
 */
class GameStart: public Message
{
public:

    /**
     * @brief GameStart Constructor with the inherited identification and length
     * @param cmd
     * @param dlc
     */
    GameStart(uint8_t cmd,uint8_t dlc);

};

/**
 * @brief The Shot class    Class for the message that is sent when a shot is send.
 * Inherits the identification and length of a message form the Message class
 */
class Shot: public Message
{
public:

    /**
     * @brief Shot  Constructor with the inherited identification and length
     * @param cmd
     * @param dlc
     */
    Shot(uint8_t cmd,uint8_t dlc);

    /**
     * @brief _coordinates_x    x coordinates that are initialized when a shot at the enemy is fired
     */
    uint8_t _coordinates_x = 0x00;

    /**
     * @brief _coordinates_y    y coordinates that are initialized when a shot at the enemy is fired
     */
    uint8_t _coordinates_y = 0x00;
};

/**
 * @brief The AnswerGame class  Class for the message that is sent after getting the gamestart question.
 * Inherits the identification and length of a message form the Message class
 */
class AnswerGame: public Message
{
public:
    /**
     * @brief AnswerGame    Constructor with the inherited identification and length
     * @param cmd
     * @param dlc
     */
    AnswerGame(uint8_t cmd,uint8_t dlc);

    /**
     * @brief _status   Status of the message that is initialized when the answer is send
     */
    uint8_t _status = 0x00;
};

/**
 * @brief The ShotAnswer class  Class for the message that is sent after a shot from the opponent is taken.
 * Inherits the identification and length of a message form the Message class
 */
class ShotAnswer: public Message
{
public:

    /**
     * @brief ShotAnswer    Constructor with the inherited identification and length
     * @param cmd
     * @param dlc
     */
    ShotAnswer(uint8_t cmd,uint8_t dlc);

    /**
     * @brief _status   Status of the message that is initialized when the shot answer is send
     */
    uint8_t _status = 0x00;

    /**
     * @brief _position Position of the sunken ship that is sent when the ship sinks. _position is a pair of coordinates
     */
    position _position;
};

/**
 * @brief The IdentificationGroup class Class for the message that is sent to show the opponent the group id.
 * Inherits the identification and length of a message form the Message class
 */
class IdentificationGroup: public Message
{
public:

    /**
     * @brief IdentificationGroup   Constructor with the inherited identification and length
     * @param cmd
     * @param dlc
     */
    IdentificationGroup(uint8_t cmd,uint8_t dlc);

    /**
     * @brief _groupNumber  The group number of our team.
     */
    uint8_t _groupNumber = 0x00;

};

/**
 * @brief The Chat class    Class for the Chat
 * Inherits the identification and length of a message form the Message class
 */
class Chat: public Message
{
public:

    /**
     * @brief Chat  Constructor with the inherited identification and length
     * @param _cmd
     * @param _dlc
     */
    Chat(uint8_t _cmd, uint8_t _dlc);

    /**
     * @brief _text QString that contains the text that will be sent.
     */
    QString _text;
};

#endif // SHOT_H
