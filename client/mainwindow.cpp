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

/*
-- FUNCTION: on_action_Join_Server_triggered
--
-- DATE: March 13, 2011
--
-- REVISIONS: (Date and Description)
--
-- DESIGNER: Luke Queenan
--
-- PROGRAMMER: Luke Queenan
--
-- INTERFACE: void MainWindow::on_action_Join_Server_triggered();
--
-- RETURNS: void
--
-- NOTES:
-- This is the event that is triggered when the menu item for joining a server
-- is selected. The function just shows the joinServer window.
*/
void MainWindow::on_action_Join_Server_triggered()
{
    joinServer_.show();
}

/*
-- FUNCTION: on_action_Leave_Server_triggered
--
-- DATE: March 13, 2011
--
-- REVISIONS: (Date and Description)
--
-- DESIGNER: Luke Queenan
--
-- PROGRAMMER: Luke Queenan
--
-- INTERFACE: void MainWindow::on_action_Leave_Server_triggered();
--
-- RETURNS: void
--
-- NOTES:
-- This is the event that is triggered when the menu item for leaving a server
-- is selected. The function calls the disconnect function on the opened socket.
*/
void MainWindow::on_action_Leave_Server_triggered()
{
    // Disconnect from server
}
