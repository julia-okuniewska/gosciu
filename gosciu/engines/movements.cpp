#include "movements.h"
#include <cstddef>
#include <iostream>
#include <thread>
void Movements::Pose(float f1, float f2, float f3, float f4,short speed)
{
    float deltaAngle[4];
    float jointSpeed[4];
    std::cout<<"actualAngles: "<<this->actualAngles[0]<<" "<<this->actualAngles[1]<<" "<<this->actualAngles[2]<<" "<<this->actualAngles[3]<<" "<<std::endl;
    deltaAngle[0] = f1 - this->actualAngles[0] ;
    deltaAngle[1] = f2 - this->actualAngles[1] ;
    deltaAngle[2] = f3 - this->actualAngles[2] ;
    deltaAngle[3] = f4 - this->actualAngles[3] ;
    this->actualAngles[0] += deltaAngle[0];
    this->actualAngles[1] += deltaAngle[1];
    this->actualAngles[2] += deltaAngle[2];
    this->actualAngles[3] += deltaAngle[3];
    std::cout<<"deltaAngles: "<<deltaAngle[0]<<" "<<deltaAngle[1]<<" "<<deltaAngle[2]<<" "<<deltaAngle[3]<<" "<<std::endl;

    jointSpeed[0] = speed/deltaAngle[0];
    jointSpeed[1] = speed/deltaAngle[1];
    jointSpeed[2] = speed/deltaAngle[2];
    jointSpeed[3] = speed/deltaAngle[3];

    std::cout<<"speeds: "<<jointSpeed[0]<<" "<<jointSpeed[1]<<" "<<jointSpeed[2]<<" "<<jointSpeed[3]<<" "<<std::endl;

    std::thread move1(&Engine::Rotate,&this->engineArray[0],
                        (deltaAngle[0] > 0)?EngineDir::left : EngineDir::right,
                         speed,deltaAngle[0]);
    std::thread move2(&Engine::Rotate,&this->engineArray[1],
                        (deltaAngle[1] > 0)?EngineDir::left : EngineDir::right,
                         speed,deltaAngle[1]);
    std::thread move3(&Engine::Rotate,&this->engineArray[2],
                        (deltaAngle[2] > 0)?EngineDir::left : EngineDir::right,
                         speed,deltaAngle[2]);
    std::thread move4(&Engine::Rotate,&this->engineArray[3],
                        (deltaAngle[3] > 0)?EngineDir::left : EngineDir::right,
                         speed,deltaAngle[3]);
    
    std::cout<<"actualAngles after: "<<this->actualAngles[0]<<" "<<this->actualAngles[1]<<" "<<this->actualAngles[2]<<" "<<this->actualAngles[3]<<" "<<std::endl;

    move1.join();
    move2.join();
    move3.join();
    move4.join();


}

void Movements::Pose(float* f,uint8_t speed)
{
    
}

Movements::Movements(Engine* engineArray)
{
    for (size_t i = 0; i < 4; i++)
    {
       this->actualAngles[i] = 0;
    }
    this->engineArray = engineArray;
}