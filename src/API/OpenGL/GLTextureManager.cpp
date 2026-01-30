#include "Common/Logging.h"
#include "glad/glad.h"
#include "API/OpenGL/GLTextureManager.h"

namespace tartarus {

bool GLTextureManager::Init(){
    return true;
}

bool GLTextureManager::Exit(){
    std::vector<uint> textureId;
    for(auto& iter : _textures2D){
        textureId.emplace_back(iter.first);
        iter.second.Exit();
    }

    if(textureId.size())
        glDeleteTextures(textureId.size(), textureId.data());

    _textures2D.clear();
    textureId.clear();
    return true;
}

GLTexture2D* GLTextureManager::GenerateTexture(){
    uint textureId = -1;
    glGenTextures(1, &textureId);

    _textures2D[textureId] = GLTexture2D();
    _textures2D[textureId].Init(textureId);

    return &_textures2D[textureId];
}

GLTexture2D* GLTextureManager::GetTexture(uint textureId){
    CHECK(_textures2D.find(textureId) == _textures2D.end())
    return &_textures2D[textureId];
}

}