#include "gosciuEngines.h"

#include <stdio.h>
#include <iostream>

int step_pins[5] = {STEP_0, STEP_1, STEP_2, STEP_3, STEP_4};
int dir_pins[5] = {DIR_0, DIR_1, DIR_2, DIR_3, DIR_4};

void pinoutSetup(void)
{

    pinMode(SPI_MOSI_PIN, OUTPUT); // mosi
    pinMode(SPI_MISO_PIN, OUTPUT); // miso
    pinMode(SPI_CLK_PIN, OUTPUT);  // s clk
    pinMode(SPI_CS_0, OUTPUT);
    pinMode(SPI_CS_1, OUTPUT);

    pinMode(STEP_0, OUTPUT);
    pinMode(DIR_0, OUTPUT);

    pinMode(STEP_1, OUTPUT);
    pinMode(DIR_1, OUTPUT);

    pinMode(STEP_2, OUTPUT);
    pinMode(DIR_2, OUTPUT);

    pinMode(STEP_3, OUTPUT);
    pinMode(DIR_3, OUTPUT);

    pinMode(STEP_4, OUTPUT);
    pinMode(DIR_4, OUTPUT);

    //INITIAL VALUES

    // teraz działa jako zwyczajne GPIO z  0 0 1 na wyjsciu
    digitalWrite(SPI_MOSI_PIN, MS1);
    digitalWrite(SPI_CLK_PIN, MS2);
    digitalWrite(SPI_CS_0, MS3);
    digitalWrite(SPI_MISO_PIN, 1);

    digitalWrite(DIR_0, 1);
    digitalWrite(STEP_0, 0);

    digitalWrite(DIR_1, 1);
    digitalWrite(STEP_1, 0);

    digitalWrite(DIR_2, 1);
    digitalWrite(STEP_2, 0);

    digitalWrite(DIR_3, 1);
    digitalWrite(STEP_3, 0);

    digitalWrite(DIR_4, 1);
    digitalWrite(STEP_4, 0);

    digitalWrite(SPI_CS_1, 0);
}

void stepUP(int which_engine, engineDIR dir)
{

    if (dir == engineDIR::left)
    {
        digitalWrite(dir_pins[which_engine], 0);
    }
    else
    {
        digitalWrite(dir_pins[which_engine], 1);
    }

    digitalWrite(step_pins[which_engine], 1);
}

void stepDOWN(int which_engine, engineDIR dir)
{
    digitalWrite(step_pins[which_engine], 1);
}

void genetate_steps(int which_engine, int how_many, engineDIR dir)
{
    for (int i = 0; i < how_many; i++)
    {

        if (dir == engineDIR::left)
        {
            digitalWrite(dir_pins[which_engine], 0);
        }
        else
        {
            digitalWrite(dir_pins[which_engine], 1);
        }

        digitalWrite(step_pins[which_engine], 0);

        std::cout << "UP " << std::endl;
        delay(1);
        digitalWrite(step_pins[which_engine], 1);
        std::cout << "DOWN " << std::endl;
        delay(1);
    }
    digitalWrite(step_pins[which_engine], 0);
}
