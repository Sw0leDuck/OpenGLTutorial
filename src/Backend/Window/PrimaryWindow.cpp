#include "Common/Logging.h"
#include "Backend/Window/PrimaryWindow.h"


namespace tartarus::glfw {

bool Window::Init(uint height, uint width, const char* label) {
    _height = height;
    _width = width;

    _window = glfwCreateWindow(_width, _height, label, NULL, NULL);


    if (!_window) {
        glfwTerminate();
        return false;
    }

    glfwMakeContextCurrent(_window);
    glfwSwapInterval(1); // TODO: Implement some kind of scheduler that handles the render/update
    glfwSetInputMode(_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    return true;
}

bool Window::Exit(){
    glfwTerminate();
    return true;
}

void Window::EndFrameWork(){
    glfwSwapBuffers(_window);
    glfwPollEvents();
}

// void BeginFrame(float delta_time){
//     g_window_manager.ProcessInput(delta_time);
// }

// void EndFrame(){
//     g_window_manager.SwapBuffers();
//     g_window_manager.PollEvents();
// }
} // namespace window