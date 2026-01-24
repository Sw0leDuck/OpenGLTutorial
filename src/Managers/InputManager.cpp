#include "Managers/InputManager.h"
#include "assert.h"

namespace tartarus {

bool InputManager::Init(GLFWwindow* window){
    _window = window;
    
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

}

void InputManager::UpdateMouseCallback(float xPosIn, float yPosIn){

}

void InputManager::UpdateMouseScrollback(float xOffset, float yOffset){

}


bool InputManager::KeyPressed(uint keycode){
    return _keys[keycode-firstKeyCode].keyPressed;
}

bool InputManager::KeyHold(uint keycode){
    return _keys[keycode-firstKeyCode].keyHold;
}

}