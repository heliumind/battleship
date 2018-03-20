#ifndef CONTROL_H
#define CONTROL_H
#include <QCoreApplication>
#include "game.hpp"
#include "mytcpserver.h"
#include "myclient.h"
#include "gui.h"

class Control : public QObject
{
    Q_OBJECT
public:
    explicit Control(QObject *parent = 0);
    Game match;
    MyTcpServer myserver;
    MyClient myclient;
    Gui gui;
    void connectGui();
    void start();

signals:

public slots:
    void setServer();
    void setClient();
};

#endif // CONTROL_H
