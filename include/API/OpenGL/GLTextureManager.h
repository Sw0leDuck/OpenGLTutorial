#ifndef GL_TEXTURE_MANAGER_H
#define GL_TEXTURE_MANAGER_H
#include "API/OpenGL/GLTexture.h"
#include "map"

namespace tartarus {

struct GLTextureManager {
    bool Init();
    bool Exit();

    GLTexture2D* GenerateTexture();
    GLTexture2D* GetTexture(uint);

    // TextureId, Texture Object
    std::map<uint, GLTexture2D> _textures2D;
};

}

#endif