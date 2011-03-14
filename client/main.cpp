#include <QtGui/QApplication>
#include "mainwindow.h"
#include "../network/network.h"
//#include "../network/network.c"

int main(int argc, char *argv[])
{
    int i = tcpSocket();
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
