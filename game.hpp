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
    void    sendMessage();
    Board   getBoard() const;
    void    checkWin();
    void    receiveShot(const coordinates point);
    void    sendShot(const coordinates point);
    void    start();
    Board   _matchboard;
    uint8_t _statuscode;
private:
    bool    _win;
    // Board   _matchboard;
    Board   _enemyboard;
    bool    _myturn;
    // uint8_t _statuscode;

signals:
    void    updateField(coordinates point, int flag);

public slots:
    void    receiveMessage(Shot &shot);

};

#endif // GAME_HPP