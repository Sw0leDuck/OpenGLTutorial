#ifndef GL_TEXTURE_MANAGER_H
#define GL_TEXTURE_MANAGER_H
#include "API/OpenGL/GLTexture.h"
#include "Common/Enums.h"
#include "unordered_map"

namespace tartarus {

struct OpenGL;

struct GLTextureManager {
    bool Init();
    bool Exit();

    // Update: based on the current scene, load the appropiate textures and 
    // maybe delete what is not needed?
    // For now, it will act as a SetLoader and load the only present scene 
    void LoadScene(LoaderManager* loader);

    GLTexture2D* GenerateTexture(AssetName);
    GLTexture2D* GetTexture(AssetName);

    uint ConfirmAttachment(GLTexture2D*);

    // TextureId, Texture Object
    std::unordered_map<AssetName, GLTexture2D> _textures2D;
    LoaderManager* _loader;
    GLTexture2D* _attachemntState[16];
};

}

#endif