#ifndef GL_SHADER_MANAGER_H
#define GL_SHADER_MANAGER_H
#include "API/ShaderManager.h"

namespace tartarus {

struct GLShaderManager : ShaderManager {
    bool Init() override;
    Shader& compileShader(const char* vert, const char* frag) override;

    std::vector<Shader> _shaders;
};

}

#endif