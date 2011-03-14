#ifndef NETWORK_H
#define NETWORK_H

// Function Prototypes
#ifdef __cplusplus
extern "C" {
#endif
int tcpSocket();
int setReuse(int* socket);
int bindAddress(int *port, int *socket);
int setListen(int *socket);
int acceptConnection(int *listenSocket);
int readData(int *socket, char *buffer, int bytesToRead);
int sendData(int *socket, char *buffer, int bytesToSend);
int closeSocket(int *socket);
#ifdef __cplusplus
}
#endif
#endif
