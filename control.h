/*******************************************************************************************************************//**
 *	@file		control.h
 *  @brief		This file holds the needed definitions to use the Control class
 *  @version 	V1.0
 *  @date		22.03.2018
 *	@author		Henry He (Student @ TUM)
 **********************************************************************************************************************/

#ifndef CONTROL_H
#define CONTROL_H

/********************************************//**
 * Includes
 ***********************************************/
#include <QCoreApplication>
#include "game.hpp"
#include "mytcpserver.h"
#include "myclient.h"
#include "gui.h"

/**
 * @brief The Control class
 *
 * The Control class is friend of all underlying classes and acts as
 * the general controller unit of the game. It coordinates the communication
 * between the logic, gui and network module.
 */
class Control : public QObject
{
    Q_OBJECT /// Needed for signals and slots
public:
    /**
     * @brief Control constructor
     * @param parent
     */
    explicit Control(QObject *parent = 0);

    /**
     * @brief creates an instance of Game containing the logic module
     */
    Game match;
    MyTcpServer myserver;
    MyClient myclient;

    /**
     * @brief creates an instance of Gui containing the window
     */
    Gui gui;

    /**
     * @brief connects every signal and slot between gui and match
     *
     * connectGui is called from Control's constructor.
     */
    void connectGui();

    /**
     * @brief starts the game
     */
    void start();

signals:

public slots:
    /**
     * @brief connects every signal and slot between myserver and match
     */
    void setServer();

    /**
     * @brief connects every signal and slot between myclient and match
     */
    void setClient();
};

#endif // CONTROL_H
