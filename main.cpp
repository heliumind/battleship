#include <QApplication>
#include "control.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Control controller;

    controller.start();

    return a.exec();
}
