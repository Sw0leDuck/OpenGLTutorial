#include "glad/glad.h"
#include "Backend/Window/glfw_window.h"
#include "common/error_handler.h"
#include "Core/game_handler.h"


namespace backend::glfw {

uint currentRasterizeMode = GL_FILL;
WindowManager g_window_manager;
bool g_mouse_registered = false;

bool InitializeGLFW(){
    return g_window_manager.Init("Sw0LeDuck");
}

bool PostInitGameHandler(){
    gameHandler::updateScreenSize(g_window_manager._width, g_window_manager._height);
    return true;
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

void BeginFrame(float delta_time){
    g_window_manager.ProcessInput(delta_time);
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
    glfwSetScrollCallback(_window, MouseScrollBack);
    glfwSetKeyCallback(_window, KeyCallback);

    return true;
}

bool WindowManager::Exit(){
    glfwTerminate();
    return true;
}

void WindowManager::ProcessInput(float delta_time) {
    if (glfwGetKey(_window, GLFW_KEY_W) == GLFW_PRESS) {
        gameHandler::MoveCamera(view::CAMERA_MOVEMENT::kMoveForward, delta_time);
        // move camera front
    }

    if (glfwGetKey(_window, GLFW_KEY_S) == GLFW_PRESS) {
        gameHandler::MoveCamera(view::CAMERA_MOVEMENT::kMoveBackward, delta_time);
        // move camera back
    }

    if (glfwGetKey(_window, GLFW_KEY_A) == GLFW_PRESS) {
        gameHandler::MoveCamera(view::CAMERA_MOVEMENT::kMoveLeft, delta_time);
        // move camera left
    }

    if (glfwGetKey(_window, GLFW_KEY_D) == GLFW_PRESS) {
        gameHandler::MoveCamera(view::CAMERA_MOVEMENT::kMoveRight, delta_time);
        // move camera right
    }
}

void FramebufferSizeCallback(GLFWwindow* window, int width, int height){
    g_window_manager._height = height;
    g_window_manager._width = width;
    glViewport(0, 0, width, height);
    gameHandler::updateScreenSize(width, height);
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
    gameHandler::updateCamera(xOffset, yOffset);
}

void MouseScrollBack(GLFWwindow* window, double xOffset, double yOffset){
    gameHandler::updateCameraZoom(float(yOffset));
}

void KeyCallback(GLFWwindow* window, int key, int scanCode, int action, int mods){
    if (key == GLFW_KEY_M && action == GLFW_PRESS) {
        if(currentRasterizeMode == GL_FILL){
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
            currentRasterizeMode = GL_LINE;
        }else if(currentRasterizeMode == GL_LINE){
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
            currentRasterizeMode = GL_FILL;
        }
        // move camera right
    }

    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
}

} // namespace window