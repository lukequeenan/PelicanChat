/*
-- SOURCE FILE: server.c
--
-- PROGRAM: Pelican Chat Program
--
-- FUNCTIONS:
-- void server (int port, int maxClients);
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

#include "server.h"
#include "../network/network.h"

#define FREE -1
#define TRUE 1

void initializeServer (int *listenSocket, int *port);
static void systemFatal (const char*);

void server (int port, int maxClients)
{
    int listenSocket = 0;
    int clientSocket = 0;
    int maxFileDescriptor = 0;
    int selectReturn = 0;
    int index = 0;
    int clientIndex = 0;
    int clients[maxClients];
    fd_set availableFileDescriptors;
    fd_set fileDescriptorSet;
    
    // Set up server
    initializeServer(&listenSocket, &port);
    
    // Set the limit for file descriptor to select on
    maxFileDescriptor = listenSocket;
    clientIndex = FREE;
    
    // Initialize the array of clients
    for (index = 0; index < maxClients; index++)
    {
        clients[index] = FREE;
    }
    FD_ZERO(&fileDescriptorSet);
    FD_SET(listenSocket, &fileDescriptorSet);
    
    while (TRUE)
    {
        availableFileDescriptors = fileDescriptorSet;
        selectReturn = select(maxFileDescriptor + 1, &availableFileDescriptors,
                                NULL, NULL, NULL);
        // Check for a new client connection
        if (FD_ISSET(listenSocket, &availableFileDescriptors))
        {
            if ((clientSocket = acceptConnection(&listenSocket)) == -1)
            {
                systemFatal("Unable To Accept Connection");
            }
            for (index = 0; index < maxClients; index++)
            {
                if (clients[index] < 0)
                {
                    clients[index] = clientSocket;
                    break;
                }
            }
            
            if (index == maxClients)
            {
                /* Unable to accept another client, should display error, but
                 * there is no need to shut down. */
                // See if we need to check clients for data
                if (--selectReturn <= 0)
                {
                    continue;
                }
            }
            else
            {
                // Add new client to file descriptor set and adjust variables
                FD_SET (clientSocket, &fileDescriptorSet);
                if (clientSocket > maxFileDescriptor)
                {
                    maxFileDescriptor = clientSocket;
                }
                if (index > clientIndex)
                {
                    clientIndex = index;
                }
                // See if we need to check clients for data
                if (--selectReturn <= 0)
                {
                    continue;
                }
            }
        }
        
        // Check for data from clients
        for (index = 0; index <= clientIndex; index++)
        {
            // If the socket is free, continue through the loop
            if ((clientSocket = clients[index]) < 0)
            {
                continue;
            }
            
            // Check to see if the this is the right client
            if (FD_ISSET(clientSocket, &availableFileDescriptors))
            {
                
            }
        }
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

