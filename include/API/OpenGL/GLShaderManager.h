#ifndef GL_SHADER_MANAGER_H
#define GL_SHADER_MANAGER_H
#include "string"
#include "Core/Shader.h"
#include "Common/Enums.h"
#include "unordered_map"

namespace tartarus {

struct ShaderLoader {
    std::string LoadGLSLsource(const char* filePath);
};

struct GLShaderManager {
    bool Init();
    bool Exit();
    void CompileShader(ShaderName id, const char* vert, const char* frag);
    Shader* GetShader(ShaderName id);
    
    std::unordered_map<ShaderName, Shader> _shaders;
    ShaderLoader _loader;
};

}

#endif