#ifndef MOVEMENT_STATE_MANAGER_H
#define MOVEMENT_STATE_MANAGER_H
#include "Camera/Camera.h"
#include "Managers/InputManager.h"
#include "Camera/CameraTypes.h"

namespace tartarus {

struct MovementStateManager {
    bool Init(void* inputManager_ptr);
    bool Exit();
    
    // probably change names
    void CheckInputManager(float delta);
    void UpdateMainCamera(float delta);
    InputManager* _inputManager;
    
    uint _movementStateFlags;
    Camera* _camera;
    bool _stopSimulation;
};
}

#endif