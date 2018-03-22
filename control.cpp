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
    connect(&match, &Game::sendName, &gui, &Gui::getName);
}


void Control::start()
{
    gui.show();
}

void Control::setServer()
{
    // logic <-> network
    connect(&myserver, &MyTcpServer::gotClient, &match, &Game::sendParameterNet);
    connect(&myserver, &MyTcpServer::gotClient, &myserver, &MyTcpServer::sendGroupId);
    connect(&myserver, &MyTcpServer::receiveGameStart, &match, &Game::receiveGameStart);
    connect(&myserver, &MyTcpServer::receiveShot, &match, &Game::receiveShot);
    connect(&myserver, &MyTcpServer::receiveAnswerGame, &match, &Game::receiveAnswerGame);
    connect(&myserver, &MyTcpServer::receiveShotAnswer, &match, &Game::receiveShotAnswer);
    connect(&myserver, &MyTcpServer::receiveGroupId, &match, &Game::receiveGroupID);

    connect(&match, &Game::sendParameter, &myserver, &MyTcpServer::sendParameter);
    connect(&match, &Game::sendGameStart, &myserver, &MyTcpServer::sendGameStart);
    connect(&match, &Game::sendShot, &myserver, &MyTcpServer::sendShot);
    connect(&match, &Game::sendAnswerGame, &myserver, &MyTcpServer::sendAnswerGame);
    connect(&match, &Game::sendShotAnswer, &myserver, &MyTcpServer::sendShotAnswer);

    // gui <-> network
    connect(&myserver, &MyTcpServer::gotClient, &gui, &Gui::foundClient);
    connect(&gui, &Gui::disconnectServer, &myserver, &MyTcpServer::disconnectNow);
    connect(&gui, &Gui::openServer, &myserver, &MyTcpServer::initServer);
    //chat gui -> network
    connect(&gui, &Gui::giveChat, &myserver, &MyTcpServer::sendChat);
    connect(&myserver, &MyTcpServer::receiveChat, &gui, &Gui::getChat);

}

void Control::setClient()
{
    // logic <-> network
    connect(&myclient, &MyClient::receiveParameter, &match, &Game::receiveParameter);
    connect(&myclient, &MyClient::receiveGameStart, &match, &Game::receiveGameStart);
    connect(&myclient, &MyClient::receiveShot, &match, &Game::receiveShot);
    connect(&myclient, &MyClient::receiveShotAnswer, &match, &Game::receiveShotAnswer);
    connect(&myclient, &MyClient::receiveAnswerGame, &match, &Game::receiveAnswerGame);
    connect(&myclient, &MyClient::receiveIdentificationGroup, &match, &Game::receiveGroupID);

    connect(&match, &Game::sendGameStart, &myclient, &MyClient::sendGameStart);
    connect(&match, &Game::sendShot, &myclient, &MyClient::sendShot);
    connect(&match, &Game::sendAnswerGame, &myclient, &MyClient::sendAnswerGame);
    connect(&match, &Game::sendShotAnswer, &myclient, &MyClient::sendShotAnswer);

    // gui <-> network
    connect(&gui, &Gui::connectClient, &myclient, &MyClient::ConnectHost);
    connect(&myclient, &MyClient::gotServer, &gui, &Gui::foundServer);
    connect(&myclient, &MyClient::gotServer, &myclient, &MyClient::sendIdentificationGroup);
    connect(&gui, &Gui::disconnectClient, &myclient, &MyClient::disconnectNow);
    //gui -> network
    connect(&gui, &Gui::giveChat, &myclient, &MyClient::sendChat);
    connect(&myclient, &MyClient::receiveChat, &gui, &Gui::getChat);

}
