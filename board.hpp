/*******************************************************************************************************************//**
 *	@file		board.hpp
 *  @brief		This file holds the needed definitions to use the board class.
 *  @version 	V1.0
 *  @date		22.03.2018
 *	@author		Henry He (Student @ TUM)
 **********************************************************************************************************************/

#ifndef BOARD_HPP
#define BOARD_HPP


/********************************************//**
 * Includes
 ***********************************************/
#include "datatypes.hpp"
#include "ship.hpp"
#include <map>

/**
 * @brief The Board class
 *
 * The Board class implements the matchboard in the battleship game.
 */
class Board
{

friend class Game; /// adds Game class as a friend to access private members

public:
    /**
     * @brief Board constructor
     * @param opt 	affects if the board is initialized with zeros or empty
     * - 0: initialize _board with 0
     * - other: _board is intialized empty
     */
    Board(const int opt = 0);

    /**
     * @brief 	returns the given field's value
     * @param 	field	coordinate of the field you want to adress
     * @return 	field's value
     */
    int     getField(coordinates field) const;

    /**
     * @brief 	set a field to the given value
     * @param 	field
     * @param 	ID
     * @return	setField's success
     */
    bool    setField(coordinates field, int ID);

    /**
     * @brief 	Board getter
     * @return 	The object's actual board
     */
    matrix  getBoard() const;

    /**
     * @brief   checks if the given coordinates can be adressed
     * @param   field coordinates to check
     * @return  true: possible, false: not possible
     */
    bool    checkCoordinates(coordinates field);

    /**
     * @brief prints the board in the terminal
     */
    void    printBoard();

    /**
     * @brief sets multiple field to a given ID specified by the ships attributes
     * @param location	list of coordinates the ship is located at
     * @param upmaxID 	if the setShip is used to set a new ship (true)
     * 					or a destroyed ship (false)
     * @return 	setShip's success
     */
    bool    setShip(position &location, bool upmaxID = true);

    /**
     * @brief checkAlive
     * @param ship	the ship to check if it still exists on the field
     * @return 		return whether the specified ship is alive (true)
     * 				or detroyed (false)
     */
    bool    checkAlive(const Ship &ship);

private:
    /**
     * @brief _maxID	holds the highest assigned ID
     */
    int _maxID;

    /**
     * @brief _board	holds the actual board
     *
     * The integer value of each field holds the state a field is in:
     * - 0: water
     * - -1: a hit ship
     * - -2: hit water
     * - -3: a destroyed ship
     *  - else: a ship with its ID being the field's value
     */
    matrix  _board;

    /**
     * @brief _ships	a map holding every exixsting ship
     *
     * This map is used to access a ship in an existing matchboard.
     * This can be done by refering its ID e.g. _ships[4] returns the
     * ship object with ID 4.
     */
    std::map<int, Ship> _ships;

};

#endif //BOARD_HPP
