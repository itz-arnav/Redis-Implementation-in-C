#ifndef CACHE_H
#define CACHE_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <assert.h>
#include <stddef.h>
#include <stdarg.h>
#include <windows.h>

// for msvc
// #pragma comment(lib, "ws2_32.lib")  // Link with the Ws2_32.lib library.

#define HOST "127.0.0.1"
#define PORT "12049"
#define log(x, ...) \
    printf(x, ##__VA_ARGS__)

typedef unsigned int int32;
typedef unsigned short int int16;
typedef unsigned char int8;

struct s_client{
    int s;
    //212.212.212.212\0
    char ip[16];
    int16 port;
};

typedef struct s_client Client;

// void zero(int8* buf, int16 size);
void zero(void* buf, int16 size);
void childloop(Client* client);
void mainloop(int s);
int initserver(int16 port);
int main(int argc, char** argv);

#endif
