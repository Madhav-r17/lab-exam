#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 12345

int main() {
    int sock;
    struct sockaddr_in server_address;
    char message[1024];
    char buffer[1024];

    // Create socket
    sock = socket(AF_INET, SOCK_STREAM, 0);

    if (sock < 0) {
        perror("Socket creation failed");
        exit(1);
    }

    // Server address
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(PORT);
    server_address.sin_addr.s_addr = inet_addr("127.0.0.1");

    // Connect to server
    if (connect(sock, (struct sockaddr *)&server_address,
                sizeof(server_address)) < 0) {
        perror("Connection failed");
        exit(1);
    }

    printf("Connected to server.\n");

    // Get input
    printf("Enter a string: ");
    scanf("%s", message);

    // Send to server
    send(sock, message, strlen(message), 0);

    // Receive result
    memset(buffer, 0, sizeof(buffer));
    read(sock, buffer, sizeof(buffer));

    printf("Server response: %s\n", buffer);

    close(sock);

    return 0;
}
