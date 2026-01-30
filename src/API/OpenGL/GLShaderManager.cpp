#include "Common/Logging.h"
#include "glad/glad.h"
#include "API/OpenGL/GLShaderManager.h"
#include "fstream"
namespace tartarus {

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

bool CheckCompilerStatus(uint shaderId);
bool CheckLinkStatus(uint programId);

bool GLShaderManager::Init() {
    return true;
}

bool GLShaderManager::Exit() {
    for(auto& iter : _shaders){
        glDeleteShader(iter._vertexShaderId);
        glDeleteShader(iter._fragmentShaderId);
        glDeleteProgram(iter._programId);
        iter._manager = nullptr;
    }
    _shaders.clear();
    return true;
}

Shader& GLShaderManager::CompileShader(const char* vert, const char* frag){
    auto& iter = _shaders.emplace_back();
    iter._manager = nullptr;

    {
        iter._vertexShaderId = glCreateShader(GL_VERTEX_SHADER);
        auto source = _loader.LoadGLSLsource(vert);
        if(source.empty()){
            glDeleteShader(iter._vertexShaderId);
            iter.valid = false;
            LOG(INFO, "Vertex Shader could not be compiled");
            return iter;
        }
        auto src = source.c_str();
        glShaderSource(iter._vertexShaderId, 1, &src, nullptr);
        
        glCompileShader(iter._vertexShaderId);
        if(!CheckCompilerStatus(iter._vertexShaderId)){
            glDeleteShader(iter._vertexShaderId);
            iter.valid = false;
            return iter;
        }

    }

    {
        iter._fragmentShaderId = glCreateShader(GL_FRAGMENT_SHADER);
        auto source = _loader.LoadGLSLsource(frag);
        if(source.empty()){
            glDeleteShader(iter._vertexShaderId);
            glDeleteShader(iter._fragmentShaderId);
            iter.valid = false;
            LOG(INFO, "Vertex Shader could not be compiled");
        }
        auto src = source.c_str();
        glShaderSource(iter._fragmentShaderId, 1, &src, nullptr);
        
        glCompileShader(iter._fragmentShaderId);
        if(!CheckCompilerStatus(iter._fragmentShaderId)){
            glDeleteShader(iter._vertexShaderId);
            glDeleteShader(iter._fragmentShaderId);
            iter.valid = false;
            return iter;
        }
    }

    {
        iter._programId = glCreateProgram();

        glAttachShader(iter._programId, iter._vertexShaderId);
        glAttachShader(iter._programId, iter._fragmentShaderId);

        glLinkProgram(iter._programId);

        if(!CheckLinkStatus(iter._programId)){
            glDeleteShader(iter._vertexShaderId);
            glDeleteShader(iter._fragmentShaderId);
            glDeleteProgram(iter._programId);
            iter.valid = false;
            return iter;
        }
    }

    iter._manager = this;
    iter.valid = true;
    return iter;
}



bool CheckCompilerStatus(uint shaderId){
    int32_t success;
    char infoLog[512];
    glGetShaderiv(shaderId, GL_COMPILE_STATUS, &success);
    if(success == GL_FALSE){
        glGetShaderInfoLog(shaderId, 512, nullptr, infoLog);
        LOG(ERROR, "ShaderId: %d failed with error %s\n", shaderId, infoLog);
        return false;
    }
    return true;
}

bool CheckLinkStatus(uint programId){
    int32_t success;
    char infoLog[512];
    glGetProgramiv(programId, GL_LINK_STATUS, &success);
    if(success == GL_FALSE){
        glGetProgramInfoLog(programId, 512, nullptr, infoLog);
        LOG(ERROR,"ProgramId: %d failed with error %s\n", programId, infoLog);
        return false;
    }
    return true;
}


} // namespace tartarus