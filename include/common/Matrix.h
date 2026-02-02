#ifndef MATRIX_H
#define MATRIX_H
#include "glm/gtc/type_ptr.hpp"


namespace tartarus {

struct Matrix;

Matrix CreateWorldPositionMatrix(float, float, float);

struct Matrix {
    Matrix() {}
    Matrix(glm::mat4 matrix) : _matrix(matrix) {}

    Matrix& Rotate(float degree, glm::vec3 vec3);
    Matrix& FastRotate(float degree, glm::vec3 vec3);
    Matrix& Scale(glm::vec3 vec3);
    Matrix& Translate(glm::vec3 vec3);
    Matrix& Perspective(float fov, float aspect, float near, float far);

    inline void Reset() { _matrix = glm::mat4(1.0f); };

    glm::mat4 _matrix;
};

}

#endif