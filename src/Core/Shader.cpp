#include "API/OpenGL/GLUtil.h"
#include "Core/Shader.h"

namespace tartarus {

void Shader::UseProgam(){
    GL_CHECK_CALL(glUseProgram(_programId))
    UpdateUniforms();
}

void Shader::Reset() {
    GL_CHECK_CALL(glUseProgram(0))
}

void Shader::InitUniformName(const char* name){
    UniformValue x;
    _uniforms[name] = {UniformType::kNotUsed, x};
    // _uniforms.emplace(name, std::make_pair<UniformType::kInt, x>);
}

void Shader::AddUniform(const char* name, 
        std::pair<UniformType, UniformValue> value){
    CHECK(_uniforms.find(name) != _uniforms.end());
    _uniforms[name] = value;
}

void Shader::RemoveUniform(const char* name){
    CHECK(_uniforms.find(name) != _uniforms.end());
    UniformValue x;    
    _uniforms[name] = {UniformType::kNotUsed, x};
}

void Shader::UpdateUniforms(){
    for(auto& iter : _uniforms) {
        switch(iter.second.first){
            case UniformType::kInt:
                SetInt(iter.first.cbegin(), iter.second.second._intValue);
                break;
            case UniformType::kFloat:
                SetFloat(iter.first.cbegin(), iter.second.second._floatValue);
                break;
            case UniformType::kFloat3:
                SetFloat3(iter.first.cbegin(), iter.second.second._f3Value);
                break;
            case UniformType::kMatrix:
                SetMatrix(iter.first.cbegin(), iter.second.second._floatPtr);
                break;
            case UniformType::kSampled2D:
                SetInt(iter.first.cbegin(), iter.second.second._intValue);
                break;
            case UniformType::kNotUsed:
                break;
        }
    }
}

void Shader::SetInt(const char* name, uint value){
    uint uniformLocation;
    GL_CHECK_SET_CALL(uniformLocation, glGetUniformLocation(_programId, name))
    GL_CHECK_CALL(glUniform1i(uniformLocation,value))
}

void Shader::SetFloat(const char* name, float value){
    uint uniformLocation;
    GL_CHECK_SET_CALL(uniformLocation, glGetUniformLocation(_programId, name))
    GL_CHECK_CALL(glUniform1f(uniformLocation, value))
}

void Shader::SetFloat3(const char* name, float x1, float x2, float x3){
    uint uniformLocation;
    GL_CHECK_SET_CALL(uniformLocation, glGetUniformLocation(_programId, name))
    GL_CHECK_CALL(glUniform3f(uniformLocation, x1, x2, x3))
}

void Shader::SetFloat3(const char* name, vec3 value){
    uint uniformLocation;
    GL_CHECK_SET_CALL(uniformLocation, glGetUniformLocation(_programId, name))
    GL_CHECK_CALL(glUniform3f(uniformLocation, value.x, value.y, value.z))
}

void Shader::SetMatrix(const char* name, float* matrix){
    uint uniformLocation;
    GL_CHECK_SET_CALL(uniformLocation, glGetUniformLocation(_programId, name))
    GL_CHECK_CALL(glUniformMatrix4fv(uniformLocation, 1, GL_FALSE, matrix))
}

}