#ifndef WINDOW_H
#define WINDOW_H

#include <GLFW/glfw3.h>
#include "common/types.h"

namespace backend::glfw {
#define WIDTH 800
#define HEIGHT 600

    bool InitializeGLFW();
    bool ExitGLFW();

    // Window methods
    void* GetWindow();
    bool IsWindowClose();

    // TOOD: change this
    void EndFrame();

    struct WindowManager {
        bool Init(
            const char* label,
            uint width = WIDTH,
            uint heigth = HEIGHT);

        bool Exit();

        inline bool Closed() { return glfwWindowShouldClose(_window); }
        inline void SwapBuffers() { glfwSwapBuffers(_window); }
        inline void PollEvents() { glfwPollEvents(); }

        void ProcessInput();

        GLFWwindow* _window;
        uint _width;
        uint _height;

        float _lastXPos;
        float _lastYPos;
    };
    
    void FramebufferSizeCallback(GLFWwindow* window, int width, int height);
    void MouseCallback(GLFWwindow* window, double xposIn, double yposIn);
} // namespace backend::glfw

#endif