#pragma once
#include <wiringPi.h>
#include "../config.h"


enum class EngineDir  {left, right};
enum class EngineRunStatus {stop, run};
enum class EngineStepMode {full = 0, half = 4, quarter = 2, one_eighth = 6,one_sixteenth = 7};

#define STEP_ANGLE 1.8f

typedef struct EngineStatus
{
    EngineDir direction;
    EngineRunStatus runStatus;
};

class Engine
{
    private:
    EngineStatus status;
    uint8_t stepPin, dirPin;
    static EngineStepMode stepMode = EngineStepMode::half;
    template<typename T>
    void Engine::Step(T durationMs);
    void SetDirection(EngineDir direction);


    public:
    void Rotate(EngineDir direction,uint8_t speed,int16_t angle);
    static void SetStepMode(EngineStepMode stepMode);
    EngineStatus GetStatus();
    EngineStepMode GetStepMode();
    void Setup(uint8_t stepPin, uint8_t dirPin);
    static void Init();
};
