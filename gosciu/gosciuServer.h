#ifndef GOSCIUSERVER_H
#define GOSCIUSERVER_H

#include <iostream>
#include <sys/types.h>
#include <unistd.h>
#include <sys/socket.h>     // linux only
#include <netdb.h>          // linux only
#include <arpa/inet.h>      // linux only
#include <string.h>
#include <string>

struct EfectorPos {
    float x;
    float y;
    float z;
};

class GosciuServer {
    private:
        EfectorPos efectorPos;

    public:
    GosciuServer();
    ~GosciuServer();

};

int serverInit(void);
int getClientOnServer(int *clientSocket);
int closeServer(int clientSocket);

#endif