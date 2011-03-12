/*
-- SOURCE FILE: server.c
--
-- PROGRAM: Pelican Chat Program
--
-- FUNCTIONS:
-- void server(int port, int maxClients);
--
-- DATE: March 12, 2011
--
-- REVISIONS: (Date and Description)
--
-- DESIGNER: Luke Queenan
--
-- PROGRAMMER: Luke Queenan
--
-- NOTES:
--
*/
#include <sys/types.h>
#include "../network/connect.h"

void server (int port, int maxClients);
static void systemFatal(const char*);

void server (int port, int maxClients)
{
    int listenSocket = 0;
    int clients[FD_SETSIZE];
    // Call wrapper functions for setting up connection
    if ((listenSocket = tcpSocket) == -1)
    {
        systemFatal("Cannot Create Socket!");
    }
    if (setReuse(&listenSocket) == -1)
    {
        systemFatal("Cannot Set Socket To Reuse");
    }
}

static void systemFatal(const char* message)
{
    perror(message);
    exit(EXIT_FAILURE);
}

