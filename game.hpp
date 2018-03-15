#ifndef GAME_HPP
#define GAME_HPP

#include <QCoreApplication>
#include "datatypes.hpp"
#include "board.hpp"
#include "ship.hpp"

class Game : public QObject
{
    Q_OBJECT
public:
    explicit Game(QObject *parent = 0);
    bool setShip(const Ship &ship);
    void update_win();
    void receiveMessage();
    void sendMessage();
    bool get_win() const;
    Board  getBoard() const;
    
private:
    bool  _win;
    Board _matchboard;

signals:

public slots:

};

#endif // GAME_HPP
