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

#include <stdlib.h>
#include <stdio.h>

#include "../network/network.h"

#define EMPTY -1
#define TRUE 1

void server (int port, int maxClients);
void initializeServer(int *listenSocket, int *port);
static void systemFatal(const char*);

void server (int port, int maxClients)
{
    int listenSocket = 0;
    int maxFileDescriptor = 0;
    int selectReturn = 0;
    int count = 0;
    int selectReady = 0;
    int clients[FD_SETSIZE];
    fd_set returnFileDescriptorSet;
    fd_set fileDescriptorSet;
    
    // Set up server
    initializeServer(&listenSocket, &port);
    
    // Set the limit for file descriptor to select on
    maxFileDescriptor = listenSocket;
    
    // Initialize the array of clients
    for (count = 0; count < FD_SETSIZE; count++)
    {
        clients[count] = EMPTY;
    }
    FD_ZERO(&fileDescriptorSet);
    FD_SET(listenSocket, &fileDescriptorSet);
    
    while (TRUE)
    {
        fileDescriptorSet = fileDescriptorSet;
        selectReady = select(maxFileDescriptor + 1, &returnFileDescriptorSet,
                                NULL, NULL, NULL);
    }
    
}

void initializeServer(int *listenSocket, int *port)
{
    // Create a TCP socket
    if ((*listenSocket = tcpSocket()) == -1)
    {
        systemFatal("Cannot Create Socket!");
    }
    
    // Allow the socket to be reused immediately after exit
    if (setReuse(&(*listenSocket)) == -1)
    {
        systemFatal("Cannot Set Socket To Reuse");
    }
    
    // Bind an address to the socket
    if (bindAddress(&(*port), &(*listenSocket)) == -1)
    {
        systemFatal("Cannot Bind Address To Socket");
    }
    
    // Set the socket to listen for connections
    if (setListen(&(*listenSocket)) == -1)
    {
        systemFatal("Cannot Listen On Socket");
    }
}

static void systemFatal(const char* message)
{
    perror(message);
    exit(EXIT_FAILURE);
}

