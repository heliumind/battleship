#include "game.hpp"

Game::Game(QObject *parent)
    : QObject(parent), _lost(false), _myturn(true), _startmsgcounter(0), _paramcounter(0)
{
    _matchboard = Board();
}

Game::Game(Game &&test)
    : _matchboard(test._matchboard), _enemyboard(test._enemyboard)
{

}

void Game::update_myturn()
{
    bool allow = false;
    if (_statuscode == 0x00 || _statuscode == 0x01 || _statuscode == 0x02) {
        allow = true;
    }

    if (allow) {
        _myturn = !_myturn;
        emit sendMyturn(_myturn);
    }
}

void Game::checkWin()
{
    bool lost = true;
    std::vector< std::vector<int> >::iterator row;
    std::vector<int>::iterator col;
    // Iterate through every row
    for (row = _matchboard._board.begin(); row != _matchboard._board.end(); row++) {
        // Iterator through every column
        for (col = row->begin(); col != row->end(); col++) {
            if (*col != 0 && *col != -1 && *col != -2 && *col != -3) {
                lost = false;
            }
        }
    }
    _lost = lost;
}

void Game::receiveParameter(Parameter &msg)
{
    _paramcounter++;
    AnswerGame answergame = AnswerGame(0x10, 0x01);
    answergame._status = 0x02;
    if (msg._field_x == 10 && msg._field_y == 10 && msg._n_battleship == 1 && msg._n_cruiser == 2 && msg._n_destroyer == 3 && msg._n_submarine == 4) {
        answergame._status = 0x00;
    }

    if (answergame._status == 0x02) {
        emit disconnect();
    }
    emit sendAnswerGame(answergame);
}

void Game::receiveShot(Shot &msg)
{
    coordinates point = std::make_pair(msg._coordinates_x, msg._coordinates_y);
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
            case -1:
                break;
            case -2:
                break;
            case -3:
                break;
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
                    for (auto point = location.begin(); point != location.end(); point++) {
                        emit updateField(*point, -3, true);
                    }

                }
                break;
        }
        checkWin();
        if (_lost) { // I lost;
            _statuscode = 0x03;
            emit sendWin(false); // Notify gui we lost
        }
    }

    // Send network statuscode
    if(_statuscode == 0x02 || _statuscode == 0x03) {
        uint8_t dlc = 0x01 + (location.size()*2);
        ShotAnswer shotanswer = ShotAnswer(0x11, dlc);
        shotanswer._status = _statuscode;
        shotanswer._position = location;
        emit sendShotAnswer(shotanswer);
    }
    else {
        ShotAnswer shotanswer = ShotAnswer(0x11, 0x01);
        shotanswer._status = _statuscode;
        emit sendShotAnswer(shotanswer);
    }

    update_myturn();
}

void Game::receiveGameStart()
{
    _startmsgcounter++;
    if(_startmsgcounter == 1) {
        _myturn = false;
    }
    AnswerGame answergame = AnswerGame(0x10, 0x01);
    if (_matchboard._maxID == 10) { // All ships set
        answergame._status = 0x00;
        if(_startmsgcounter == 2) {
            emit sendMyturn(_myturn);
        }
    }
    else { // Not all ships are set
        answergame._status = 0x01;
    }
    emit sendAnswerGame(answergame);
}

void Game::receiveAnswerGame(AnswerGame &msg)
{
    if(msg._status == 0x00 && _startmsgcounter == 2 && _paramcounter == 1) {
        emit sendMyturn(_myturn);
        }
}

void Game::sendShotGui(const coordinates point)
{
    _lastShot = point;
    // Pack point in a message and send to network
    Shot shot = Shot(0x03, 0x02);
    uint8_t x = point.first;
    uint8_t y = point.second;
    shot._coordinates_x = x;
    shot._coordinates_y = y;
    emit sendShot(shot);
}

void Game::setship(position location)
{
    _matchboard.setShip(location);
}

void Game::receiveShotAnswer(ShotAnswer &msg)
{
    uint8_t code = msg._status;
    position location = {std::make_pair(0,0)};
    if (code == 0x02 || code == 0x03) {
        location = msg._position;
    }
    _statuscode = code;
    switch(code) {
        case 0x00: // Nicht getroffen
            _enemyboard.setField(_lastShot, -2);
            emit updateField(_lastShot, -2, false);
            break;
        case 0x01: // Getroffen
            _enemyboard.setField(_lastShot, -1);
            emit updateField(_lastShot, -1, false);
            break;
        case 0x02: {// Getroffen und versenkt
            _enemyboard.setShip(location, false);
            for (auto point = location.begin(); point != location.end(); point++) {
                emit updateField(*point, -3, false);
            }
            emit shipDestroyed(location.size());
            break;}
        case 0x03: // Getroffen und versenkt, Spielende

            _enemyboard.setShip(location, false);
            for (auto point = location.begin(); point != location.end(); point++) {
                emit updateField(*point, -3, false);
            }
            emit shipDestroyed(location.size());
            emit sendWin(true);
            break;

    }

    update_myturn();
}

void Game::sendParameterNet()
{
    Parameter param = Parameter(0x01, 0x06);
    emit sendParameter(param);
}

void Game::start()
{
   GameStart gamestart = GameStart(0x02, 0x00);
   _startmsgcounter++;
   emit sendGameStart(gamestart);
}
