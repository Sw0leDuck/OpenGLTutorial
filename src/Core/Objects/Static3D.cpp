#include "Core/Objects/Static3D.h"

namespace tartarus {

bool Static3D::Init(){
    _type = Type::kStatic;
    return true;
}

bool Static3D::Exit(){
    _meshBuffer = nullptr;
    _shader = nullptr;
    return true;
}

void Static3D::Draw(float){
    for(auto& iter : _textures)
        iter->BindTexture();
    _shader->UseProgam();
    _meshBuffer->Draw();
    _shader->Reset();
}

void Static3D::Update(float){
    Shader::UniformValue x;

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

    for(auto& iter : _textures){
        uint attachId = iter->ConfirmAttachment();
    }
}

}