#include "Common/Logging.h"
#include "Core/MovementStateManager.h"
#include "Common/TartarusKeycodes.h"

namespace tartarus {

bool MovementStateManager::Init(void* inputManager_ptr){
    _inputManager = static_cast<InputManager*>(inputManager_ptr);
    _movementStateFlags = 0;
    _stopSimulation = false;
    return true;
}

bool MovementStateManager::Exit(){
    return true;
}

void MovementStateManager::CheckInputManager(float delta){
    // currently set only the escape key, this code handles the UI stuff i would say
    // so everything needs to be moved to the UI handler
    // For now we have a pointer to the GameHandler struct to be able to change the state
    // TODO: remove the need to have a pointer to the GameHandler
    if(_inputManager->KeyPressed((uint)keycodes::TARTARUS_KEY_ESCAPE)){
        _stopSimulation = true;
    }

    // Movement state important keys
    if(_inputManager->KeyUsed((uint)keycodes::TARTARUS_KEY_W)){
        _movementStateFlags |= (uint)CAMERA_MOVEMENT::kMoveForward;
    }

    if(_inputManager->KeyUsed((uint)keycodes::TARTARUS_KEY_S)){
        _movementStateFlags |= (uint)CAMERA_MOVEMENT::kMoveBackward;
    }

    if(_inputManager->KeyUsed((uint)keycodes::TARTARUS_KEY_A)){
        _movementStateFlags |= (uint)CAMERA_MOVEMENT::kMoveLeft;
    }

    if(_inputManager->KeyUsed((uint)keycodes::TARTARUS_KEY_D)){
        _movementStateFlags |= (uint)CAMERA_MOVEMENT::kMoveRight;
    }
}

void MovementStateManager::UpdateMainCamera(float delta){
    _camera->_movementFlags = _movementStateFlags;
    if(_inputManager->_mouseMoved){
        _camera->_offsets.xOffset = _inputManager->ComputeXOffset();
        _camera->_offsets.yOffset = _inputManager->ComputeYOffset();
        _inputManager->_mouseMoved = false;
    }
    if(_inputManager->_wheelMoved){
        _camera->_offsets.zOffset = _inputManager->ComputeZOffset();
        _inputManager->_wheelMoved = false;
    }
}
}