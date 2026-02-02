#define STB_IMAGE_IMPLEMENTATION
#include "stb/stb_image.h"
#include "Common/Logging.h"
#include "File/File.h"

namespace tartarus {

bool RawImage::LoadImage(const char* filePath){
    _data = stbi_load(filePath, &_width, &_height, &_nrChannels, 0);
    if(!_data){
        _type = kInvalid;
        return false;
    }

    _type = RawImage::Type::kPNG;

    if(_nrChannels == 4)
        _type = RawImage::Type::kPNG;
    else if(_nrChannels == 3)
        _type = RawImage::Type::kJpg;

    return true;
}

void RawImage::UnloadImage(){
    stbi_image_free(_data);
}

bool LoaderManager::Init(){
    _rawImages.reserve(10);
    stbi_set_flip_vertically_on_load(true);
    return true;
}

bool LoaderManager::Exit(){
    ClearImages();
    return true;
}

RawImage* LoaderManager::LoadImage(AssetName id){
    CHECK(_rawImages.find(id) == _rawImages.end());
    auto iter = _rawImages.emplace(id, RawImage());
    iter.first->second.LoadImage(GetAssetPathName(id));
    return &iter.first->second;
}

void LoaderManager::DeleteImage(AssetName id){
    if(_rawImages.find(id) != _rawImages.end()){
        _rawImages[id].UnloadImage();
        _rawImages.erase(id);
    }
}

void LoaderManager::ClearImages(){
    for(auto& iter : _rawImages){
        iter.second.UnloadImage();
    }
    _rawImages.clear();
}


}