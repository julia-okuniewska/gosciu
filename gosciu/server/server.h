#pragma once

#include <iostream>
#include <sys/types.h>
#include <unistd.h>
#include <sys/socket.h>     // linux only
#include <netdb.h>          // linux only
#include <arpa/inet.h>      // linux only
#include <string.h>
#include <string>
#include <functional>


struct EfectorPos {
    float x;
    float y;
    float z;
};

class Server {
    private:
    int* clientSocket;
    int GetClient();
    int Init(uint32_t port);
    int statusCode;
    char buf[4096];
    void CloseServer();


    public:
    Server();
    Server(uint32_t port);
    ~Server();
    int* GetClientSocket();
    int GetStatusCode();
    void Loop(std::function<void(char*)> callback);


};
