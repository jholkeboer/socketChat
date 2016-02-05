// # Jack Holkeboer
// # Oregon State University
// # cs372
// # Project 1
// # holkeboj@onid.oregonstate.edu
// Based on: http://www.linuxhowtos.org/data/6/server.c

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>

using namespace std;


int main(int argc, char *argv[]) {
    int port, initial_sock, connected_sock, backlog = 5;
    char buffer[500];
    struct sockaddr_in server_address, client_address;
    socklen_t client_length;
    
    // Get port number from client
    printf("Welcome to the socketChat server.\nEnter a port number: ");
    int port;
    cin >> port;
    if (cin.fail()) {
        printf("Invalid port number. Exiting.\n");
        exit(1);
    }
    
    // Create Socket
    initial_sock = socket(AF_INET, SOCK_STREAM, 0);
    if (initial_sock < 0) {
        printf("Could not open socket. Exiting.\n");
        exit(1);
    }

    // Specify address type
    server_address.sin_family = AF_INET;
    
    // Whatever IP this program is running on will be assigned
    server_address.sin_addr.s_adds = INADDR_ANY;
    
    // Attach port number, convert to network btye order
    server_address.sin_port = htons(port);
    
    // Bind to socket.  This socket will accept initial conenctions from clients
    if (bind(initial_sock, (struct sockaddr *) server_address, sizeof(server_address)) < 0) {
        printf("Could not bind to socket. Exiting.\n");
    }
    
    while(1) {
        // Listen for connections
        listen(initial_sock, backlog);
        printf("\nWaiting on port %d ... s",port);    
        
        // accept connections
        connected_sock = accept(initial_sock, (struct sockaddr *) &client_address, &client_length);
        if (connected_sock < 0) {
            printf("Connection Failed. Exiting.\n");
            exit(1);        
        }
        
    }

    
    return 0;
}