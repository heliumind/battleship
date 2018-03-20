#include <QApplication>
#include "control.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Control controller;

    controller.start();

    controller.match._matchboard.printBoard();
    std::cout << "Win: " << controller.match.get_win() << std::endl;

    //controller.myserver.receiveData();

    controller.match._matchboard.printBoard();
    std::cout << "Win: " << controller.match.get_win() << std::endl;

    return a.exec();
}
