#include <QCoreApplication>
#include "game.hpp"
#include "board.hpp"
#include "ship.hpp"
#include "datatypes.hpp"
#include "control.h"
#include <iostream> 

int main(int argc, char **argv)
{
    QCoreApplication a(argc, argv);
    
    Control controller;


    return a.exec();
}

