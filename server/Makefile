# MakeFile for COMP 4981 Assignment Two

CC=gcc
CFLAGS=-W -Wall
NETWORKPATH=../network/

project: network.o server.o main.o
	$(CC) $(CFLAGS) main.o network.o server.o -o PelicanChatServer

clean:
	rm -f *.o *.bak ex

network.o: $(NETWORKPATH)network.c $(NETWORKPATH)network.h
	$(CC) $(CFLAGS) -O -c $(NETWORKPATH)network.c

server.o: server.c
	$(CC) $(CFLAGS) -O -c server.c

main.o: main.c
	$(CC) $(CFLAGS) -O -c main.c
