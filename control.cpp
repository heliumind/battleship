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
    connect(&match, &Game::shipDestroyed, &gui, &Gui::getShipDestroyed);
}


void Control::start()
{
    gui.show();

    // Modus 1: Server


}

void Control::setServer()
{
    myserver.initServer();

    // logic <-> network
    connect(&myserver, &MyTcpServer::receiveGameStart, &match, &Game::receiveGameStart);
    connect(&myserver, &MyTcpServer::receiveShot, &match, &Game::receiveShot);
    connect(&myserver, &MyTcpServer::receiveAnswerGame, &match, &Game::receiveAnswerGame);
    connect(&myserver, &MyTcpServer::receiveShotAnswer, &match, &Game::receiveShotAnswer);
    // connect(&myserver, &MyTcpServer::receiveGroupId, &match, &Game::receiveGroupId);

    connect(&match, &Game::sendParameter, &myserver, &MyTcpServer::sendParameter);
    connect(&match, &Game::sendGameStart, &myserver, &MyTcpServer::sendGameStart);
    connect(&match, &Game::sendShot, &myserver, &MyTcpServer::sendShot);
    connect(&match, &Game::sendAnswerGame, &myserver, &MyTcpServer::sendAnswerGame);
    connect(&match, &Game::sendShotAnswer, &myserver, &MyTcpServer::sendShotAnswer);
    // connect(&match, &Game::sendGroupId, &myserver, MyTcpServer::sendGroupId)

    // gui <-> network
    connect(&myserver, &MyTcpServer::gotClient, &gui, &Gui::foundClient);
}

void Control::setClient()
{

    // logic <-> network
    //connect(&myclient, &MyClient::receiveParameter, &match, &Game::re) //
    connect(&myclient, &MyClient::receiveGameStart, &match, &Game::receiveGameStart);
    connect(&myclient, &MyClient::receiveShot, &match, &Game::receiveShot);
    connect(&myclient, &MyClient::receiveShotAnswer, &match, &Game::receiveShotAnswer);
    connect(&myclient, &MyClient::receiveAnswerGame, &match, &Game::receiveAnswerGame);
    //connect(&myclient, &MyClient::receiveIdentificationGroup, &match, &Game::receiveGroupId);

     // connect every Message#

    connect(&match, &Game::sendGameStart, &myclient, &MyClient::sendGameStart);
    connect(&match, &Game::sendShot, &myclient, &MyClient::sendShot);
    connect(&match, &Game::sendAnswerGame, &myclient, &MyClient::sendAnswerGame);
    connect(&match, &Game::sendShotAnswer, &myclient, &MyClient::sendShotAnswer);
    //connect(&match, &Game::, &myclient, &MyClient::sendIdentificationGroup);


    // gui <-> network
    connect(&gui, &Gui::connectClient, &myclient, &MyClient::ConnectHost);
    connect(&myclient, &MyClient::gotServer, &gui, &Gui::foundServer);
}
