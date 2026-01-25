#ifndef INPUT_MANAGER_H
#define INPUT_MANAGER_H

#include "glfw/glfw3.h"
#include "Common/TartarusKeycodes.h"
#include "Common/types.h"
#include <vector>

namespace tartarus {

struct InputManager{
    bool Init(GLFWwindow* window);
    bool Exit();

    void UpdateKeyboardInput(int, int, int, int);
    void UpdateMouseCallback(float, float);
    void UpdateMouseScrollback(float, float);
    bool KeyPressed(uint keycode);
    bool KeyHold(uint keycode);

    struct KeyBehavior {
        KeyBehavior(uint code) : keycode(code) {};
        uint keycode;
        bool keyPressed = false;
        bool keyHold = false;
        bool previousPressState = false;
    };
    
    GLFWwindow* _window;
    std::vector<KeyBehavior> _keys;
    static constexpr uint firstKeyCode = uint(keycodes::TARTARUS_KEY_FIRST_ENTRY);
    static constexpr uint lastKeyCode = uint(keycodes::TARTARUS_KEY_LAST_ENTRY); 
};

}

#endif