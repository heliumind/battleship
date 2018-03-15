#ifndef SHIP_HPP
#define SHIP_HPP

#include "datatypes.hpp"
#include "board.hpp"
#include <iostream>

class Ship
{
public:
    Ship(const int ID, const position &location); 
    bool checkAlive(const Board &_board);
    int getID() const;
    position getLocation() const;
    int getLength() const;

private:
    const int _ID;
    const position _location;
    const int _length;
};

#endif //SHIP_HPP
