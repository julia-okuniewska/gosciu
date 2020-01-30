#include "server.h"

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

    this->listening = socket(AF_INET, SOCK_STREAM, 0);

    if(this->listening == -1)
    {
        std::cerr<< "Can't create a socket!";
        return -1;
    }

    // bind the socket to IP/port
   
    this->hint.sin_family = AF_INET;
    this->hint.sin_port = htons(port);                  // PORT NUMBER
    inet_pton(AF_INET, "0.0.0.0", &this->hint.sin_addr); //convert number to array of integers (ip adress)

    if(bind(this->listening, (sockaddr*)&this->hint, sizeof(this->hint)) == -1)
    {
        std::cerr << "Can't bind to IP/port";
        return -2;
    }
    
    // Mark the socket for this->listening in

    if(listen(this->listening, SOMAXCONN) == -1)
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
    *this->clientSocket = accept(this->listening,(sockaddr*)&this->client, &this->clientSize);

    if(*this->clientSocket == -1)
    {
        std::cerr<<"Problem with client - server connection!";
        return -4;
    }

    // close the this->listening socket
    close(this->listening);

    memset(this->host, 0, NI_MAXHOST);
    memset(this->svc, 0, NI_MAXSERV);

    int result = getnameinfo((sockaddr*)&this->client, sizeof(this->client), this->host, NI_MAXHOST,this->svc, NI_MAXSERV,0);

    if(result)
    {
        std::cout<< this->host << " connected on " << this->svc << std::endl;
    }
    else
    {
        inet_ntop(AF_INET, &this->client.sin_addr, this->host, NI_MAXHOST);
        std::cout << this->host << " connected on "<< ntohs(this->client.sin_port)<<std::endl;
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