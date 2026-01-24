#include "Backend/Window/PrimaryWindow.h"


namespace tartarus::glfw {

bool Window::Init(uint height, uint width, const char* label) {
    _height = height;
    _width = width;

    if (!glfwInit()){
        return false;
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    _window = glfwCreateWindow(_width, _height, label, NULL, NULL);

    if (!_window) {
        glfwTerminate();
        return false;
    }

    glfwMakeContextCurrent(_window);
    glfwSwapInterval(1);
    glfwSetInputMode(_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    return true;
}

bool Window::Exit(){
    glfwTerminate();
    return true;
}

// void BeginFrame(float delta_time){
//     g_window_manager.ProcessInput(delta_time);
// }

// void EndFrame(){
//     g_window_manager.SwapBuffers();
//     g_window_manager.PollEvents();
// }
} // namespace window