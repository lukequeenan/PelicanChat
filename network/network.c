#include "network.h"

int tcpSocket()
{
    return socket(AF_INET, SOCK_STREAM, 0);
}

int setReuse(int *socket)
{
    int arg = 1;
    return setsockopt(*socket, SOL_SOCKET, SO_REUSEADDR, &arg, sizeof(arg));
}
