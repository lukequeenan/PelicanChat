/*
-- SOURCE FILE: server.c
--
-- PROGRAM: Pelican Chat Program
--
-- FUNCTIONS:
-- void server (int port, int maxClients);
-- void initializeServer (int *listenSocket, int *port);
-- int processMessage(int clientIndex, int clients[], int numberOfClients);
-- static void systemFatal (const char*);
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
-- This file contains the server functionality of the program. This includes
-- the list of connected clients, all open connections, and the logic of
-- accepting new clients and passing on messages.
*/

#include <string.h>

#include "server.h"
#include "../network/network.h"

#define FREE -1
#define TRUE 1
#define BUFFER_LENGTH 160
#define JOIN_MESSAGE 1
#define TEXT_MESSAGE 2
#define REQUEST_LIST_MESSAGE 3

typedef struct
{
    char name[16];
    char ip[16];
} clientInfo;

void initializeServer (int *listenSocket, int *port);
int processMessage(int clientIndex, int clients[], int numberOfClients);
static void systemFatal (const char*);

/*
-- FUNCTION: server
--
-- DATE: March 12, 2011
--
-- REVISIONS: (Date and Description)
--
-- DESIGNER: Luke Queenan
--           Richard Stevens
--           Aman Abdulla
--
-- PROGRAMMER: Luke Queenan
--
-- INTERFACE: void server (int port, int maxClients);
--
-- RETURNS: void
--
-- NOTES:
-- This is the main function of the server application. It calls functions to
-- setup the server, then enters an infinite loop waiting for connections or
-- messages from clients. The waiting is done with select. When clients join
-- the server, they are added to the list of clients, and when messages are
-- received, they are passed on to all the other clients in the list.
*/
void server (int port, int maxClients)
{
    int listenSocket = 0;
    int clientSocket = 0;
    int maxFileDescriptor = 0;
    int selectReturn = 0;
    int index = 0;
    int clientIndex = 0;
    int clients[maxClients];
    clientInfo connectedClients[maxClients];
    fd_set availableFileDescriptors;
    fd_set fileDescriptorSet;
    
    // Set up server
    initializeServer(&listenSocket, &port);
    
    // Set the limit for file descriptor to select on
    maxFileDescriptor = listenSocket;
    clientIndex = FREE;
    
    // Initialize the array of clients and client info
    for (index = 0; index < maxClients; index++)
    {
        clients[index] = FREE;
        strcpy(connectedClients[index].name, "N/A\0");
        strcpy(connectedClients[index].ip, "000.000.000.000\0");
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
                if (processMessage(index, &clients[0], clientIndex) == -1)
                {
                    if (closeSocket(&clientSocket) == -1)
                    {
                        systemFatal("Cannot Close Socket!");
                    }
                    FD_CLR(clientSocket, &fileDescriptorSet);
                    clients[clientIndex] = FREE;
                }
            }
            
            // See if there are any more clients to check
            if (--selectReturn <= 0)
            {
                break;
            }
        }
    }
}

/*
-- FUNCTION: initializeServer
--
-- DATE: March 13, 2011
--
-- REVISIONS: (Date and Description)
--
-- DESIGNER: Luke Queenan
--
-- PROGRAMMER: Luke Queenan
--
-- INTERFACE: int processMessage(int, int*, int);
--
-- RETURNS: -1 if the client disconnected or 1 if successful
--
-- NOTES:
-- This function is called when one of the clients has a message to send out
-- through the server. The message is retrieved from the client and sent out to
-- all other connected clients. If the client disconnected, the function returns
-- -1, otherwise 1 after the message has been passed on.
*/
int processMessage(int clientIndex, int clients[], int numberOfClients)
{
    char *buffer = (char*)malloc(sizeof(char) * BUFFER_LENGTH);
    int bytesRead = 0;
    int count = 0;
    
    // Read message
    bytesRead = readData(&(clients[clientIndex]), &(*buffer), BUFFER_LENGTH);
    
    // Check if client disconnected
    if (bytesRead == 0)
    {
        return -1;
    }
    
    // Check for type of message
    switch ((int)buffer[0])
    {
    case JOIN_MESSAGE:
        // Update client list with name
        break;
    case TEXT_MESSAGE:
        // Pass the message on to other clients
        break;
    case REQUEST_LIST_MESSAGE:
        // Send back the list of connect clients
        break;
    default:
        // If the message type is not recognized, disconnect the client
        return -1;
    }
    
    // Send message
    for (count = 0; count < numberOfClients; count++)
    {
        if (clients[count] > 0 && clients[count] != clients[clientIndex])
        {
            sendData(&(clients[count]), &(*buffer), BUFFER_LENGTH);
        }
    }

    return 1;
}

/*
-- FUNCTION: initializeServer
--
-- DATE: March 12, 2011
--
-- REVISIONS: (Date and Description)
--
-- DESIGNER: Luke Queenan
--
-- PROGRAMMER: Luke Queenan
--
-- INTERFACE: void initializeServer(int *listenSocket, int *port);
--
-- RETURNS: void
--
-- NOTES:
-- This function sets up the required server connections, such as creating a
-- socket, setting the socket to reuse mode, binding it to an address, and
-- setting it to listen.
*/
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

/*
-- FUNCTION: systemFatal
--
-- DATE: March 12, 2011
--
-- REVISIONS: (Date and Description)
--
-- DESIGNER: Aman Abdulla
--
-- PROGRAMMER: Luke Queenan
--
-- INTERFACE: static void systemFatal(const char* message);
--
-- RETURNS: void
--
-- NOTES:
-- This function displays an error message and shuts down the program.
*/
static void systemFatal(const char* message)
{
    perror(message);
    exit(EXIT_FAILURE);
}

