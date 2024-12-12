#define _WIN32_WINNT 0x0601 // Para habilitar funciones modernas de WinSock
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h> // Para Sleep

#pragma comment(lib, "ws2_32.lib") // Enlaza la biblioteca de WinSock

#define PORT 23
#define BUFFER_SIZE 1024
#define USERNAME "admin"
#define PASSWORD "1234"

void handle_client(SOCKET client_socket) {
    char buffer[BUFFER_SIZE];
    char username[BUFFER_SIZE];
    char password[BUFFER_SIZE];
    const char *message = "Esto es una simulación Telnet";
    // Channel CC3
    // char buffer_data[] = {0x15, 0x26, 0x15, 0x2D, 0x14, 0x60, 0x41, 0x49, 0x50, 0x2D, 0x34, 0x39, 0x34, 0x20, 0x46, 0x69, 0x72, 0x6D, 0x77, 0x61, 0x72, 0x65, 0x20, 0x56, 0x65, 0x72, 0x15, 0x26, 0x15, 0x2D, 0x14, 0x60, 0x41, 0x70, 0x70, 0x3D, 0x42, 0x35, 0x20, 0x46, 0x50, 0x47, 0x41, 0x3D, 0x42, 0x35, 0x20, 0x42, 0x4C, 0x3D, 0x58, 0x35, 0x15, 0x26, 0x15, 0x2D, 0x14, 0x60, 0x33, 0x2D, 0x4C, 0x69, 0x6E, 0x65, 0x20, 0x52, 0x6F, 0x6C, 0x6C, 0x2D, 0x75, 0x70, 0x20, 0x43, 0x43, 0x33, 0x20, 0x20, 0x15, 0x26, 0x15, 0x2D, 0x14, 0x60, 0x4C, 0x69, 0x6E, 0x6B, 0x20, 0x45, 0x6C, 0x65, 0x63, 0x74, 0x72, 0x6F, 0x6E, 0x69, 0x63, 0x73, 0x20, 0x20, 0x20, 0x20, 0x15, 0x26, 0x15, 0x2D, 0x14, 0x60};

    // Channel CC1
    char buffer_data[] = {0x14, 0x26, 0x14, 0x26, 0x14, 0x2D, 0x14, 0x2D, 0x14, 0x60, 0x14, 0x60, 0x41, 0x70, 0x70, 0x3D, 0x42, 0x35, 0x20, 0x46, 0x50, 0x47, 0x41, 0x3D, 0x42, 0x35, 0x20, 0x42, 0x4C, 0x3D, 0x58, 0x35, 0x14, 0x26, 0x14, 0x26, 0x14, 0x2D, 0x14, 0x2D, 0x14, 0x60, 0x14, 0x60, 0x33, 0x2D, 0x4C, 0x69, 0x6E, 0x65, 0x20, 0x52, 0x6F, 0x6C, 0x6C, 0x2D, 0x75, 0x70, 0x20, 0x43, 0x43, 0x31, 0x20, 0x20, 0x14, 0x26, 0x14, 0x26, 0x14, 0x2D, 0x14, 0x2D, 0x14, 0x60, 0x14, 0x60, 0x4C, 0x69, 0x6E, 0x6B, 0x20, 0x45, 0x6C, 0x65, 0x63, 0x74, 0x72, 0x6F, 0x6E, 0x69, 0x63, 0x73, 0x20, 0x20, 0x20, 0x20, 0x14, 0x26, 0x14, 0x26, 0x14, 0x2D, 0x14, 0x2D, 0x14, 0x60, 0x14, 0x60, 0x41, 0x49, 0x50, 0x2D, 0x34, 0x39, 0x34, 0x20, 0x46, 0x69, 0x72, 0x6D, 0x77, 0x61, 0x72, 0x65, 0x20, 0x56, 0x65, 0x72, 0x14, 0x26, 0x14, 0x26, 0x14, 0x2D, 0x14, 0x2D, 0x14, 0x60, 0x14, 0x60};
    int size_data = sizeof(buffer_data);

    // Prompt for username
    send(client_socket, "login: ", 7, 0);
    recv(client_socket, username, BUFFER_SIZE, 0);
    username[strcspn(username, "\r\n")] = 0; // Remove newline

    // Prompt for password
    send(client_socket, "Password: ", 10, 0);
    recv(client_socket, password, BUFFER_SIZE, 0);
    password[strcspn(password, "\r\n")] = 0; // Remove newline

    // Authentication
    if (strcmp(username, USERNAME) == 0 && strcmp(password, PASSWORD) == 0) {
        send(client_socket, "Use ^AH{return} for help\r\n", 24, 0);

        while(1){
            // Receive a single command
            memset(buffer, 0, BUFFER_SIZE);
            int bytes_received = recv(client_socket, buffer, BUFFER_SIZE, 0);

            if (bytes_received <= 0) {
                closesocket(client_socket);
                printf("Client disconnected.\n");
                return;
            }

            // Check if the command contains the sequence ^A5 (0x01 0x35)
            if (strstr(buffer, "\x01\x35") != NULL) {
                // Respond with '*'
                send(client_socket, "*\r\n", 3, 0);
                // if (bytes_received > 0) {
                //     // Respond with '*'
                //     send(client_socket, "*\r\n", 3, 0);
                // }

                // Send repetitive message word by word
                while (1) {
                    // char temp_message[BUFFER_SIZE];
                    // strncpy(temp_message, message, BUFFER_SIZE);
                    // char *token = strtok(temp_message, " ");
                    // while (token != NULL) {
                    //     if (send(client_socket, token, strlen(token), 0) == SOCKET_ERROR) {
                    //         // Exit if sending fails (e.g., client disconnects)
                    //         closesocket(client_socket);
                    //         printf("Client disconnected.\n");
                    //         return;
                    //     }
                    //     send(client_socket, "\r\n", 2, 0); // Newline after each word
                    //     Sleep(500); // Delay of 500 ms
                    //     token = strtok(NULL, " ");
                    // }

                    // Send repetitive message byte by byte
                    for (size_t i = 0; i < size_data; ++i) {
                        if (send(client_socket, (const char*) &buffer_data[i], 1, 0) == SOCKET_ERROR) {
                            // Exit if sending fails (e.g., client disconnects)
                            closesocket(client_socket);
                            printf("Client disconnected.\n");
                            return;
                        }
                        Sleep(100); // Retardo de 500 ms entre bytes
                    
                    }
                }
            } // Check if the command contains the sequence ^A3 (0x01 0x33)
            else if  (strstr(buffer, "\x01\x33") != NULL) {
                // Respond with ':'
                send(client_socket, "*\r\n", 3, 0);

                // Receive and print bytes in hexadecimal
                while (1) {
                    memset(buffer, 0, BUFFER_SIZE);
                    bytes_received = recv(client_socket, buffer, BUFFER_SIZE, 0);
                    if (bytes_received <= 0) {
                        // Exit loop if client disconnects
                        // Exit if sending fails (e.g., client disconnects)
                        closesocket(client_socket);
                        printf("Client disconnected.\n");
                        return;
                    }

                    for (int i = 0; i < bytes_received; ++i) {
                        printf("0x%02X ", (unsigned char)buffer[i]);
                        fflush(stdout);
                    }
                    //printf("\n");
                }
            }
        }

    } else {
        send(client_socket, "Login incorrect. Authentication failed.\r\n", 25, 0);
    }

    closesocket(client_socket);
    printf("Client disconnected.\n");
}

