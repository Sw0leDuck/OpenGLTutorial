#ifndef TEXTURE_H
#define TEXTURE_H
#include "glad/glad.h"
#include <string>
#include "common/types.h"

namespace graphic {

    struct texture2D {
        float triangleCoords[3];
        float rectangleCoords[4];

        ~texture2D();

        void init(const std::string& filePath, GLenum type);
        inline void bindTexture() { glBindTexture(GL_TEXTURE_2D, textureId); };
        void loadTexture(bool clamp);

        uint textureId = -1;
        GLenum type;
    };

} // namespace texture

#endif