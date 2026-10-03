#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 12345

int isPalindrome(char str[]) {
    int i = 0;
    int j = strlen(str) - 1;

    while (i < j) {
        if (str[i] != str[j])
            return 0;
        i++;
        j--;
    }

    return 1;
}

int main() {
    int server_fd, client_fd;
    struct sockaddr_in address;
    char buffer[1024];

    // Create socket
    server_fd = socket(AF_INET, SOCK_STREAM, 0);

    if (server_fd < 0) {
        perror("Socket creation failed");
        exit(1);
    }

    // Server address
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    // Bind socket
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("Bind failed");
        exit(1);
    }

    // Listen
    listen(server_fd, 5);

    printf("Server waiting for connection...\n");

    // Accept client
    client_fd = accept(server_fd, NULL, NULL);

    if (client_fd < 0) {
        perror("Accept failed");
        exit(1);
    }

    printf("Client connected.\n");

    // Receive string
    memset(buffer, 0, sizeof(buffer));
    read(client_fd, buffer, sizeof(buffer));

    printf("Received: %s\n", buffer);

    // Check palindrome
    if (isPalindrome(buffer))
        send(client_fd, "Palindrome", 11, 0);
    else
        send(client_fd, "Not Palindrome", 15, 0);

    close(client_fd);
    close(server_fd);

    return 0;
}
