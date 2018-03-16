#include "control.h"

Control::Control(QObject *parent)
    : QObject(parent), match(Game()), myserver(MyTcpServer())
{
    connectAll();
}

void Control::connectAll()
{
    connect(&myserver, &MyTcpServer::messageSent, &match, &Game::receiveMessage);
}

