#include "Common/Logging.h"
#include "Managers/WindowManager.h"

namespace tartarus {

namespace global {
// accessed only in this file, specifically the callback function, could be done with singleton
// accordint to stack overflow, is it worthy/possible?
WindowManager* g_WindowManager;
}


bool WindowManager::Init(const char* label, uint width, uint height){
    if (!glfwInit()){
        return false;
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    
    if(!_TartarusWindow.Init(height, width, label)){
        return false;
    }
    
    // glfwSetErrorCallback(GetGLFWError);
    // glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT , GL_TRUE);

    _inputManager.Init(_TartarusWindow._window);

    global::g_WindowManager = this;
    
    glfwSetFramebufferSizeCallback(_TartarusWindow._window, FramebufferSizeCallback);
    glfwSetCursorPosCallback(_TartarusWindow._window, MouseCallback);
    glfwSetScrollCallback(_TartarusWindow._window, MouseScrollBack);
    glfwSetKeyCallback(_TartarusWindow._window, KeyCallback);

    _mainWindow = &_TartarusWindow;
    needResizeViewport = false;
    _height = height;
    _width = width;

    return true;
}

bool WindowManager::Exit(){
    _mainWindow = nullptr;
    if(!_TartarusWindow.Exit())
        return false;
    return true;
}

void WindowManager::ProcessInput(float delta_time) {
    // if (glfwGetKey(_TartarusWindow, GLFW_KEY_W) == GLFW_PRESS) {
    //     gameHandler::MoveCamera(view::CAMERA_MOVEMENT::kMoveForward, delta_time);
    //     // move camera front
    // }

    // if (glfwGetKey(_TartarusWindow, GLFW_KEY_S) == GLFW_PRESS) {
    //     gameHandler::MoveCamera(view::CAMERA_MOVEMENT::kMoveBackward, delta_time);
    //     // move camera back
    // }

    // if (glfwGetKey(_TartarusWindow, GLFW_KEY_A) == GLFW_PRESS) {
    //     gameHandler::MoveCamera(view::CAMERA_MOVEMENT::kMoveLeft, delta_time);
    //     // move camera left
    // }

    // if (glfwGetKey(_TartarusWindow, GLFW_KEY_D) == GLFW_PRESS) {
    //     gameHandler::MoveCamera(view::CAMERA_MOVEMENT::kMoveRight, delta_time);
    //     // move camera right
    // }
}

void GetGLFWError(int error_code, const char* description){
    LOG(FATAL, "Error code: %d - %s", error_code, description);
}

void FramebufferSizeCallback(GLFWwindow* window, int width, int height){
    global::g_WindowManager->_height =
        global::g_WindowManager->_TartarusWindow._height = height;
    global::g_WindowManager->_width =
        global::g_WindowManager->_TartarusWindow._width = width;
    
    global::g_WindowManager->needResizeViewport = true;
}

void MouseCallback(GLFWwindow* window, double xposIn, double yposIn){
    global::g_WindowManager->_inputManager.UpdateMouseCallback(float(xposIn), float(yposIn));
    // float xpos = static_cast<float>(xposIn);
    // float ypos = static_cast<float>(yposIn);
    
    // if(!g_mouse_registered){
    //     g_window_manager._lastXPos = xpos;
    //     g_window_manager._lastYPos = ypos;
    //     g_mouse_registered = true;
    // }

    // float xOffset = xpos - g_window_manager._lastXPos;
    // float yOffset = g_window_manager._lastYPos - ypos;

    // g_window_manager._lastXPos = xpos;
    // g_window_manager._lastYPos = ypos;

    // // update the camera with the new xOffset, yOffset
    // gameHandler::updateCamera(xOffset, yOffset);
}

void MouseScrollBack(GLFWwindow* window, double xOffset, double yOffset){
    global::g_WindowManager->_inputManager.UpdateMouseScrollback(float(xOffset), float(yOffset));
}

void KeyCallback(GLFWwindow* window, int key, int scanCode, int action, int mods){
    global::g_WindowManager->_inputManager.UpdateKeyboardInput(key, scanCode, action, mods);
}

}