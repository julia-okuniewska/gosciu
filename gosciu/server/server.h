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
    int listening = 0;
    sockaddr_in hint;
    sockaddr_in client;
    socklen_t clientSize = sizeof(client);
    char host[NI_MAXHOST];  
    char svc[NI_MAXSERV];  
    int statusCode;
    char buf[4096];

    int GetClient();
    int Init(uint32_t port);
    void CloseServer();


    public:
    Server();
    Server(uint32_t port);
    ~Server();
    int* GetClientSocket();
    int GetStatusCode();
    void Loop(std::function<void(char*)> callback);


};
