#ifndef NETWORK_H
#define NETWORK_H

// Function Prototypes
int tcpSocket();
int setReuse(int* socket);
int bindAddress(int *port, int *socket);
int setListen(int *socket);
int acceptConnection(int *listenSocket);
int readData(int *socket, char *buffer, int bytesToRead);
int sendData(int *socket, char *buffer, int bytesToSend);
int closeSocket(int *socket);

#endif
