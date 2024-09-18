/*
===========================================================================================================================
Name : 33a.c
Author : Harshal Purohit
Description : Write a program to communicate between two machines using socket.
Date: 18th Sept, 2024.
===========================================================================================================================
*/

// server.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    char *message = "Hello from server!";

    // Create socket
    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    
    // Bind to the address and port
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    bind(server_fd, (struct sockaddr *)&address, sizeof(address));

    // Listen for incoming connections
    listen(server_fd, 3);

    printf("Server is listening on port %d...\n", PORT);

    // Accept a client connection
    new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t *)&addrlen);
    
    // Send message to the client
    send(new_socket, message, strlen(message), 0);
    printf("Message sent to client\n");

    close(new_socket);
    close(server_fd);
    return 0;
}


