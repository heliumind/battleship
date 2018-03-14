#ifndef GAME_HPP
#define GAME_HPP

#include "datatypes.hpp"
#include "board.hpp"
#include "ship.hpp"

class Game
{
public:
    Board   matchboard;
    Game();
    bool setShip(const Ship &ship);
    void update_win();
    void receiveMessage();
    void sendMessage();
    bool get_win() const;
    matrix  getBoard() const;
    
private:
    bool  _win;
};

#endif // GAME_HPP