int main() {
    WSADATA wsa_data;
    SOCKET server_socket, client_socket;
    struct sockaddr_in server_addr, client_addr;
    int client_len = sizeof(client_addr);

    // Inicializa WinSock
    if (WSAStartup(MAKEWORD(2, 2), &wsa_data) != 0) {
        perror("WSAStartup failed");
        exit(EXIT_FAILURE);
    }

    // Crea el socket
    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket == INVALID_SOCKET) {
        perror("Socket creation failed");
        WSACleanup();
        exit(EXIT_FAILURE);
    }

    // Configura la dirección del servidor
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    // Enlaza el socket
    if (bind(server_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) == SOCKET_ERROR) {
        perror("Bind failed");
        closesocket(server_socket);
        WSACleanup();
        exit(EXIT_FAILURE);
    }

    // Escucha conexiones
    if (listen(server_socket, 5) == SOCKET_ERROR) {
        perror("Listen failed");
        closesocket(server_socket);
        WSACleanup();
        exit(EXIT_FAILURE);
    }

    printf("==== Telnet Simulator v1.0 - Encoder/Decoder Evertz ====\n");
    printf("Credentials:\nUser: admin - Pass: 1234\n");
    printf("Command ^A5: Decoder\nCommand ^A3: Encoder\n");
    printf("Telnet server is running on port %d\n", PORT);

    // Acepta clientes
    while (1) {
        client_socket = accept(server_socket, (struct sockaddr *)&client_addr, &client_len);
        if (client_socket == INVALID_SOCKET) {
            perror("Accept failed");
            continue;
        }

        printf("Connection established with %s\n", inet_ntoa(client_addr.sin_addr));
        handle_client(client_socket);
    }

    closesocket(server_socket);
    WSACleanup();
    return 0;
}