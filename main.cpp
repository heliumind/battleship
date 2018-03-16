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

    position location2 = { std::make_pair(3,4), std::make_pair(4,4)};

    match._matchboard.setShip(location);
    match._matchboard.setShip(location2);
    match._matchboard.printBoard();
    Ship test = match._matchboard._ships[1];
    match._matchboard.checkAlive(test);
    match.checkWin();
    std::cout << match.get_win() << std::endl;
    match.receiveShot(location[0]);
    match._matchboard.printBoard();
    std::cout << "Status: " << match._statuscode << std::endl;
    match.receiveShot(location[1]);
    match._matchboard.printBoard();
    std::cout << "Status: " << match._statuscode << std::endl;
    match.receiveShot(location2[0]);
    match._matchboard.printBoard();
    std::cout << "Status: " << match._statuscode << std::endl;
    match.receiveShot(location2[1]);
    match._matchboard.printBoard();
    std::cout << "Status: " << match._statuscode << std::endl;


    return a.exec();
}

