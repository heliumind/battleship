#include <QApplication>
#include "control.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Control controller;

    controller.start();

    // controller.myserver.receiveData();

    return a.exec();
}
