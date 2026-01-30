#ifndef GL_SHADER_MANAGER_H
#define GL_SHADER_MANAGER_H
#include "Common/Types.h"
#include "string"
#include "Core/Shader.h"
#include "vector"

namespace tartarus {

struct ShaderLoader {
    std::string LoadGLSLsource(const char* filePath);
};

struct GLShaderManager {
    bool Init();
    bool Exit();
    Shader& CompileShader(const char* vert, const char* frag);
    
    std::vector<Shader> _shaders;
    ShaderLoader _loader;
};

}

#endif