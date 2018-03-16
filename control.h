#ifndef CONTROL_H
#define CONTROL_H
#include <QCoreApplication>
#include "game.hpp"
#include "mytcpserver.h"

class Control : public QObject
{
    Q_OBJECT
public:
    explicit Control(QObject *parent = 0);
    Game match;
    MyTcpServer myserver;
    void connectAll();

signals:

public slots:
};

#endif // CONTROL_H
