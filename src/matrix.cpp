#include "matrix.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace graphic {

    Matrix::Matrix() {
        _matrix = glm::mat4(1.0f);
    }

    Matrix& Matrix::Rotate(float degree, glm::vec3 vec3){
        _matrix = glm::rotate(_matrix, glm::radians(degree), vec3);
        return *this;
    }

    Matrix& Matrix::FastRotate(float time, glm::vec3 vec3){
        _matrix = glm::rotate(_matrix, time * glm::radians(45.f), vec3);
        return *this;
    }

    Matrix& Matrix::Scale(glm::vec3 vec3){
        _matrix = glm::scale(_matrix, vec3);
        return *this;
    }

    Matrix& Matrix::Translate(glm::vec3 vec3){
        _matrix = glm::translate(_matrix, vec3);
        return *this;
    }

    Matrix& Matrix::Perspective(float fov, float aspect, float near, float far){
        _matrix = glm::perspective(glm::radians(fov), aspect, near, far);
        return *this;
    }
}