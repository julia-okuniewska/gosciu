#include "main.h"
#include <thread>
#include <stdio.h>
#include <iostream>



//-------- server variables ------------ 

void dataParser(char* msg)
{

}

int main(void){

    std::cout<<"START!"<<std::endl;
    //Server* server = new Server();

    std::cout<<"GOSCIU SOFTWARE"<<std::endl;
    std::cout<<"REMEMBER TO CONNECT WITH 54000 PORT"<<std::endl;
   
    if(wiringPiSetup() == -1)
    {
        printf("wiringPi is not enabled!!!");
        return 1;
    }

    Engine engine[4];
    Engine::Init();
    Engine::SetStepMode(EngineStepMode::half);
    engine[0].Setup(STEP_3,DIR_3); //podstawa step3
    engine[1].Setup(STEP_4,DIR_4); //przechyl step3
    engine[2].Setup(STEP_2,DIR_2); //pisak obrot step0 --brak stepsticka
    engine[3].Setup(STEP_0,DIR_0); //pisak gora dol step4
    
    Movements movements(engine);
   
//engine 0 - 2 stopien - right - w gore (od strony napisu feel na zasilaczu) i pisakiem po lewej

   //std::thread rotate(&Engine::Rotate,&engine[1],EngineDir::right,80,100);
   //engine[0].Rotate(EngineDir::left,50,50); //obrot 1 stopien
  //engine[4].Rotate(EngineDir::left,50,50); //pisak left - w gore 
   // while(1);
    // while(1)
    // {
       
    //     //sleep(2);
    //     engine[3].Rotate(EngineDir::left,50,50); //obrot 1 stopien
       
    //     engine[3].Rotate(EngineDir::right,50,50); //obrot 1 stopien
    //     //sleep(2);
    // }    //     engine[3].Rotate(EngineDir::left,50,50); //obrot 1 stopien
    while(1)
    {


     movements.Pose(30,0,0,0,70);
    movements.Pose(0,30,0,0,70);
    movements.Pose(0,-30,0,0,70);
    movements.Pose(-30,0,0,0,70);
    }   
   
    //engine[1].Rotate(EngineDir::left,100,5);
    //engine[2].Rotate(EngineDir::left,100,5);
    //engine[3].Rotate(EngineDir::right,100,20); //obrot 1 stopien
   // engine[4].Rotate(EngineDir::right,100,5); //pisak
    //std::thread serverLoopThread(&Server::Loop,server,dataParser);
    
    return 0;
}

// void parse(char* buf)
// {

//     if(strstr(buf, "jt0left_pressed")!=NULL)
//     {
//         engines[3].STATUS = run;
//         engines[3].DIR = left;          
//     }

//     else if(strstr(buf, "jt0left_released")!=NULL)
//     {
//         engines[3].STATUS = stop;    
//     }

//     else if(strstr(buf, "jt0right_pressed")!=NULL)
//     {
//         engines[3].STATUS = run;
//         engines[3].DIR = right;        
//     }    

//     else if(strstr(buf, "jt0right_released")!=NULL)
//     {
//         engines[3].STATUS = stop;        
//     }

//     else if(strstr(buf, "jt1left_pressed")!=NULL)
//     {        
//         engines[1].STATUS = run;
//         engines[1].DIR = left;
//     }   
//     else if(strstr(buf, "jt1left_released")!=NULL)
//     {         
//         engines[1].STATUS = stop;
//     }

//     else if(strstr(buf, "jt1right_pressed")!=NULL)
//     {        
//         engines[1].STATUS = run;
//         engines[1].DIR = right;
//     }   
//     else if(strstr(buf, "jt1right_released")!=NULL)
//     {         
//         engines[1].STATUS = stop;
//     }      


// }