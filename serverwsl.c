#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080
#define BUFFER_SIZE 1024

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    char buffer[BUFFER_SIZE] = {0};
    char *response = "Hello from TCP Server!";

    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("Socket creation failed.\n");
        return 1;
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        printf("Bind failed.\n");
        close(server_fd);
        return 1;
    }

    listen(server_fd, 3);
    printf("TCP Server listening on port %d...\n", PORT);

    new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t *)&addrlen);
    if (new_socket < 0) {
        printf("Accept failed.\n");
        close(server_fd);
        return 1;
    }

    recv(new_socket, buffer, BUFFER_SIZE, 0);
    printf("Client says: %s\n", buffer);

    send(new_socket, response, strlen(response), 0);
    printf("Response sent to client.\n");

    close(new_socket);
    close(server_fd);

    return 0;
}
