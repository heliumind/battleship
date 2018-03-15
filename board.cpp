#include "board.hpp"
#include <iostream>

Board::Board(int opt)
{
    if (opt == 0) {
        _board = matrix(10, std::vector<int>(10, 0));
    }
}

bool Board::checkCoordinates(coordinates field)
{
    int x = field.first;
    int y = field.second;
    if ((x < 0 || x > 9) || (y < 0 || y > 9)) {
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

bool Board::checkWin() 
{
    std::vector< std::vector<int> >::iterator row;
    std::vector<int>::iterator col;
    // Iterate through every row
    for (row = _board.begin(); row != _board.end(); row++) { 
        // Iterator through every column
        for (col = row->begin(); col != row->end(); col++) {
            if (*col != 0 && *col != -1 && *col != -2) {
                return false;
            }
        }
    }
    // Board only consists of 0, -1 and -2
    return true;
}

void Board::printBoard()
{
    std::vector< std::vector<int> >::iterator row;
    std::vector<int>::iterator col;
    // Iterate through every row
    for (row = _board.begin(); row != _board.end(); ++row) { 
        // Iterator through every column
        for (col = row->begin(); col != row->end(); ++col) {
            std::cout << *col << "  ";
        }
        std::cout << "\n";
    }
}
