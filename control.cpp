#include "control.h"

Control::Control(QObject *parent)
    : QObject(parent), match(Game()), myserver(MyTcpServer())
{
    connectGui();
}

void Control::connectGui()
{

    // logic <-> gui
    connect(&gui, &Gui::giveStart, &match, &Game::start);
    connect(&match, &Game::sendMyturn, &gui, &Gui::getYourTurn);
    connect(&match, &Game::sendWin, &gui, &Gui::getWin);
    connect(&match, &Game::updateField, &gui, &Gui::getUpdateField);
    connect(&gui, &Gui::giveShoot, &match, &Game::sendShotGui);
    connect(&gui, &Gui::giveShip, &match, &Game::setship);
    connect(&gui, &Gui::serverMode, this, &Control::setServer);
    connect(&gui, &Gui::clientMode, this, &Control::setClient);
}


void Control::start()
{
    gui.show();

    // Modus 1: Server


}

void Control::setServer()
{
    myserver.initServer();
    Parameter msg = Parameter(0x01, 0x06);
    myserver.sendParameter(msg);

    // logic <-> network
    connect(&myserver, &MyTcpServer::receiveGameStart, &match, &Game::receiveGameStart);
    connect(&myserver, &MyTcpServer::receiveShot, &match, &Game::receiveShot);
    connect(&myserver, &MyTcpServer::receiveAnswerGame, &match, &Game::receiveAnswerGame);
    connect(&myserver, &MyTcpServer::receiveShotAnswer, &match, &Game::receiveShotAnswer);
    // connect(&myserver, &MyTcpServer::receiveGroupId, &match, &Game::receiveGroupId);


    // gui <-> network
    connect(&myserver, &MyTcpServer::gotClient, &gui, &Gui::foundClient);
}

void Control::setClient()
{

    // logic <-> network
     // connect every Message
    // gui <-> network
    connect(&gui, &Gui::connectClient, &myclient, &MyClient::ConnectHost);
    connect(&myclient, &MyClient::gotServer, &gui, &Gui::foundServer);
}
