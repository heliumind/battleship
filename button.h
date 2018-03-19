#ifndef BUTTON_H
#define BUTTON_H

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

class Button : public QPushButton
{
    Q_OBJECT

public:
    explicit Button( int x, int y);


private:
    std::pair<int, int> _point;
    bool _used;

signals:
    void clickedPos(std::pair<int, int>);

public slots:
    void forwardClick();
};

#endif // BUTTON_H
