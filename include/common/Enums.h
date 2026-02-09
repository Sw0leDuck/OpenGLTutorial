#ifndef ENUMS_H
#define ENUMS_H

namespace tartarus {

enum class BufferName : unsigned int {
    kRectangleColor = 0,
    kRectangleTexture = 1,
    kRectangleTextureNorm = 2,
    kTriangleColor = 3,
    kTriangleTexture = 4,
    kTriangleTextureNorm = 5
};

const char* GetBufferName(BufferName id);

enum class ShaderName : unsigned int {
    kDefault = 0,
    kPointLight = 1,
};

const char* GetShaderName(ShaderName id);

enum class AssetName : unsigned int {
    kFloor_0 = 0,
    kWall_0 = 1,
    kLowWall_0 = 2,
    kBlood_0 = 3,
    kBarrel_0 = 4,
    kBarrelSpecular_0 = 5,
    kMonster_0 = 6,
    kCount = kMonster_0+1
};

const char* GetAssetPathName(AssetName id);

}

#endif