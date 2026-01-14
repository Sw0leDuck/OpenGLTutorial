#include "image_loader.h"
#include <iostream>
#define STB_IMAGE_IMPLEMENTATION
#include "stb/stb_image.h"

namespace imageLoader {

bool image::loadImage(const std::string& filePath){
    data = stbi_load(filePath.c_str(), &width, &height, &nrChannels, 0);
    if(!data)
        return false;
    return true;
}

void image::unloadImage(){
    stbi_image_free(data);
}

ImageLoaderManager::ImageLoaderManager(){
    stbi_set_flip_vertically_on_load(true);
}

void ImageLoaderManager::insertImage(const std::string& filePath, uint imageId){
    if(image_map.find(imageId) != image_map.end()){
        std::cerr << "ImageID already exists in image_map " << imageId << std::endl;
        std::cerr << "Image File Name " << filePath.c_str() << std::endl;
        return;
    }
    if(!image_map[imageId].loadImage(filePath)){
        std::cerr << "FilePath of image not found\n";
        return;
    }
}

void ImageLoaderManager::deleteImage(uint imageId){
    if(image_map.find(imageId) == image_map.end()){
        std::cerr << "Trying to delete an image that does not exist\n";
        return;
    }
    image_map[imageId].unloadImage();
    image_map.erase(imageId);
}

} // namespace imageLoader