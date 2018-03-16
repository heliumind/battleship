#include "ship.hpp"

Ship::Ship()
    : _ID(-3), _location(0), _length(0)
{}

Ship::Ship(const int ID, const position &location)
    : _ID(ID), _location(location), _length(location.size())
{
    switch (location.size()) {
        case 5:
            _shipclass = Battleship;
            break;
        case 4:
            _shipclass = Cruiser;
            break;
        case 3:
            _shipclass = Destroyer;
            break;
        case 2:
            _shipclass = Submarine;
    }
}

int Ship::getID() const
{
    return _ID;
}


position Ship::getLocation() const
{
    return _location;
}

int Ship::getLength() const
{
    return _length;
}


