#include <QCoreApplication>
#include "game.hpp"
#include "board.hpp"
#include "ship.hpp"
#include <iostream> 

int main(int argc, char **argv)
{
    QCoreApplication a(argc, argv);
    Game match;
    Board matchboard = match.getBoard();
    matchboard.printBoard();
    position ort = {std::make_pair(0,0), std::make_pair(0,1)};
    Ship uboot(1, ort);
    match.setShip(uboot);
    std::cout << "Uboot length:" << uboot.getLength() << std::endl;
    matchboard = match.getBoard();
    matchboard.printBoard();
    match.update_win();
    match.get_win();
    uboot.checkAlive(matchboard);
    matchboard.setField(ort[0], -1);
    matchboard.setField(ort[1], -1);
    matchboard.printBoard();
    uboot.checkAlive(matchboard);
    match.update_win();
    match.get_win();
    
    return a.exec();
}

