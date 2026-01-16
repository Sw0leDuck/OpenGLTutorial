#include "glad/glad.h"
#include "Backend/Window/glfw_window.h"
#include "common/error_handler.h"


namespace backend::glfw {

WindowManager g_window_manager;
bool g_mouse_registered = false;

bool InitializeGLFW(){
    return g_window_manager.Init("Sw0LeDuck");
}

bool ExitGLFW(){
    return g_window_manager.Exit();
}

void* GetWindow(){
    return g_window_manager._window;
}

bool IsWindowClose(){
    return g_window_manager.Closed();
}

void EndFrame(){
    g_window_manager.SwapBuffers();
    g_window_manager.PollEvents();
}


bool WindowManager::Init(const char* label, uint width, uint height){
    _height = height;
    _width = width;

    if (!glfwInit()){
        errorHandler::UpdateError("glfwInit failed\n");
        return false;
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    _window = glfwCreateWindow(_width, _height, label, NULL, NULL);

    if (!_window) {
        errorHandler::UpdateError("glfwCreateWindow failed\n");
        glfwTerminate();
        return false;
    }

    glfwMakeContextCurrent(_window);
    glfwSwapInterval(1);
    glfwSetInputMode(_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetFramebufferSizeCallback(_window, FramebufferSizeCallback);
    glfwSetCursorPosCallback(_window, MouseCallback);

    return true;
}

bool WindowManager::Exit(){
    glfwTerminate();
    return true;
}

void WindowManager::ProcessInput() {
    if (glfwGetKey(_window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(_window, true);
    }

    if (glfwGetKey(_window, GLFW_KEY_W) == GLFW_PRESS) {
        // move camera front
    }

    if (glfwGetKey(_window, GLFW_KEY_S) == GLFW_PRESS) {
        // move camera back
    }

    if (glfwGetKey(_window, GLFW_KEY_A) == GLFW_PRESS) {
        // move camera left
    }

    if (glfwGetKey(_window, GLFW_KEY_D) == GLFW_PRESS) {
        // move camera right
    }
}

void FramebufferSizeCallback(GLFWwindow* window, int width, int height){
    g_window_manager._height = height;
    g_window_manager._width = width;
    glViewport(0, 0, width, height);
}

void MouseCallback(GLFWwindow* window, double xposIn, double yposIn){
    float xpos = static_cast<float>(xposIn);
    float ypos = static_cast<float>(yposIn);
    
    if(!g_mouse_registered){
        g_window_manager._lastXPos = xpos;
        g_window_manager._lastYPos = ypos;
        g_mouse_registered = true;
    }

    float xOffset = xpos - g_window_manager._lastXPos;
    float yOffset = g_window_manager._lastYPos - ypos;

    g_window_manager._lastXPos = xpos;
    g_window_manager._lastYPos = ypos;

    // update the camera with the new xOffset, yOffset
}

} // namespace window