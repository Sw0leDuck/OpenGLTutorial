#ifndef GL_TEXTURE_H
#define GL_TEXTURE_H
#include "File/File.h"
#include "Common/Enums.h"

namespace tartarus {

struct GLTextureManager;

struct GLTexture2D {
    struct TextureArgs {
        uint _target;
        RawImage* _imageData;
        uint _format;
    };
    
    bool Init(AssetName, GLTextureManager*);
    bool Exit();

    void BindTexture();
    void UnbindTexture();
    void SetTextureMetadata(RawImage* data, uint);
    void LoadImage();

    uint ConfirmAttachment();

    uint _textureId;
    bool used = false;
    uint _attachIndex;
    uint _height;
    uint _width;
    uint _nrChannels;
    TextureArgs _texArgs;
    AssetName _assetName;
    GLTextureManager* _manager;
};

}

#endif