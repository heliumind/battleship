/*******************************************************************************************************************//**
 *	@file		ship.hpp
 *  @brief		This file holds the needed definitions to use the exxampleTask.
                The canTask does no calculates and only sends dummy messages.
 *  @version 	V1.0
 *  @date		22.03.2018
 *	@author		Henry He (Student @ TUM)
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
 */
class Ship
{

friend class Game;

public:
    /**
     * @brief The shipclass enum
     */
    enum shipclass {Battleship, Cruiser, Destroyer, Submarine};

    /**
     * @brief Ship
     */
    Ship(); // empty constructor needed for _ships map

    /**
     * @brief Ship
     * @param ID
     * @param location
     */
    Ship(const int ID, const position &location);

    /**
     * @brief getID
     * @return
     */
    int getID() const;

    /**
     * @brief getLocation
     * @return
     */
    position getLocation() const;

    /**
     * @brief getLength
     * @return
     */
    int getLength() const;


private:
    /**
     * @brief _ID
     */
    const int _ID;

    /**
     * @brief _location
     */
    const position _location;

    /**
     * @brief _length
     */
    const int _length;

    /**
     * @brief _shipclass
     */
    shipclass _shipclass;
};

#endif //SHIP_HPP
