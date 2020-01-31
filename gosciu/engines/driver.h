#pragma once
#include <wiringPi.h>
#include <stdint.h>
#include "../config.h"


enum class EngineDir  {left, right};
enum class EngineRunStatus {stop, run};
enum class EngineStepMode {full = 0, half = 4, quarter = 2, one_eighth = 6,one_sixteenth = 7};

#define STEP_ANGLE 1.8f

typedef struct EngineStatus_t
{
    EngineDir direction;
    EngineRunStatus runStatus;
}EngineStatus;

class Engine
{
    private:
    EngineStatus status;
    short stepPin, dirPin;
    static EngineStepMode stepMode;
    template<typename T>
    void Step(T durationMs);
    void SetDirection(EngineDir direction);


    public:
    void Rotate(EngineDir direction,uint8_t speed,float angle);
    static void SetStepMode(EngineStepMode stepMode);
    EngineStatus GetStatus();
    EngineStepMode GetStepMode();
    void Setup(short stepPin, short dirPin);
    static void Init();
};
