/*
-- SOURCE FILE: main.c
--
-- PROGRAM: Pelican Chat Program
--
-- FUNCTIONS:
-- int main(int argc , char *argv[]);
--
-- DATE: March 12, 2011
--
-- REVISIONS: (Date and Description)
--
-- DESIGNER: Luke Queenan
--
-- PROGRAMMER: Luke Queenan
--
-- NOTES:
-- This file contains main.cpp, which is the entry point of the server
-- application.
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "server.h"

#define DEFAULT_PORT 8929

int main(int argc, char **argv);

/*
-- FUNCTION: main
--
-- DATE: March 12, 2011
--
-- REVISIONS: (Date and Description)
--
-- DESIGNER: Luke Queenan
--
-- PROGRAMMER: Luke Queenan
--
-- INTERFACE: int main (int argc , char *argv[]);
--
-- RETURNS: 0 on successful completion of the main function
--
-- NOTES:
-- This is the main entry point for the program. It allows the user to specify a
-- port on the command line, otherwise it will use a default. After setting the
-- port, from either the user or the default, the program calls the server
-- function. You are also able to specify the maximum number of clients you
-- would like to support though command line arguments.
*/
int main (int argc, char **argv)
{
    // Initialize port and maxClients to default values in case of no user input
    int port = DEFAULT_PORT;
    int maxClients = FD_SETSIZE;
    int option = 0;

    // Parse command line paramters using getopt
    while ((option = getopt(argc, argv, "p:c:")) != -1)
    {
        switch (option)
        {
            case 'p':
                port = atoi(optarg);
                break;
            case 'c':
                maxClients = atoi(optarg);
                break;
            default:
                fprintf(stderr, "Usage: %s -p [port] -c [max clients]\n",
                        argv[0]);
                exit(1);
        }
    }

    // Start server
    server(port, maxClients);

    return 0;
}

