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
    _shader->UseProgam();
    _meshBuffer->Draw();
    _shader->Reset();
}

void Static3D::Update(float){

}

}