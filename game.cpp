#include "game.hpp"

Game::Game(QObject *parent)
    : QObject(parent), _win(false), _myturn(false)
{
    _matchboard = Board();
}

Game::Game(Game &&test)
    : _matchboard(test._matchboard)
{

}


bool Game::get_win() const
{
    if (_win == true) {
        std::cout << "Game Won!" << std::endl;

    }
    else {
        std::cout << "Still going" << std::endl;
    }
    return _win;
}

void Game::update_myturn()
{
    bool allow = false;
    if (_statuscode == 0x00 || _statuscode == 0x02 || _statuscode == 0x03) {
        allow = true;
    }

    if (allow) {
        _myturn = !_myturn;
    }
}

void Game::receiveMessage(Shot &shot)
{
    int x = shot._coordinates_x;
    int y = shot._coordinates_y;
    coordinates point = std::make_pair(x, y);
    receiveShot(point);
}

Board Game::getBoard() const
{
    return _matchboard;
}

void Game::checkWin()
{
    bool win = true;
    std::vector< std::vector<int> >::iterator row;
    std::vector<int>::iterator col;
    // Iterate through every row
    for (row = _matchboard._board.begin(); row != _matchboard._board.end(); row++) {
        // Iterator through every column
        for (col = row->begin(); col != row->end(); col++) {
            if (*col != 0 && *col != -1 && *col != -2) {
                win = false;
            }
        }
    }

    _win = win;
}


void Game::receiveShot(const coordinates point)
{
    if (!_matchboard.checkCoordinates(point)) {
        // coordinates are out of bound
        _statuscode = 0x11;
    }
    else if (_myturn) {
        // Not opponents turn
        _statuscode = 0x10;
    }
    else { // Opponents turn
        int flag = _matchboard.getField(point);
        switch (flag) {
            case 0:
                // No Hit
                _statuscode = 0x00;
                _matchboard.setField(point, -2);
                break;

            default:
                // Opponent hit a ship
                _matchboard.setField(point, -1);
                _statuscode = 0x01;
                Ship target = _matchboard._ships[flag];
                if (!_matchboard.checkAlive(target)) {
                    _statuscode = 0x02;
                }
                break;
        }
        checkWin();
        if (_win) {
            _statuscode = 0x03;
        }
    }

    // Send network statuscode

    // update_myturn();
}

void Game::sendShot(const coordinates point) //Message Pointer)
{
    // _matchboard.setField(point, )
}

void Game::start()
{
    _myturn = true;

}
