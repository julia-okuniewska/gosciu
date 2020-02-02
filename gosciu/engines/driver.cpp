#include "driver.h"

#include <stdio.h>
#include <iostream>
#include <unistd.h>
#include <math.h>

EngineStepMode Engine::stepMode;

void Engine::Init()
{
    pinMode(SPI_MOSI_PIN, OUTPUT); // mosi
    pinMode(SPI_MISO_PIN, OUTPUT); // miso
    pinMode(SPI_CLK_PIN, OUTPUT);  // s clk
    pinMode(SPI_CS_0, OUTPUT);
    pinMode(SPI_CS_1, OUTPUT);

    digitalWrite(SPI_MISO_PIN, 1);
    digitalWrite(SPI_CS_1, 0);
    stepMode = EngineStepMode::half;
   // std::cout<<"init done"<<std::endl;
}

void Engine::Setup(short stepPin, short dirPin)
{
    pinMode(stepPin, OUTPUT);
    pinMode(dirPin, OUTPUT);

    digitalWrite(dirPin, 1);
    digitalWrite(stepPin, 0);
    this->stepPin = stepPin;
    this->dirPin = dirPin;
   // std::cout<<"setup done: step:"<<stepPin<<" dir:"<<dirPin<<std::endl;
}

void Engine::SetStepMode(EngineStepMode stepMode)
{
    digitalWrite(SPI_MOSI_PIN, (uint8_t)stepMode & (1<<2));
    digitalWrite(SPI_CLK_PIN, (uint8_t)stepMode & (1<<1));
    digitalWrite(SPI_CS_0, (uint8_t)stepMode & (1<<0));
    
}

void Engine::SetDirection(EngineDir direction)
{
    digitalWrite(this->dirPin, (uint8_t)direction);
    this->status.direction = direction;
}

template<typename T>
void Engine::Step(T durationMs)
{
   // std::cout<<"STEP PIN: "<<this->stepPin<<std::endl;
    digitalWrite(this->stepPin, 1);
    usleep(durationMs*1000);
    digitalWrite(this->stepPin, 0);
    
}

EngineStatus Engine::GetStatus()
{
    return this->status;
}

EngineStepMode Engine::GetStepMode()
{
    return stepMode;
}
//Rotate geared engine 

//Rotate geared engine 
void Engine::Rotate(EngineDir direction,uint8_t speed,float angle)
{
    //std::cout<<"dir: "<<(short)direction<<std::endl;
    this->SetDirection(direction);
    usleep(1000);
    unsigned long rotationSteps;
    float stepTime;
    angle = abs(angle);
    //steptime <=2 ms
  
    switch (this->stepMode)
    {
    case EngineStepMode::full:
        rotationSteps = long(STEP_ANGLE*angle*0.5*GEAR_RATIO);
        //stepTime ~ speed
    break;
    case EngineStepMode::half:
        rotationSteps = long(STEP_ANGLE*angle*GEAR_RATIO);
         //stepTime ~ speed
    break;
    case EngineStepMode::quarter:
        rotationSteps = long(STEP_ANGLE*angle*2*GEAR_RATIO);
         //stepTime ~ speed
    break;
    case EngineStepMode::one_eighth:
        rotationSteps = long(STEP_ANGLE*angle*4*GEAR_RATIO);
         //stepTime ~ speed
    break;
    case EngineStepMode::one_sixteenth:
        rotationSteps = long(STEP_ANGLE*angle*8*GEAR_RATIO);
         //stepTime ~ speed
    break;
    }
    stepTime = 0.8*(100/speed);
    while (rotationSteps)
    {
        this->Step(stepTime);
        rotationSteps--;
       // std::cout<<rotationSteps<<std::endl;
    }
    


}

