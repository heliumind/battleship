#ifndef GAME_HPP
#define GAME_HPP

#include "datatypes.hpp"
#include "board.hpp"
#include "ship.hpp"

class Game
{
public:
    Game();
    bool setShip(const Ship &ship);
    void update_win();
    void receiveMessage();
    void sendMessage();
    bool get_win() const;
    matrix  getBoard() const;
    Board matchboard;
    
private:
    bool  _win;

};

#endif // GAME_HPP
