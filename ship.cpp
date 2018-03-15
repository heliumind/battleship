#include "ship.hpp"

Ship::Ship(const int ID, const position &location)
    : _ID(ID), _location(location), _length(location.size())
{
};

int Ship::getID() const
{
    return _ID;
}

bool Ship::checkAlive(const Board &board)
{
    std::vector< std::vector<int> >::iterator row;
    std::vector<int>::iterator col;
    matrix _board = board.getBoard();
    // Iterate through every row
    for (row = _board.begin(); row != _board.end(); ++row) { 
        // Iterator through every column
        for (col = row->begin(); col != row->end(); ++col) {
            if (*col == _ID) {
                std::cout << "Ship " << _ID << " alive" << std::endl;
                return false;
            }
        }
    }
    std::cout << "Ship " << _ID << " destroyed" << std::endl;
    return true;
}

position Ship::getLocation() const
{
    return _location;
}

int Ship::getLength() const
{
    return _length;
}

