#include "API/OpenGL_Backend.h"
#include "glad/glad.h"
#include "GLFW/glfw3.h"

namespace tartarus {

bool OpenGL::Init(){
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        return false;
    }
    glEnable(GL_DEPTH_TEST);
    return true;
}

bool OpenGL::Exit(){
    return true;
}


void OpenGL::ClearScreen(){
    glClearColor(0.2, 0.4, 0.6, 1.0);
}

void OpenGL::UpdateViewPort(uint height, uint width){
    glViewport(0, 0, width, height);
}


} // backend::gl