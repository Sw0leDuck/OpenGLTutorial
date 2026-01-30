#ifndef MOVEMENT_STATE_MANAGER_H
#define MOVEMENT_STATE_MANAGER_H
#include "Managers/InputManager.h"
#include "Camera/CameraTypes.h"

namespace tartarus {

struct MovementStateManager {
    bool Init(void* inputManager_ptr);
    bool Exit();
    
    // probably change names
    void BeginFrame(float delta);
    InputManager* _inputManager;
    
    CAMERA_MOVEMENT _movementState;
    bool _stopSimulation;
};
}

#endif