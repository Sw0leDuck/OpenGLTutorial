#ifndef SHADER_MANAGER_H
#define SHADER_MANAGER_H
#include "Core/Shader.h"
#include <string>
#include <vector>

namespace tartarus {

struct ShaderLoader {
    std::string LoadGLSLsource(const char* filePath);
};

struct ShaderManager {
    virtual bool Init();


    virtual Shader& compileShader(const char* vert, const char* frag);

    ShaderLoader _loader;
};

} // namespace tartarus

#endif
