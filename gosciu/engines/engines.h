#pragma once
#include <wiringPi.h>
#include "../config.h"


enum class EngineDir  {left, right};
enum class EngineRunStatus {stop, run};
enum class EngineStepMode {full = 0, half = 4, quarter = 2, one_eighth = 6,one_sixteenth = 7};

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
    static EngineStepMode stepMode;

    public:
    template<typename T>
    void Engine::Step(T durationMs);
    void SetDirection(EngineDir direction);
    static void SetStepMode(EngineStepMode stepMode);
    EngineStatus GetStatus();
    EngineStepMode GetStepMode();
    void Setup(uint8_t stepPin, uint8_t dirPin);
    static void Init();
};
