// # Jack Holkeboer
// # Oregon State University
// # cs372
// # Project 1
// # holkeboj@onid.oregonstate.edu
// Based on: http://www.tutorialspoint.com/unix_sockets/socket_server_example.htm

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>

// using namespace std;


int main(int argc, char *argv[]) {
    int port, initial_sock, connected_sock, backlog = 5;
    char buffer[500];
    struct sockaddr_in server_address, client_address;
    socklen_t client_length;
    
    if (argc != 2) {
        printf("Please provide a port number as an argument.\n");
        exit(1);
    } else {
        port = atoi(argv[1]);
        if ((port < 1024) || (port > 65535)) {
            printf("Please enter a port number between 1024 and 65535.\n");
            exit(1);
        }
        printf("Welcome to the socketChat server.\n");
    }
    
    // Create Socket
    initial_sock = socket(AF_INET, SOCK_STREAM, 0);
    if (initial_sock < 0) {
        printf("Could not open socket. Exiting.\n");
        exit(1);
    }

    bzero((char*) &server_address, sizeof(server_address));

    // Specify address type
    server_address.sin_family = AF_INET;
    
    // Whatever IP this program is running on will be assigned
    server_address.sin_addr.s_addr = INADDR_ANY;
    
    // Attach port number, convert to network btye order
    server_address.sin_port = htons(port);
    
    // Bind to socket.  This socket will accept initial conenctions from clients
    if (bind(initial_sock, (struct sockaddr *) &server_address, sizeof(server_address)) < 0) {
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