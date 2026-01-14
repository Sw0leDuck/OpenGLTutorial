#include "matrix.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace graphic {

    Matrix& Matrix::rotate(float degree, glm::vec3 vec3){
        matrix = glm::rotate(matrix, glm::radians(degree), vec3);
        return *this;
    }

    Matrix& Matrix::fast_rotate(float time, glm::vec3 vec3){
        matrix = glm::rotate(matrix, time * glm::radians(45.f), vec3);
        return *this;
    }

    Matrix& Matrix::scale(glm::vec3 vec3){
        matrix = glm::scale(matrix, vec3);
        return *this;
    }

    Matrix& Matrix::translate(glm::vec3 vec3){
        matrix = glm::translate(matrix, vec3);
        return *this;
    }

    Matrix& Matrix::perspective(float fov, float aspect, float near, float far){
        matrix = glm::perspective(glm::radians(fov), aspect, near, far);
        return *this;
    }
}