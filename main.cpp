#include "game.hpp"
#include "board.hpp"
#include "ship.hpp"
#include <iostream> 

int main()
{
    Game match;
    match.matchboard.printBoard();
    match.update_win();
    match.get_win();
    position ort = {std::make_pair(0,0), std::make_pair(0,1)};
    Ship uboot(1, ort);
    match.setShip(uboot);
    match.matchboard.printBoard();
    match.update_win();
    match.get_win();
    uboot.checkAlive(match.matchboard);
    match.matchboard.setField(ort[0], -1);
    match.matchboard.setField(ort[1], -1);
    match.matchboard.printBoard();
    uboot.checkAlive(match.matchboard);
    match.update_win();
    match.get_win();
    
    return 0;
}

