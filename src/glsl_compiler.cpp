#include "glsl_compiler.h"
#include <glad/glad.h>

#include <fstream>
#include <iostream>

namespace compiler {

Context::~Context(){
    for(auto& iter : _ShaderId)
        glDeleteShader(iter.second);

    for(auto& iter : _programId)
        glDeleteProgram(iter.second.id);
}

std::string loadGLSLsource(std::string filePath) {
    std::string source{};
    std::ifstream inFile{filePath};

    if(!inFile){
        std::cerr << "File " << filePath.c_str() << " not found\n";
        return source;
    }

    std::string line{};
    while (std::getline(inFile, line)){
        line += '\n';
        source.operator+=(line);
    }

    return source;
}

bool Context::compileShader(std::string filePath, uint shaderType, uint id) {
    uint shaderId;
    shaderId = glCreateShader(shaderType);

    std::string source = loadGLSLsource(filePath);
    if(source.empty()){
        glDeleteShader(shaderId);
        return false;
    }

    {
        auto str = source.c_str();
        glShaderSource(shaderId, 1, &str, nullptr);
    }

    glCompileShader(shaderId);

    if(!checkCompilerStatus(shaderId, id)){
        glDeleteShader(shaderId);
        return false;
    }

    _ShaderId[id] = shaderId;
    return true;
}

bool checkCompilerStatus(uint shaderId, uint id){
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

bool Context::linkProgram(uint id, uint vertexId, uint fragmentId){
    uint programId;
    programId = glCreateProgram();

    glAttachShader(programId, _ShaderId[vertexId]);
    glAttachShader(programId, _ShaderId[fragmentId]);
    glLinkProgram(programId);

    if(!checkLinkStatus(programId, id)){
        glDeleteProgram(programId);
        return false;
    }

    _programId[id] = Program(programId);

    glDeleteShader(_ShaderId[vertexId]);
    _ShaderId.erase(vertexId);
    glDeleteShader(_ShaderId[fragmentId]);
    _ShaderId.erase(fragmentId);
    return true;
}

bool checkLinkStatus(uint programId, uint id){
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

void Context::setInt(const std::string& name, uint id, uint value){
    _programId[id].setInt(name, value);
}

void Context::setFloat(const std::string& name, uint id, float value){
    _programId[id].setFloat(name, value);
}

void Context::setMatrix(const std::string& name, uint id, float* matrix){
    _programId[id].setMatrix(name, matrix);
}

Program::Program(uint id) : id(id) {}

void Program::setInt(const std::string& name, uint value){
    glUniform1i(glGetUniformLocation(id, name.c_str()), value);
}

void Program::setFloat(const std::string& name, float value){
    glUniform1f(glGetUniformLocation(id, name.c_str()), value);
}

void Program::setMatrix(const std::string& name, float* matrix){
    glUniformMatrix4fv(glGetUniformLocation(id, name.c_str()), 1, GL_FALSE, matrix);
}

} // namespace compiler