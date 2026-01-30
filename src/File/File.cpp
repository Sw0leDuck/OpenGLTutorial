#define STB_IMAGE_IMPLEMENTATION
#include "File/File.h"
#include "stb/stb_image.h"

#include <algorithm> // Eeew 😱, TODO: remove this and make a std::find algorithm

namespace tartarus {

bool RawImage::LoadImage(const char* filePath, RawImage::Type type){

    _data = stbi_load(filePath, &_width, &_height, &_nrChannels, 0);
    if(!_data){
        _type = kInvalid;
        return false;
    }
    _type = type;
    return true;
}

void RawImage::UnloadImage(){
    stbi_image_free(_data);
}


bool LoaderManager::Init(){
    stbi_set_flip_vertically_on_load(true);
    return true;
}

bool LoaderManager::Exit(){
    for(auto& iter : _rawImages)
        iter.UnloadImage();
    _rawImages.clear();

    return true;
}

RawImage& LoaderManager::LoadImage(const char* filePath, RawImage::Type _type){
    auto& iter = _rawImages.emplace_back();
    iter.LoadImage(filePath, _type);
    return iter;
}

void LoaderManager::DeleteImage(RawImage& ref){
    auto iter = std::find(_rawImages.begin(), _rawImages.end(), ref);
    if(iter == _rawImages.end())
        return;
    iter->UnloadImage();
    _rawImages.erase(iter);
}



}