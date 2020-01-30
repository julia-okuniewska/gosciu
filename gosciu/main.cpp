#include "main.h"
#include <thread>
#include <stdio.h>
#include <iostream>



//-------- server variables ------------ 

void dataParser(char* msg)
{

}

int main(void){

    Server* server = new Server();

    std::cout<<"GOSCIU SOFTWARE"<<std::endl;
    std::cout<<"REMEMBER TO CONNECT WITH 54000 PORT"<<std::endl;
   
    if(wiringPiSetup() == -1)
    {
        printf("wiringPi is not enabled!!!");
        return 1;
    }

    Engine engine[5];
    Engine::Init();
    Engine::SetStepMode(EngineStepMode::half);
    engine[0].Setup(STEP_0,DIR_0);
    engine[1].Setup(STEP_1,DIR_1);
    engine[2].Setup(STEP_2,DIR_2);
    engine[3].Setup(STEP_3,DIR_3);
    engine[4].Setup(STEP_4,DIR_4);

    std::thread serverLoopThread(server->Loop,dataParser);


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