#include "API/OpenGL/GLUtil.h"
#include "API/OpenGL/GLBackend.h"
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

    this->EnableDepthTest();
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
    GL_MAKE_CALL(glClearColor(0.2, 0.4, 0.6, 1.0))
    GL_MAKE_CALL(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT))
}

void OpenGL::UpdateViewPort(uint width, uint height){
    GL_MAKE_CALL(glViewport(0, 0, width, height))
}

void OpenGL::EnableDepthTest(){
    GL_MAKE_CALL(glEnable(GL_DEPTH_TEST))
}

} // backend::gl