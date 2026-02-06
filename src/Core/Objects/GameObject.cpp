#include "Core/Objects/GameObject.h"

namespace tartarus {

void GameObject::SetWorldPosition(Matrix matrix){
    _worldPosition = matrix;
    _inverseModel = glm::transpose(_worldPosition._matrix);
}

void GameObject::TranslateWorldPosition(glm::vec3 vec3){
    _worldPosition.Translate(vec3);
    _inverseModel = glm::transpose(_worldPosition._matrix);
}

void GameObject::RotateWorldPosition(float degree, glm::vec3 vec3){
    _worldPosition.Rotate(degree, vec3);
    _inverseModel = glm::transpose(_worldPosition._matrix);
}

void GameObject::ScaleWorldPosition(glm::vec3 vec3){
    _worldPosition.Scale(vec3);
    _inverseModel = glm::transpose(_worldPosition._matrix);
}

}