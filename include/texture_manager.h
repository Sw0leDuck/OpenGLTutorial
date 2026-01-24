#ifndef TEXTURE_MANAGER_H
#define TEXTURE_MANAGER_H

#include <map>
#include "texture.h"

namespace tartarus {

    struct TextureManager {
        bool Init();
        bool Exit();

        std::pair<uint, uint> Load2DTexture(const char *filePath, uint type);

        std::map<uint, graphic::Texture2D> _textures2D;
        std::map<uint, graphic::Texture3D> _textures3D;
    };
}

#endif