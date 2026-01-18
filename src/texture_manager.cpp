#include "texture_manager.h"

namespace texture::manager {

bool TextureManager::Init(){
    return true;
}

bool TextureManager::Exit(){
    for(auto& iter : _textures2D)
        iter.second.Exit();
    return true;
}

std::pair<uint, uint> TextureManager::Load2DTexture(const char *filePath, uint type){
    graphic::Texture2D tex;
    tex.Init(filePath, type);
    tex.LoadTexture(false);
    _textures2D.emplace(tex._textureId, std::move(tex));
    return {tex._textureId, GL_TEXTURE_2D};
}



} // namespace texture::manager