#ifndef SERVERTCP_H
#define SERVERTCP_H

#include <iostream>
#include <sys/types.h>
#include <unistd.h>
#include <sys/socket.h>     // linux only
#include <netdb.h>          // linux only
#include <arpa/inet.h>      // linux only
#include <string.h>
#include <string>

class serverTCP 
{
    public:
    


    int listening = 0;
    sockaddr_in hint;
    sockaddr_in client;
    socklen_t clientSize;
    char host[NI_MAXHOST];  
    char svc[NI_MAXSERV];  

    serverTCP();
    int serverInit(void);
    int getClientOnServer(int *clientSocket);
    int closeServer(int clientSocket);
    
};



#endif