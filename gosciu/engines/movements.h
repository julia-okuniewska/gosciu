#pragma once
#include "driver.h"
#include <stdint.h>
#include <vector>

class Movements
{

private:

    float actualAngles[4];
    Engine* engineArray;

public:
    void Pose(float f1, float f2, float f3, float f4,short speed);
    void Pose(float* f,uint8_t speed);
    Movements(Engine* engineArray);
}; 