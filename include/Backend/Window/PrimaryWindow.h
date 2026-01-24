#ifndef WINDOW_H
#define WINDOW_H

#include <GLFW/glfw3.h>
#include "Common/types.h"

namespace tartarus::glfw {

    struct Window {
        bool Init(uint height, uint width, const char* label);
        bool Exit();

        GLFWwindow* _window;
        uint _height;
        uint _width;
    };

    bool InitializeGLFW();
    bool PostInitGameHandler();
    bool ExitGLFW();

    // Window methods
    void* GetWindow();
    bool IsWindowClose();

    // TOOD: change this
    void BeginFrame(float delta_time);
    void EndFrame();


    
    void FramebufferSizeCallback(GLFWwindow* window, int width, int height);
    void MouseCallback(GLFWwindow* window, double xposIn, double yposIn);
    void MouseScrollBack(GLFWwindow* window, double xOffset, double yOffset);
    void KeyCallback(GLFWwindow* window, int key, int scanCode, int action, int mods);
} // namespace backend::glfw

#endif