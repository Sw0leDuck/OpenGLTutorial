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
    void EnableDepthTest();

    GLMeshBuffer* GetMeshBuffer(BufferName id) {
        return _bufferManager->GetCreateMeshBuffer(id);
    }

    GLTexture2D* GetTexture(AssetName id) {
        return _textureManager->GetTexture(id);
    }

    Shader* GetShader(ShaderName id){
        return _shaderManager->GetShader(id);
    }

    std::unique_ptr<GLShaderManager> _shaderManager;
    std::unique_ptr<GLBufferManager> _bufferManager;
    std::unique_ptr<GLTextureManager> _textureManager;
};

} // namespace tartarus::gl

#endif