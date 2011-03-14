#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "../network/network.h"

MainWindow::MainWindow(QWidget *parent) :
        QMainWindow(parent),
        ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_action_Join_Server_triggered()
{
    joinServer_.show();
}
