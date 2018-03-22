/*******************************************************************************************************************//**
 *  @file		ship.hpp
 *  @brief		This file holds the needed definitions to use the ship class.
 *  @version 		V1.0
 *  @date		22.03.2018
 *  @author		Henry He (Student @ TUM)
 **********************************************************************************************************************/

#ifndef SHIP_HPP
#define SHIP_HPP

/********************************************//**
 * Includes
 ***********************************************/
#include "datatypes.hpp"
#include <iostream>

/**
 * @brief The Ship class
 *
 * The Ship class implement the game piece in the battleship game.
 */
class Ship
{

friend class Game; /// adds Game class as friend to access private members

public:
    /**
     * @brief The shipclass enum
     *
     * In addition to a classic ID number a ship has a specifier
     * in form of its type.
     */
    enum shipclass {Battleship, Cruiser, Destroyer, Submarine};

    /**
     * @brief Ship constructor
     *
     * Empty / default constructor is need for _ships map.
     */
    Ship();

    /**
     * @brief Ship constructor
     * @param ID        unique identification number of a ship instance
     * @param location  holds the coordinates the ship is located at
     */
    Ship(const int ID, const position &location);

    /**
     * @brief 	_ID getter
     * @return 	ship's ID
     */
    int getID() const;

    /**
     * @brief 	_location getter
     * @return	ships's location
     */
    position getLocation() const;

    /**
     * @brief 	Length getter
     * @return	length of the _location vector
     */
    int getLength() const;


private:
    /**
     * @brief _ID 	unique integer number to identify the ship
     */
    const int _ID;

    /**
     * @brief _location	holds the coordinates the ship is located at
     */
    const position _location;

    /**
     * @brief _length		holds the ships's length
     */
    const int _length;

    /**
     * @brief _shipclass	holds one of the declared textbased identifier of the ship
     */
    shipclass _shipclass;
};

#endif //SHIP_HPP
