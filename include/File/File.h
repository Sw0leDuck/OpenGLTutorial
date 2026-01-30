#ifndef FILE_H
#define FILE_H
#include "Common/Types.h"
#include "vector"

// contains all the operations done to load files from disk such as
// jpg, png, assimp etc etc?

namespace tartarus {

struct RawImage {
    enum Type {
        kInvalid = 0,
        kJpg = 1,
        kPNG = 2
    };

    ubyte* _data;
    int _width;
    int _height;
    int _nrChannels;
    Type _type;

    bool operator==(const RawImage& other){
        return this->_height == other._height &&
                this->_width == other._width &&
                this->_nrChannels == other._nrChannels &&
                this->_type == other._type &&
                this->_data == other._data;
    }
    
    bool LoadImage(const char* filePath, Type type);
    void UnloadImage();
};


struct LoaderManager {
    bool Init();
    bool Exit();

    RawImage& LoadImage(const char* filePath, RawImage::Type _type);
    void DeleteImage(RawImage& ref);

    std::vector<RawImage> _rawImages;
};

}

#endif