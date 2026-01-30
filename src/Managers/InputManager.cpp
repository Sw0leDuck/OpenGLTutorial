#include "Common/Logging.h"
#include "Managers/InputManager.h"
#include "assert.h"

namespace tartarus {

bool InputManager::Init(GLFWwindow* window){
    _window = window;
    _registeredMouse = false;
    
    _keys.reserve(lastKeyCode - firstKeyCode + 1);

    for(uint index=firstKeyCode; index<lastKeyCode+1; index++){
        _keys.emplace_back(index);
    }
    assert(!_keys[firstKeyCode].keyHold);
    
    return true;
}    

bool InputManager::Exit(){
    return true;
}

void InputManager::UpdateKeyboardInput(int key, int scanCode, int action, int mods){
    for(auto& iter : _keys){
        if(iter.keycode == key && action == GLFW_PRESS)
            iter.keyPressed = true;
        else
            iter.keyPressed = false;

        if(iter.keyPressed && !iter.previousPressState)
            iter.keyHold = true;
        else
            iter.keyHold = false;
        
        iter.previousPressState = iter.keyPressed;
    }
}

void InputManager::UpdateMouseCallback(float xPosIn, float yPosIn){
    if(!_registeredMouse){
        _oldWindowCoords = {xPosIn, yPosIn, 0};
        _currentWindowCoords = _oldWindowCoords;
        _registeredMouse = true;
        return;
    }
    _oldWindowCoords = _currentWindowCoords;
    _currentWindowCoords = {xPosIn, yPosIn, 0};
}

// TODO: z should not be used here
void InputManager::UpdateMouseScrollback(float xOffset, float yOffset){
    _oldWindowCoords.z = _currentWindowCoords.z;
    _currentWindowCoords.z = yOffset;
}


bool InputManager::KeyPressed(uint keycode){
    return _keys[keycode-firstKeyCode].keyPressed;
}

bool InputManager::KeyHold(uint keycode){
    return _keys[keycode-firstKeyCode].keyHold;
}

}