#include "network.h"

#define MAX_QUEUE 10

int tcpSocket()
{
    return socket(AF_INET, SOCK_STREAM, 0);
}

int setReuse(int *socket)
{
    int arg = 1;
    return setsockopt(*socket, SOL_SOCKET, SO_REUSEADDR, &arg, sizeof(arg));
}

int bindAddress(int *port, int *socket)
{
    struct sockaddr_in address;
    
    bzero((char *)&address, sizeof(struct sockaddr_in));
    address.sin_family = AF_INET;
    address.sin_port = htons(*port);
    address.sin_addr.s_addr = htonl(INADDR_ANY);

    return bind(*socket, (struct sockaddr *)&address, sizeof(address));
}

int setListen(int *socket)
{
    return listen(*socket, MAX_QUEUE);
}

int acceptConnection(int *listenSocket)
{
    struct sockaddr_in clientAddress;
    int arg = sizeof(clientAddress);
    return accept(*listenSocket, (struct sockaddr *) &clientAddress, &arg);
}
