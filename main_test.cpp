#include <QCoreApplication>
#include "mytcpserver.h"
#include "myclient.h"




int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    //test for a incoming signal of gui which setting was picked (server/client)
    int i=0;

    //select one mode
    if(i==1)
    {

        MyClient *myclient;
        myclient = new MyClient;
        myclient->ConnectHost();
    }
    if(i==0)
    {
        MyTcpServer *mytcpserver;

        mytcpserver = new MyTcpServer;
        //mytcpserver->newConnection();
    }


    //write test for disconnection-test
    //signal comes in exp. int i=2; => server or client should disconnect

    return a.exec();
}

