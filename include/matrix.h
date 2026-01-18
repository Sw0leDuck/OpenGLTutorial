#ifndef MATRIX_H
#define MATRIX_H
#include <glm/gtc/type_ptr.hpp>
#include "common/types.h"

namespace graphic {

    enum MatrixType : byte{
        kIdentity = 0,
        kTransalte = 1,
        kScale = 2,
        kLast = kScale
    };

    struct Matrix {
        Matrix();

        Matrix& Rotate(float degree, glm::vec3 vec3);
        Matrix& FastRotate(float degree, glm::vec3 vec3);
        Matrix& Scale(glm::vec3 vec3);
        Matrix& Translate(glm::vec3 vec3);
        Matrix& Perspective(float fov, float aspect, float near, float far);

        inline void Reset() { _matrix = glm::mat4(1.0f); };

        MatrixType _type;
        glm::mat4 _matrix;
    };

    

} // namespace graphic

#endif