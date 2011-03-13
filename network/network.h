#ifndef NETWORK_H
#define NETWORK_H
// Includes
#include <sys/socket.h>
#include <sys/types.h>
// Function Prototypes
int tcpSocket();
int setReuse(int*);
#endif
