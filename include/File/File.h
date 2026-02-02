#ifndef FILE_H
#define FILE_H
#include "Common/Types.h"
#include "Common/Enums.h"
#include "unordered_map"

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
    
    bool LoadImage(const char* filePath);
    void UnloadImage();
};


struct LoaderManager {
    bool Init();
    bool Exit();

    RawImage* LoadImage(AssetName id);
    void DeleteImage(AssetName id);

    void ClearImages();

    std::unordered_map<AssetName, RawImage> _rawImages;
};

}

#endif