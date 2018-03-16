#ifndef SHIP_HPP
#define SHIP_HPP

#include "datatypes.hpp"
#include <iostream>

enum shipclass {Battleship, Cruiser, Destroyer, Submarine};

class Ship
{
friend class Game;
public:
    Ship();
    Ship(const int ID, const position &location);
    int getID() const;
    position getLocation() const;
    int getLength() const;


private:
    const int _ID;
    const position _location;
    const int _length;
    shipclass _shipclass;
};

#endif //SHIP_HPP
