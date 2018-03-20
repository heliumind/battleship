#include "control.h"

Control::Control(QObject *parent)
    : QObject(parent)
{
    connectAll();
}

void Control::connectAll()
{

    // logic <-> gui
    connect(&gui, &Gui::giveStart, &match, &Game::start);
    connect(&match, &Game::sendMyturn, &gui, &Gui::getYourTurn);
    connect(&match, &Game::sendWin, &gui, &Gui::getWin);
    connect(&match, &Game::updateField, &gui, &Gui::getUpdateField);
    connect(&gui, &Gui::giveShoot, &match, &Game::sendShot);
    connect(&gui, &Gui::giveShip, &match, &Game::setship);

    // logic <-> network
        // Modus Server
    connect(&myserver, &MyTcpServer::messageSent, &match, &Game::receiveMessage);
    connect(&match, &Game::MessageSent, &myserver, &MyTcpServer::sendMessage);

        // Modus Client
    connect(&myclient, &MyClient::messageSent, &match, &Game::receiveMessage);
    connect(&match, &Game::MessageSent, &myclient, &MyClient::sendMessage);

    // gui <-> network
        // Modus Server
    connect(&gui, &Gui::serverMode, &myserver, &MyTcpServer::initServer);
    connect(&myserver, &MyTcpServer::gotClient, &gui, &Gui::foundClient);

        // Modus Client
    connect(&gui, &Gui::connectClient, &myclient, &MyClient::ConnectHost);
    connect(&myclient, &MyClient::gotServer, &gui, &Gui::foundServer);
}

void Control::start()
{
    gui.show();

    // Modus 1: Server

    // myserver.sendParameterData();



}
