#ifndef IMAGE_LOADER_H
#define IMAGE_LOADER_H
#include "common/types.h"
#include <string>
#include <map>

namespace imageLoader {

    struct image {
        ubyte* data;
        int width;
        int height;
        int nrChannels;

        bool loadImage(const std::string& filePath);
        void unloadImage();
    };

    struct ImageLoaderManager {
        ImageLoaderManager();

        void insertImage(const std::string& filePath, uint imageId);
        void deleteImage(uint imageId);
        std::map<uint, image> image_map;
    };

} // namespace imageLoader

#endif