#include "Common/Logging.h"
#include "API/OpenGL/GLBackend.h"
#include "API/OpenGL/GLShaderManager.h"
#include "API/OpenGL/GLBufferManager.h"
#include "glad/glad.h"
#include "GLFW/glfw3.h"

namespace tartarus {

bool OpenGL::Init(){
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        return false;
    }

    _shaderManager = std::make_unique<GLShaderManager>();
    if(!_shaderManager->Init())
        return false;

    _bufferManager = std::make_unique<GLBufferManager>();
    if(!_bufferManager->Init())
        return false;

    _textureManager = std::make_unique<GLTextureManager>();
    if(!_textureManager->Init())
        return false;

    glEnable(GL_DEPTH_TEST);
    return true;
}

bool OpenGL::Exit(){
    if(!_shaderManager->Exit())
        return false;
    _shaderManager.reset();

    if(!_bufferManager->Exit())
        return false;
    _bufferManager.reset();

    if(!_textureManager->Exit())
        return false;
    _textureManager.reset();

    return true;
}


void OpenGL::ClearScreen(){
    glClearColor(0.2, 0.4, 0.6, 1.0);
}

void OpenGL::UpdateViewPort(uint width, uint height){
    glViewport(0, 0, width, height);
}

} // backend::gl