#include "Common/Logging.h"
#include "glad/glad.h"
#include "fstream"
#include "Managers/ShaderManager.h"

namespace tartarus {

bool ShaderManager::Init(Gpu* gpuPtr) {
    _gpuPtr = gpuPtr;
    return true;
}

Shader& ShaderManager::compileShader(const char* vert, const char* frag){
    auto& iter = _shaders.emplace_back();

    _gpuPtr->CreateShader(GL_VERTEX_SHADER, iter._vertexShaderId);
    _gpuPtr->CreateShader(GL_FRAGMENT_SHADER, iter._fragmentShaderId);
    
    
    std::string vertSource = _loader.LoadGLSLsource(vert);
    std::string fragSource = _loader.LoadGLSLsource(frag);

    if(fragSource.empty() || vertSource.empty()){
        _gpuPtr->DeleteShader(iter._vertexShaderId);
        _gpuPtr->DeleteShader(iter._fragmentShaderId);
        iter.valid = false;
    }

    



    return iter;
}

std::string ShaderLoader::LoadGLSLsource(const char* filePath) {
    std::string source{};
    std::ifstream inFile{filePath};

    if(!inFile){
        LOG(ERROR, "File %s not found", filePath);
        return source;
    }

    std::string line{};
    while (std::getline(inFile, line)){
        line += '\n';
        source.operator+=(line);
    }

    return source;
}


} // namespace tartarus