#include "Common/Logging.h"
#include "glad/glad.h"
#include "API/OpenGL/GLTextureManager.h"

namespace tartarus {

bool GLTextureManager::Init(){
    _textures2D.reserve(10);
    for(auto& iter : _attachemntState)
        iter = nullptr;
    return true;
}

bool GLTextureManager::Exit(){
    for(auto& iter : _textures2D){
        iter.second.Exit();
    }
    _textures2D.clear();

    return true;
}

void GLTextureManager::LoadScene(LoaderManager* loader){
    _loader = loader;

    for(uint index=0; index<(uint)AssetName::kCount; index++){
        auto* ref = GenerateTexture((AssetName)index);
        ref->SetTextureMetadata(_loader->LoadImage((AssetName)index), 
            GL_TEXTURE_2D, GL_UNSIGNED_BYTE);
        ref->LoadImage();
    }

    _loader->ClearImages();

    // GenerateTexture(AssetName::kFloor_0)->SetTextureMetadata(
    //     _loader->LoadImage(AssetName::kFloor_0), 
    //         GL_TEXTURE_2D, GL_UNSIGNED_BYTE);

    // GenerateTexture(AssetName::kWall_0)->SetTextureMetadata(
    //     _loader->LoadImage(AssetName::kLowWall_0), 
    //         GL_TEXTURE_2D, GL_UNSIGNED_BYTE);
    
    // GenerateTexture(AssetName::kLowWall_0)->SetTextureMetadata(
    //     _loader->LoadImage(AssetName::kLowWall_0),
    //         GL_TEXTURE_2D, GL_UNSIGNED_BYTE);

    // GenerateTexture(AssetName::kBarrel_0)->SetTextureMetadata(
    //     _loader->LoadImage(AssetName::kBarrel_0) ,
    //         GL_TEXTURE_2D, GL_UNSIGNED_BYTE);
    
    // GenerateTexture(AssetName::kBarrelSpecular_0)->SetTextureMetadata(
    //     _loader->LoadImage(AssetName::kBarrelSpecular_0), 
    //         GL_TEXTURE_2D, GL_UNSIGNED_BYTE);
}

GLTexture2D* GLTextureManager::GenerateTexture(AssetName id){
    CHECK(_textures2D.find(id) == _textures2D.end());
    auto iter = _textures2D.emplace(id, GLTexture2D());
    iter.first->second.Init(id, this);

    return &iter.first->second;
}

GLTexture2D* GLTextureManager::GetTexture(AssetName id){
    CHECK(_textures2D.find(id) != _textures2D.end())
    return &_textures2D[id];
}

uint GLTextureManager::ConfirmAttachment(GLTexture2D* tex){
    uint index = 0;
    uint id = tex->_textureId;
    for(; index<std::size(_attachemntState); index++){
        if(_attachemntState[index] == tex)
            return index;
    }
    index = 0;
    for(; index<std::size(_attachemntState); index++){
        if(_attachemntState[index] == nullptr){
            _attachemntState[index] = tex;
            tex->used = true;
            return index;
        }
    }

    index = 0;
    for(; index<std::size(_attachemntState); index++){
        if(!_attachemntState[index]->used){
            _attachemntState[index] = tex;
            tex->used = true;
            return index;
        }
    }

    // TODO: handle the case where the attach buffer is full, 16 for now
    // opengl can handle up to 32 or more?
    return -1;
}

}