// # Jack Holkeboer
// # Oregon State University
// # cs372
// # Project 1
// # holkeboj@onid.oregonstate.edu
// Based on: http://www.tutorialspoint.com/unix_sockets/socket_server_example.htm

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <signal.h>

void signal_handler(int sig) {
    if (sig == SIGINT) {
        printf("\nReceived SIGINT, terminating.\n");
        exit(1);
    }
    if (sig == SIGKILL) {
        printf("\nReceived SIGKILL, terminating.\n");
        exit(1);
    }
}

int main(int argc, char *argv[]) {
    int port, initial_sock, connected_sock, backlog = 5, 
        stop = 0, reuse = 1, first = 1, i = 0;
    char buffer[512];
    char message[500];
    struct sockaddr_in server_address, client_address;
    socklen_t client_length;
    char char_handle[12];
    char quit[6] = "\\quit";
    
    // handle sigint and sigkill
    signal(SIGINT, signal_handler);
    signal(SIGKILL, signal_handler);
    
    // get port number from argument
    if (argc != 2) {
        printf("Please provide a port number as an argument.\n");
        exit(1);
    } else {
        port = atoi(argv[1]);
        if ((port < 20000) || (port > 65535)) {
            printf("Please enter a port number between 20000 and 65535.\n");
            exit(1);
        }
        printf("Welcome to the socketChat server.\n");
    }
    
    // Get Handle
    printf("Please enter your handle: ");
    fgets(char_handle,sizeof(char) * 12, stdin);
    // remove newline from input
    char_handle[strcspn(char_handle, "\n")] = 0;
    printf("Your handle is %s\n", char_handle);

    // start server
    while(1) {
        // reset connection close flag
        stop = 0;

        if (first) {
            // Create Socket
            initial_sock = socket(AF_INET, SOCK_STREAM, 0);
            if (initial_sock < 0) {
                printf("Could not open socket. Exiting.\n");
                exit(1);
            }

            // clear server address
            bzero((char*) &server_address, sizeof(server_address));

            // Specify address type
            server_address.sin_family = AF_INET;
            
            // Whatever IP this program is running on will be assigned
            server_address.sin_addr.s_addr = INADDR_ANY;
            
            // Attach port number, convert to network btye order
            server_address.sin_port = htons(port);

            // Make socket reusable
            setsockopt(initial_sock, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(int));

            printf("Waiting on port %d ... \n",port);

            // Bind to socket.  This socket will accept initial conenctions from clients
            if (bind(initial_sock, (struct sockaddr *) &server_address, sizeof(server_address)) < 0) {
                printf("Could not bind to socket. Exiting.\n");
            }

            // Listen for connections
            listen(initial_sock, backlog);

        } else {
            printf("Waiting for a new client to connect...\n");
        }

        // accept connection
        connected_sock = accept(initial_sock, (struct sockaddr *) &client_address, &client_length);
        if (connected_sock < 0) {
            printf("Connection Failed. Exiting.\n");
            exit(1);        
        }
        
        printf("Accepted connection from client.\n");
        
        while (!stop) {
            // clear buffer
            bzero(buffer,512);
            printf("[waiting for response...]\n");
            
            // read from socket
            if (read(connected_sock,buffer,512) < 0) {
                printf("Could not read from socket.\n");
            } else {
                // check if \quit was received from client
                if (strcmp(buffer, quit) == 0) {
                    printf("Client closed the connection.\n");
                    shutdown(connected_sock,2);
                    close(connected_sock);
                    
                    // set control flags
                    stop = 1;
                    first = 0;
                } else {
                    // Print received message
                    printf("%s\n", buffer);

                    // send message
                    printf("%s> ", char_handle);
                    bzero(buffer,512);
                    bzero(message,500);

                    // get user message input
                    std::cin.getline(message, 500);
                    
                    // copy handle and message to buffer
                    i = 0;
                    while (char_handle[i] != '\0') {
                        buffer[i] = char_handle[i];
                        i++;
                    }
                    buffer[i] = '>';
                    i++;
                    buffer[i] = ' ';
                    i++;
                    strcpy(buffer + (i * sizeof(int)), message);
                    
                    // check for quit signal
                    if (strcmp(message, quit) == 0) {
                        printf("Closing the connection.\n");
                        write(connected_sock,quit,6);
                        shutdown(connected_sock,2);
                        close(connected_sock);
                        stop = 1;
                        first = 0;
                    } else{
                        // write message to socket
                        if ((write(connected_sock,buffer, 512) < 0)) {
                            printf("Could not send to socket.\n");
                        }
                    }
                }
            }
        }
    }

    return 0;
}