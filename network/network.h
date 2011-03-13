#ifndef NETWORK_H
#define NETWORK_H

// Includes
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <strings.h>

// Function Prototypes
int tcpSocket();
int setReuse(int* socket);
int bindAddress(int *port, int *socket);
int setListen(int *socket);
int acceptConnection(int *listenSocket);

#endif
