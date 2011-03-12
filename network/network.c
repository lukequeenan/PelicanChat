int tcpSocket()
{
    return socket(AF_INET, SOCKSTREAM, 0);
}

int setReuse(int *socket)
{
    int arg = 1;
    return setsockopt(*socket, SOL_SOCKET, SO_REUSEADDR, &arg, sizeof(arg));
}
