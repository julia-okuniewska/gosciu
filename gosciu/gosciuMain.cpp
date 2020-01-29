#include "gosciuMain.h"

#include <stdio.h>
#include <iostream>

//enum engineDIR  {left, right};
enum engineSTATUS {stop, run};

struct Engine {
    enum engineDIR DIR;
    enum engineSTATUS STATUS;
};

struct Engine engines[5];

//-------- server variables ------------ 
int clientSocket = 0;

int main(void){

    std::cout<<"GOSCIU SOFTWARE"<<std::endl;
    std::cout<<"REMEMBER TO CONNECT WITH 54000 PORT"<<std::endl;

    if(wiringPiSetup() == -1)
    {
        printf("wiringPi is not enabled!!!");
        return 1;
    }
    pinoutSetup();


while(1)
   {
        genetate_steps(4, 20, engineDIR::right);
   }



//--------------- SERVER INIT -----------------
    int initVal = serverInit();
    if (initVal != 0)
    {
        std::cerr<<"Server init failed. Shutting down the system ... ";
        return -1;
    }
    
    getClientOnServer(&clientSocket);





//=============== MAIN SERVER LOOP ==================
char buf[4096];
    while(true)
    {
        //clear a buffer
        memset(buf,0,sizeof(buf)/sizeof(buf[0]));
        //wait for a message
        int bytesRecv = recv(clientSocket, buf, 4096, 0);
        if(bytesRecv == -1)
        {
            std::cerr<< "There was a connection issue" <<std::endl;            
            std::cout<< "Client socket = " << clientSocket;
            closeServer(clientSocket);
            break;
        }
        
        if (bytesRecv == 0 )
        {
            std::cout << "The client is disconnected"<<std::endl;
            closeServer(clientSocket);
            break;
        }


        // display message
        std::cout << "Received " << std::string(buf,0,bytesRecv) <<std::endl;        
          // resend message
        send(clientSocket, buf,bytesRecv + 1, 0);        

        parse(buf);
        
    }

    return 0;
}

void parse(char* buf)
{

    if(strstr(buf, "jt0left_pressed")!=NULL)
    {
        engines[3].STATUS = run;
        engines[3].DIR = left;          
    }

    else if(strstr(buf, "jt0left_released")!=NULL)
    {
        engines[3].STATUS = stop;    
    }

    else if(strstr(buf, "jt0right_pressed")!=NULL)
    {
        engines[3].STATUS = run;
        engines[3].DIR = right;        
    }    

    else if(strstr(buf, "jt0right_released")!=NULL)
    {
        engines[3].STATUS = stop;        
    }

    else if(strstr(buf, "jt1left_pressed")!=NULL)
    {        
        engines[1].STATUS = run;
        engines[1].DIR = left;
    }   
    else if(strstr(buf, "jt1left_released")!=NULL)
    {         
        engines[1].STATUS = stop;
    }

    else if(strstr(buf, "jt1right_pressed")!=NULL)
    {        
        engines[1].STATUS = run;
        engines[1].DIR = right;
    }   
    else if(strstr(buf, "jt1right_released")!=NULL)
    {         
        engines[1].STATUS = stop;
    }      


}