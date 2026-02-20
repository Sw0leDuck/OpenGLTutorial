#include "Core/Objects/FlatGridMap.h"

namespace tartarus {

bool FlatGridMap::Init(){
    _instanceCount = 0;
    _material._ambient = {0.1, 0.1, 0.1};
    _material._shininess = 32.0f;
    return true;
}

bool FlatGridMap::Exit(){
    return true;
}

void FlatGridMap::Update(float){
    Shader::UniformValue x;

    x._f3Value = _cameraPosition;
    _shader->AddUniform("viewPos", 
        {Shader::UniformType::kFloat3, x});

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

    x._f3Value = _material._ambient;
    _shader->AddUniform("material.ambient", 
        {Shader::UniformType::kFloat3, x});

    x._floatValue = _material._shininess;
    _shader->AddUniform("material.shininess", 
        {Shader::UniformType::kFloat, x});

    for(uint index=0; index<_textures.size(); index++){
        x._intValue = _textures[index]->ConfirmAttachment();
        _shader->AddUniform(_uniformNames[index], 
            {Shader::UniformType::kInt, x});
    }
}

void FlatGridMap::Draw(float){
    for(auto& iter : _textures)
        iter->BindTexture();
    _shader->UseProgam();
    _meshBuffer->DrawInstanced(_instanceCount);
    _shader->Reset();
}

    
}