#include "Common/Logging.h"
#include "glad/glad.h"
#include "Core/Shader.h"

namespace tartarus {

void Shader::UseProgam(){
    glUseProgram(_programId);
    UpdateUniforms();
}

void Shader::Reset() {
    glUseProgram(0);
}

void Shader::AddUniform(const char* name, 
        std::pair<UniformType, UniformValue> value){
    CHECK(_uniforms.find(name) != _uniforms.end());
    _uniforms[name] = value;
}

void Shader::UpdateUniforms(){
    for(auto& iter : _uniforms) {
        switch(iter.second.first){
            case UniformType::kInt:
                SetInt(iter.first, iter.second.second._intValue);
                break;
            case UniformType::kFloat:
                SetFloat(iter.first, iter.second.second._floatValue);
                break;
            case UniformType::kFloat3:
                SetFloat3(iter.first, iter.second.second._f3Value);
                break;
            case UniformType::kMatrix:
                SetMatrix(iter.first, iter.second.second._floatPtr);
                break;
            case UniformType::kSampled2D:
                SetInt(iter.first, iter.second.second._intValue);
                break;
        }
    }
}

void Shader::SetInt(const char* name, uint value){
    glUniform1i(glGetUniformLocation(_programId, name), value);
}

void Shader::SetFloat(const char* name, float value){
    glUniform1f(glGetUniformLocation(_programId, name), value);
}

void Shader::SetFloat3(const char* name, float x1, float x2, float x3){
    glUniform3f(glGetUniformLocation(_programId, name), x1, x2, x3);
}

void Shader::SetFloat3(const char* name, vec3 value){
    glUniform3f(glGetUniformLocation(_programId, name), value.x, value.y, value.z);
}

void Shader::SetMatrix(const char* name, float* matrix){
    glUniformMatrix4fv(glGetUniformLocation(_programId, name), 1, GL_FALSE, matrix);
}

}