#ifndef GL_TEXTURE_H
#define GL_TEXTURE_H
#include "File/File.h"

namespace tartarus {

struct GLTexture2D {
    struct TextureArgs {
        uint _target;
        RawImage _imageData;
        uint _type;
    };
    
    bool Init(uint);
    bool Exit();

    void BindTexture();
    void UnbindTexture();
    void SetTextureMetadata(RawImage data, uint, uint);
    void LoadImage();

    TextureArgs _texArgs;
    uint _textureId;
    
};

}

#endif