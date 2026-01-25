#ifndef SIMULATION_H
#define SIMULATION_H
#include "API/Gpu_Backend.h"
#include "Core/MovementHandler.h"
#include "Core/Scene.h"

namespace tartarus{

struct Simulation{
    bool Init(void*, void*);
    bool Exit();

    bool Run();
    void BeginFrame(float delta);
    void UpdateFrame(float delta);
    void ExitFrame(float delta);

    void SetCurrentScene(Scene*);

    Gpu* _gpu;
    Scene* _currentScene;
    MovementHandler _movementHandler;
};

}

#endif