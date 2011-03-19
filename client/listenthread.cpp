/*
-- SOURCE FILE: listenThread.cpp
--
-- PROGRAM: Pelican Chat Program
--
-- FUNCTIONS:
-- void ListenThread::run();
-- void ListenThread::setSocket(int *socket);
--
-- DATE: March 19, 2011
--
-- REVISIONS: (Date and Description)
--
-- DESIGNER: Luke Queenan
--
-- PROGRAMMER: Luke Queenan
--
-- NOTES:
-- This file contains the thread functions for monitoring the socket for data.
*/

#include "listenthread.h"
#include "../network/network.h"
#include <stdlib.h>

/*
-- FUNCTION: run
--
-- DATE: March 19, 2011
--
-- REVISIONS: (Date and Description)
--
-- DESIGNER: Luke Queenan
--
-- PROGRAMMER: Luke Queenan
--
-- INTERFACE: void ListenThread::run();
--
-- RETURNS: void
--
-- NOTES:
-- This is the run function for the thread. It monitors the socket for data and
-- upon receiving a text message, sends it via a signal to the main program.
*/
void ListenThread::run()
{
    int bytesRead = 0;
    char *buffer = (char*)malloc(sizeof(char) * BUFFER_LENGTH);
    while(true) {
        // May need to change this to use select so that we can write
        bytesRead = readData(&(*mySocket_), &(*buffer), BUFFER_LENGTH);
        if(buffer[0] == TEXT_MESSAGE) {
            QString data(buffer + 1);
            emit ListenThread::textMessageReceived(data);
        }
    }
}

/*
-- FUNCTION: setSocket
--
-- DATE: March 13, 2011
--
-- REVISIONS: (Date and Description)
--
-- DESIGNER: Qt
--
-- PROGRAMMER: Qt
--
-- INTERFACE: void ListenThread::setSocket(int *socket);
--
-- RETURNS: void
--
-- NOTES:
-- This allows the calling program to set the socket this thread is to monitor.
*/
void ListenThread::setSocket(int *socket)
{
    mySocket_ = socket;
}
