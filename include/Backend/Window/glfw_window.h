#ifndef WINDOW_H
#define WINDOW_H

#include <GLFW/glfw3.h>
#include "common/types.h"

namespace backend::glfw {
#define WIDTH 1280
#define HEIGHT 720

    bool InitializeGLFW();
    bool PostInitGameHandler();
    bool ExitGLFW();

    // Window methods
    void* GetWindow();
    bool IsWindowClose();

    // TOOD: change this
    void BeginFrame(float delta_time);
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

        void ProcessInput(float delta_time);

        GLFWwindow* _window;
        uint _width;
        uint _height;

        float _lastXPos;
        float _lastYPos;
    };
    
    void FramebufferSizeCallback(GLFWwindow* window, int width, int height);
    void MouseCallback(GLFWwindow* window, double xposIn, double yposIn);
    void MouseScrollBack(GLFWwindow* window, double xOffset, double yOffset);
    void KeyCallback(GLFWwindow* window, int key, int scanCode, int action, int mods);
} // namespace backend::glfw

#endif