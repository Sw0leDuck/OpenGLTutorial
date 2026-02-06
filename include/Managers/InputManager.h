#ifndef INPUT_MANAGER_H
#define INPUT_MANAGER_H

#include "glfw/glfw3.h"
#include "Common/TartarusKeycodes.h"
#include "Common/types.h"
#include <vector>

namespace tartarus {

struct InputManager {
    struct WindowCoordinates {
        float x = 0.f;
        float y = 0.f;
        float z = 0.f;
    };

    bool Init(GLFWwindow* window);
    bool Exit();

    void UpdateKeyboardInput(int, int, int, int);
    void UpdateMouseCallback(float, float);
    void UpdateMouseScrollback(float, float);
    bool KeyPressed(uint keycode) { return  _keys[keycode-firstKeyCode].keyPressed; }
    bool KeyHold(uint keycode) { return _keys[keycode-firstKeyCode].keyHold; }
    bool KeyUsed(uint keycode) { return _keys[keycode-firstKeyCode].keyPressed || _keys[keycode-firstKeyCode].keyHold; }


    inline float ComputeXOffset() { return _currentWindowCoords.x - _oldWindowCoords.x; }
    inline float ComputeYOffset() { return _oldWindowCoords.y - _currentWindowCoords.y; }
    inline float ComputeZOffset() { return _currentWindowCoords.z - _oldWindowCoords.z; }

    struct KeyBehavior {
        KeyBehavior(uint code) : keycode(code) {};
        uint keycode;
        bool keyPressed = false;
        bool keyHold = false;
    };
    
    GLFWwindow* _window;
    WindowCoordinates _oldWindowCoords;
    WindowCoordinates _currentWindowCoords;
    bool _registeredMouse;
    bool _mouseMoved;
    bool _wheelMoved;
    std::vector<KeyBehavior> _keys;
    static constexpr uint firstKeyCode = uint(keycodes::TARTARUS_KEY_FIRST_ENTRY);
    static constexpr uint lastKeyCode = uint(keycodes::TARTARUS_KEY_LAST_ENTRY);
};

}

#endif