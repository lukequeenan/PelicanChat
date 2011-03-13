// Includes
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <unistd.h>
#include <strings.h>

#include "network.h"

#define MAX_QUEUE 10

int tcpSocket()
{
    return socket(AF_INET, SOCK_STREAM, 0);
}

int setReuse(int *socket)
{
    socklen_t optlen = 1;
    return setsockopt(*socket, SOL_SOCKET, SO_REUSEADDR, &optlen, 
                        sizeof(optlen));
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
    socklen_t addrlen = sizeof(clientAddress);
    return accept(*listenSocket, (struct sockaddr *) &clientAddress, &addrlen);
}

int readData(int *socket, char *buffer, int bytesToRead)
{
    int bytesRead = 0;
    while ((bytesRead = read(*socket, buffer, bytesToRead)) > 0)
    {
        buffer += bytesRead;
        bytesToRead -= bytesRead;
    }
    return bytesRead;
}

int sendData(int *socket, char *buffer, int bytesToSend)
{
    return write(*socket, buffer, bytesToSend);
}

int closeSocket(int *socket)
{
    return close(*socket);
}

