#include <QtGui/QApplication>
#include "mainwindow.h"
#include "../network/network.h"

int main(int argc, char *argv[])
{
    // Temporary function call for testing
    int i = tcpSocket();

    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
