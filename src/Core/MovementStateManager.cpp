#include "Common/Logging.h"
#include "Core/MovementStateManager.h"
#include "Common/TartarusKeycodes.h"

namespace tartarus {

bool MovementStateManager::Init(void* inputManager_ptr){
    _inputManager = static_cast<InputManager*>(inputManager_ptr);
    _movementState = CAMERA_MOVEMENT::kNothing;
    _stopSimulation = false;
    return true;
}

bool MovementStateManager::Exit(){
    return true;
}

void MovementStateManager::BeginFrame(float delta){
    // currently set only the escape key, this code handles the UI stuff i would say
    // so everything needs to be moved to the UI handler
    // For now we have a pointer to the GameHandler struct to be able to change the state
    // TODO: remove the need to have a pointer to the GameHandler
    if(_inputManager->KeyPressed((uint)keycodes::TARTARUS_KEY_ESCAPE)){
        _stopSimulation = true;
    }

    // Movement state important keys
    if(_inputManager->KeyPressed((uint)keycodes::TARTARUS_KEY_W)){
        _movementState = CAMERA_MOVEMENT::kMoveForward;
    }

    if(_inputManager->KeyPressed((uint)keycodes::TARTARUS_KEY_S)){
        _movementState = CAMERA_MOVEMENT::kMoveBackward;
    }

    if(_inputManager->KeyPressed((uint)keycodes::TARTARUS_KEY_A)){
        _movementState = CAMERA_MOVEMENT::kMoveLeft;
    }

    if(_inputManager->KeyPressed((uint)keycodes::TARTARUS_KEY_D)){
        _movementState = CAMERA_MOVEMENT::kMoveRight;
    }
}

}