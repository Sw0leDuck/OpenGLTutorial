#ifndef WINDOW_MANAGER_H
#define WINDOW_MANAGER_H

#include "Backend/Window/PrimaryWindow.h"
#include "Managers/InputManager.h"

namespace tartarus{

#define WIDTH 1280
#define HEIGHT 720


void FramebufferSizeCallback(GLFWwindow* window, int width, int height);
void MouseCallback(GLFWwindow* window, double xposIn, double yposIn);
void MouseScrollBack(GLFWwindow* window, double xOffset, double yOffset);
void KeyCallback(GLFWwindow* window, int key, int scanCode, int action, int mods);

struct WindowManager {
    bool Init(
        const char* label,
        uint width = WIDTH,
        uint heigth = HEIGHT);
    
    bool Exit();
    
    // inline bool Closed() { return glfwWindowShouldClose(_window); }
    // inline void SwapBuffers() { glfwSwapBuffers(_window); }
    // inline void PollEvents() { glfwPollEvents(); }
    void ProcessInput(float delta_time);

    glfw::Window _TartarusWindow;
    InputManager _inputManager;

    uint _width;
    uint _height;
    float _lastXPos;
    float _lastYPos;
};

}

#endif