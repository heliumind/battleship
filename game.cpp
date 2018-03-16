#include "game.hpp"

Game::Game(QObject *parent)
    : QObject(parent), _win(false)
{
    _matchboard = Board();
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

Board Game::getBoard() const
{
    return _matchboard;
}

void Game::checkWin()
{
    std::vector< std::vector<int> >::iterator row;
    std::vector<int>::iterator col;
    // Iterate through every row
    for (row = _matchboard._board.begin(); row != _matchboard._board.end(); row++) {
        // Iterator through every column
        for (col = row->begin(); col != row->end(); col++) {
            if (*col != 0 && *col != -1 && *col != -2) {
                _win = false;
            }
        }
    }
    // Board only consists of 0, -1 and -2
    _win = true;
}


void receiveShot(const coordinates point)
{

}

//void Game::getShot(coordinates point)
//{
//    uint8_t statuscode;
//    position dummy(0, std::pair<int, int>(0, 0));

//    if (!_matchboard.checkCoordinates(point)) {
//        // coordinates are out of bound
//        statuscode = 0x11;
//    }
//    else if (_myturn) {
//        // Not opponents turn
//        statuscode = 0x10;
//    }
//    else { // Opponents turn
//        int flag = _matchboard.getField(point);
//        switch (flag) {
//            case 0:
//                // No Hit
//                statuscode = 0x00;
//                _matchboard.setField(point, -2);
//                break;

//            default:
//                // Opponent hit a ship
//                _matchboard.setField(point, -1);
//                update_win();
//                if (_win) {
//                    statuscode = 0x03;
//                }
//                else if(!_matchboard.checkAlive(flag)) {
//                    statuscode = 0x02;
//                }
//                else {
//                    statuscode = 0x01;
//                }
//                break;
//        }
//    }
//    update_myturn(statuscode);

//    if(statuscode == 0x02) {
//        int id = _matchboard.getField(point);
//        Ship target = _matchboard._ships[id];
//        emit Game::sendShotAnswer(statuscode, target._location);
//    }
//    else {
//        emit Game::sendShotAnswer(statuscode, dummy);
//    }
//}
