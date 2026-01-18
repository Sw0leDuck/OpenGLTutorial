#include "image_loader.h"
#include <iostream>
#define STB_IMAGE_IMPLEMENTATION
#include "stb/stb_image.h"

namespace imageLoader {

bool image::LoadImage(const std::string& filePath){
    _data = stbi_load(filePath.c_str(), &_width, &_height, &_nrChannels, 0);
    if(!_data)
        return false;
    return true;
}

void image::UnloadImage(){
    stbi_image_free(_data);
}

ImageLoaderManager::ImageLoaderManager(){
    stbi_set_flip_vertically_on_load(true);
}

void ImageLoaderManager::InsertImage(const std::string& filePath, uint imageId){
    if(_imageMap.find(imageId) != _imageMap.end()){
        std::cerr << "ImageID already exists in image_map " << imageId << std::endl;
        std::cerr << "Image File Name " << filePath.c_str() << std::endl;
        return;
    }
    if(!_imageMap[imageId].LoadImage(filePath)){
        std::cerr << "FilePath of image not found\n";
        return;
    }
}

void ImageLoaderManager::DeleteImage(uint imageId){
    if(_imageMap.find(imageId) == _imageMap.end()){
        std::cerr << "Trying to delete an image that does not exist\n";
        return;
    }
    _imageMap[imageId].UnloadImage();
    _imageMap.erase(imageId);
}

} // namespace imageLoader