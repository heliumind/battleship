#ifndef GAME_HPP
#define GAME_HPP

#include <QCoreApplication>
#include "datatypes.hpp"
#include "board.hpp"
#include "ship.hpp"
#include "messages.h"

class Game : public QObject
{
    Q_OBJECT
public:
    explicit Game(QObject *parent = 0);
    Game(Game&&);
    Game(Game&) = default;
    bool    get_win() const;
    void    update_myturn();
    Board   getBoard() const;
    void    checkWin();
    void    receiveShot(const coordinates point);
    void    receiveShotAnswer(const uint8_t code, position location);
    void    start();
    void    restart();
    Board   _matchboard;
private:
    bool    _win;
//    Board   _matchboard;
    Board   _enemyboard;
    bool    _myturn;
    uint8_t _statuscode;
    coordinates _lastShot;

signals:
    // logic -> gui
    void    sendMyturn(bool);
    void    sendWin(bool);
    void    updateField(coordinates point, int flag, bool own);

    // logic -> network
    void    MessageSent(Message* msg);

    // logic -> controller


public slots:
    // logic -> network
    void    receiveMessage(Message* msg);

    // logic -> gui
    void    sendShot(const coordinates point);
    void    setship(const position location);
};

#endif // GAME_HPP
