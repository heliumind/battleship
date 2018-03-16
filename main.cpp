#include <QCoreApplication>
#include "game.hpp"
#include "board.hpp"
#include "ship.hpp"
#include "datatypes.hpp"
#include <iostream> 

int main(int argc, char **argv)
{
    QCoreApplication a(argc, argv);
    
    Game match;

    position location = { std::make_pair(0,0), std::make_pair(0,1)};

    match._matchboard.setShip(location);
    match._matchboard.printBoard();
    Ship test = match._matchboard._ships[1];
    match._matchboard.checkAlive(test);
    match.checkWin();
    std::cout << match.get_win() << std::endl;


    return a.exec();
}

