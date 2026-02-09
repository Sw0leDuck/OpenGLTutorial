#include "Core/Objects/Light.h"
#include "Common/LightEnums.h"

namespace tartarus {

bool PointLight::Init() {
    return true;
}

bool PointLight::Exit() {
    return true;
}

void PointLight::SetIndex(uint val){
    _index = val;
}

void PointLight::AttachShader(Shader* ptr){
    _attachedShader = ptr;
}

void PointLight::SetAttenuation(uint index){
    _constant = light_attenuations[index][0];
    _linear = light_attenuations[index][1];
    _quadratic = light_attenuations[index][2];
    _update = true;
}

void PointLight::Draw(float delta){
    for(auto& iter : _textures)
        iter->BindTexture();
    _shader->UseProgam();
    _meshBuffer->Draw();
    _shader->Reset();
}

void PointLight::Update(float val){
    Shader::UniformValue x;
    char buffer[32];

    x._floatPtr = glm::value_ptr(_worldPosition._matrix);
    _shader->AddUniform("modelMatrix",
        {Shader::UniformType::kMatrix, x});

    x._floatPtr = glm::value_ptr((_viewMatrix._matrix));
    _shader->AddUniform("viewMatrix",
        {Shader::UniformType::kMatrix, x});

    x._floatPtr = glm::value_ptr((_projectionMatrix._matrix));
    _shader->AddUniform("projectionMatrix", 
        {Shader::UniformType::kMatrix, x});

    x._floatPtr = glm::value_ptr((_inverseModel._matrix));
    _shader->AddUniform("modelInverseTransposeMatrix",
        {Shader::UniformType::kMatrix, x});

    x._f3Value = {1, 1, 1};
    _shader->AddUniform("lightColor", {Shader::UniformType::kFloat3, x});

    if(!_update)
        return;

    x._f3Value = {_worldPosition._matrix[3].x, 
        _worldPosition._matrix[3].y,
        _worldPosition._matrix[3].z}; 
    snprintf(buffer, sizeof(buffer),
        "pointLight[%d].position", _index);
    _attachedShader->AddUniform(buffer, 
        {Shader::UniformType::kFloat3, x});

    x._f3Value = _lightProperties._ambient;
    snprintf(buffer, sizeof(buffer), 
        "pointLight[%d].ambient", _index);
    _attachedShader->AddUniform(buffer, 
        {Shader::UniformType::kFloat3, x});

    x._f3Value = _lightProperties._diffuse;
    snprintf(buffer, sizeof(buffer), 
        "pointLight[%d].diffuse", _index);
    _attachedShader->AddUniform(buffer, 
        {Shader::UniformType::kFloat3, x});

    x._f3Value = _lightProperties._specular;
    snprintf(buffer, sizeof(buffer), 
        "pointLight[%d].specular", _index);
    _attachedShader->AddUniform(buffer, 
        {Shader::UniformType::kFloat3, x});


    x._floatValue = _constant;
    snprintf(buffer, sizeof(buffer), 
        "pointLight[%d].constant", _index);
    _attachedShader->AddUniform(buffer, 
        {Shader::UniformType::kFloat, x});

    x._floatValue = _linear;
    snprintf(buffer, sizeof(buffer), 
        "pointLight[%d].linear", _index);
    _attachedShader->AddUniform(buffer, 
        {Shader::UniformType::kFloat, x});

    x._floatValue = _quadratic;
    snprintf(buffer, sizeof(buffer), 
        "pointLight[%d].quadratic", _index);
    _attachedShader->AddUniform(buffer, 
        {Shader::UniformType::kFloat, x});

    _update = false;
}

void PointLight::SetPosition(Matrix value){
    _update = true;
    _worldPosition = value;
}

void PointLight::SetConstant(float value){
    _update = true;
    _constant = value;
}

void PointLight::SetLinear(float value){
    _update = true;
    _linear = value;
}

void PointLight::SetQuadratic(float value){
    _update = true;
    _quadratic = value;
}

void PointLight::SetAmbient(vec3 value){
    _update = true;
    _lightProperties._ambient = value;
}

void PointLight::SetDiffuse(vec3 value){
    _update = true;
    _lightProperties._diffuse = value;
}

void PointLight::SetSpecular(vec3 value){
    _update = true;
    _lightProperties._specular = value;
}


}