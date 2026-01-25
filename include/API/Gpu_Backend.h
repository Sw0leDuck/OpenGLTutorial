#ifndef GPU_BACKEND_H
#define GPU_BACKEND_H
#include <stdlib.h>
#include "Common/types.h"
#include "API/ShaderManager.h"
#include <memory>

namespace tartarus {

// Is this even worth it?
// Will definetly need rewrite when implementing vulkan, in 5 years from now ...
struct Gpu {
    virtual bool Init() { abort(); }
    virtual bool Exit() { abort(); }
    virtual bool IsValid() { return false; }
    
    virtual void ClearScreen() { abort(); }
    virtual void UpdateViewPort(uint, uint) { abort(); }

    virtual void CreateShader(uint, uint&) { abort(); }
    virtual void DeleteShader(uint) { abort(); }
    virtual void ShaderSource(uint, uint, const char*, void*) { abort(); };
    virtual void CompileShader(uint) { abort(); }
    virtual void GetShaderIv(uint, uint, uint*) { abort(); }
    virtual void GetShaderInfoLog(uint, uint, void*, char*) { abort(); }

    std::unique_ptr<ShaderManager> _shaderManager;
};

}

#endif