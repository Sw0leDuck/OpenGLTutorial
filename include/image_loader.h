#ifndef IMAGE_LOADER_H
#define IMAGE_LOADER_H
#include "common/types.h"
#include <string>
#include <map>

namespace imageLoader {

    struct image {
        ubyte* _data;
        int _width;
        int _height;
        int _nrChannels;

        bool LoadImage(const std::string& filePath);
        void UnloadImage();
    };

    struct ImageLoaderManager {
        ImageLoaderManager();

        void InsertImage(const std::string& filePath, uint imageId);
        void DeleteImage(uint imageId);
        std::map<uint, image> _imageMap;
    };

} // namespace imageLoader

#endif