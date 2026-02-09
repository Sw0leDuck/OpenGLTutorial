#include "Core/Objects/Light.h"


namespace tartarus {

bool DirectLight::Init(){
    return true;
}

bool DirectLight::Exit(){
    return true;
}

void DirectLight::AttachShader(Shader* ptr){
    _shaderPtr = ptr;
}

void DirectLight::Update(float delta){
    Shader::UniformValue x;

    if(!_update)
        return;

    x._f3Value = _direction; 
    _shaderPtr->AddUniform("dirLight.direction", 
        {Shader::UniformType::kFloat3, x});

    x._f3Value = _lightProperties._ambient;
    _shaderPtr->AddUniform("dirLight.ambient", 
        {Shader::UniformType::kFloat3, x});

    x._f3Value = _lightProperties._diffuse;
    _shaderPtr->AddUniform("dirLight.diffuse", 
        {Shader::UniformType::kFloat3, x});

    x._f3Value = _lightProperties._specular;
    _shaderPtr->AddUniform("dirLight.specular", 
        {Shader::UniformType::kFloat3, x});

    _update = false;
}

void DirectLight::SetDirection(vec3 val){
    _update = true;
    _direction = val;
}

void DirectLight::SetAmbient(vec3 val){
    _update = true;
    _lightProperties._ambient = val;
}

void DirectLight::SetDiffuse(vec3 val){
    _update = true;
    _lightProperties._diffuse = val;
}

void DirectLight::SetSpecular(vec3 val){
    _update = true;
    _lightProperties._specular = val;
}

}