#include "gosciuServer.h"


int listening = 0;
sockaddr_in hint;
sockaddr_in client;
socklen_t clientSize = sizeof(client);
char host[NI_MAXHOST];  
char svc[NI_MAXSERV];  

int serverInit(void)
{

    listening = socket(AF_INET, SOCK_STREAM, 0);

    if(listening == -1)
    {
        std::cerr<< "Can't create a socket!";
        return -1;
    }

    // bind the socket to IP/port
   
    hint.sin_family = AF_INET;
    hint.sin_port = htons(54000);                  // PORT NUMBER
    inet_pton(AF_INET, "0.0.0.0", &hint.sin_addr); //convert number to array of integers (ip adress)

    if(bind(listening, (sockaddr*)&hint, sizeof(hint)) == -1)
    {
        std::cerr << "Can't bind to IP/port";
        return -2;
    }
    
    // Mark the socket for listening in

    if(listen(listening, SOMAXCONN) == -1)
    {
        std::cerr << "Can't listen!";
        return -3;
    }

    return 0;
}

int getClientOnServer(int *clientSocket){

    
 // now accepring incoming connection
    *clientSocket = accept(listening,(sockaddr*)&client, &clientSize);

    if(*clientSocket == -1)
    {
        std::cerr<<"Problem with client - server connection!";
        return -4;
    }

    // close the listening socket
    close(listening);

    memset(host, 0, NI_MAXHOST);
    memset(svc, 0, NI_MAXSERV);

    int result = getnameinfo((sockaddr*)&client, sizeof(client), host, NI_MAXHOST,svc, NI_MAXSERV,0);

    if(result)
    {
        std::cout<< host << " connected on " << svc << std::endl;
    }
    else
    {
        inet_ntop(AF_INET, &client.sin_addr, host, NI_MAXHOST);
        std::cout << host << " connected on "<< ntohs(client.sin_port)<<std::endl;
    }


    return 0;
}


int closeServer(int clientSocket)
{
   close(clientSocket);
   return 0;
}