#include "control.h"

Control::Control(QObject *parent)
    : QObject(parent)
{
    connectAll();
}

void Control::connectAll()
{
    // logic <-> network
    connect(&myserver, &MyTcpServer::messageSent, &match, &Game::receiveMessage);
    // connect(&match, &Game::MessageSent, &myserver, &MyTcp)

    // logic <-> gui
    connect(&match, &Game::sendMyturn, &gui, &Gui::getYourTurn);
    connect(&match, &Game::sendWin, &gui, &Gui::getWin);
    connect(&match, &Game::updateField, &gui, &Gui::getUpdateField);
    connect(&gui, &Gui::giveShoot, &match, &Game::sendShot);
    connect(&gui, &Gui::giveShip, &match, &Game::setship);

    // gui <-> network
    connect(&gui, &Gui::serverMode, &myserver, &MyTcpServer::initServer);
}

void Control::start()
{
    gui.show();

    // Modus 1: Server

    // myserver.sendParameterData();



}
