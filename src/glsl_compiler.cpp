#include "glsl_compiler.h"
#include <glad/glad.h>
#include "common/error_handler.h"

#include <fstream>
#include <iostream>

namespace compiler {

Context g_context;

bool Init(){
    return true;
}

bool Exit(){
    return g_context.Exit();
}

bool CompileShader(const char* filePath, uint shaderType, uint id){
    return g_context.CompileShader(filePath, shaderType, id);
}

bool LinkProgram(uint id, uint vertexId, uint fragmentId){
    return g_context.LinkProgram(id, vertexId, fragmentId);
}

bool DeleteShaders(){
    for(auto& iter : g_context._vertexShaderId)
        glDeleteShader(iter.second);

    for(auto& iter : g_context._fragmentShaderId)
        glDeleteShader(iter.second);
    return true;
}

Program* GetProgram(uint id){
    return &g_context._programId[id];
}

Context::~Context() { }

bool Context::Exit(){
    for(auto& iter : _vertexShaderId)
        glDeleteShader(iter.second);
    
    for(auto& iter : _fragmentShaderId)
        glDeleteShader(iter.second);

    for(auto& iter : _programId)
        glDeleteProgram(iter.second.id);
    return true;
} 

std::string LoadGLSLsource(const char* filePath) {
    std::string source{};
    std::ifstream inFile{filePath};

    if(!inFile){
        std::cerr << "File " << filePath << " not found\n";
        return source;
    }

    std::string line{};
    while (std::getline(inFile, line)){
        line += '\n';
        source.operator+=(line);
    }

    return source;
}

bool Context::CompileShader(const char* filePath, uint shaderType, uint id) {
    switch(shaderType){
        case GL_VERTEX_SHADER:
            if(_vertexShaderId.find(id) != _vertexShaderId.end())
                return true;
            break;
        case GL_FRAGMENT_SHADER:
            if(_fragmentShaderId.find(id) != _fragmentShaderId.end())
                return true;
            break;
        default:
            errorHandler::UpdateError("Got invalid shaderType in CompileShader");
            return false;
    }
    
    uint shaderId;
    shaderId = glCreateShader(shaderType);
    glCheckError();

    std::string source = LoadGLSLsource(filePath);
    if(source.empty()){
        glDeleteShader(shaderId);
        return false;
    }

    {
        auto str = source.c_str();
        glShaderSource(shaderId, 1, &str, nullptr);
    }

    glCompileShader(shaderId);
    glCheckError();

    if(!CheckCompilerStatus(shaderId, id)){
        glDeleteShader(shaderId);
        return false;
    }

    switch(shaderType){
        case GL_VERTEX_SHADER:
            _vertexShaderId[id] = shaderId;
            break;
        case GL_FRAGMENT_SHADER:
            _fragmentShaderId[id] = shaderId;
            break;
    }
    return true;
}

bool CheckCompilerStatus(uint shaderId, uint id){
    int32_t success;
    char infoLog[512];
    glGetShaderiv(shaderId, GL_COMPILE_STATUS, &success);
    if(success == GL_FALSE){
        glGetShaderInfoLog(shaderId, 512, nullptr, infoLog);
        std::cerr << "ShaderId: " << id << " failed with error\n\t"
            << infoLog << std::endl;
        return false;
    }
    return true;
}

bool Context::LinkProgram(uint id, uint vertexId, uint fragmentId){
    uint programId;
    programId = glCreateProgram();

    glAttachShader(programId, _vertexShaderId[vertexId]);
    glCheckError();
    glAttachShader(programId, _fragmentShaderId[fragmentId]);
    glCheckError();
    glLinkProgram(programId);

    if(!CheckLinkStatus(programId, id)){
        glDeleteProgram(programId);
        return false;
    }

    _programId.emplace(id, Program(programId));

    // glDeleteShader(_vertexShaderId[vertexId]);
    // _vertexShaderId.erase(vertexId);
    // glDeleteShader(_fragmentShaderId[fragmentId]);
    // _fragmentShaderId.erase(fragmentId);
    return true;
}

bool CheckLinkStatus(uint programId, uint id){
    int32_t success;
    char infoLog[512];
    glGetProgramiv(programId, GL_LINK_STATUS, &success);
    if(success == GL_FALSE){
        glGetProgramInfoLog(programId, 512, nullptr, infoLog);
        std::cerr << "ProgramId: " << id << " failed with error\n\t"
            << infoLog << std::endl;
        return false;
    }
    return true;
}

void Context::SetInt(const char* name, uint id, uint value){
    _programId[id].SetInt(name, value);
}

void Context::SetFloat(const char* name, uint id, float value){
    _programId[id].SetFloat(name, value);
}

void Context::SetMatrix(const char* name, uint id, float* matrix){
    _programId[id].SetMatrix(name, matrix);
}

Program::Program(uint id) : id(id) {}

void Program::SetInt(const char* name, uint value){
    glUniform1i(glGetUniformLocation(id, name), value);
}

void Program::SetFloat(const char* name, float value){
    glUniform1f(glGetUniformLocation(id, name), value);
}

void Program::SetFloat3(const char* name, float x1, float x2, float x3){
    glUniform3f(glGetUniformLocation(id, name), x1, x2, x3);
}

void Program::SetFloat3(const char* name, glm::vec3 value){
    glUniform3f(glGetUniformLocation(id, name), value.x, value.y, value.z);
}

void Program::SetMatrix(const char* name, float* matrix){
    glUniformMatrix4fv(glGetUniformLocation(id, name), 1, GL_FALSE, matrix);
}

void Program::UseProgram(){
    glUseProgram(id);
}

} // namespace compiler