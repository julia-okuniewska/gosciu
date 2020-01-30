#include "engines.h"

#include <stdio.h>
#include <iostream>
#include <unistd.h>


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

void Engine::Step(unsigned int durationMs)
{
    digitalWrite(this->stepPin, 1);
    usleep(durationMs*1000);
    digitalWrite(this->stepPin, 0);
}

EngineStatus Engine::GetStatus()
{
    return this->status;
}

EngineStatus Engine::GetStepMode()
{
    return stepMode;
}


