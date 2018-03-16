#include "board.hpp"
#include <iostream>

Board::Board(const int opt)
    : _maxID(0)
{
    if (opt == 0) {
        _board = matrix(10, std::vector<int>(10, 0));
    }
}

bool Board::checkCoordinates(coordinates field)
{
    int x = field.first;
    int y = field.second;
    int max = _board.size() - 1;
    if ((x < 0 || x > max) || (y < 0 || y > max)) {
        return false;
    }
    else {
        return true;
    }
}

int Board::getField(coordinates field) const
{
    int x = field.first;
    int y = field.second;
    return _board[x][y];
}

bool Board::setField(coordinates field, int ID)
{
    int x = field.first;
    int y = field.second;
    if (!checkCoordinates(field)) {
        std::cout << "Wrong Coordinates!" << std::endl;
        return false;
    }
    else {
        _board[x][y] = ID;
        return true;
    }
}

matrix Board::getBoard() const
{
    return _board;
}

bool Board::receiveShot(coordinates field)
{
    if (!checkCoordinates(field)) {
        return false;
    }
    else {
        int ID = getField(field);
        switch(ID) {
            case 0:
                std::cout << "Missed!" << std::endl;
                break;
            case -2:
                std::cout << "You have already shot here! (Water)" << std::endl;
                break;
            case -1:
                std::cout << "You have already shot here! (Ship)" << std::endl;
                break;
            default:
                std::cout << "Hit!" << std::endl;
                setField(field, -1);
                break;
        }
        return true;
    }
}

void Board::printBoard()
{
    std::vector< std::vector<int> >::iterator row;
    std::vector<int>::iterator col;
    // Iterate through every row
    for (row = _board.begin(); row != _board.end(); ++row) { 
        // Iterator through every column
        for (col = row->begin(); col != row->end(); ++col) {
            std::cout << *col << "";
        }
        std::cout << std::endl;
    }
    std::cout << "\n" << std::endl;
}

bool Board::checkAlive(const Ship &ship)
{
    int ID = ship.getID();
    std::vector< std::vector<int> >::iterator row;
    std::vector<int>::iterator col;
    // Iterate through every row
    for (row = _board.begin(); row != _board.end(); ++row) {
        // Iterator through every column
        for (col = row->begin(); col != row->end(); ++col) {
            if (*col == ID) {
                std::cout << "Ship " << ID << " alive" << std::endl;
                return true;
            }
        }
    }
    std::cout << "Ship " << ID << " destroyed" << std::endl;
    return false;
}

bool Board::setShip(position &location)
{
    _maxID++;
    Ship ship(_maxID, location);
    _ships.emplace(_maxID, ship);   // Add generated ship to _ships map
    std::vector< std::pair<int, int> >::iterator point;
    for (point = location.begin(); point != location.end(); point++) {
        setField(*point, _maxID);
    }

    return true;
}
