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
        Matrix& rotate(float degree, glm::vec3 vec3);
        Matrix& fast_rotate(float degree, glm::vec3 vec3);
        Matrix& scale(glm::vec3 vec3);
        Matrix& translate(glm::vec3 vec3);
        Matrix& perspective(float fov, float aspect, float near, float far);

        inline void reset() { matrix = glm::mat4(1.0f); };

        MatrixType type;
        glm::mat4 matrix;
    };

    

} // namespace graphic

#endif