#include "glad/glad.h"
#include "Core/Shader.h"

namespace tartarus {

void Shader::UseProgam(){
    glUseProgram(_programId);
}

void Shader::Reset() {
    glUseProgram(0);
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