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

    // logic -> gui
    connect(&match, &Game::updateField, &gui, &Gui::getUpdateField);
}

void Control::start()
{
    gui.show();
}

