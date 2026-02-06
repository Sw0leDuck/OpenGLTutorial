#include "Core/Objects/Static3D.h"

namespace tartarus {

bool Static3D::Init(){
    _type = Type::kStatic;
    _meshBuffer = nullptr;
    _shader = nullptr;
    _material._ambient = {0.2125, 0.1275, 0.054};
    _material._shininess = 16.0f;
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

void Static3D::SetMeshBuffer(GLMeshBuffer* meshBuffer) {
    if(_meshBuffer)
        _meshBuffer->_used = false;
    _meshBuffer = meshBuffer;
    _meshBuffer->_used = true;
}

void Static3D::Update(float){
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

}