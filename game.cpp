#include "game.hpp"

Game::Game()
    : _win(false)
{
    matchboard = Board();
}

bool Game::setShip(const Ship &ship)
{
    int ID = ship.getID();
    position location = ship.getLocation();
    std::vector< std::pair<int, int> >::iterator point;
    for (point = location.begin(); point != location.end(); point++) {
        matchboard.setField(*point, ID);
    }
    return true;
}

void Game::update_win()
{
    _win = matchboard.checkWin();
}

bool Game::get_win() const
{
    if (_win) {
        std::cout << "Game Won!" << std::endl;

    }
    else {
        std::cout << "Still going" << std::endl;
    }
    return _win;
}
