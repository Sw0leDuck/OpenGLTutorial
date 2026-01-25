#ifndef GL_BACKEND_H
#define GL_BACKEND_H
#include "API/Gpu_Backend.h"


namespace tartarus {

struct OpenGL : Gpu {
    bool Init() override;
    bool Exit() override;
    bool IsValid() override { return true; }

    void ClearScreen() override;
    void UpdateViewPort(uint, uint) override;
    
    void CreateShader(uint, uint&) override;
    void DeleteShader(uint) override;
    void ShaderSource(uint, uint, const char*, void*) override;
    void CompileShader(uint) override;
    void GetShaderIv(uint, uint, uint*) override;
    void GetShaderInfoLog(uint, uint, void*, char*) override;
};

} // namespace tartarus::gl

#endif