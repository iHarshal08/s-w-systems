/*
===========================================================================================================================
Name : 33b.c
Author : Harshal Purohit
Description : Write a program to communicate between two machines using socket.
Date: 18th Sept, 2024.
===========================================================================================================================
*/

// client.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080

int main() {
    int sock = 0;
    struct sockaddr_in serv_addr;
    char buffer[1024] = {0};

    // Create socket
    sock = socket(AF_INET, SOCK_STREAM, 0);

    // Set up server address
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    // Convert address to binary form and connect
    inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr);

    connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr));

    // Read message from server
    read(sock, buffer, sizeof(buffer));
    printf("Message from server: %s\n", buffer);

    close(sock);
    return 0;
}
