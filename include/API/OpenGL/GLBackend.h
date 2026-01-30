#ifndef GL_BACKEND_H
#define GL_BACKEND_H
#include "API/OpenGL/GLShaderManager.h"
#include "API/OpenGL/GLBufferManager.h"
#include "API/OpenGL/GLTextureManager.h"
#include <memory>

namespace tartarus {

struct OpenGL {
    bool Init();
    bool Exit();
    bool IsValid() { return true; }

    void ClearScreen();
    void UpdateViewPort(uint, uint);

    inline Shader& CompileShader(const char* vert, const char* frag) { return _shaderManager->CompileShader(vert, frag); }
    inline GLBuffer* GetNextBuffer(GLBuffer::BufferType type) { return _bufferManager->GetNextBuffer(type); }

    std::unique_ptr<GLShaderManager> _shaderManager;
    std::unique_ptr<GLBufferManager> _bufferManager;
    std::unique_ptr<GLTextureManager> _textureManager;
};

} // namespace tartarus::gl

#endif