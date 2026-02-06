#ifndef SIMULATION_H
#define SIMULATION_H
#include "API/OpenGL/GLBackend.h"
#include "Core/MovementStateManager.h"
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
    Camera* GetMainCamera() { return _currentScene->_camera->AsType<Camera>(); }

    void UpdateCameraAspect(uint, uint);

    OpenGL* _gpu;
    Scene* _currentScene;
    MovementStateManager _movementHandler;
};

}

#endif