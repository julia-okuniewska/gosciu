#include "driver.h"

#include <stdio.h>
#include <iostream>
#include <unistd.h>
#include <math.h>

void Engine::Init()
{
    pinMode(SPI_MOSI_PIN, OUTPUT); // mosi
    pinMode(SPI_MISO_PIN, OUTPUT); // miso
    pinMode(SPI_CLK_PIN, OUTPUT);  // s clk
    pinMode(SPI_CS_0, OUTPUT);
    pinMode(SPI_CS_1, OUTPUT);

    digitalWrite(SPI_MISO_PIN, 1);
    digitalWrite(SPI_CS_1, 0);
}

void Engine::Setup(uint8_t stepPin, uint8_t dirPin)
{
    pinMode(stepPin, OUTPUT);
    pinMode(dirPin, OUTPUT);

    digitalWrite(dirPin, 1);
    digitalWrite(stepPin, 0);
}

static void Engine::SetStepMode(EngineStepMode stepMode)
{
    digitalWrite(SPI_MOSI_PIN, stepMode & (1<<2));
    digitalWrite(SPI_CLK_PIN, stepMode & (1<<1));
    digitalWrite(SPI_CS_0, stepMode & (1<<0));
    
}

void Engine::SetDirection(EngineDir direction)
{
    this->dirPin = direction;
    this->status.direction = direction;
}

template<typename T>
void Engine::Step(T durationMs)
{
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

//Rotate geared engine 

//Rotate geared engine 
void Engine::Rotate(EngineDir direction,uint8_t speed,float angle)
{
    this->SetDirection(direction);
    unsigned long rotationSteps;
    float stepTime;
    angle = abs(angle);
    //steptime <=2 ms

    switch (this->stepMode)
    {
    case EngineStepMode::full:
        rotationSteps = STEP_ANGLE*angle*GEAR_RATIO;
        //stepTime ~ speed
    break;
    case EngineStepMode::half:
        rotationSteps = STEP_ANGLE*angle*2*GEAR_RATIO;
         //stepTime ~ speed
    break;
    case EngineStepMode::quarter:
        rotationSteps = STEP_ANGLE*angle*4*GEAR_RATIO;
         //stepTime ~ speed
    break;
    case EngineStepMode::one_eighth:
        rotationSteps = STEP_ANGLE*angle*8*GEAR_RATIO;
         //stepTime ~ speed
    break;
    case EngineStepMode::one_sixteenth:
        rotationSteps = STEP_ANGLE*angle*16*GEAR_RATIO;
         //stepTime ~ speed
    break;
    }

    while (rotationSteps)
    {
        this->Step(stepTime);
        rotationSteps--;
    }
    


}

