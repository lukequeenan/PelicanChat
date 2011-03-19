#include "listenthread.h"
#include "../network/network.h"
#include <stdlib.h>

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

void ListenThread::setSocket(int *socket)
{
    mySocket_ = socket;
}
