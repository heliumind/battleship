#include "game.hpp"

Game::Game(QObject *parent)
    : QObject(parent), _win(false), _myturn(false)
{
    _matchboard = Board();
}

Game::Game(Game &&test)
    : _matchboard(test._matchboard), _enemyboard(test._enemyboard)
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
    emit sendMyturn(_myturn);
}

void Game::receiveMessage(Message *msg)
{
    switch (msg->_cmd) {

    case 0x01: // Aushandeln der Spielfeldparameter -> gui nur Client Modus
        break;

    case 0x02: {// Anforderung Spielbeginn
        AnswerGame answergame = AnswerGame(0x10, 0x01);
        answergame._status = 0x01; // Not ready
        if (_matchboard._maxID == 10) { // Ready
            AnswerGame answergame = AnswerGame(0x10, 0x01);
            answergame._status = 0x00;
        }
        Message *msgptr = &answergame;
        emit MessageSent(msgptr);
        break;}

    case 0x03: {// Schuss -> gui & network
        Shot *shot = dynamic_cast<Shot*>(msg);
        int x = shot->_coordinates_x;
        int y = shot->_coordinates_y;
        coordinates point = std::make_pair(x, y);
        receiveShot(point);
        break;}

    case 0x10: {// Antwort auf Anfrage
        AnswerGame *answergame = dynamic_cast<AnswerGame*>(msg);
        if (answergame->_status == 0x00) {
            _myturn = true;
            emit sendMyturn(_myturn);
        }
        break;}

    case 0x11: {// Antwort auf Schuss
        ShotAnswer *shotanswer = dynamic_cast<ShotAnswer*>(msg);
        uint8_t code = shotanswer->_status;
        position location = {std::make_pair(0,0)};
        if (code == 0x02 || code == 0x03) {
            location = shotanswer->_position;
        }
        receiveShotAnswer(code, location);
        break;}
     default:
        break;
    }
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
            if (*col != 0 && *col != -1 && *col != -2 && *col != 3) {
                win = false;
            }
        }
    }

    _win = win;
}


void Game::receiveShot(const coordinates point)
{
    position location;
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
                emit updateField(point, -2, true);
                break;

            default:
                // Opponent hit a ship
                _matchboard.setField(point, -1);
                emit updateField(point, -1, true);
                _statuscode = 0x01;
                Ship target = _matchboard._ships[flag];
                location = target.getLocation();
                if (!_matchboard.checkAlive(target)) {
                    _statuscode = 0x02;
                    _matchboard.setShip(location, false);
                    std::vector< std::pair<int, int> >::iterator point;
                    for (point = location.begin(); point != location.end(); point++) {
                        emit updateField(*point, -3, true);
                    }
                    emit shipDestroyed(location.size());

                }
                break;
        }
        checkWin();
        if (_win) {
            _statuscode = 0x03;
            emit sendWin(_win);
        }
    }

    // Send network statuscode
    if(_statuscode == 0x02 || _statuscode == 0x03) {
        uint8_t dlc = 0x01 + (location.size()*2);
        ShotAnswer shotanswer = ShotAnswer(0x11, dlc);
        shotanswer._status = _statuscode;
        shotanswer._position = location;
        Message *msgptr = &shotanswer;
        emit MessageSent(msgptr);
    }
    else {
        ShotAnswer shotanswer = ShotAnswer(0x11, 0x01);
        shotanswer._status = _statuscode;
        Message *msgptr = &shotanswer;
        emit MessageSent(msgptr);
    }

    update_myturn();
}

void Game::sendShot(const coordinates point) //Message Pointer)
{
    _lastShot = point;
    // Pack point in a message and send to network
    Shot shot = Shot(0x02, 0x02);
    uint8_t x = point.first;
    uint8_t y = point.second;
    shot._coordinates_x = x;
    shot._coordinates_y = y;
    Message *msgptr = &shot;
    emit MessageSent(msgptr);
}

void Game::setship(position location)
{
    _matchboard.setShip(location);
}

void Game::receiveShotAnswer(const uint8_t code, position location)
{
    _statuscode = code;
    switch(code) {
        case 0x00: // Nicht getroffen
            _matchboard.setField(_lastShot, -2);
            emit updateField(_lastShot, -2, false);
            break;
        case 0x01: // Getroffen
            _matchboard.setField(_lastShot, -1);
            emit updateField(_lastShot, -1, false);
            break;
        case 0x02: {// Getroffen und versenkt
            _matchboard.setShip(location, false);
            std::vector< std::pair<int, int> >::iterator point;
            for (point = location.begin(); point != location.end(); point++) {
                emit updateField(*point, -3, false);
            }
            break;}
        case 0x03: // Getroffen und versenkt, Spielende

            _matchboard.setShip(location, false);
            std::vector< std::pair<int, int> >::iterator point;
            for (point = location.begin(); point != location.end(); point++) {
                emit updateField(*point, -3, false);
            }
            checkWin();
            if (_win == true) {
                emit sendWin(_win);
            }
            break;

    }

    update_myturn();
}

void Game::start()
{

}
