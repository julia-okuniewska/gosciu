#include "server.h"


int listening = 0;
sockaddr_in hint;
sockaddr_in client;
socklen_t clientSize = sizeof(client);
char host[NI_MAXHOST];  
char svc[NI_MAXSERV];  


Server::Server(){

    std::cout<<"gosciu init";
    this->statusCode = this->Init(54000);
    if (this->statusCode != 0)
    {
        std::cerr<<"Server init failed. Shutting down the system ... ";
        exit(-1);
    }
};
Server::Server(uint32_t port){

    std::cout<<"gosciu init";
    this->statusCode = this->Init(port);
    if (this->statusCode != 0)
    {
        std::cerr<<"Server init failed. Shutting down the system ... ";
        exit(-1);
    }
};

Server::~Server(){
    close(*this->clientSocket);
};

int Server::GetStatusCode()
{
    return this->statusCode;
}
int Server::Init(uint32_t port)
{

    listening = socket(AF_INET, SOCK_STREAM, 0);

    if(listening == -1)
    {
        std::cerr<< "Can't create a socket!";
        return -1;
    }

    // bind the socket to IP/port
   
    hint.sin_family = AF_INET;
    hint.sin_port = htons(port);                  // PORT NUMBER
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
    if(this->GetClient() != 0)
        return -4;
    return 0;
}

int Server::GetClient(){

    
 // now accepring incoming connection
    *this->clientSocket = accept(listening,(sockaddr*)&client, &clientSize);

    if(*this->clientSocket == -1)
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

int* Server::GetClientSocket()
{
    return this->clientSocket;
}
void Server::CloseServer()
{
    close(*this->clientSocket);
}

void Server::Loop(std::function<void(char*)> callback)
{
    while(true)
    {
        //clear a buffer
        memset(this->buf,0,sizeof(this->buf)/sizeof(this->buf[0]));
        //wait for a message
        int bytesRecv = recv(*this->clientSocket, this->buf, 4096, 0);
        if(bytesRecv == -1)
        {
            std::cerr<< "There was a connection issue" <<std::endl;            
            std::cout<< "Client socket = " << *this->clientSocket;
            this->CloseServer();
            break;
        }
        
        if (bytesRecv == 0 )
        {
            std::cout << "The client is disconnected"<<std::endl;
            this->CloseServer();
            break;
        }


        // display message
        //std::cout << "Received " << std::string(this->buf,0,bytesRecv) <<std::endl;        
          // resend message
        send(*this->clientSocket, this->buf,bytesRecv + 1, 0);        

        if(callback != NULL)
            callback(this->buf);
        
    }
    std::cerr<<"Something broke up server loop. Exiting..."<<std::endl;
    exit(-2);
}