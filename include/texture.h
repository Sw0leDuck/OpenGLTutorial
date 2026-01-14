#ifndef TEXTURE_H
#define TEXTURE_H
#include "glad/glad.h"
#include <string>
#include "common/types.h"

namespace graphic {

    struct Texture2D {
        float triangleCoords[3];
        float rectangleCoords[4];

        void init(const std::string& filePath, GLenum type);
        void exit();
        inline void bindTexture() { glBindTexture(GL_TEXTURE_2D, textureId); };
        void loadTexture(bool clamp);

        uint textureId = -1;
        GLenum type;
    };

    struct Texture3D {
        Texture3D() {};
        uint textureId = -1;
    };

} // namespace texture

#endif