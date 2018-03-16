#ifndef BOARD_HPP
#define BOARD_HPP

#include "datatypes.hpp"
#include "ship.hpp"
#include <unordered_map>

class Board
{
friend class Game;
public:
    Board(const int opt = 0); // 0: initialize _board with 0
    int     getField(coordinates field) const;
    bool    setField(coordinates field, int ID);
    matrix  getBoard() const;
    bool    receiveShot(coordinates field);
    bool    sendShot(coordinates field);
    bool    checkCoordinates(coordinates field);
    void    printBoard();
    bool    checkWin();
    bool    setShip(position &location);
    bool    checkAlive(const Ship &ship);
    std::unordered_map<int, Ship> _ships;

private:
    int _maxID;
    matrix  _board;
    // std::map<int, Ship> _ships;


};

#endif //BOARD_HPP
