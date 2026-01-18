#ifndef TEXTURE_H
#define TEXTURE_H
#include <string>
#include "common/types.h"

namespace graphic {

#define GL_TEXTURE_2D 0x0DE1 // TODO: change this

    struct Texture2D {
        float _triangleCoords[3];
        float _rectangleCoords[4];

        void Init(const std::string& filePath, uint type);
        void Exit();
        void BindTexture();
        void LoadTexture(bool clamp);

        uint _textureId = -1;
        uint _type;
    };

    struct Texture3D {
        Texture3D() {};
        uint _textureId = -1;
    };

} // namespace texture

#endif