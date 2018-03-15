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
<<<<<<< HEAD
    Board  getBoard() const;
    
private:
    bool  _win;
    Board _matchboard;

signals:

public slots:
=======
    matrix  getBoard() const;
    Board matchboard;
    
private:
    bool  _win;
>>>>>>> fe064bbb05153baa82a970635e06d3549ef71962

};

#endif // GAME_HPP
