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
    void connectAll();
    void start();

signals:

public slots:
};

#endif // CONTROL_H
