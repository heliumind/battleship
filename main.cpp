#include <QApplication>
#include "control.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Control controller;

    controller.start();

    controller.match._matchboard.printBoard();

    controller.myserver.receiveData();

    controller.match._matchboard.printBoard();

    return a.exec();
}
