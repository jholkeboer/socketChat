// # Jack Holkeboer
// # Oregon State University
// # cs372
// # Project 1
// # holkeboj@onid.oregonstate.edu

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>

using namespace std;

int main(int argc, char *argv[]) {
    // Get port number from client
    printf("Welcome to the socketChat server.\nEnter a port number: ");
    int port;
    cin >> port;
    if (cin.fail()) {
        printf("Invalid port number. Exiting.\n");
        exit(1);
    }
    
    //cout << "Port " << port << "/n";
    printf("\nWaiting on port %d ... ",port);
    return 0;
}