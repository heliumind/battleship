#ifndef BOARD_HPP
#define BOARD_HPP

#include "datatypes.hpp" 

class Board
{
public:
    Board(int opt = 0); // for local matchboard initialize with 0, for opponent leave matrix empty
    int     getField(coordinates field) const;
    bool    setField(coordinates field, int ID);
    matrix  getBoard() const;
    bool    receiveShot(coordinates field);
    bool    sendShot(coordinates field);
    bool    checkCoordinates(coordinates field);
    void    printBoard();
    bool    checkWin();

private:
    matrix  _board;

};

#endif //BOARD_HPP
