/*
-- SOURCE FILE: mainwindow.cpp
--
-- PROGRAM: Pelican Chat Program
--
-- FUNCTIONS:
-- explicit MainWindow(QWidget *parent = 0);
-- ~MainWindow();
-- void on_action_Leave_Server_triggered();
-- void on_action_Join_Server_triggered();
--
-- DATE: March 13, 2011
--
-- REVISIONS: (Date and Description)
--
-- DESIGNER: Luke Queenan
--           Joel Stewart
--
-- PROGRAMMER: Luke Queenan
--             Joel Stewart
--
-- NOTES:
-- This file contains the information for the chat client program. All
-- interactions are done though this window, which includes send and receiving
-- messages, and connecting and disconnecting from the server.
*/

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "../network/network.h"

/*
-- FUNCTION: MainWindow
--
-- DATE: March 13, 2011
--
-- REVISIONS: (Date and Description)
--
-- DESIGNER: Qt
--
-- PROGRAMMER: Qt
--
-- INTERFACE: explicit MainWindow(QWidget *parent = 0);
--
-- RETURNS:
--
-- NOTES:
-- This is the constructor for the main window of the chat client.
*/
MainWindow::MainWindow(QWidget *parent) :
        QMainWindow(parent),
        ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    statusBarText_ = new QLabel(this);
    statusBar()->addWidget(statusBarText_);
    setStatusBarText("Status: Disconnected");
}

/*
-- FUNCTION: ~MainWindow
--
-- DATE: March 13, 2011
--
-- REVISIONS: (Date and Description)
--
-- DESIGNER: Qt
--
-- PROGRAMMER: Qt
--
-- INTERFACE: ~MainWindow();
--
-- RETURNS:
--
-- NOTES:
-- This is the destructor for the main window of the chat client.
*/
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
    if (joinServer_.exec() == QDialog::Accepted)
    {
        serverIp_ = joinServer_.getIp();
        serverPort_ = joinServer_.getPort();
        myName_ = joinServer_.getName();
        // Attempt to connect to server here.
    }
    // Temporary message
    //setStatusBarText("Status: Connected to 000.000.000.000");
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
    setStatusBarText("Status: Disconnected");
}

/*
-- FUNCTION: on_action_Record_to_File_toggled
--
-- DATE: March 13, 2011
--
-- REVISIONS: (Date and Description)
--
-- DESIGNER: Luke Queenan
--
-- PROGRAMMER: Luke Queenan
--
-- INTERFACE: void MainWindow::on_action_Record_to_File_toggled(bool );
--
-- RETURNS: void
--
-- NOTES:
-- This is the event that is triggered when the menu item for saving messages is
-- activated. When this is true, new messages must be recorded to a log file
-- until the switch is toggled off.
*/
void MainWindow::on_action_Record_to_File_toggled(bool )
{
    // Start recording messages to the log file.
}

/*
-- FUNCTION: setStatusBarText
--
-- DATE: March 14, 2011
--
-- REVISIONS: (Date and Description)
--
-- DESIGNER: Luke Queenan
--
-- PROGRAMMER: Luke Queenan
--
-- INTERFACE: void MainWindow::setStatusBarText(const QString text)
--
-- RETURNS: void
--
-- NOTES:
-- This function will set the text on the status bar to the provided string.
*/
void MainWindow::setStatusBarText(const QString text)
{
    statusBarText_->setText(text);
}

