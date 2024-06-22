#include "cache.h"

bool scontinuation;

void zero(void* buf, int16 size) {
    memset(buf, 0, size);
}

void childloop(Client* client) {
    Sleep(100);
    return;
}

DWORD WINAPI ThreadFunction(LPVOID param) {
    Client* client = (Client*)param;
    const char* msg = "200 Connected to Cache server";
    int bytesSent = send(client->s, msg, strlen(msg), 0);
    if (bytesSent == SOCKET_ERROR) {
        printf("Send failed with error: %d\n", WSAGetLastError());
    } else {
        printf("Sent message to client: %s\n", msg);
    }

    scontinuation = true;
    while (scontinuation) {
        childloop(client);
    }
    closesocket(client->s);
    free(client);
    return 0;
}

void mainloop(int s) {
    struct sockaddr_in cli;
    int len = sizeof(cli);
    int s2;
    char* ip;
    int16 port;
    Client* client;
    HANDLE hThread;
    DWORD threadID;

    s2 = accept(s, (struct sockaddr*)&cli, &len);
    if (s2 == INVALID_SOCKET) {
        printf("Accept failed with error: %d\n", WSAGetLastError());
        Sleep(1000);
        return;
    }

    port = (int16)ntohs(cli.sin_port);
    ip = inet_ntoa(cli.sin_addr);

    printf("\n\nConnection accepted from %s:%d\n", ip, port);

    client = (Client*)malloc(sizeof(Client));
    if (!client) {
        printf("Memory allocation failed\n");
        closesocket(s2);
        return;
    }

    zero(client, sizeof(Client));

    client->s = s2;
    client->port = port;
    strncpy(client->ip, ip, 15);

    hThread = CreateThread(NULL, 0, ThreadFunction, client, 0, &threadID);
    if (hThread == NULL) {
        printf("CreateThread failed with error: %d\n", GetLastError());
        closesocket(s2);
        free(client);
        return;
    }

    CloseHandle(hThread);
}

int initserver(int16 port) {
    WSADATA wsaData;
    int s;
    struct sockaddr_in sock;

    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        printf("WSAStartup failed with error: %d\n", WSAGetLastError());
        return INVALID_SOCKET;
    }

    sock.sin_family = AF_INET;
    sock.sin_port = htons(port);
    sock.sin_addr.s_addr = inet_addr(HOST);

    s = socket(AF_INET, SOCK_STREAM, 0);
    if (s == INVALID_SOCKET) {
        printf("Socket creation failed with error: %d\n", WSAGetLastError());
        WSACleanup();
        return INVALID_SOCKET;
    }

    if (bind(s, (struct sockaddr*)&sock, sizeof(sock)) == SOCKET_ERROR) {
        printf("Bind failed with error: %d\n", WSAGetLastError());
        closesocket(s);
        WSACleanup();
        return INVALID_SOCKET;
    }

    if (listen(s, 20) == SOCKET_ERROR) {
        printf("Listen failed with error: %d\n", WSAGetLastError());
        closesocket(s);
        WSACleanup();
        return INVALID_SOCKET;
    }

    printf("Server listening on %s:%d\n", HOST, port);
    return s;
}

int main(int argc, char** argv) {
    char* sport;
    int16 port;
    int s;

    if (argc < 2) {
        sport = PORT;
    } else {
        sport = argv[1];
    }

    port = (int16)atoi(sport);
    s = initserver(port);
    if (s == INVALID_SOCKET) {
        return 1;
    }

    scontinuation = true;
    while (scontinuation) {
        mainloop(s);
    }

    printf("Shutting down the server...\n");
    closesocket(s);
    WSACleanup();
    return 0;
}