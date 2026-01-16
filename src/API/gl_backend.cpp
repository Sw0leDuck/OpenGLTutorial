#include "API/gl_backend.h"
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "common/error_handler.h"

namespace backend::gl {
    bool InitializeGL() {
        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
            errorHandler::UpdateError("Failed to initialize GLAD\n");
            return false;
        }
        glEnable(GL_DEPTH_TEST);
        return true;
    }

    void ClearScreen(){
        glClearColor(0.2f, 0.3f, 0.4f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }
} // backend::gl