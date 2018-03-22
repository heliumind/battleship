/*******************************************************************************************************************//**
 *	@file		button.h
 *  @brief		This file holds the two generated button fields.
 *  @version 	V1.0
 *  @date		22.03.2018
 *	@author		Niklas Schwarz (Student @ TUM)
 **********************************************************************************************************************/

#ifndef BUTTON_H
#define BUTTON_H

/********************************************//**
 * Includes
 ***********************************************/
#include <QWidget>
#include <QMainWindow>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QLabel>
#include <QString>
#include <QTcpSocket>
#include <QTextStream>
#include <iostream>
#include <QtGui>
#include <vector>
#include <QDebug>
#include <QCoreApplication>

/**
 * @brief The Button class
 */
class Button : public QPushButton
{
    Q_OBJECT

public:
    explicit Button( int x, int y);


private:
    /**
     * @brief Coordinate of button
     */
    std::pair<int, int> _point;

signals:
    /**
    * @brief Sending out coordinates of button clicked
    *
    * @param std::pair<int,int> x and y coordinates of the button
    */
    void clickedPos(std::pair<int, int>);

public slots:
    /**
    * @brief Getting a click of one button
    */
    void forwardClick();
};

#endif // BUTTON_H
